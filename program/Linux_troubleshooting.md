<!-- MarkdownTOC -->

- [Linux system](#linux-system)
  - [netstat -apn](#netstat--apn)
  - [top -o %MEM](#top--o-%25mem)
- [Linux process](#linux-process)
  - [gdb prog procID](#gdb-prog-procid)
  - [ldd](#ldd)
  - [pmap -x pid](#pmap--x-pid)
  - [pstack pid](#pstack-pid)
  - [nm objfile...](#nm-objfile)

<!-- /MarkdownTOC -->

# Linux system
### netstat -apn
### top -o %MEM

# Linux process
### gdb prog procID

* NAME<br/>
	gdb - The GNU Debugger

* SYNOPSIS<br/>
gdb [-help] [-nh] [-nx] [-q] [-batch] __[-cd=dir]__ [-f] [-b bps]<br/>
           [-tty=dev] [-s symfile] [-e prog] [-se prog] [-c core] __[-p procID]__<br/>
           __[-x cmds]__ __[-d dir]__ __[prog|prog procID|prog core]__<br/>


You can run "gdb" with no arguments or options; but the most usual way to start GDB is with one argument or two, specifying an executable program as the argument:

       gdb program, then run attach PID, enter continue

You can also start with both an executable program and a core file specified:

       gdb program core

You can, instead, specify a process ID as a second argument, if you want to debug a running process:

       gdb program 1234<br/>
       __gdb -p 1234__

* cmds file example

```shell
# test.gdb
source stl-views-1.0.3.gdb
file test
set args 'a' 'b' ccc
directory /xxx/src

b test.cpp:100
b ClassA::test

set print element 0
```

### ldd

* NAME<br/>
	ldd - print shared library dependencies

* SYNOPSIS<br/>
	ldd [OPTION]... FILE...

* OPTIONS<br/>
	-v --verbose<br/>
	      Print all information, including, for example, symbol versioning information.

```shell
(master)# ldd  abc
	libssl.so.10 => /lib64/libssl.so.10 (0x00007f16f0787000)
	libodbc.so.2 => /lib64/libodbc.so.2 (0x00007f16f051e000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f16ef8d7000)
	libxerces-c-3.1.so => /lib64/libxerces-c-3.1.so (0x00007f16ef329000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f16ef022000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f16eed20000)
	...
```

### pmap -x pid

* NAME<br/>
	pmap - report memory map of a process

* SYNOPSIS<br/>
	pmap [options] pid [...]

* OPTIONS<br/>
	-x, --extended<br/>
	      Show the extended format.<br/>
	-X     Show even more details than the -x option. WARNING: format changes according to /proc/PID/smaps<br/>
	-p, --show-path<br/>
	      Show full path to files in the mapping column<br/>

```shell
(master)# pmap -pX 56
56:   nginx: master process /xxx/nginx/nginx_binary/nginx -c /xxx/nginx/nginx_conf/nginx.conf
 Address Perm   Offset Device    Inode    Size  Rss Pss Referenced Anonymous Swap Locked Mapping
00400000 r-xp 00000000  fd:0b  1052997     732   40  10          4         0    0      0 /xxx/nginx/nginx_binary/nginx
006b7000 r--p 000b7000  fd:0b  1052997       4    4   1          0         4    0      0 /xxx/nginx/nginx_binary/nginx
006b8000 rw-p 000b8000  fd:0b  1052997      84   72  27          0        72    0      0 /xxx/nginx/nginx_binary/nginx

...

7f967d12a000 r-xp 00000000  fd:0b  1196156      88    8   0          8         0    0      0 /usr/lib64/libpthread-2.17.so
7f967d140000 ---p 00016000  fd:0b  1196156    2048    0   0          0         0    0      0 /usr/lib64/libpthread-2.17.so
7f967d340000 r--p 00016000  fd:0b  1196156       4    4   1          0         4    0      0 /usr/lib64/libpthread-2.17.so
7f967d341000 rw-p 00017000  fd:0b  1196156       4    4   4          0         4    0      0 /usr/lib64/libpthread-2.17.so
```

### pstack pid

* NAME<br/>
	gstack - __print__ a stack trace of a running process

* SYNOPSIS<br/>
	gstack pid

* SEE ALSO<br/>
       nm(1), ptrace(2), gdb(1)

```shell
~$ which pstack
/usr/bin/pstack
~$ ll /usr/bin/pstack
lrwxrwxrwx. 1 root root 6 Jun  7  2016 /usr/bin/pstack -> gstack
```

### nm objfile...

* NAME<br/>
	nm - list symbols from object files

```shell
0000000000401200 W _Z10mergeSort2IiEvPT_i
0000000000401787 W _Z11mergeSorti2IiEvPT_S1_ii
```