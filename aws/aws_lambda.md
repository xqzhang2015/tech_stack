<!-- MarkdownTOC -->

- [How to associate instance group with a cname](#how-to-associate-instance-group-with-a-cname)
  - [Lambda => functions: updateroute53](#lambda--functions-updateroute53)

<!-- /MarkdownTOC -->

AWS related handles.

# How to associate instance group with a cname

### Lambda => functions: updateroute53
1. Add triggers: CloudWatch Events

Event pattern example:

```
{
  "detail-type": [
    "EC2 Instance Launch Successful",
    "EC2 Instance Terminate Successful",
    "EC2 Instance-launch Lifecycle Action",
    "EC2 Instance-terminate Lifecycle Action"
  ],
  "source": [
    "aws.autoscaling"
  ],
  "detail": {
    "AutoScalingGroupName": [
      "aaa.bbb.ccc"
    ]
  }
}
```

2. Handling event

```python
# lambda_function.py
import boto3
import time

def lambda_handler(event, context):
    print "event: ", event
    print "lambda_handler"
    iplist=get_iplist_in_ASG()
    issucceed = update_route53(iplist)
```