<!-- MarkdownTOC -->

- [etcd arch](#etcd-arch)
- [节点间数据传输 网络拓扑](#%E8%8A%82%E7%82%B9%E9%97%B4%E6%95%B0%E6%8D%AE%E4%BC%A0%E8%BE%93-%E7%BD%91%E7%BB%9C%E6%8B%93%E6%89%91)
- [节点间 数据类型和通道类型](#%E8%8A%82%E7%82%B9%E9%97%B4-%E6%95%B0%E6%8D%AE%E7%B1%BB%E5%9E%8B%E5%92%8C%E9%80%9A%E9%81%93%E7%B1%BB%E5%9E%8B)
- [Study notes](#study-notes)
  - [NoFreelistSync](#nofreelistsync)
  - [mmap flag: syscall.MAP_POPULATE](#mmap-flag-syscallmap_populate)
  - [etcd 概念词汇表](#etcd-%E6%A6%82%E5%BF%B5%E8%AF%8D%E6%B1%87%E8%A1%A8)
- [References](#references)

<!-- /MarkdownTOC -->

# etcd arch

![etcd arch](../../images/2019/etcd_arch.png)

# 节点间数据传输 网络拓扑

1. 各节点间通过HTTP协议来传递数据
	* Leader向Follower 发送心跳包，Follower向Leader回复消息
	* Leader向Follower 发送日志追加信息
	* Leader向Follower 发送Snapshot数据
	* Candidate发起 选举，向其他node发起投票请求
	* Follower 将收的写操作转发给Leader

2. 任意两个nodes之间，建立 __长连接__ (网状结构), which is created during ETCD bootstrap. 
	* 减少创建连接的开销

# 节点间 数据类型和通道类型
有各种不同message，通过 __google protocol buffer__ 传输，size 各不相同:

| Message Type | 通道类型  | 通道类型 |
| ------------ | ------- |-------- |
| heartbeat: 几十 bytes | Stream   | 短连接传输，用完即关闭; 避免阻塞心跳包 |
| SNAPSHOT: even over 1GB | Pipeline | 点到点1个HTTP长连接 |

# Study notes

## NoFreelistSync

```golang
// Do not sync freelist to disk. This improves the database write performance
// under normal operation, but requires a full database re-sync during recovery.
NoFreelistSync bool

```

https://coreos.com/blog/announcing-etcd-3.3

However, the free list sync demands more disk space and incurs extra latencies.

In one user's case, where there were lots of free pages due to frequent snapshots with read transactions, the database size quickly grew from 16 MiB to 4 GiB as a result of large freelist syncs.

## mmap flag: syscall.MAP_POPULATE

https://www.jianshu.com/p/1cb00b599079

## etcd 概念词汇表
* Raft：etcd 所采用的保证分布式系统强一致性的算法。
* Node：一个 Raft 状态机实例。
* Member： 一个 etcd 实例。它管理着一个 Node，并且可以为客户端请求提供服务。
* Cluster：由多个 Member 构成可以协同工作的 etcd 集群。
* Peer：对同一个 etcd 集群中另外一个 Member 的称呼。
* Client： 向 etcd 集群发送 HTTP 请求的客户端。
* WAL：预写式日志，etcd 用于持久化存储的日志格式。
* snapshot：etcd 防止 WAL 文件过多而设置的快照，存储 etcd 数据状态。
* Proxy：etcd 的一种模式，为 etcd 集群提供反向代理服务。
* Leader：Raft 算法中通过竞选而产生的处理所有数据提交的节点。
* Follower：竞选失败的节点作为 Raft 中的从属节点，为算法提供强一致性保证。
* Candidate：当 Follower 超过一定时间接收不到 Leader 的心跳时转变为 Candidate 开始竞选。
* Term：某个节点成为 Leader 到下一次竞选时间，称为一个 Term。
* Index：数据项编号。Raft 中通过 Term 和 Index 来定位数据。

# References

https://www.cnblogs.com/seattle-xyt/p/10366131.html
