<!-- MarkdownTOC -->

- [node affinity](#node-affinity)
  - [for node](#for-node)
  - [for pod](#for-pod)
- [Taints and Tolerations](#taints-and-tolerations)
  - [for node](#for-node-1)
  - [for pod](#for-pod-1)
- [References](#references)

<!-- /MarkdownTOC -->


# node affinity

Note: pod 选择哪个 node

## for node

* by kubectl

```sh
kubectl label nodes kubernetes-foo-node-1.c.a-robinson.internal node-role=etcd
```

* by kops

```yaml
apiVersion: kops/v1alpha2
kind: InstanceGroup
spec:
  nodeLabels:
    node-role: etcd
  ...
```

or

```sh
/usr/local/bin/kubelet ... --node-labels=node-role=etcd ...
```

## for pod

* pods/pod-with-node-affinity.yaml 

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: with-node-affinity
spec:
  affinity:
    nodeAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
        nodeSelectorTerms:
        - matchExpressions:
          - key: node-role
            operator: In
            values:
            - etcd
            - xxx
      preferredDuringSchedulingIgnoredDuringExecution:
      - weight: 1
        preference:
          matchExpressions:
          - key: another-node-label-key
            operator: In
            values:
            - another-node-label-value
  containers:
  - name: with-node-affinity
    image: k8s.gcr.io/pause:2.0
```

# Taints and Tolerations

Note: node 选择哪个 pod

## for node

* by kubectl

```sh
kubectl taint nodes node1 disktype=ssd:NoSchedule
```

* by kops

```yaml
apiVersion: kops/v1alpha2
kind: InstanceGroup
spec:
  ...
  taints:
  - disktype=ssd:NoSchedule
```

* by kubelet directly

```sh
/usr/local/bin/kubelet ... --register-with-taints=disktype=ssd:NoSchedule
```

## for pod

```yaml
tolerations:
- key: "key"
  operator: "Equal"
  value: "value"
  effect: "NoSchedule"
```
or

```yaml  
apiVersion: v1
kind: Pod
metadata:
  name: nginx
  labels:
    env: test
spec:
  containers:
  - name: nginx
    image: nginx
    imagePullPolicy: IfNotPresent
  tolerations:
  - key: "example-key"
    operator: "Exists"
    effect: "NoSchedule"
```

# References

[K8S Concepts: Assigning Pods to Nodes](https://kubernetes.io/docs/concepts/configuration/assign-pod-node/#node-affinity-beta-feature)<br>

[K8S Concepts: Taints and Tolerations](https://kubernetes.io/docs/concepts/configuration/taint-and-toleration/)<br>

[]()<br>



