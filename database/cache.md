Here is the homepage of cache

<!-- MarkdownTOC -->

- [Inner process](#inner-process)
  - [缓存穿透](#%E7%BC%93%E5%AD%98%E7%A9%BF%E9%80%8F)
    - [Introduction](#introduction)
    - [Solution](#solution)
  - [缓存击穿](#%E7%BC%93%E5%AD%98%E5%87%BB%E7%A9%BF)
    - [Introduction](#introduction-1)
    - [Solution](#solution-1)
  - [缓存雪崩解](#%E7%BC%93%E5%AD%98%E9%9B%AA%E5%B4%A9%E8%A7%A3)
    - [Introduction](#introduction-2)
    - [Solution](#solution-2)
- [Outer process](#outer-process)
  - [Aerospike](#aerospike)
  - [Memcached](#memcached)
  - [Redis](#redis)
  - [Others](#others)
- [References](#references)

<!-- /MarkdownTOC -->


# Inner process

## 缓存穿透

Note: 重点在__透__上，DB中__不存在的data__。

### Introduction

访问一个不存在的key，缓存不起作用，请求会穿透到DB，流量大时DB会挂掉。

要是有人利用不存在的key频繁攻击我们的应用，这就是漏洞。

### Solution

* 通过布隆过滤器拦截.
* 对空结果进行缓存，但是过期时间很短，不超过5分钟.


## 缓存击穿

Note: 重点在__穿__上，DB中__存在的data__，一个高频访问的key过期了。

### Introduction

一个存在的key，在缓存过期的一刻，同时有大量的请求，这些请求都会击穿到DB，造成瞬时DB请求量大、压力骤增。


缓存在某个点过期的时候，恰好在这个时间点对这个key有大量的并发请求过来，这些请求发现缓存过期一般都会从后端加载数据并回设到缓存，这个时候大并发的请求可能瞬间把后端DB压垮。


### Solution

* 热点 key 永不过期
* 在访问key之前，采用SETNX（set if not exists）来设置另一个短期key来锁住当前key的访问，访问结束再删除该短期key。

(比如 set一个in-memory key，说明 是正在执行读MySQL&写Aerospike 这个动作)

* 缓存过期仍然可用

## 缓存雪崩解

Note: 重点在__穿__上，DB中__存在的data__，所有key 同时过期了。

### Introduction

大量的key设置了相同的过期时间，导致在缓存在同一时刻全部失效，造成瞬时DB请求量大、压力骤增，引起雪崩。

### Solution
* 采用同步或者队列的方式保证缓存的单线程写，从而避免失效时大量的并发请求落到底层储存系统上。
* 在缓存的失效时间基础上增加一个随机值，比如1-5分钟。

# Outer process
## Aerospike
## Memcached
## Redis
## Others

# References

[CSDN: 缓存穿透，缓存击穿，缓存雪崩解决方案分析](https://blog.csdn.net/zeb_perfect/article/details/54135506)<br/>

[简书: 缓存穿透、缓存击穿、缓存雪崩概念及解决方案](https://www.jianshu.com/p/b57d0773ee96)<br/>
