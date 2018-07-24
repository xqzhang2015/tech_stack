- [Instance Groups](#instance-groups)
  - [Change the instance type in an instance group](#change-the-instance-type-in-an-instance-group)
  - [Resize an instance group](resize-an-instance-group)
  - [Changing the root volume size or type](changing-the-root-volume-size-or-type)

# [Instance Groups](https://github.com/kubernetes/kops/blob/master/docs/instance_groups.md)
### Change the instance type in an instance group

First you edit the instance group spec, using 
```
kops edit ig nodes.
```

To preview the change:
```
kops update cluster <clustername>
```

Presuming you're happy with the change, go ahead and apply it: 
```
kops update cluster <clustername> --yes
```

See a preview with:
```
kops rolling-update cluster
```

Then restart the machines with:
```
kops rolling-update cluster --yes
```

or __modify yaml, then__
```
kops replace -f xxx.yml
kops update cluster $CLUSTER_NAME --yes
kops rolling-update cluster --fail-on-validate-error="false" --force --yes
```

* [XXX ~]$ kops rolling-update cluster --help

This command updates a kubernetes cluster to match the cloud and kops specifications.

```
Usage:
  kops rolling-update cluster [flags]
  
Examples:
  # Roll the k8s-cluster.example.com kops cluster,
  # only roll the node instancegroup,
  # use the new drain an validate functionality.
  kops rolling-update cluster k8s-cluster.example.com --yes \
  --fail-on-validate-error="false" \
  --node-interval 8m \
  --instance-group nodes

Flags:
      --bastion-interval duration    Time to wait between restarting bastions (default 5m0s)
      --cloudonly                    Perform rolling update without confirming progress with k8s
      --fail-on-drain-error          The rolling-update will fail if draining a node fails. (default true)
      --fail-on-validate-error       The rolling-update will fail if the cluster fails to validate. (default true)
      --force                        Force rolling update, even if no changes
      --instance-group stringSlice   List of instance groups to update (defaults to all if not specified)
      --master-interval duration     Time to wait between restarting masters (default 5m0s)
      --node-interval duration       Time to wait between restarting nodes (default 4m0s)
  -y, --yes                          Perform rolling update immediately, without --yes rolling-update executes a dry-run

Global Flags:
      --alsologtostderr                  log to standard error as well as files
      --config string                    config file (default is $HOME/.kops.yaml)
      --log_backtrace_at traceLocation   when logging hits line file:N, emit a stack trace (default :0)
      --log_dir string                   If non-empty, write log files in this directory
      --logtostderr                      log to standard error instead of files (default false)
      --name string                      Name of cluster
      --state string                     Location of state storage (default "s3://adsk8s.replay.ads.aws.fwmrm.net")
      --stderrthreshold severity         logs at or above this threshold go to stderr (default 2)
  -v, --v Level                          log level for V logs
      --vmodule moduleSpec               comma-separated list of pattern=N settings for file-filtered logging
```

### Resize an instance group
The procedure to resize an instance group works the same way:
* Edit the instance group, set minSize and maxSize to the desired size: `kops edit ig nodes`
* Preview changes: `kops update cluster <clustername>`
* Apply changes: `kops update cluster <clustername> --yes`

(__you do not need a rolling-update when changing instancegroup sizes__)

### Changing the root volume size or type

The default volume size for Masters is 64 GB, while the default volume size for a node is 128 GB.

The procedure to resize the root volume works the same way:

* Edit the instance group, set rootVolumeSize and/or rootVolumeType to the desired values: 
```
kops edit ig nodes
```
  * `rootVolumeType` must be one of supported volume types, e.g. `gp2` (default), `io1` (high performance) or `standard` (for testing).
  * If `rootVolumeType` is set to `io1` then you can define the number of Iops by specifying `rootVolumeIops` (defaults to 100 if not defined)
* Preview changes: `kops update cluster <clustername>`
* Apply changes: `kops update cluster <clustername> --yes`
* Rolling update to update existing instances: `kops rolling-update cluster --yes`

For example, to set up a 200GB gp2 root volume, your InstanceGroup spec might look like:
```
metadata:
  creationTimestamp: "2016-07-11T04:14:00Z"
  name: nodes
spec:
  machineType: t2.medium
  maxSize: 2
  minSize: 2
  role: Node
  rootVolumeSize: 200
  rootVolumeType: gp2
```

