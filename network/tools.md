-[traceroute](#traceroute)
-[Linux TCP/IP 网络工具对比：net-tools 和 iproute2](##linux-tcpip-网络工具对比net-tools-和-iproute2)
-[tee 命令](#tee-命令)
-[ethtool 命令](#ethtool-命令)
-[](#)
-[](#)


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

### References
[Linux TCP/IP 网络工具对比：net-tools 和 iproute2](http://blog.jobbole.com/97270/)<br/>

[linuxde: Linux命令大全](http://man.linuxde.net)<br/>

[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
