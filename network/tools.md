<!-- MarkdownTOC -->

- [network tools](#network-tools)
  - [nmap -p](#nmap--p)
  - [ssh -p](#ssh--p)
  - [how to check if a port is opened\(or ocuppied\)? And then kill?](#how-to-check-if-a-port-is-openedor-ocuppied-and-then-kill)
  - [traceroute](#traceroute)
  - [Linux TCP/IP 网络工具对比：net-tools 和 iproute2](#linux-tcpip-%E7%BD%91%E7%BB%9C%E5%B7%A5%E5%85%B7%E5%AF%B9%E6%AF%94%EF%BC%9Anet-tools-%E5%92%8C-iproute2)
  - [tee 命令](#tee-%E5%91%BD%E4%BB%A4)
  - [ethtool 命令](#ethtool-%E5%91%BD%E4%BB%A4)
  - [iftop: like top](#iftop-like-top)
  - [dig www.baidu.com +trace](#dig-wwwbaiducom-trace)
- [References](#references)

<!-- /MarkdownTOC -->


# network tools

### nmap -p

```
Usage: nmap [Scan Type(s)] [Options] {target specification}

TARGET SPECIFICATION:
  Can pass hostnames, IP addresses, networks, etc.

HOST DISCOVERY:
  -Pn: Treat all hosts as online -- skip host discovery

PORT SPECIFICATION AND SCAN ORDER:
  -p <port ranges>: Only scan specified ports
    Ex: -p22; -p1-65535; -p U:53,111,137,T:21-25,80,139,8080,S:9
```

Example

```
nmap -P0 smtp.bbb.ccc.net -p 25

nmap -P0 smtp.bbb.ccc.net -p 25
```

Output

```
[root /]# nmap smtp.bbb.net -p 25

Starting Nmap 6.40 ( http://nmap.org ) at 2018-08-23 12:12 UTC
Nmap scan report for smtp.bbb.net (10.0.2.3)
Host is up (0.0095s latency).
rDNS record for 10.0.10.37: ip-10-0-2-3.ec2.internal
PORT   STATE SERVICE
25/tcp open  smtp

Nmap done: 1 IP address (1 host up) scanned in 0.13 seconds

```

```
[root /]# nmap smtp.stg.bbb.net -p 25

Starting Nmap 6.40 ( http://nmap.org ) at 2018-08-23 12:13 UTC
Nmap scan report for smtp.stg.bbb.net (10.1.2.3)
Host is up (0.0095s latency).
rDNS record for 10.2.2.42: ip-10-1-2-3.ec2.internal
PORT   STATE    SERVICE
25/tcp filtered smtp

Nmap done: 1 IP address (1 host up) scanned in 0.32 seconds
```

### ssh -p
```
[root@ltr-latest-ads-646f9cbbdb-dnccd /]# ssh -v smtp.bbb.net -p 25
OpenSSH_7.4p1, OpenSSL 1.0.2k-fips  26 Jan 2017
debug1: Reading configuration data /etc/ssh/ssh_config
debug1: /etc/ssh/ssh_config line 58: Applying options for *
debug1: Connecting to smtp.bbb.net [10.0.2.3] port 25.
debug1: Connection established.
```

```
[root@ltr-latest-ads-646f9cbbdb-dnccd /]# ssh -v smtp.stg.bbb.net -p 25
OpenSSH_7.4p1, OpenSSL 1.0.2k-fips  26 Jan 2017
debug1: Reading configuration data /etc/ssh/ssh_config
debug1: /etc/ssh/ssh_config line 58: Applying options for *
debug1: Connecting to smtp.stg.bbb.net [10.1.2.3] port 25.

```


### how to check if a port is opened(or ocuppied)? And then kill?
* lsof - list open files
* An open file may be a regular file, a directory, a block special file, a character special file, an executing text reference, a library, a stream or  a  network  file (Internet socket, NFS file or UNIX domain socket.)
* -i [i]   selects the listing of files any of whose Internet address matches the address specified in i.  If no address is specified, this option selects  the  listing of all Internet and x.25 (HP-UX) network files.
```
An Internet address is specified in the form (Items in square brackets are optional.):

                [46][protocol][@hostname|hostaddr][:service|port]
```
Example
```
➜  ~ lsof -i :7777
COMMAND     PID    USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
AdServerR 43027 xqzhang    3u  IPv6 0xfc83dc0e547207f7      0t0  TCP *:cbt (LISTEN)
➜  ~ lsof -i :6321
COMMAND     PID    USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
AdServerR 43041 xqzhang    3u  IPv6 0xfc83dc0e4858a7f7      0t0  TCP *:emp-server1 (LISTEN)
```

### traceroute
In computing, traceroute is a computer network diagnostic tool for 
* displaying the route (path) and
* measuring transit delays of packets across an Internet Protocol (IP) network.


### Linux TCP/IP 网络工具对比：net-tools 和 iproute2

net-tools
* ifconfig
* netstat
* route

iproute2
* ip link show
* ip addr show dev eth0
```
$ ip addr show dev eth0
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP qlen 1000
    link/ether 14:02:ec:32:4b:90 brd ff:ff:ff:ff:ff:ff
    inet 192.168.14.139/23 brd 192.168.15.255 scope global eth0
       valid_lft forever preferred_lft forever
    inet 192.168.14.231/24 brd 192.168.14.255 scope global eth0:0
       valid_lft forever preferred_lft forever
    inet 192.168.14.232/24 brd 192.168.14.255 scope global secondary eth0:1
       valid_lft forever preferred_lft forever
```
* ip route show

### [tee 命令](http://man.linuxde.net/tee)

* NAME<br/>
       tee - read from standard input and write to __standard output and files__
* SYNOPSIS<br/>
       tee [OPTION]... [FILE]...

![linux_tee](../images/2018/linux_tee.png)<br/>

### [ethtool 命令](http://man.linuxde.net/ethtool)

```
NAME
       ethtool - query or control network driver and hardware settings
SYNOPSIS
       ethtool devname
```
* Example
```
# ethtool eth0
Settings for eth0:
	Speed: 1000Mb/s
	Duplex: Full
```

### iftop: like top

iftop does for network usage what top(1) does for CPU usage.

```
NAME
       iftop - display bandwidth usage on an interface by host

Synopsis: iftop -h | [-npblNBP] [-i interface] [-f filter code]
                               [-F net/mask] [-G net6/mask6]
```

```
sudo yum install -y iftop

sudo iftop
```

```
   Sorting orders:
   -o 2s                Sort by first column (2s traffic average)
   -o 10s               Sort by second column (10s traffic average) [default]
   -o 40s               Sort by third column (40s traffic average)
   -o source            Sort by source address
   -o destination       Sort by destination address
```

### dig www.baidu.com +trace

`dig (domain information groper)` is a flexible tool for interrogating DNS name servers.

```
NAME
       dig - DNS lookup utility

SYNOPSIS
       dig [@server] [-b address] [-c class] [-f filename] [-k filename] [-m] [-p port#] [-q name] [-t type] [-x addr] [-y [hmac:]name:key] [-4] [-6] [name] [type] [class] [queryopt...]

       dig [-h]

       dig [global-queryopt...] [query...]

SIMPLE USAGE
       A typical invocation of dig looks like:

            dig @server name type

QUERY OPTIONS
       +[no]trace
           Toggle tracing of the delegation path from the root name servers for the name being looked up. Tracing is disabled by default. When tracing is enabled, dig makes iterative queries to resolve
           the name being looked up. It will follow referrals from the root servers, showing the answer from each server that was used to resolve the lookup.
```


* Example

For the 1st DNS server providing DNS query, its IP is configured as the `nameserver` in `/etc/resolv.conf`.

```
[xqzhang@PEKdev032 ~]$ dig www.baidu.com +trace

; <<>> DiG 9.9.4-RedHat-9.9.4-18.el7_1.1 <<>> www.baidu.com +trace
;; global options: +cmd
.     164163  IN  NS  h.root-servers.net.
.     164163  IN  NS  l.root-servers.net.
.     164163  IN  NS  e.root-servers.net.
.     164163  IN  NS  a.root-servers.net.
.     164163  IN  NS  j.root-servers.net.
.     164163  IN  NS  c.root-servers.net.
.     164163  IN  NS  d.root-servers.net.
.     164163  IN  NS  k.root-servers.net.
.     164163  IN  NS  f.root-servers.net.
.     164163  IN  NS  g.root-servers.net.
.     164163  IN  NS  i.root-servers.net.
.     164163  IN  NS  m.root-servers.net.
.     164163  IN  NS  b.root-servers.net.
.     489147  IN  RRSIG NS 8 0 518400 20181230210000 20181217200000 2134 . jOPrjdmM0tr9h1mIOpqx+pVQdxE0bj/DzR+Rskh04lwVsgGjaY4Lsl1M faRzDkA0F8i1IwoO/2pT2OjwfLCw7XmlOb6oeCU39PBf5T+wIEJnJlf6 3NEEx1MWSwh2A37ombwRXRQ7Ta5zEi/gI5zKk8SRZ57AgzoqZNA6wAAW woqeI1pYloDMQlt+vdZumzyh1Su9cp+nI/zTRbKRGufPpQzA9cyuOywv poWhr89m5iir0UdnUg/kSIu7tAZYK+Lv5tDIgjULZpbkg7lAGDb4XTr6 r9HQChC8QieilpM6bYPVirnGpLne1S5JMb7I3JRckA2WLQMwXwp6a+J3 y6sAYw==
;; Received 1097 bytes from 192.168.14.21#53(192.168.14.21) in 356 ms

com.      172800  IN  NS  a.gtld-servers.net.
com.      172800  IN  NS  b.gtld-servers.net.
  1 domain  dev.fwmrm.net
com.      172800  IN  NS  c.gtld-servers.net.
com.      172800  IN  NS  d.gtld-servers.net.
com.      172800  IN  NS  e.gtld-servers.net.
com.      172800  IN  NS  f.gtld-servers.net.
com.      172800  IN  NS  g.gtld-servers.net.
com.      172800  IN  NS  h.gtld-servers.net.
com.      172800  IN  NS  i.gtld-servers.net.
com.      172800  IN  NS  j.gtld-servers.net.
com.      172800  IN  NS  k.gtld-servers.net.
com.      172800  IN  NS  l.gtld-servers.net.
com.      172800  IN  NS  m.gtld-servers.net.
com.      86400 IN  DS  30909 8 2 E2D3C916F6DEEAC73294E8268FB5885044A833FC5459588F4A9184CF C41A5766
com.      86400 IN  RRSIG DS 8 1 86400 20181231050000 20181218040000 2134 . GHLMCyfe6yOuBON0nmb0XR2cV7WbwMbwgyF2UQQn9n/EL7KRyUEqlPg/ Af9Fm+O0Qulhw4AJ02CSftIkJ+X57BrwTiFDUrCGz+337H1RLlV6eL9f fV7/+nkbsa4YwgGxd/Yu2c+3/qgYk7fUJRmmfXnuHVaQc4rg71/TFwjR lnKL4pgGV/yFxUm73Zc/aaaXh3goOfqw9TifBDPP3NU5INhb3g+9AopM 0ZFVizT1QTCiIPHdGBBY7nweAFFnC8rsrGnSJhNP6sMmDpFgwjpcgpHk oyzFwRScDCgezUb7iTDzZBFskghvCh81K+ehCNJ9eMmbyiyQDd+ax6yk DCoZxA==
;; Received 1173 bytes from 192.58.128.30#53(j.root-servers.net) in 496 ms

baidu.com.    172800  IN  NS  dns.baidu.com.
baidu.com.    172800  IN  NS  ns2.baidu.com.
baidu.com.    172800  IN  NS  ns3.baidu.com.
baidu.com.    172800  IN  NS  ns4.baidu.com.
baidu.com.    172800  IN  NS  ns7.baidu.com.
CK0POJMG874LJREF7EFN8430QVIT8BSM.com. 86400 IN NSEC3 1 1 0 - CK0Q1GIN43N1ARRC9OSM6QPQR81H5M9A NS SOA RRSIG DNSKEY NSEC3PARAM
CK0POJMG874LJREF7EFN8430QVIT8BSM.com. 86400 IN RRSIG NSEC3 8 2 86400 20181222054127 20181215043127 37490 com. fg2Am2hnZ5MK3yDC1WGq/qEgn/B3kE0WMFgRloIpu1JhSaOCMVMnmJBr 15XeWn3OhX6TDYd92m5aLouBr+D2bFCaBfKZWEAx/gzzU+wM/fpkgSMp nlCb5TkI+TVIpij8B3O/1fv2T8mZk0UoyX3kkU5WXto5s/DXGIDBX522 oIY=
HPVV2B5N85O7HJJRB7690IB5UVF9O9UA.com. 86400 IN NSEC3 1 1 0 - HPVVN3Q5E5GOQP2QFE2LEM4SVB9C0SJ6 NS DS RRSIG
HPVV2B5N85O7HJJRB7690IB5UVF9O9UA.com. 86400 IN RRSIG NSEC3 8 2 86400 20181224060830 20181217045830 37490 com. cSrPdt4z2mvL14K3s148YmXf53ymFCD5lv5FK4+7S1yJzUlgZlclIrJT xMe1VcDzxxQkUDJRwlR7fcitDfmEDmvzcdyF/oA5cLUODSympGcA12fr KdbZ3Q1shMxRbeleVwXSCz/13YsgKUHTEenak6swOMPIK8SsK5T+Awlk wVY=
;; Received 697 bytes from 192.26.92.30#53(c.gtld-servers.net) in 207 ms

www.baidu.com.    1200  IN  CNAME www.a.shifen.com.
a.shifen.com.   1200  IN  NS  ns2.a.shifen.com.
a.shifen.com.   1200  IN  NS  ns3.a.shifen.com.
a.shifen.com.   1200  IN  NS  ns4.a.shifen.com.
a.shifen.com.   1200  IN  NS  ns1.a.shifen.com.
a.shifen.com.   1200  IN  NS  ns5.a.shifen.com.
;; Received 239 bytes from 180.76.76.92#53(ns7.baidu.com) in 2 ms
```


# References
[Linux TCP/IP 网络工具对比：net-tools 和 iproute2](http://blog.jobbole.com/97270/)<br/>

[linuxde: Linux命令大全](http://man.linuxde.net)<br/>

[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
