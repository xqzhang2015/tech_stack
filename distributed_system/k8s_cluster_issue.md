<!-- MarkdownTOC -->

- [configmap](#configmap)
  - [configmap key-value: value is not pretty\(multiple line\)](#configmap-key-value-value-is-not-prettymultiple-line)
- [Failing to communication between pods on same host, if kube-dns is also on this host](#failing-to-communication-between-pods-on-same-host-if-kube-dns-is-also-on-this-host)
  - [Solution](#solution)
  - [Checking system env](#checking-system-env)
- [Kubernetes stuck on ContainerCreating](#kubernetes-stuck-on-containercreating)
  - [kubectl describe pods](#kubectl-describe-pods)

<!-- /MarkdownTOC -->

## configmap

### configmap key-value: value is not pretty(multiple line)

The file for value cann't contain `tab`, but blank space is okay.

* issue example

```sh
kubectl get configmap game-config  -o yaml
apiVersion: v1
data:
  game.properties: "enemies=aliens\nlives=3\nenemies.cheat=true\nenemies.cheat.level=noGoodRotten\nsecret.code.passphrase=UUDDLRLRBABAS\nsecret.code.allowed=true\n\tsecret.code.lives=30\n"
  ui.properties: |+
    color.good=purple
    color.bad=yellow
    allow.textmode=true
    how.nice.to.look=fairlyNice

kind: ConfigMap
metadata:
  creationTimestamp: 2018-12-12T03:31:13Z
  name: game-config
  namespace: default
  resourceVersion: "27648074"
  selfLink: /api/v1/namespaces/default/configmaps/game-config
  uid: 6010d450-fdbe-11e8-80e8-02b5f4111f4a
```

## Failing to communication between pods on same host, if kube-dns is also on this host

### Solution
1. load kernel module __br_netfilter__ when booting
```shell
centos@ip-xxx.ec2.internal:~ ·
!45 $ cat /etc/modules-load.d/net.conf
br_netfilter
```

2. set system variables when booting

```shell
centos@ip-xxx.ec2.internal:~ ·
!46 $ cat /etc/sysctl.d/net.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
```

### Checking system env

* Checking if a module is loaded
```shell
!47 $ sudo lsmod  | grep br
br_netfilter           22209  0
bridge                136173  1 br_netfilter
```
or

```shell
!48 $ cat /proc/modules | grep br
br_netfilter 22209 0 - Live 0xffffffffc02af000
bridge 136173 1 br_netfilter, Live 0xffffffffc0281000
stp 12976 1 bridge, Live 0xffffffffc027c000
llc 14552 2 bridge,stp, Live 0xffffffffc0209000
```

* /proc/sys/...

```shell
centos@ip-10-xxx-21-111.ec2.internal:~ · 05:31 AM Tue Aug 28 ·
!10 $ ls -l /proc/sys/net/bridge/bridge-nf-call-ip*
-rw-r--r--. 1 root root 0 Aug 28 05:10 /proc/sys/net/bridge/bridge-nf-call-ip6tables
-rw-r--r--. 1 root root 0 Aug 28 05:10 /proc/sys/net/bridge/bridge-nf-call-iptables

centos@ip-10-xxx-21-111.ec2.internal:~ · 05:31 AM Tue Aug 28 ·
!11 $ cat /proc/sys/net/bridge/bridge-nf-call-ip*
1
1
```

## Kubernetes stuck on ContainerCreating

`kubectl logs` doesn't seem to work since the container needs to be in a `non-pending` state.

### kubectl describe pods

`kubectl describe pods` will list all the events associated with the pod, including pulling of images, starting of containers. 
