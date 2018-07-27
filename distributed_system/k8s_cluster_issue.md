

### Failing to communication between pods on same host, if kube-dns is also on this host

##### Solution
1. load kernel module __br_netfilter__
```
centos@ip-xxx.ec2.internal:~ ·
!45 $ cat /etc/modules-load.d/net.conf
br_netfilter
```

2. set system variables

```
centos@ip-xxx.ec2.internal:~ ·
!46 $ cat /etc/sysctl.d/net.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
```

* Note,
Checking if a module is loaded
```
!47 $ sudo lsmod  | grep br
br_netfilter           22209  0
bridge                136173  1 br_netfilter
```
or
```
!48 $ cat /proc/modules | grep br
br_netfilter 22209 0 - Live 0xffffffffc02af000
bridge 136173 1 br_netfilter, Live 0xffffffffc0281000
stp 12976 1 bridge, Live 0xffffffffc027c000
llc 14552 2 bridge,stp, Live 0xffffffffc0209000
```
