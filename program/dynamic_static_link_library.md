<!-- MarkdownTOC -->

- [MySQL library](#mysql-library)
  - [Architecture](#architecture)
  - [Workflow](#workflow)
  - [First call: SQLDriverConnect](#first-call-sqldriverconnect)
  - [References](#references)

<!-- /MarkdownTOC -->

# MySQL library

### Architecture

![mysql_driver](../images/2018/mysql_driver.png)


```

			[Driver Manager]
				|
		   [Driver conf: /etc/odbcinst.ini]
				|
	  +----------+----------+---------------------+-----------------------+
 	  |	     |  	|	  	      |			      |
      [PostgreSQL] [MySQL] [MySQL ANSI Driver]   [MySQL Unicode Driver]     [...]
          	     |
          	     |
     		 [DataBase]
```    

[The unixODBC Project home page](http://www.unixodbc.org/)<br/>

### Workflow
Driver manager: /lib64/libodbc.so.2

1. SQLDriverConnect(,,,
		    dsn.str, dsn.length, ...)
==> parsing

dsn='DRIVER=MySQL;...'

__For "DRIVER" in dsn.str, which is MySQL, get Driver or Driver64 from [MySQL]__

\# cat /etc/odbcinst.ini

```
[MySQL]
Description=ODBC for MySQL
Driver=/usr/lib64/libmyodbc5w.so
Driver64=/usr/lib64/libmyodbc5w.so
Setup=/usr/lib64/libodbcmyS.so
Setup64=/usr/lib64/libodbcmyS.so
FileUsage=1
```

2. For driver `Driver64=/usr/lib64/libmyodbc5w.so`,

==> dlopen() & dlsym()

All related *.so will be linked.

3. ==> ldd

```
tech_stack/program/code_library(master)$ ldd /usr/lib64/libmyodbc5w.so
	linux-vdso.so.1 =>  (0x00007fff74dfe000)
	libodbc.so.2 => /lib64/libodbc.so.2 (0x00007fa27244e000)
	libmysqlclient.so.18 => /usr/lib64/mysql/libmysqlclient.so.18 (0x00007fa271f4e000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fa271d32000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fa271a30000)
	libodbcinst.so.2 => /lib64/libodbcinst.so.2 (0x00007fa27181d000)
	...
```
### First call: SQLDriverConnect

```
tech_stack/program/code_library(master)$ readelf -s /lib64/libodbc.so.2.0.0 | grep SQLDriverConnect
   192: 0000000000014590    21 FUNC    GLOBAL DEFAULT   11 SQLDriverConnectA
   224: 000000000002ce50  3644 FUNC    GLOBAL DEFAULT   11 SQLDriverConnectW
   226: 0000000000012eb0  5850 FUNC    GLOBAL DEFAULT   11 SQLDriverConnect
```


### References
[cnblogs: C/C++ 静态链接库(.a) 与 动态链接库(.so)](https://www.cnblogs.com/52php/p/5681711.html)<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
