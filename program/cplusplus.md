<!-- MarkdownTOC -->

- [Algorithm](#algorithm)
  - [RB Tree](#rb-tree)
- [Some holes\(坑\) ever met](#some-holes%E5%9D%91-ever-met)
  - [MySQL charset: varchar vs text](#mysql-charset-varchar-vs-text)
- [References](#references)

<!-- /MarkdownTOC -->

# Algorithm
## RB Tree

C++ STL中标准关联容器set, multiset, map,multimap内部采用的就是一种非常高效的平衡检索二叉树：红黑树，也成为RB树(Red-Black Tree)。


# Some holes(坑) ever met

## MySQL charset: varchar vs text

* Case
Column `praram_value` changes from varchar(2048) to text. If all records of column `praram_value` are stored for long-duration, __memory size will increase a lot, even lead to OOM__.

* Analysis

1. varchar(2048): if charset is utf-8, we usually set `char param_value[2048\*3+1]`.
2. text: we usually set `char param_value[]`.

# References
[STL中map、set的数据结构及底层实现](http://blog.csdn.net/PirLCK/article/details/51326547)

[print: Linux内核spin_lock与spin_lock_irq分析](https://blog.csdn.net/zhanglei4214/article/details/6837697)

[]()

[]()


[]()


[]()
