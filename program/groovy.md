<!-- MarkdownTOC -->

- [Introduction](#introduction)
- [Groovy 数据类型](#groovy-%E6%95%B0%E6%8D%AE%E7%B1%BB%E5%9E%8B)
  - [Java 基本类型](#java-%E5%9F%BA%E6%9C%AC%E7%B1%BB%E5%9E%8B)
  - [Groovy 容器](#groovy-%E5%AE%B9%E5%99%A8)
  - [Code examples](#code-examples)
    - [Flow control](#flow-control)
    - [Groovy containers](#groovy-containers)
    - [Groovy closure](#groovy-closure)
- [References](#references)

<!-- /MarkdownTOC -->

# Introduction
Groovy是一种动态语言，它和Java类似（算是Java的升级版，但是又具备脚本语言的特点），都在Java虚拟机中运行。

当运行Groovy脚本时它会先被编译成Java类字节码，然后通过JVM虚拟机执行这个Java字节码类。

# Groovy 数据类型

Groovy中的数据类型主要分2种

* 一个是Java中的基本数据类型。

* 另外一个是Groovy中的容器类。

最后一个非常重要的是闭包。

### Java 基本类型

```
def boolean s1 = true

def int s2 = 100

def String s3 = "hello world"

if (s1) {
    println("hello world")
}
```

### Groovy 容器

```
List：链表，其底层对应Java中的List接口，一般用ArrayList作为真正的实现类。 
Map：键-值表，其底层对应Java中的LinkedHashMap。 
Range：范围，它其实是List的一种拓展。
```

### Code examples


##### Flow control
```
/* Hello World in Groovy */
println("Hello world")


println("\n========Flow control: if========")
def ss = "groovy"
if (ss == "groovy") {
    println("I am ${ss}")
}

println("\n========Flow control: for========")
for (i = 0; i <= 3; i++) {
    println("Test ${i}th")
}
println()
for (i in 1..3) {
    println("Test ${i}th")
}

println("\n========Flow control: switch========")
age = 37
def rate

switch (age) {
    case 10..25:
        rate = 0.05
        break
    case 26..35:
        rate = 0.06
        break
    case 36..45:
        rate = 0.07
        break
    default:
        throw new IllegalArgumentException()
}

println("The rate is ${rate}\n")
```

##### Groovy containers

```
/* Groovy 容器
List：链表，其底层对应Java中的List接口，一般用ArrayList作为真正的实现类。 
Map：键-值表，其底层对应Java中的LinkedHashMap。 
Range：范围，它其实是List的一种拓展。
*/

// list
println("\n========Container: list========")
def list = [true, false, "Hellow world", 1.1, 10]

println list
println '\n'

println("list[0]: " + list[0])
println("list[0]: ${list[0]}")

println(list[2])
println(list[4])

println("List length: " + list.size())

list[10] = 10.1
list << 10.2
println("${list}")

println("\n========Container: map========")
def map = ['10': "value1"
            , 10: "value2"
            , key3: "value3"]
println map
println map.keySet()

println("数据长度：" + map.size())
//数据长度：3

println(map.keySet())
//[key1, key2, key3]

println(map.values())
//[value1, value2, value3]

println("key1的值：" + map.key1)
//key1的值：value1

println("key1的值：" + map.get("key1"))
//key1的值：value1

//赋值
map.put("key4", "value4")

Iterator it = map.iterator()
while (it.hasNext()) {
    println "遍历map: " + it.next()
}

//遍历map: key1=value1
//遍历map: key2=value2
//遍历map: key3=value3
//遍历map: key4=value4

map.containsKey("key1") //判断map是否包含某个key

map.containsValue("values1")  //判断map是否包含某个values

map.clear()  //清除map里面的内容

Set set = map.keySet(); //把 map 的key值转换为 set

println("\n========Container: range========")
def range = 1..10
println(range)
println range.from
println range.to
```

##### Groovy closure

```
println("\n========Closure========")
def closure = { // closure is code segment, which should be included by 花括号
    String param1, double param2 -> // -> is critical, before it: params, after it: code
    println "I am a closure, How are you?\n\tHere are the params: ${param1}, ${param2}"
}

println("\n说实话，从C/C++语言的角度看，闭包和函数指针很像。\n")

// 简而言之，Closure的定义格式是：
// def xxx = {paramters -> code} 
// or
// def xxx = {无参数，纯code}
closure.call("I am the 1st param", 10)
closure("I am the 1st param", 10)

// Groovy中，当函数的最后一个参数是闭包的话，可以省略圆括号
def fun(int a1,String b1, Closure closure){  
      //dosomething  
     closure(a1, b1) //调用闭包  
}

fun 4, "test", {
    int i, String s ->
    println "I am in closure, ${i}, ${s}\n"
}

##### Groovy IO

```
println("\n========File operations========")
def filePath = "."
def fileHandler = new File(filePath)

fileHandler.eachFileRecurse {
    println it.path
}
```

# References


[www.compileonline.com: Execute Groovy Online (Groovy v2.4.8)](http://www.compileonline.com/execute_groovy_online.php)<br/>

[CSDN: Groovy 使用完全解析](https://blog.csdn.net/zhaoyanjun6/article/details/70313790/)<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>
