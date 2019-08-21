<!-- MarkdownTOC -->

- [Overview](#overview)
  - [Part-1 containers and pods](#part-1-containers-and-pods)
  - [Part-2 services: the abstraction layer that allows pods to be ephemeral](#part-2-services-the-abstraction-layer-that-allows-pods-to-be-ephemeral)
  - [Part-3 ingress: getting traffic to your pods from outside the cluster](#part-3-ingress-getting-traffic-to-your-pods-from-outside-the-cluster)
- [Network: flannel](#network-flannel)
  - [vxlan: Virtual eXtensible Local Area Network](#vxlan-virtual-extensible-local-area-network)
  - [vxlan vs udp vs host-gw](#vxlan-vs-udp-vs-host-gw)
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

# Network: flannel

### vxlan: Virtual eXtensible Local Area Network

外层是宿主机的IP和mac，内层IP是容器的IP，但源mac和目的mac分别是宿主机上面flannel.1（vtep设备的）的mac，这点一定要注意。

[csdn: flannel 实战与源码分析](https://blog.csdn.net/u010278923/article/details/70598428)<br/>

### vxlan vs udp vs host-gw

* 其实flannel还支持别的模式常用的是UPD，它是直接封装到udp，没有vxlan的封装，这种网络模式损耗非常大50%左右，
* 即便是vxlan也有30%左右的损耗，
* 如果允许的话host-gw是个很好的选择，它也是通过路由的方式，类似于calico

[Flannel vs Calico : A battle of L2 vs L3 based networking](https://medium.com/@jain.sm/flannel-vs-calico-a-battle-of-l2-vs-l3-based-networking-5a30cd0a3ebd)<br/>


# References

[Understanding kubernetes networking: pods](https://medium.com/google-cloud/understanding-kubernetes-networking-pods-7117dd28727)<br/>

* Good

[An illustrated guide to Kubernetes Networking: Part 1](https://itnext.io/an-illustrated-guide-to-kubernetes-networking-part-1-d1ede3322727)<br/>
[An illustrated guide to Kubernetes Networking: Part 2](https://itnext.io/an-illustrated-guide-to-kubernetes-networking-part-2-13fdc6c4e24c)<br/>
[An illustrated guide to Kubernetes Networking: Part 3](https://itnext.io/an-illustrated-guide-to-kubernetes-networking-part-3-f35957784c8e)<br/>


[A high level overview of kubernetes](https://kubernetes.io/)<br/>

[An overview of pods specifically](https://kubernetes.io/docs/concepts/workloads/pods/pod/)<br/>

[k8s networking](https://www.digitalocean.com/community/tutorials/an-introduction-to-networking-terminology-interfaces-and-protocols)<br/>

[k8s IP address spaces](https://www.digitalocean.com/community/tutorials/understanding-ip-addresses-subnets-and-cidr-notation-for-networking)<br/>

[wikipedia.org: IP routing table](https://en.wikipedia.org/wiki/Routing_table)<br/>

[cnblogs.com: 一分钟看懂Docker的网络模式和跨主机通信](https://www.cnblogs.com/yy-cxd/p/6553624.html)<br/>
