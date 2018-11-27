<!-- MarkdownTOC -->

- [iptables](#iptables)
  - [concepts](#concepts)
  - [install on centos](#install-on-centos)
  - [Usage](#usage)
    - [-I versus -A](#-i-versus--a)
    - [-j: REJECT versus DROP](#-j-reject-versus-drop)
    - [comment](#comment)
    - [List rules: -L](#list-rules--l)
    - [save persistence](#save-persistence)
    - [more examples: adding rules](#more-examples-adding-rules)
    - [more examples: deleting rules](#more-examples-deleting-rules)
    - [Notes](#notes)
- [References](#references)

<!-- /MarkdownTOC -->

# iptables

Control Network Traffic with iptables

```
NAME
       iptables/ip6tables -- administration tool for IPv4/IPv6 packet filtering and NAT
```

## concepts

__iptables__ is an application that allows users to configure specific rules that will be enforced by the kernel’s netfilter framework.

It acts as a packet filter and firewall that examines and directs traffic based on port, protocol and other criteria.

## install on centos

`yum install -y iptables`

## Usage

* Options

```sh
  --table	-t table	table to manipulate (default: `filter`)
```

[note] -t table: filter or nat

### -I versus -A

* -I: put to the head.
* -A: put to the tail.

```
  --append  -A chain		Append to chain
  --insert  -I chain [rulenum]
				Insert in chain as rulenum (default 1=first)
```

### -j: REJECT versus DROP

* use __REJECT__ when you want the other end to know the port is unreachable.
* use __DROP__ for connections to hosts you don't want people to see.

In the following example, __REJECT__ wil lead to __refused__ immediately, while __DROP__ will lead to __timed out__ after a long duration.

```sh
[root@aerospike-6bd97c8475-7sqs4 /]# iptables -A OUTPUT -d 61.135.169.125/32 -j REJECT -m comment --comment "test"
[root@aerospike-6bd97c8475-7sqs4 /]# iptables -L -nv
Chain INPUT (policy ACCEPT 928K packets, 189M bytes)
 pkts bytes target     prot opt in     out     source               destination

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination

Chain OUTPUT (policy ACCEPT 714K packets, 154M bytes)
 pkts bytes target     prot opt in     out     source               destination
    6   360 REJECT     all  --  *      *       0.0.0.0/0            61.135.169.125       /* test */ reject-with icmp-port-unreachable
[root@aerospike-6bd97c8475-7sqs4 /]# curl -vvv 61.135.169.125
* About to connect() to 61.135.169.125 port 80 (#0)
*   Trying 61.135.169.125...
* Connection refused
* Failed connect to 61.135.169.125:80; Connection refused
* Closing connection 0
curl: (7) Failed connect to 61.135.169.125:80; Connection refused
```

```sh
[root@aerospike-6bd97c8475-7sqs4 /]# iptables -D OUTPUT 1
[root@aerospike-6bd97c8475-7sqs4 /]# iptables -A OUTPUT -d 61.135.169.125/32 -j DROP -m comment --comment "test"
[root@aerospike-6bd97c8475-7sqs4 /]# iptables -L -nv
Chain INPUT (policy ACCEPT 4777 packets, 890K bytes)
 pkts bytes target     prot opt in     out     source               destination

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination

Chain OUTPUT (policy ACCEPT 3378 packets, 767K bytes)
 pkts bytes target     prot opt in     out     source               destination
    0     0 DROP       all  --  *      *       0.0.0.0/0            61.135.169.125       /* test */
[root@aerospike-6bd97c8475-7sqs4 /]# time curl -vvv 61.135.169.125
* About to connect() to 61.135.169.125 port 80 (#0)
*   Trying 61.135.169.125...

* Connection timed out
* Failed connect to 61.135.169.125:80; Connection timed out
* Closing connection 0
curl: (7) Failed connect to 61.135.169.125:80; Connection timed out

real	2m7.338s
user	0m0.003s
sys	0m0.003s
```

### comment

```
-m comment --comment "limit ssh access"
```

### List rules: -L

```
  --list    -L [chain [rulenum]]
				List the rules in a chain or all chains

  --numeric	-n		numeric output of addresses and ports
  --verbose	-v		verbose mode
```

`sudo iptables -L -nv --line-number`

### save persistence

* Rules created with the iptables command are stored in memory.

* To save netfilter rules, type the following command as root:

Centos: 
`/sbin/service iptables save`

This executes the iptables init script, which runs the __/sbin/iptables-save__ program and writes the current iptables configuration to __/etc/sysconfig/iptables__. The existing __/etc/sysconfig/iptables__ file is saved as __/etc/sysconfig/iptables.save__.

### more examples: adding rules

```sh
sudo iptables -I OUTPUT -d 0.0.0.0/8 -j ACCEPT
sudo iptables -I OUTPUT -d 10.0.0.0/8 -j ACCEPT
sudo iptables -I OUTPUT -d 100.64.0.0/10 -j ACCEPT
sudo iptables -I OUTPUT -d 127.0.0.0/8 -j ACCEPT
sudo iptables -I OUTPUT -d 169.254.0.0/16 -j ACCEPT
sudo iptables -I OUTPUT -d 172.16.0.0/12 -j ACCEPT
sudo iptables -I OUTPUT -d 192.0.0.0/24 -j ACCEPT
sudo iptables -I OUTPUT -d 192.0.0.0/29 -j ACCEPT
sudo iptables -I OUTPUT -d 192.168.0.0/16 -j ACCEPT
sudo iptables -I OUTPUT -d 52.95.255.96/28 -j ACCEPT

sudo iptables -I OUTPUT -d 54.231.0.0/17 -j ACCEPT -m comment --comment "AWS S3"
sudo iptables -I OUTPUT -d 52.92.16.0/20 -j ACCEPT -m comment --comment "AWS S3"
sudo iptables -I OUTPUT -d 52.216.0.0/15 -j ACCEPT -m comment --comment "AWS S3"

sudo iptables -A OUTPUT -d 0.0.0.0/0 -j REJECT -m comment --comment "limit Internet access"
```

### more examples: deleting rules

```
	-D, --delete chain rule-specification
	-D, --delete chain rulenum
	      Delete one or more rules from the selected chain. There are two versions of this command: the rule can be specified as a number in the chain (starting at 1 for the first rule) or a rule to match.
```

```
sudo iptables -D OUTPUT -d 0.0.0.0/0 -j REJECT
sudo iptables -D OUTPUT -d 54.231.0.0/17 -j ACCEPT -m comment --comment "AWS S3"
sudo iptables -D OUTPUT -d 52.92.16.0/20 -j ACCEPT -m comment --comment "AWS S3"
sudo iptables -D OUTPUT -d 52.216.0.0/15 -j ACCEPT -m comment --comment "AWS S3"

sudo iptables -D OUTPUT -
```

### Notes

Could not connect to the endpoint URL: "https://s3.amazonaws.com/"

# References

[major.io: Best practices: iptables](https://major.io/2010/04/12/best-practices-iptables/)<br/>

[www.linode.com: Control Network Traffic with iptables](https://www.linode.com/docs/security/firewalls/control-network-traffic-with-iptables/)<br/>

