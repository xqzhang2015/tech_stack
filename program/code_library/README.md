
### compile dynamic library
将这几个文件编译成动态库libdynamic.so。编译命令如下：

```
g++ dynamic_a.cpp dynamic_b.cpp dynamic_c.cpp -fPIC -shared -o libdynamic.so
```

