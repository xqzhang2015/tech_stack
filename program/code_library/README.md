<!-- MarkdownTOC -->

- [compile dynamic library](#compile-dynamic-library)
  - [Step 1: Compiling with Position Independent Code](#step-1-compiling-with-position-independent-code)
  - [Step 2: Creating a shared library from an object file](#step-2-creating-a-shared-library-from-an-object-file)
  - [Step 3: Linking with a shared library](#step-3-linking-with-a-shared-library)
  - [Step 4: Making the library available at runtime](#step-4-making-the-library-available-at-runtime)
    - [1. Using env variable LD_LIBRARY_PATH, work for one user](#1-using-env-variable-ld_library_path-work-for-one-user)
    - [2. System conf, work for all users](#2-system-conf-work-for-all-users)
  - [check result](#check-result)
  - [Notes](#notes)
- [compile static library](#compile-static-library)

<!-- /MarkdownTOC -->

# compile dynamic library
将这几个文件编译成动态库libdynamic.so。编译命令如下：

```
g++ dynamic_a.cpp dynamic_b.cpp dynamic_c.cpp -fpic -shared -o libdynamic.so
```

参数说明：

* -shared：该选项指定生成动态连接库
* -fPIC：表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的所以动态载入时是通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码段共享的目的。


将main.cpp与libdynamic.so链接成一个可执行文件main。命令如下：

``` 
g++ main.cpp -L. -ldynamic -o main
```

参数说明：

* -L.：表示要连接的库在当前目录中
* -ldynamic：编译器查找动态连接库时有隐含的命名规则，即在给出的名字前面加上lib，后面加上.so来确定库的名称


or

### Step 1: Compiling with Position Independent Code
We need to compile our library source code into __position-independent code (PIC)__:

```
$ gcc -c -Wall -Werror -fpic foo.c
```

### Step 2: Creating a shared library from an object file
Now we need to actually turn this object file into a shared library. We will call it libfoo.so:

```
gcc -shared -o libfoo.so foo.o
```

### Step 3: Linking with a shared library
* Telling GCC where to find the shared library

```
$ gcc -L/home/username/foo -Wall -o test main.c -lfoo
```

### Step 4: Making the library available at runtime
##### 1. Using env variable LD_LIBRARY_PATH, work for one user

```
$ echo $LD_LIBRARY_PATH
```

* In __Linux__, if you don't export the changes to an environment variable, they won't be inherited by the child processes. 

```
$ export LD_LIBRARY_PATH=${pwd}:$LD_LIBRARY_PATH
$ ./test
```
or In __Mac-OS__,

```
export DYLD_LIBRARY_PATH=$HOME/Desktop/codes/tech_stack/program/code_library:$DYLD_LIBRARY_PATH
```

Last, `unset LD_LIBRARY_PATH`.

##### 2. System conf, work for all users

Here are some approaches,

2.1 put the library in a standard location

probably /usr/lib or /usr/local/lib, then you will need to modify the ld.so config file and cache. As __root__, do the following:

```
$ cp /home/username/foo/libfoo.so /usr/lib
$ chmod 0755 /usr/lib/libfoo.so
```

Last, we need to tell the loader it's available for use.

```
$ sudo ldconfig


$ ldconfig -p | grep foo
libfoo.so (libc6) => /usr/lib/libfoo.so
```


2.2 Modify /etc/ld.so.conf

在新的一行中加入库文件所在目录；比如笔者应添加：

```
/home/neu/code/Dynamic_library
```

Then run `sudo ldconfig`.

2.3 Add another xxx.conf into this folder

```
tech_stack/program/code_library(master)$ ls /etc/ld.so.conf.d/
atlas-x86_64.conf  dyninst-x86_64.conf  kernel-3.10.0-229.el7.x86_64.conf  llvm5.0-x86_64.conf  llvm-x86_64.conf  mariadb-x86_64.conf
```

Then run `sudo ldconfig`.

### check result

```
tech_stack/program/code_library(master)$ ldd main
	linux-vdso.so.1 =>  (0x00007fffa7508000)
	libdynamic.so => /home/xqzhang/docker/tech_stack/program/code_library/libdynamic.so (0x00007fd0c400f000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fd0c3cf6000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fd0c39f4000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fd0c37de000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fd0c341c000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fd0c4212000)
```

### Notes

* 





# compile static library