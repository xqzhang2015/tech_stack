Brief introduction

* Shared library is .so(shared object) <br/>
** gcc -c -Wall -Werror -fpic foo.c <br/>
** g++ --shared -o libfoo.so foo.o <br/>
** gcc -L/home/username/foo -Wall -o test main.c -lfoo <br/>
** ldd main

* Static library is .a(archive file). <br/>
** g++ -c foo_a.cpp foo_b.cpp foo_c.cpp <br/>
** ar -rc libfoo.a foo_a.o foo_b.o foo_c.o <br/>
** g++ main.cpp -L. -lfoo -o main <br/>
** nm -s main

<!-- MarkdownTOC -->

- [Compile foo library](#compile-foo-library)
  - [将这几个文件编译成动态库 libfoo.so](#%E5%B0%86%E8%BF%99%E5%87%A0%E4%B8%AA%E6%96%87%E4%BB%B6%E7%BC%96%E8%AF%91%E6%88%90%E5%8A%A8%E6%80%81%E5%BA%93-libfooso)
  - [将main.cpp与libfoo.so链接成一个可执行文件main](#%E5%B0%86maincpp%E4%B8%8Elibfooso%E9%93%BE%E6%8E%A5%E6%88%90%E4%B8%80%E4%B8%AA%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6main)
  - [Step 1: Compiling with Position Independent Code](#step-1-compiling-with-position-independent-code)
  - [Step 2: Creating a shared library from an object file](#step-2-creating-a-shared-library-from-an-object-file)
  - [Step 3: Linking with a shared library](#step-3-linking-with-a-shared-library)
  - [Step 4: Making the library available at runtime](#step-4-making-the-library-available-at-runtime)
    - [1. Using env variable LD_LIBRARY_PATH, work for one user](#1-using-env-variable-ld_library_path-work-for-one-user)
    - [2. System conf, work for all users](#2-system-conf-work-for-all-users)
  - [check result](#check-result)
  - [dynamic on-demand load shared library](#dynamic-on-demand-load-shared-library)
    - [Making C++ Shared Libraries](#making-c-shared-libraries)
- [Compile static library](#compile-static-library)
  - [编译静态库: an archive](#%E7%BC%96%E8%AF%91%E9%9D%99%E6%80%81%E5%BA%93-an-archive)
  - [使用 ar 命令创建静态库文件](#%E4%BD%BF%E7%94%A8-ar-%E5%91%BD%E4%BB%A4%E5%88%9B%E5%BB%BA%E9%9D%99%E6%80%81%E5%BA%93%E6%96%87%E4%BB%B6)
  - [链接静态库](#%E9%93%BE%E6%8E%A5%E9%9D%99%E6%80%81%E5%BA%93)
  - [使用nm -s 命令来查看.a文件的内容](#%E4%BD%BF%E7%94%A8nm--s-%E5%91%BD%E4%BB%A4%E6%9D%A5%E6%9F%A5%E7%9C%8Ba%E6%96%87%E4%BB%B6%E7%9A%84%E5%86%85%E5%AE%B9)

<!-- /MarkdownTOC -->

# Compile foo library
### 将这几个文件编译成动态库 libfoo.so
编译命令如下：

```
g++ foo_a.cpp foo_b.cpp foo_c.cpp -fpic -shared -o libfoo.so
```

参数说明：

* -shared：该选项指定生成动态连接库
* -fpic：表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的所以动态载入时是通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码段共享的目的。


### 将main.cpp与libfoo.so链接成一个可执行文件main
命令如下：

``` 
g++ main.cpp -L. -lfoo -o main
```

参数说明：

* -L.：表示要连接的库在当前目录中
* -lfoo：编译器查找动态连接库时有隐含的命名规则，即在给出的名字前面加上lib，后面加上.so来确定库的名称


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

* This is not arbitrary - shared libraries should be called __lib\<name\>.so__ for them to link properly later on (as we’ll see in the linking section below).

### Step 3: Linking with a shared library
* Telling GCC where to find the shared library

```
$ gcc -L/home/username/foo -Wall -o test main.c -lfoo
```

* Note that paths specified by __-L__ only affect the search path when linking - not during runtime. We’ll specify the current directory:

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
export DYLD_LIBRARY_PATH=$(pwd):$DYLD_LIBRARY_PATH
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
	libfoo.so => /home/xxx/docker/tech_stack/program/code_library/libfoo.so (0x00007fd0c400f000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fd0c3cf6000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fd0c39f4000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fd0c37de000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fd0c341c000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fd0c4212000)
```

* ldd only output __Shared Libraries__, not including __Static Libraries__.

```
SYNOPSIS
       ldd [OPTION]... FILE...
NAME
       ldd - print shared library dependencies
```

### dynamic on-demand load shared library: dlopen and dlsym

1. generate shared library: libfoo.so, better only with __gcc__.

`gcc -shared -fPIC -o libfoo.so foo_a.c foo_b.c foo_c.c`

2. g++ or gcc is both ok.

`gcc main_dlsym.c -ldl -o main_dlsym`

##### Making C++ Shared Libraries
In order to work with C++, you need to understand C++ name mangling. A C++ compiler essentially converts all your method calls into C functions with the name mangled so that it resolves to the correct method.

In general, 

* you do not need to do anything special to use C++ libraries, 
* but you need to be careful when mixing straight C and C++. 

If you are calling and compiling C code with a C++ compiler, you need to make sure that the C++ compiler does not mangle the name by wrapping your C function declarations such as:
```
#ifdef  __cplusplus
extern "C" {
#endif

int my_c_function();

#ifdef  __cplusplus
}
#endif
```

For example,

* gcc -shared -fPIC -o libfoo.so foo_a.c foo_b.c foo_c.c

`nm -s libfoo.so` will output,

```
0000000000000708 T foo_a
000000000000071c T foo_b
0000000000000730 T foo_c
```

* g++ -shared -fPIC -o libfoo.so foo_a.c foo_b.c foo_c.c

`nm -s libfoo.so` will output,

```
0000000000000738 T _Z5foo_av
000000000000074c T _Z5foo_bv
0000000000000760 T _Z5foo_cv
```

__So dlsym() need to use \_Z5foo\_av, instead of foo_a__.


* __C++ compiler has issue when compiling c codes library__

# Compile static library

* __Static Libraries are linked into a compiled executable (or another library)__.

### 编译静态库: an archive

```
g++ -c foo_a.cpp foo_b.cpp foo_c.cpp
```

### 使用 ar 命令创建静态库文件

```
ar -rc libfoo.a foo_a.o foo_b.o foo_c.o  //cr标志告诉ar将object文件封装(archive)
```

```
NAME
    ar - create, modify, and extract from archives

SYNOPSIS
    ar [--plugin name] [-X32_64] [-]p[mod [relpos] [count]] [--target bfdname] archive [member...] 

 
The p keyletter specifies what operation to execute; it may be any of the following, but you must specify only one of them:
	r   Insert the files member... into archive (with replacement).

A number of modifiers (mod) may immediately follow the p keyletter, to specify variations on an operation's behavior:    
	c   Create the archive.
```

### 链接静态库

```
$:~/docker/tech_stack/program/code_library(master)$ g++ main.cpp -L. -lfoo -o main
```

If lib is not found, `-static` could be append.

Notes:

`libfoo.a` must be named with prefix __lib__.

### 使用nm -s 命令来查看.a文件的内容

```
nm -s libfoo.a
```

# References

[Shared Library Mini-Tutorial](http://ehuss.com/shared/)<br/>

* In order to work with C++, you need to understand C++ name mangling. 


[Shared Libraries: Understanding Dynamic Loading](https://amir.rachum.com/blog/2016/09/17/shared-libraries/#debugging-cheat-sheet)<br/>




