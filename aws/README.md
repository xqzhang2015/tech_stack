<!-- MarkdownTOC -->

- [AWS Concept](#aws-concept)
  - [Concepts comparison](#concepts-comparison)
  - [Security: Security groups and ACLs](#security-security-groups-and-acls)
  - [Controlling Which Auto Scaling Instances Terminate](#controlling-which-auto-scaling-instances-terminate)
- [AWS CLI](#aws-cli)
  - [aws ec2 describe-volumes](#aws-ec2-describe-volumes)
  - [aws ec2 delete-volume](#aws-ec2-delete-volume)
- [References](#references)

<!-- /MarkdownTOC -->



# AWS Concept
### Concepts comparison

| AWS | Traditional |
| :--- | :--- |
| VPC(Virtual Private Cloud)  | DC(Data Center) |
| ACL | subnet firewall  |
| Security group | single host firewall |


### Security: Security groups and ACLs
Amazon VPC provides features that you can use to increase and monitor the security for your VPC:

* Security groups — Act as a __firewall__ for associated Amazon __EC2 instances__, controlling both inbound and outbound traffic at the instance level
* Network access control lists (ACLs) — Act as a __firewall__ for associated __subnets__, controlling both inbound and outbound traffic at the subnet level
* Flow logs — Capture information about the IP traffic going to and from network interfaces in your VPC

![security-diagram](../images/2018/security-diagram.png)<br/>


### Controlling Which Auto Scaling Instances Terminate

https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-termination.html

https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-termination.html

# AWS CLI

### aws ec2 describe-volumes

* status - The status of the volume (creating | available | in-use | deleting | deleted | error ).

```
[ ~]$ aws ec2 describe-volumes --filters Name=status,Values=in-use,available,deleted --query 'Volumes[*].{ID:VolumeId, Status:State}'
```

output

```
[
    {
        "Status": "in-use",
        "ID": "vol-0899f757129ed827c"
    },
    {
        "Status": "in-use",
        "ID": "vol-07fa6b5f27710d17d"
    },
    {
        "Status": "available",
        "ID": "vol-0f343ce4d3ebdfc38"
    },
    {
        "Status": "in-use",
        "ID": "vol-061223ae9277fa73e"
    }
]
```

### aws ec2 delete-volume

```
[ec2-user@ip-10-206-29-116 cluster]$ aws ec2 delete-volume --volume-id vol-0f343ce4d3ebdfc38
```


# References
[VPC Security](https://docs.aws.amazon.com/AmazonVPC/latest/UserGuide/VPC_Security.html)<br/>


[]()<br/>


[]()<br/>


[]()<br/>


[]()<br/>


[]()<br/>
