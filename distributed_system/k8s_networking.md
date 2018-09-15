<!-- MarkdownTOC -->

- [Overview](#overview)
  - [Part-1 containers and pods](#part-1-containers-and-pods)
  - [Part-2 services: the abstraction layer that allows pods to be ephemeral](#part-2-services-the-abstraction-layer-that-allows-pods-to-be-ephemeral)
  - [Part-3 ingress: getting traffic to your pods from outside the cluster](#part-3-ingress-getting-traffic-to-your-pods-from-outside-the-cluster)
- [References](#references)

<!-- /MarkdownTOC -->

# Overview
Discussing the way things interact can get confusing: 

* pod networks, service networks, cluster IPs, 
* container ports, host ports, node ports

In order to keep things focused I’m going to split the post into three parts.

### Part-1 containers and pods

1. So what is a pod? 

`A pod consists of one or more containers that are collocated on the same host, and are configured to share a network stack and other resources such as volumes.`

2. What does “share a network stack” actually mean?

` In practical terms it means that all the containers in a pod can reach each other on localhost.`

3. The pod network

### Part-2 services: the abstraction layer that allows pods to be ephemeral

### Part-3 ingress: getting traffic to your pods from outside the cluster

# References

[Understanding kubernetes networking: pods](https://medium.com/google-cloud/understanding-kubernetes-networking-pods-7117dd28727)<br/>

[A high level overview of kubernetes](https://kubernetes.io/)<br/>

[An overview of pods specifically](https://kubernetes.io/docs/concepts/workloads/pods/pod/)<br/>

[k8s networking](https://www.digitalocean.com/community/tutorials/an-introduction-to-networking-terminology-interfaces-and-protocols)<br/>

[k8s IP address spaces](https://www.digitalocean.com/community/tutorials/understanding-ip-addresses-subnets-and-cidr-notation-for-networking)<br/>

[wikipedia.org: IP routing table](https://en.wikipedia.org/wiki/Routing_table)<br/>

[cnblogs.com: 一分钟看懂Docker的网络模式和跨主机通信](https://www.cnblogs.com/yy-cxd/p/6553624.html)<br/>
