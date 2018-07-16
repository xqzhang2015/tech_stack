- [Instance Groups](#instance-groups)
  - [Change the instance type in an instance group](#change-the-instance-type-in-an-instance-group)


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
