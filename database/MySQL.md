
### [GTID(Global Transaction IDentifier)](https://blog.csdn.net/solarison/article/details/60468505)
##### __简介__
基于GTID的复制是MySQL 5.6后新增的复制方式.

GTID (global transaction identifier) 即全局事务ID, 保证了在每个在主库上提交的事务在集群中有一个唯一的ID.

在原来基于日志的复制中, 从库需要告知主库要从哪个偏移量进行增量同步, 如果指定错误会造成数据的遗漏, 从而造成数据的不一致.

而基于GTID的复制中, 从库会告知主库已经执行的事务的GTID的值, 然后主库会将所有未执行的事务的GTID的列表返回给从库. 并且可以保证同一个事务只在指定的从库执行一次.

##### __GTID Limits__
`enforce_gtid_consistency` 强制GTID一致性, 启用后以下命令无法再使用

1. create table … select …

```
mysql> create table dept select * from departments;
ERROR 1786 (HY000): Statement violates GTID consistency: CREATE TABLE ... SELECT.
```
* 因为实际上是两个独立事件, 所以只能将其拆分先建立表, 然后再把数据插入到表中

2. create temporary table

* 事务内部不能创建临时表
```
mysql> begin;
Query OK, 0 rows affected (0.00 sec)

mysql> create temporary table dept(id int);
ERROR 1787 (HY000): Statement violates GTID consistency: CREATE TEMPORARY TABLE and DROP TEMPORARY TABLE can only be executed outside transactional context.  These statements are also not allowed in a function or trigger because functions and triggers are also considered to be multi-statement transactions.
```

3. 同一事务中更新事务表与非事务表(MyISAM)

```
mysql> CREATE TABLE `dept_innodb` (id INT(11) UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT);
Query OK, 0 rows affected (0.04 sec)

mysql> CREATE TABLE `dept_myisam` (id INT(11) UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT)   ENGINE = `MyISAM`;
Query OK, 0 rows affected (0.03 sec)

mysql> begin;
Query OK, 0 rows affected (0.00 sec)

mysql> insert into dept_innodb(id) value(1);
Query OK, 1 row affected (0.00 sec)

mysql> insert into dept_myisam(id) value(1);
ERROR 1785 (HY000): Statement violates GTID consistency: Updates to non-transactional tables can only be done in either autocommitted statements or single-statement transactions, and never in the same statement as updates to transactional tables.
```

* 所以建议选择Innodb作为默认的数据库引擎


### ODBC Driver and Data Source
```
  $ odbcinst -j
unixODBC 2.3.1
DRIVERS............: /etc/odbcinst.ini
SYSTEM DATA SOURCES: /etc/odbc.ini
FILE DATA SOURCES..: /etc/ODBCDataSources
USER DATA SOURCES..: /home/user-name/.odbc.ini
SQLULEN Size.......: 8
SQLLEN Size........: 8
SQLSETPOSIROW Size.: 8
```


### References
[CSDN: LINUX安装ODBC驱动](https://blog.csdn.net/dongweizu33/article/details/54616258)<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
