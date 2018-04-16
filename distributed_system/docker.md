
## Docker Architecture
- Docker 使用客户端-服务器 **(C/S)架构模式**，使用远程API来管理和创建Docker容器。
- Docker 容器通过 Docker 镜像来创建。
- 容器与镜像的关系类似于面向对象编程中的 **对象与类**。

| Docker | 面向对象 |
| :--- | :--- |
| Container  | 对象  |
| Image  | 类  |

![docker_architecture](../images/2018/docker_architecture.png)<br/>

## docker run
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

## References
[Docker 架构](http://www.runoob.com/docker/docker-architecture.html)<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
