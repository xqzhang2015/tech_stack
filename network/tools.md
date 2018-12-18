<!-- MarkdownTOC -->

- [network tools](#network-tools)
    - [nmap -p](#nmap--p)
    - [ssh -p](#ssh--p)
    - [how to check if a port is opened\(or ocuppied\)? And then kill?](#how-to-check-if-a-port-is-openedor-ocuppied-and-then-kill)
    - [traceroute](#traceroute)
  - [### Linux TCP/IP 网络工具对比：net-tools 和 iproute2](#-linux-tcpip-%E7%BD%91%E7%BB%9C%E5%B7%A5%E5%85%B7%E5%AF%B9%E6%AF%94%EF%BC%9Anet-tools-%E5%92%8C-iproute2)
  - [### tee 命令](#-tee-%E5%91%BD%E4%BB%A4)
  - [### ethtool 命令](#-ethtool-%E5%91%BD%E4%BB%A4)
    - [iftop: like top](#iftop-like-top)
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
---
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
---
* NAME<br/>
       tee - read from standard input and write to __standard output and files__
* SYNOPSIS<br/>
       tee [OPTION]... [FILE]...

![linux_tee](../images/2018/linux_tee.png)<br/>

### [ethtool 命令](http://man.linuxde.net/ethtool)
---
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

# References
[Linux TCP/IP 网络工具对比：net-tools 和 iproute2](http://blog.jobbole.com/97270/)<br/>

[linuxde: Linux命令大全](http://man.linuxde.net)<br/>

[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
