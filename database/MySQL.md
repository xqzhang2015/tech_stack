<!-- MarkdownTOC -->

- [GTID\(Global Transaction IDentifier\)](#gtidglobal-transaction-identifier)
    - [简介](#%E7%AE%80%E4%BB%8B)
    - [GTID Limits](#gtid-limits)
- [ODBC Driver and Data Source](#odbc-driver-and-data-source)
- [Connect timeout](#connect-timeout)
- [Globalization: timezone switch](#globalization-timezone-switch)
  - [concepts](#concepts)
    - [夏令时: daylight-saving time\(DST\) or summer time](#%E5%A4%8F%E4%BB%A4%E6%97%B6-daylight-saving-timedst-or-summer-time)
    - [冬令时: winter time](#%E5%86%AC%E4%BB%A4%E6%97%B6-winter-time)
    - [Example: Daylight Saving Time Changes 2018 in New York, New York, USA](#example-daylight-saving-time-changes-2018-in-new-york-new-york-usa)
  - [Approach of calculating local timezone: MySQL loading zoneinfo database](#approach-of-calculating-local-timezone-mysql-loading-zoneinfo-database)
    - [Populating the Time Zone Tables](#populating-the-time-zone-tables)
    - [Get shifting seconds for a timezone: 时间差](#get-shifting-seconds-for-a-timezone-%E6%97%B6%E9%97%B4%E5%B7%AE)
    - [Issue trouble shooting: CONVERT_TZ\(\) returns null](#issue-trouble-shooting-convert_tz-returns-null)
- [References](#references)

<!-- /MarkdownTOC -->

# [GTID(Global Transaction IDentifier)](https://blog.csdn.net/solarison/article/details/60468505)
### 简介

---
基于GTID的复制是MySQL 5.6后新增的复制方式.

GTID (global transaction identifier) 即全局事务ID, 保证了在每个在主库上提交的事务在集群中有一个唯一的ID.

在原来基于日志的复制中, 从库需要告知主库要从哪个偏移量进行增量同步, 如果指定错误会造成数据的遗漏, 从而造成数据的不一致.

而基于GTID的复制中, 从库会告知主库已经执行的事务的GTID的值, 然后主库会将所有未执行的事务的GTID的列表返回给从库. 并且可以保证同一个事务只在指定的从库执行一次.

### GTID Limits

---
`enforce_gtid_consistency` 强制GTID一致性, 启用后以下命令无法再使用

1. __create table … select …__

```
mysql> create table dept select * from departments;
ERROR 1786 (HY000): Statement violates GTID consistency: CREATE TABLE ... SELECT.
```
* 因为实际上是两个独立事件, 所以只能将其拆分先建立表, 然后再把数据插入到表中

2. __create temporary table__

* 事务内部不能创建临时表
```
mysql> begin;
Query OK, 0 rows affected (0.00 sec)

mysql> create temporary table dept(id int);
ERROR 1787 (HY000): Statement violates GTID consistency: CREATE TEMPORARY TABLE and DROP TEMPORARY TABLE can only be executed outside transactional context.  These statements are also not allowed in a function or trigger because functions and triggers are also considered to be multi-statement transactions.
```

* __How to solve it?__

calling `set autocommit = 1` before executing it.

3. __同一事务中更新事务表与非事务表(MyISAM)__

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


# ODBC Driver and Data Source
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

# Connect timeout

* SQL_ATTR_CONNECTION_TIMEOUT (ODBC 3.0)	

```
An SQLUINTEGER value corresponding to the number of seconds to wait for any request on the connection to complete before returning to the application. The driver should return SQLSTATE HYT00 (Timeout expired) anytime that it is possible to time out in a situation not associated with query execution or login.

If ValuePtr is equal to 0 (the default), there is no timeout.
```

```
+       rc = SQLSetConnectAttr(hdbc_, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)10, 0);
```

https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqlsetconnectattr-function?view=sql-server-2017

# Globalization: timezone switch

## concepts
The primary reason that Daylight Saving Time is a part of many societies is simply because people like to enjoy long summer evenings.
In summer, sunrise is earlier. 

Starting in 2007, DST begins in the United States on __the second Sunday in March__, when people move their clocks forward an hour at 2 a.m. local standard time (so at 2 a.m. on that day, the clocks will then read 3 a.m. local daylight time). Daylight saving time ends on __the first Sunday in November__, when clocks are moved back an hour at 2 a.m. local daylight time (so they will then read 1 a.m. local standard time).

### 夏令时: daylight-saving time(DST) or summer time
### 冬令时: winter time
### Example: Daylight Saving Time Changes 2018 in New York, New York, USA

|| Year ||	DST Start (Clock Forward) || DST End (Clock Backward) ||
| 2017 | Sunday, March 12, 2:00 am | Sunday, November 5, 2:00 am |
| 2018 | Sunday, March 11, 2:00 am | Sunday, November 4, 2:00 am |
| 2019 | Sunday, March 10, 2:00 am | Sunday, November 3, 2:00 am |

## Approach of calculating local timezone: MySQL loading zoneinfo database

If your system has its own zoneinfo database (the set of files describing time zones), you should use the __mysql_tzinfo_to_sql__ program for filling __the time zone tables__. Examples of such systems are Linux, FreeBSD, Solaris, and macOS. One likely location for these files is the __/usr/share/zoneinfo__ directory.

### Populating the Time Zone Tables

The __mysql_tzinfo_to_sql__ program is used to load the time zone tables. On the command line, pass the zoneinfo directory path name to __mysql_tzinfo_to_sql__ and send the output into the mysql program. For example:

```
shell> mysql_tzinfo_to_sql /usr/share/zoneinfo | mysql -u root mysql
```

If not, download the package from MySQL Developer Zone:
https://dev.mysql.com/downloads/timezones.html


* Checking if one MySQL DB contains the zoneinfo data:

```
select CONVERT_TZ(NOW(),'SYSTEM','GMT');
2018-10-28 16:12:01

select CONVERT_TZ(NOW(),'SYSTEM','Asia/Chongqing');
2018-10-29 00:12:01

select UNIX_TIMESTAMP(CONVERT_TZ(NOW(),'SYSTEM', 'Asia/Chongqing'))
-
UNIX_TIMESTAMP(CONVERT_TZ(NOW(),'SYSTEM','GMT'));

28800
```

28800 = 8 * 60 * 60 (seconds)

### Get shifting seconds for a timezone: 时间差
Given a timezone name, like Pacific/Honolulu(US/Hawaii), America/Chicago, Asia/Chongqing, 
```
UNIX_TIMESTAMP(CONVERT_TZ(NOW(),'SYSTEM',tz_name))
-
UNIX_TIMESTAMP(CONVERT_TZ(NOW(),'SYSTEM','GMT'))
```

### Issue trouble shooting: CONVERT_TZ() returns null

This will happen if you haven't loaded the time zone table into mysql.

```
mysql_tzinfo_to_sql /usr/share/zoneinfo | mysql -u root -p mysql
```


# References
[CSDN: LINUX安装ODBC驱动](https://blog.csdn.net/dongweizu33/article/details/54616258)<br/>
[dev.mysql.com: MySQL Server Time Zone Support](https://dev.mysql.com/doc/refman/8.0/en/time-zone-support.html)<br/>
[]()<br/>
[]()<br/>
[]()<br/>
