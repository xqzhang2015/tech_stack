<!-- MarkdownTOC -->

- [cluster-autoscaler](#cluster-autoscaler)
  - [AWS IAM policy](#aws-iam-policy)
  - [Deployment: k8s cluster cert](#deployment-k8s-cluster-cert)
  - [expander](#expander)
  - [scale down](#scale-down)
    - [autoscaler args](#autoscaler-args)
    - [trigger condition](#trigger-condition)
  - [What are the key best practices for running Cluster Autoscaler?](#what-are-the-key-best-practices-for-running-cluster-autoscaler)
  - [FAQ](#faq)
    - [How can I monitor Cluster Autoscaler?](#how-can-i-monitor-cluster-autoscaler)
    - [How can I scale a node group to 0?](#how-can-i-scale-a-node-group-to-0)
    - [How can I prevent Cluster Autoscaler from scaling down a particular node?](#how-can-i-prevent-cluster-autoscaler-from-scaling-down-a-particular-node)
    - [How fast is Cluster Autoscaler?](#how-fast-is-cluster-autoscaler)
- [HPA vs CA](#hpa-vs-ca)
  - [How does Horizontal Pod Autoscaler work with Cluster Autoscaler?](#how-does-horizontal-pod-autoscaler-work-with-cluster-autoscaler)
  - [How fast is HPA when combined with CA?](#how-fast-is-hpa-when-combined-with-ca)
- [References](#references)

<!-- /MarkdownTOC -->


# cluster-autoscaler

https://github.com/kubernetes/autoscaler

## AWS IAM policy

```json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "autoscaling:DescribeAutoScalingGroups",
                "autoscaling:DescribeAutoScalingInstances",
                "autoscaling:DescribeTags",
                "autoscaling:DescribeLaunchConfigurations",
                "autoscaling:SetDesiredCapacity",
                "autoscaling:TerminateInstanceInAutoScalingGroup",
                "ec2:DescribeLaunchTemplateVersions"
            ],
            "Resource": "*"
        }
    ]
}
```

## Deployment: k8s cluster cert

* Deployment: `certs`

Note: hostPath may be different.

```
            command:
              - ./cluster-autoscaler
              - --v=4
              - --stderrthreshold=info
              - --cloud-provider=aws
              - --skip-nodes-with-local-storage=false
              - --expander=least-waste
              - --node-group-auto-discovery=asg:tag=k8s.io/cluster-autoscaler/enabled,k8s.io/cluster-autoscaler/xxx.aws.yyy.net
            env:
              - name: AWS_REGION
                value: us-east-1
            volumeMounts:
              - name: ssl-certs
                mountPath: /etc/ssl/certs/ca-certificates.crt
                readOnly: true
            imagePullPolicy: "Always"
        volumes:
          - name: ssl-certs
            hostPath:
              path: "/etc/ssl/certs/ca-bundle.crt"
```

And we need to add `tolerations` and `nodeAffinity/nodeSelector` if necessary, so as to schedule to desired nodes.


## expander

There are a few ways how the Cluster Autoscaler will react and which instance group it will pick up for scaling.

* random - selects the instance group randomly
* most-pods - selects the instance group that will schedule the most amount of pods.
* least-waste - selects the instance group that will waste the least amount of CPU/Memory resources
* price - selects the instance group based on price


## scale down
### [autoscaler args](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/main.go)

* --scan-interval duration

```
	--scan-interval duration How often cluster is reevaluated for scale up or down (default 10 seconds)
```

* --scale-down-unneeded-time duration

```
      --scale-down-unneeded-time duration                                  How long a node should be unneeded before it is eligible for scale down (default 10m0s)
      --scale-down-unready-time duration                                   How long an unready node should be unneeded before it is eligible for scale down (default 20m0s)
      --scale-down-utilization-threshold float                             Node utilization level, defined as sum of requested resources divided by capacity, below which a node can be considered for scale down (default 0.5)
```


### trigger condition

A node is considered for `removal` or `unneeded` when all below conditions hold:

* The sum of cpu and memory requests of all pods running on this node is smaller than 50% of the node's allocatable. (Before 1.1.0, node capacity was used instead of allocatable.) Utilization threshold can be configured using `--scale-down-utilization-threshold` flag.

* All pods running on the node (except these that run on all nodes by default, like manifest-run pods or pods created by daemonsets) can be moved to other nodes. See [What types of pods can prevent CA from removing a node?](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/FAQ.md#what-types-of-pods-can-prevent-ca-from-removing-a-node) section for more details on what pods don't fulfill this condition, even if there is space for them elsewhere. While checking this condition, the new locations of all moved pods are memorized. With that, Cluster Autoscaler knows where each pod can be moved, and which nodes depend on which other nodes in terms of pod migration. Of course, it may happen that eventually the scheduler will place the pods somewhere else.

* It doesn't have scale-down disabled annotation (see [How can I prevent Cluster Autoscaler from scaling down a particular node?](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/FAQ.md#how-can-i-prevent-cluster-autoscaler-from-scaling-down-a-particular-node))


## What are the key best practices for running Cluster Autoscaler?

* Do not modify the nodes belonging to autoscaled node groups directly. All nodes within the same node group should have the same capacity, labels and system pods running on them.
* Specify requests for your pods.
* Use PodDisruptionBudgets to prevent pods from being deleted too abruptly (if needed).
* Check if your cloud provider's quota is big enough before specifying min/max settings for your node pools.
* Do not run any additional node group autoscalers (especially those from your cloud provider).

## FAQ
### How can I monitor Cluster Autoscaler?

Cluster Autoscaler provides metrics and livenessProbe endpoints. By default they're available on port 8085 (configurable with `--address` flag), respectively under `/metrics` and `/health-check`.

Metrics are provided in Prometheus format and their detailed description is available [here](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/proposals/metrics.md).

### How can I scale a node group to 0?

For AWS, if you are using `nodeSelector`, you need to tag the ASG with a node-template key `"k8s.io/cluster-autoscaler/node-template/label/"`.

For example, for a node label of foo=bar, you would tag the ASG with:

```json
{
    "ResourceType": "auto-scaling-group",
    "ResourceId": "foo.example.com",
    "PropagateAtLaunch": true,
    "Value": "bar",
    "Key": "k8s.io/cluster-autoscaler/node-template/label/foo"
}
```
### How can I prevent Cluster Autoscaler from scaling down a particular node?

From CA 1.0, node will be excluded from scale-down if it has the annotation preventing scale-down:

```
"cluster-autoscaler.kubernetes.io/scale-down-disabled": "true"
```

### How fast is Cluster Autoscaler?
By default, scale-up is considered up to `10 seconds` after pod is marked as unschedulable, and scale-down `10 minutes` after a node becomes unneeded.


# HPA vs CA

* [kubernetes: Horizontal Pod Autoscaler](https://kubernetes.io/docs/tasks/run-application/horizontal-pod-autoscale/)
* [kubernetes: Horizontal Pod Autoscaler Walkthrough](https://kubernetes.io/docs/tasks/run-application/horizontal-pod-autoscale-walkthrough/)

## How does Horizontal Pod Autoscaler work with Cluster Autoscaler?

Horizontal Pod Autoscaler changes the deployment's or replicaset's number of replicas based on the current CPU load. If the load increases, HPA will create new replicas, for which there may or may not be enough space in the cluster.

If there are not enough resources, CA will try to bring up some nodes, so that the HPA-created pods have a place to run.

If the load decreases, HPA will stop some of the replicas. As a result, some nodes may become underutilized or completely empty, and then CA will delete such unneeded nodes.

## How fast is HPA when combined with CA?

When HPA is combined with CA, the total time from increased load to new pods running is determined by three major factors:

* HPA reaction time,
* CA reaction time,
* node provisioning time.


# References

[github.com/kubernetes: CA - How does scale-up work?](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/FAQ.md#how-does-scale-up-work)<br/>

[github.com/kubernetes: CA - How does scale-down work](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/FAQ.md#how-does-scale-down-work)<br/>

[github.com/kubernetes: CA - Frequently Asked Questions](https://github.com/kubernetes/autoscaler/blob/master/cluster-autoscaler/FAQ.md)<br/>

[]()<br/>

[]()<br/>
