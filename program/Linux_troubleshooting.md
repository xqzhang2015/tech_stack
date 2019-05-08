<!-- MarkdownTOC -->

- [Linux system](#linux-system)
  - [Linux CPU](#linux-cpu)
  - [Linux memory](#linux-memory)
  - [Linux disk](#linux-disk)
    - [fio and iostat\(systat\)](#fio-and-iostatsystat)
  - [Linux network](#linux-network)
    - [netstat -apn](#netstat--apn)
      - [How to install netstat](#how-to-install-netstat)
    - [top -o %MEM](#top--o-%25mem)
    - [brctl show](#brctl-show)
- [Linux process](#linux-process)
    - [ab: Apache Bench](#ab-apache-bench)
    - [gdb prog procID](#gdb-prog-procid)
      - [gdb output string limit](#gdb-output-string-limit)
    - [ldd](#ldd)
    - [pmap -x pid](#pmap--x-pid)
    - [pstack pid](#pstack-pid)
    - [nm objfile...](#nm-objfile)
    - [lsblk and fdisk](#lsblk-and-fdisk)
    - [iftop](#iftop)

<!-- /MarkdownTOC -->

# Linux system

## Linux CPU

```sh
$ lscpu
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                2
On-line CPU(s) list:   0,1
Thread(s) per core:    2
...
```

## Linux memory

```
!16 $ free -h
              total        used        free      shared  buff/cache   available
Mem:           7.5G        186M        6.4G        268M        997M        6.8G
Swap:            0B          0B          0B

!17 $ cat /proc/meminfo
MemTotal:        7906032 kB
MemFree:         6694120 kB
MemAvailable:    7171352 kB
Buffers:            2068 kB
Cached:           948968 kB
SwapCached:            0 kB
```

## Linux disk

### fio and iostat(systat)

使用 fio(or dd) 进行存储性能测试(IOPS). fio support `multi-threads`.

```
NAME
       fio - flexible I/O tester

DESCRIPTION
       fio is a tool that will spawn a number of threads or processes doing a particular type of I/O action as specified by the user.
```

* Install

```
sudo yum install -y fio
sudo yum install -y sysstat
```

* Usage

```
nohup sudo fio --filename=/dev/nvme1n1p1 --rw=read --bs=128k --iodepth=32 --ioengine=libaio --direct=1 --name=volume-initialize --numjobs=4 &
```

`iostat -x 3` or `iostat -d 3`


```
NAME
       iostat - Report Central Processing Unit (CPU) statistics and input/output statistics for devices and partitions.

SYNOPSIS
       iostat  [ -c ] [ -d ] [ -h ] [ -k | -m ] [ -N ] [ -t ] [ -V ] [ -x ] [ -y ] [ -z ] [...] [ interval [ count ] ]
```

## Linux network

### netstat -apn

##### How to install netstat

* yum `whatprovides` netstat

```
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
 * base: centos.mirror.secureax.com
 * extras: centos.mirror.secureax.com
 * updates: centos.mirror.secureax.com
net-tools-2.0-0.17.20131004git.el7.x86_64 : Basic networking tools
```

* yum install -y `net-tools`

### top -o %MEM


### brctl show

```sh
!28 $ sudo yum install -y bridge-utils

!29 $ brctl show
bridge name	bridge id		STP enabled	interfaces
cni0		8000.0a5864607501	no		veth301b7b1d
										veth964e8abb
docker0		8000.024252639fcf	no
```

```sh
!33 $ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN qlen 1
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 9001 qdisc mq state UP qlen 1000
    link/ether 02:d4:48:7b:4f:74 brd ff:ff:ff:ff:ff:ff
    inet 10.206.153.65/20 brd 10.206.159.255 scope global dynamic eth0
       valid_lft 3547sec preferred_lft 3547sec
    inet6 fe80::d4:48ff:fe7b:4f74/64 scope link
       valid_lft forever preferred_lft forever
3: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN
    link/ether 02:42:52:63:9f:cf brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 scope global docker0
       valid_lft forever preferred_lft forever
4: flannel.1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 8951 qdisc noqueue state UNKNOWN
    link/ether 0e:0b:21:7c:0f:40 brd ff:ff:ff:ff:ff:ff
    inet 100.96.117.0/32 scope global flannel.1
       valid_lft forever preferred_lft forever
    inet6 fe80::c0b:21ff:fe7c:f40/64 scope link
       valid_lft forever preferred_lft forever
5: cni0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 8951 qdisc noqueue state UP qlen 1000
    link/ether 0a:58:64:60:75:01 brd ff:ff:ff:ff:ff:ff
    inet 100.96.117.1/24 scope global cni0
       valid_lft forever preferred_lft forever
    inet6 fe80::ac9d:dbff:fed6:5a3e/64 scope link
       valid_lft forever preferred_lft forever
6: veth964e8abb@if3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 8951 qdisc noqueue master cni0 state UP
    link/ether b6:f6:77:f6:d3:47 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet6 fe80::b4f6:77ff:fef6:d347/64 scope link
       valid_lft forever preferred_lft forever
15: veth301b7b1d@if3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 8951 qdisc noqueue master cni0 state UP
    link/ether 86:d0:0a:f7:c2:ac brd ff:ff:ff:ff:ff:ff link-netnsid 1
    inet6 fe80::84d0:aff:fef7:c2ac/64 scope link
       valid_lft forever preferred_lft forever
```

Prepare

```sh
!35 $ container_id=ce7d6a0d713f

!36 $ pid=`sudo docker inspect --format '{{.State.Pid}}' ${container_id}`

!37 $ echo $pid
34575

!38 $ sudo ln -sfT /proc/$pid/ns/net /var/run/netns/$container_id
```

```sh
!44 $ sudo nsenter -t 34575 -n ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN qlen 1
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host
       valid_lft forever preferred_lft forever
3: eth0@if15: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 8951 qdisc noqueue state UP
    link/ether 0a:58:64:60:75:0b brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 100.96.117.11/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::e06c:24ff:fe05:129e/64 scope link tentative dadfailed
       valid_lft forever preferred_lft forever

!45 $ sudo nsenter -t 34575 -n ethtool -S eth0
NIC statistics:
     peer_ifindex: 15
```

```
bridge:                 virtual-eth       veth-pair         eth-in-container             container-name
                                              |
cni0                    6:  veth964e8abb    <-|->           3: eth0(100.96.117.2/24)     pause:dockerd-status
(100.96.117.1/24)       15: veth301b7b1d    <-|->           3: eth0(100.96.117.11/24)    pause:core
```

# Linux process

### ab: Apache Bench 

```
# yum search httpd-tools

======================================= N/S matched: httpd-tools ========================================
httpd-tools.x86_64 : Tools for use with the Apache HTTP Server

# yum install -y httpd-tools
```

* Usage

```sh
ab -h
Usage: ab [options] [http[s]://]hostname[:port]/path
Options are:
    -n requests     Number of requests to perform
    -c concurrency  Number of multiple requests to make
    -t timelimit    Seconds to max. wait for responses

    -v verbosity    How much troubleshooting info to print
    -k              Use HTTP KeepAlive feature
```
* Example-1: using Apache Bench (ab) to POST JSON to an API

```
ab -p post_loc.txt -T application/json -H 'Authorization: Token abcd1234' -c 10 -n 2000 http://example.com/api/v1/locations/
```

* Example-2
```sh
ab -n 100 -c 5 "https://serverfault.com/questions"
This is ApacheBench, Version 2.3 <$Revision: 655654 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking serverfault.com (be patient).....done


Server Software:
Server Hostname:        serverfault.com
Server Port:            443
SSL/TLS Protocol:       TLSv1.2,ECDHE-RSA-AES128-GCM-SHA256,2048,128

Document Path:          /questions
Document Length:        208360 bytes

Concurrency Level:      5
Time taken for tests:   4.905 seconds
Complete requests:      100
Failed requests:        99
   (Connect: 0, Receive: 0, Length: 99, Exceptions: 0)
Write errors:           0
Total transferred:      20906113 bytes
HTML transferred:       20837746 bytes
Requests per second:    20.39 [#/sec] (mean)
Time per request:       245.238 [ms] (mean)
Time per request:       49.048 [ms] (mean, across all concurrent requests)
Transfer rate:          4162.52 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        4    6   2.9      6      25
Processing:    30  230 173.8    252    1019
Waiting:       22   68  49.2     46     214
Total:         35  236 174.2    257    1025

Percentage of the requests served within a certain time (ms)
  50%    257
  66%    345
  75%    363
  80%    376
  90%    421
  95%    447
  98%    574
  99%   1025
 100%   1025 (longest request)
```

### gdb prog procID

* NAME<br/>
	gdb - The GNU Debugger

* SYNOPSIS<br/>
gdb [-help] [-nh] [-nx] [-q] [-batch] __[-cd=dir]__ [-f] [-b bps]<br/>
           [-tty=dev] [-s symfile] [-e prog] [-se prog] [-c core] __[-p procID]__<br/>
           __[-x cmds]__ __[-d dir]__ __[prog|prog procID|prog core]__<br/>


You can run "gdb" with no arguments or options; but the most usual way to start GDB is with one argument or two, specifying an executable program as the argument:

       gdb program, then run attach PID, enter continue

You can also start with both an executable program and a core file specified:

       gdb program core

You can, instead, specify a process ID as a second argument, if you want to debug a running process:

       gdb program 1234<br/>
       Pgdb -p 1234

* cmds file example

```shell
# test.gdb
source stl-views-1.0.3.gdb
file test
set args 'a' 'b' ccc
directory /xxx/src

b test.cpp:100
b ClassA::test

set print element 0
```
##### gdb output string limit

```shell
(gdb) show print elements
Limit on string chars or array elements to print is 200.

(gdb) set print elements 30000
```

### ldd

* NAME<br/>
	ldd - print shared library dependencies

* SYNOPSIS<br/>
	ldd [OPTION]... FILE...

* OPTIONS<br/>
	-v --verbose<br/>
	      Print all information, including, for example, symbol versioning information.

```shell
(master)# ldd  abc
	libssl.so.10 => /lib64/libssl.so.10 (0x00007f16f0787000)
	libodbc.so.2 => /lib64/libodbc.so.2 (0x00007f16f051e000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f16ef8d7000)
	libxerces-c-3.1.so => /lib64/libxerces-c-3.1.so (0x00007f16ef329000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f16ef022000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f16eed20000)
	...
```

### pmap -x pid

* NAME<br/>
	pmap - report memory map of a process

* SYNOPSIS<br/>
	pmap [options] pid [...]

* OPTIONS<br/>
	-x, --extended<br/>
	      Show the extended format.<br/>
	-X     Show even more details than the -x option. WARNING: format changes according to /proc/PID/smaps<br/>
	-p, --show-path<br/>
	      Show full path to files in the mapping column<br/>

```shell
(master)# pmap -pX 56
56:   nginx: master process /xxx/nginx/nginx_binary/nginx -c /xxx/nginx/nginx_conf/nginx.conf
 Address Perm   Offset Device    Inode    Size  Rss Pss Referenced Anonymous Swap Locked Mapping
00400000 r-xp 00000000  fd:0b  1052997     732   40  10          4         0    0      0 /xxx/nginx/nginx_binary/nginx
006b7000 r--p 000b7000  fd:0b  1052997       4    4   1          0         4    0      0 /xxx/nginx/nginx_binary/nginx
006b8000 rw-p 000b8000  fd:0b  1052997      84   72  27          0        72    0      0 /xxx/nginx/nginx_binary/nginx

...

7f967d12a000 r-xp 00000000  fd:0b  1196156      88    8   0          8         0    0      0 /usr/lib64/libpthread-2.17.so
7f967d140000 ---p 00016000  fd:0b  1196156    2048    0   0          0         0    0      0 /usr/lib64/libpthread-2.17.so
7f967d340000 r--p 00016000  fd:0b  1196156       4    4   1          0         4    0      0 /usr/lib64/libpthread-2.17.so
7f967d341000 rw-p 00017000  fd:0b  1196156       4    4   4          0         4    0      0 /usr/lib64/libpthread-2.17.so
```

### pstack pid

* NAME<br/>
	gstack - __print__ a stack trace of a running process

* SYNOPSIS<br/>
	gstack pid

* SEE ALSO<br/>
       nm(1), ptrace(2), gdb(1)

```shell
~$ which pstack
/usr/bin/pstack
~$ ll /usr/bin/pstack
lrwxrwxrwx. 1 root root 6 Jun  7  2016 /usr/bin/pstack -> gstack
```

### nm objfile...

* NAME<br/>
	nm - list symbols from object files

```shell
0000000000401200 W _Z10mergeSort2IiEvPT_i
0000000000401787 W _Z11mergeSorti2IiEvPT_S1_ii
```

### lsblk and fdisk

```sh
centos@ip-10-206-63-100.ec2.internal:~ · 07:32 AM Mon Nov 05 ·
!10 $ sudo fdisk -l

Disk /dev/nvme0n1: 32.2 GB, 32212254720 bytes, 62914560 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x000ae09f

        Device Boot      Start         End      Blocks   Id  System
/dev/nvme0n1p1   *        2048    62914526    31456239+  83  Linux
WARNING: fdisk GPT support is currently new, and therefore in an experimental phase. Use at your own discretion.

Disk /dev/nvme1n1: 10.7 GB, 10737418240 bytes, 20971520 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: gpt
Disk identifier: 8523AD60-8641-4E59-B066-CC42AA57953D


#         Start          End    Size  Type            Name
 1         2048     20969471     10G  Microsoft basic primary
```

```sh
centos@ip-10-206-63-100.ec2.internal:~ · 07:32 AM Mon Nov 05 ·
!11 $ lsblk
NAME        MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
nvme0n1     259:0    0  30G  0 disk
`-nvme0n1p1 259:1    0  30G  0 part /
nvme1n1     259:2    0  10G  0 disk
`-nvme1n1p1 259:3    0  10G  0 part
```

```sh
centos@ip-10-206-63-100.ec2.internal:~ · 07:33 AM Mon Nov 05 ·
!13 $ sudo file -s /dev/nvme0n1p1
/dev/nvme0n1p1: SGI XFS filesystem data (blksz 4096, inosz 512, v2 dirs)

centos@ip-10-206-63-100.ec2.internal:~ · 07:33 AM Mon Nov 05 ·
!14 $ sudo file -s /dev/nvme1n1p1
/dev/nvme1n1p1: SGI XFS filesystem data (blksz 4096, inosz 512, v2 dirs)
```

### iftop
