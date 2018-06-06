- [Docker Architecture](#docker-architecture)
  - [命名空间 namespaces](#命名空间namespaces)
    - [pid namespace](#pid-namespace)
    - [mnt namespace](#mnt-namespace)
    - [net namespace](#net-namespace)
    - [uts namespace](#uts-namespace)
    - [ipc namespace](#ipc-namespace)
    - [user namespace](#user-namespace)
  - [资源配额「cgroups」](#资源配额cgroups)
    - [memory](#memory)
    - [cpu](#cpu)
    - [blkio](#blkio)
    - [devices](#devices)
- [Container: docker run](#container-docker-run)
  - [运行交互式的容器](#运行交互式的容器)
  - [运行一个web应用: port mapping](#运行一个web应用-port-mapping)
  - [Docker container start/stop/rm](#docker-container-startstoprm)
  - [Docker daemon start/stop](#docker-daemon-startstop)
- [Image: docker build](#image-docker-build)
  - [Commands](#commands)
  - [构建镜像](#构建镜像)
- [References](#references)

# Docker Architecture
- Docker 使用客户端-服务器 **(C/S)架构模式**，使用远程API来管理和创建Docker容器。
- Docker 容器通过 Docker 镜像来创建。
- 容器与镜像的关系类似于面向对象编程中的 **对象与类**。

| Docker | 面向对象 |
| :--- | :--- |
| Container  | 对象  |
| Image  | 类  |

![docker_architecture](../images/2018/docker_architecture.png)<br/>
### 命名空间「Namespaces」
---
##### pid namespace
不同用户的进程就是通过 pid namespace 隔离开的，且不同 namespace 中可以有相同 PID。具有以下特征:

* 每个 namespace 中的 pid 是有自己的 pid=1 的进程(类似 /sbin/init 进程)
* 每个 namespace 中的进程只能影响自己的同一个 namespace 或子 namespace 中的进程
* 因为 /proc 包含正在运行的进程，因此在 container 中的 pseudo-filesystem 的 /proc 目录只能看到自己 namespace 中的进程
* 因为 namespace 允许嵌套，父 namespace 可以影响子 namespace 的进程，所以子 namespace 的进程可以在父 namespace 中看到，但是具有不同的 pid

参考文档：[Introduction to Linux namespaces – Part 3: PID](https://blog.yadutaf.fr/2014/01/05/introduction-to-linux-namespaces-part-3-pid/)

##### mnt namespace
类似 chroot，将一个进程放到一个特定的目录执行。mnt namespace 允许不同 namespace 的进程看到的文件结构不同，这样每个 namespace 中的进程所看到的文件目录就被隔离开了。

同 chroot 不同，每个 namespace 中的 Container 在 /proc/mounts 的信息只包含所在 namespace 的 mount point。

##### net namespace
网络隔离是通过 net namespace 实现的， 每个 net namespace 有独立的 network devices, IP addresses, IP routing tables, /proc/net 目录。

这样每个 container 的网络就能隔离开来。 docker 默认采用 veth 的方式将 container 中的虚拟网卡同 host 上的一个 docker bridge 连接在一起。

参考文档：[Introduction to Linux namespaces – Part 5: NET](https://blog.yadutaf.fr/2014/01/19/introduction-to-linux-namespaces-part-5-net/)

##### uts namespace
UTS ("UNIX Time-sharing System") namespace 允许每个 container 拥有独立的 hostname 和 domain name, 使其在网络上可以被视作一个独立的节点而非 Host 上的一个进程。

##### ipc namespace
container 中进程交互还是采用 Linux 常见的进程间交互方法 (interprocess communication - IPC), 包括常见的信号量、消息队列和共享内存。

##### user namespace
每个 container 可以有不同的 user 和 group id, 也就是说可以以 container 内部的用户在 container 内部执行程序而非 Host 上的用户。

<br/>
有了以上 6 种 namespace 从进程、网络、IPC、文件系统、UTS 和用户角度的隔离，一个 container 就可以对外展现出一个独立计算机的能力，并且不同 container 从 OS 层面实现了隔离。 然而不同 namespace 之间资源还是相互竞争的，仍然需要类似 ulimit 来管理每个 container 所能使用的资源 - cgroup。<br/>

### 资源配额「cgroups」
---
##### Memory
内存相关的限制

##### CPU
在 cgroup 中，并不能像硬件虚拟化方案一样能够定义 CPU 能力，但是能够定义 CPU 轮转的优先级，因此具有较高 CPU 优先级的进程会更可能得到 CPU 运算。 通过将参数写入 cpu.shares ,即可定义改 cgroup 的 CPU 优先级 - 这里是一个相对权重，而非绝对值

##### blkio
block IO 相关的统计和限制，byte/operation 统计和限制 (IOPS 等)，读写速度限制等，但是这里主要统计的都是同步 IO

##### devices
设备权限限制

# Container: docker run
### 运行交互式的容器
我们通过docker的两个参数 -i -t，让docker运行的容器实现"对话"的能力

```
runoob@runoob:~$ docker run -i -t ubuntu:15.10 /bin/bash
root@dc0050c79503:/#
```
各个参数解析：
* -t:在新容器内指定一个伪终端或终端。
* -i:允许你对容器内的标准输入 (STDIN) 进行交互。

此时我们已进入一个 ubuntu15.10系统的容器

### 运行一个web应用: port mapping
```
 -p, --publish=[]
    Publish a container's port, or range of ports, to the host.
      format: ip:hostPort:containerPort | ip::containerPort | hostPort:containerPort | containerPort
```
* Both hostPort and containerPort can be specified as a range of ports.
* When specifying ranges for both, the number of container ports in the range must match the number of host ports in the range. (e.g.,
```
      -p 1234-1236:1234-1236/tcp)
```
* docker port 查看端口映射
```
test$ sudo docker port 21e9305569d1
3306/tcp -> 0.0.0.0:30002
8999/tcp -> 0.0.0.0:30000
9000/tcp -> 0.0.0.0:30001
```
### Docker container start/stop/rm
```
runoob@runoob:~$ docker stop determined_swanson   
determined_swanson

runoob@runoob:~$ docker start determined_swanson
determined_swanson

runoob@runoob:~$ docker rm determined_swanson  
determined_swanson
```
* 删除容器时，容器必须是停止状态，否则会报错误.

### Docker daemon start/stop
* start/stop/restart Docker daemon
```
sudo service docker start

sudo service docker stop

sudo service docker restart

sudo service docker status
```


# Image: docker build

### commands
* 我们可以使用 docker images 来列出本地主机上的镜像。
同一仓库源可以有多个 TAG，代表这个仓库源的不同个版本.
```
runoob@runoob:~$ docker images           
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              14.04               90d5884b1ee0        5 days ago          188 MB
php                 5.6                 f40e9e0f10c8        9 days ago          444.8 MB
ubuntu              15.10               4e3b13c8a266        4 weeks ago         136.3 MB
```
* 获取一个新的镜像
当我们在本地主机上使用一个不存在的镜像时 Docker 就会自动下载这个镜像。如果我们想预先下载这个镜像，我们可以使用 docker pull 命令来下载它。
```
Crunoob@runoob:~$ docker pull ubuntu:13.10
13.10: Pulling from library/ubuntu
6599cadaf950: Pull complete 
23eda618d451: Pull complete 
f0be3084efe9: Pull complete 
52de432f084b: Pull complete 
a3ed95caeb02: Pull complete 
Digest: sha256:15b79a6654811c8d992ebacdfbd5152fcf3d165e374e264076aa435214a947a3
Status: Downloaded newer image for ubuntu:13.10
```
下载完成后，我们可以直接使用这个镜像来运行容器。

* 查找镜像
```
runoob@runoob:~$  docker search httpd
```
### 构建镜像
我们使用命令 docker build ， 从零开始来创建一个新的镜像.
为此，我们需要创建一个 **Dockerfile** 文件，其中包含一组指令来告诉 Docker 如何构建我们的镜像。
```
runoob@runoob:~$ cat Dockerfile 
FROM    centos:6.7
MAINTAINER      Fisher "fisher@sudops.com"

RUN     /bin/echo 'root:123456' |chpasswd
RUN     useradd runoob
RUN     /bin/echo 'runoob:123456' |chpasswd
RUN     /bin/echo -e "LANG=\"en_US.UTF-8\"" >/etc/default/local
EXPOSE  22
EXPOSE  80
CMD     /usr/sbin/sshd -D
```
每一个指令都会在镜像上创建一个新的层，每一个指令的前缀都必须是大写的。
第一条FROM，指定使用哪个镜像源
RUN 指令告诉docker 在镜像内执行命令，安装了什么。。。
然后，我们使用 Dockerfile 文件，通过 docker build 命令来构建一个镜像。
```
runoob@runoob:~$ docker build -t runoob/centos:6.7 .
Sending build context to Docker daemon 17.92 kB
Step 1 : FROM centos:6.7
 ---&gt; d95b5ca17cc3
Step 2 : MAINTAINER Fisher "fisher@sudops.com"
 ---&gt; Using cache
 ---&gt; 0c92299c6f03
Step 3 : RUN /bin/echo 'root:123456' |chpasswd
 ---&gt; Using cache
 ---&gt; 0397ce2fbd0a
Step 4 : RUN useradd runoob
......
```
* 设置镜像标签
我们可以使用 docker tag 命令，为镜像添加一个新的标签。
```
runoob@runoob:~$ docker tag 860c279d2fec runoob/centos:dev
```


# References
[Docker 架构](http://www.runoob.com/docker/docker-architecture.html)<br/>

[Docker 镜像使用](http://www.runoob.com/docker/docker-image-usage.html)<br/>

[cnblogs: 非常详细的Docker学习笔记](https://www.cnblogs.com/huatianbuyuexia/p/6540166.html)<br/>
* 命名空间 Namespaces
  * pid namespace
  * mnt namespace
  * net namespace
  * uts namespace
  * ipc namespace
  * user namespace

[kamilszymanski.github.io: Optimizing Docker images for image size and build time](https://kamilszymanski.github.io/optimizing-docker-images-for-image-size-and-build-time/)<br/>

[Redhat developer: Keep it small: a closer look at Docker image sizing](https://developers.redhat.com/blog/2016/03/09/more-about-docker-images-size/)<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>
