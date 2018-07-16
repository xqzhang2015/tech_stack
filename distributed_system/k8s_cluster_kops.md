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

or modify yaml, then
```
kops replace -f xxx.yml
kops update cluster $CLUSTER_NAME --yes
kops rolling-update cluster --force --yes
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
** `rootVolumeType` must be one of supported volume types, e.g. `gp2` (default), `io1` (high performance) or `standard` (for testing).
** If `rootVolumeType` is set to `io1` then you can define the number of Iops by specifying `rootVolumeIops` (defaults to 100 if not defined)
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

