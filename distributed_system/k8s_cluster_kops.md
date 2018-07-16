- [Instance Groups](#instance-groups)
  - [Change the instance type in an instance group](#change-the-instance-type-in-an-instance-group)
  - [Resize an instance group](resize-an-instance-group)

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

(you do not need a rolling-update when changing instancegroup sizes)

