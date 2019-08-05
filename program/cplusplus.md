<!-- MarkdownTOC -->

- [Algorithm](#algorithm)
  - [RB Tree](#rb-tree)
- [Some holes\(坑\) ever met](#some-holes%E5%9D%91-ever-met)
  - [lambda: anonymous function](#lambda-anonymous-function)
    - [Captured values. What you can to capture](#captured-values-what-you-can-to-capture)
    - [Return type deduction](#return-type-deduction)
  - ["Undefined reference to" template class constructor](#undefined-reference-to-template-class-constructor)
    - [Understanding the problem](#understanding-the-problem)
    - [General answer](#general-answer)
    - [Edge answer](#edge-answer)
  - [error: member access into incomplete type](#error-member-access-into-incomplete-type)
  - [MySQL charset: varchar vs text](#mysql-charset-varchar-vs-text)
- [References](#references)

<!-- /MarkdownTOC -->

# Algorithm
## RB Tree

C++ STL中标准关联容器set, multiset, map,multimap内部采用的就是一种非常高效的平衡检索二叉树：红黑树，也成为RB树(Red-Black Tree)。


# Some holes(坑) ever met

## lambda: anonymous function

https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11

### Captured values. What you can to capture

1.1. You can reference to a variable with static storage duration in lambdas. They all are captured.

1.2. You can use lambda for capture values "by value". In such case captured vars will be copied to the function object (closure).

```cpp
[captureVar1,captureVar2](int arg1){}
```

1.3. You can capture be reference. & -- in this context mean reference, not pointers.

```cpp
   [&captureVar1,&captureVar2](int arg1){}
```

1.4. It exists notation to capture all non-static vars by value, or by reference

```cpp
  [=](int arg1){} // capture all not-static vars by value

  [&](int arg1){} // capture all not-static vars by reference
```

1.5. It exists notation to capture all non-static vars by value, or by reference and specify smth. more. Examples: Capture all not-static vars by value, but by reference capture Param2

```cpp
[=,&Param2](int arg1){} 
```

Capture all not-static vars by reference, but by value capture Param2

```cpp
[&,Param2](int arg1){} 
```

### Return type deduction


## "Undefined reference to" template class constructor

https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor


### Understanding the problem

he problem is caused by the fact that main.cpp and cola.cpp will be compiled separately first. In  main.cpp, the compiler will implicitly instantiate the template classes cola<float> and cola<string> because those particular instantiations are used in main.cpp.

### General answer

The common answer is to move all the code from the implementation files cola.cpp and nodo_colaypila.cpp into cola.h and nodo_colaypila.h. In the long run, this is more flexible as it means you can use extra instantiations (e.g. cola<char>) without any more work. But it could mean the same functions are compiled many times, once in each translation unit. This is not a big problem, as the linker will correctly ignore the duplicate implementations. But it might slow down the compilation a little.



### Edge answer

* Explicitly instantiate the template, and its member definitions


At the end of cola.cpp,

```cpp
template class cola<float>;
template class cola<string>;
```

## error: member access into incomplete type

https://stackoverflow.com/questions/19962812/error-member-access-into-incomplete-type-forward-declaration-of

* Move ___doSomething___ definition outside of its class declaration and after B and also make add accessible to A by ___public-ing___ it or ___friend-ing___ it.

```cpp
class B;

class A
{
    void doSomething(B * b);
};

class B
{
public:
    void add() {}
};

void A::doSomething(B * b)
{
    b->add();
}
```

## MySQL charset: varchar vs text

* Case
Column `praram_value` changes from varchar(2048) to text. If all records of column `praram_value` are stored for long-duration, __memory size will increase a lot, even lead to OOM__.

* Analysis

1. varchar(2048): if charset is utf-8, we usually set `char param_value[2048\*3+1]`.
2. text: we usually set `char param_value[]`.

# References
[STL中map、set的数据结构及底层实现](http://blog.csdn.net/PirLCK/article/details/51326547)

[print: Linux内核spin_lock与spin_lock_irq分析](https://blog.csdn.net/zhanglei4214/article/details/6837697)

[]()

[]()


[]()


[]()
