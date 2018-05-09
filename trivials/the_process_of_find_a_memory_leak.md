# The Process of figure out memory leak issue
### Issue
The memory of one server is always increasing and higher than others.

### Suspect
Some kind of memory leak maybe happen or some kind of traffic should be different from other servers, because service binary and conf are same with other servers.

### Process
利用gdb打印内存信息并从信息中观察可能的内存泄漏点。

1. pmap -x {PID}
如：pmap -x 24671；得到类似如下信息，注意标记为anon的位置：
![memory_1](../images/2018/memory_1.png)


2. 启动gdb ./bin/broker并使用 attach {PID}命令加载现有进程
例如上述进程号为24671，则使用：attach 24671；

3. 使用setheight 0和 setlogging on开启gdb日志
日志将存储于gdb.txt文件中；

4. 使用x/{内存字节数}a {内存地址} 打印出一段内存信息
例如上述的anon为堆头地址，占用了144508kb内存，则使用：x/18497024a0x000000000109d000；
若命令行较多，可以在外围编辑好命令行直接张贴至gdb命令行提示符中运行，或者将命令行写到一个文本文件中，例如command.txt中，
然后再gdb命令行提示符中使用 source command.txt来执行文件中的命令集合，下面是command.txt文件的内容:
![memory_2](../images/2018/memory_2.png)

5. 分析gdb.txt文件中的信息，gdb.txt中的内容如下：
![memory_3](../images/2018/memory_3.png)

Gdb.txt中内容的说明和分析：第一列为当前内存地址，如0x22c2f00；第二、三、四列分别为当前内存地址对应所存储的值（使用十六进制表示），以及gdb的debug的符号信息，例如：0x10200d0<_ZTVN7bigpipe15BigpipeDIEngineE+16> 0x4600000001，分别表示：“前16字节”、“符号信息（注意有+16的偏移）”、“后16字节”，但不是所有地址都会打印gdb的debug符号信息，有时符号信息显示在第三列，有时显示在第二列。

....

### References
There is one memory leak bug in mysql-connector-odbc-5.2.5-6.el7.x86_64,
described in https://bugs.mysql.com/bug.php?id=70113
<br/>
[利用进程信息追查内存泄漏](https://blog.csdn.net/baidu_mtc/article/details/50504608)

<br/>


<br/>


<br/>


<br/>


<br/>
