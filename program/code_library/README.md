<!-- MarkdownTOC -->

- [compile dynamic library](#compile-dynamic-library)
  - [Step 1: Compiling with Position Independent Code](#step-1-compiling-with-position-independent-code)
  - [Step 2: Creating a shared library from an object file](#step-2-creating-a-shared-library-from-an-object-file)
  - [Step 3: Linking with a shared library](#step-3-linking-with-a-shared-library)
  - [Step 4: Making the library available at runtime](#step-4-making-the-library-available-at-runtime)
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
Using LD_LIBRARY_PATH

```
$ echo $LD_LIBRARY_PATH
```

* In Linux, if you don't export the changes to an environment variable, they won't be inherited by the child processes. 

```
$ export LD_LIBRARY_PATH=/home/username/foo:$LD_LIBRARY_PATH
$ ./test
```
or

```
export DYLD_LIBRARY_PATH=$HOME/Desktop/codes/tech_stack/program/code_library:$DYLD_LIBRARY_PATH
```


__Notes__:

* 





# compile static library