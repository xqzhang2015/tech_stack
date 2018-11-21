<!-- MarkdownTOC -->

- [NAT: network address translation](#nat-network-address-translation)
  - [Why?](#why)
  - [Static NAT](#static-nat)
  - [Dynamic NAT](#dynamic-nat)
  - [NAT Overload: PAT](#nat-overload-pat)
  - [Checking configuration: show the NAT translations and statistics](#checking-configuration-show-the-nat-translations-and-statistics)

<!-- /MarkdownTOC -->

# NAT: network address translation

private internal IP ==> private global IP

Work with nat table, or nat mappings.

## Why?
* At first: 推迟IP 地址空间耗尽
* But also: 网络迁移和合并 / 服务器负载均衡 / 创建虚拟服务器 也很有用

NAT 通常用于边界路由器. 

## Static NAT
To do a __one-to-one mapping__ between an inside address and an outside address.

Usually, static NAT is used for servers inside your network. For example, you may have a web server with the inside IP address 192.168.0.10 and you want it to be accessible when a remote host makes a request to 209.165.200.10.

## Dynamic NAT
Dynamic NAT is used when you have __a "pool" of public IP addresses__ that you want to assign to your internal hosts dynamically. 


## NAT Overload: PAT

NAT Overload, sometimes also called PAT, is probably the most used type of NAT. You can configure NAT overload in two ways, depending on how many public IP address you have available.

Work also with ports.

* 1st case: you have only one public IP address allocated by your ISP.

In this case, you map all your inside hosts to the available IP address. The configuration is almost the same as for dynamic NAT, but this time you specify the outside interface instead of a NAT pool.

* 2nd case: your ISP gave you more than one public IP addresses.

## Checking configuration: show the NAT translations and statistics

```
show ip nat statistics
```
