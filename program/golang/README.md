<!-- MarkdownTOC -->

- [Golang spec](#golang-spec)
  - [Expressions](#expressions)
    - [Type assertions](#type-assertions)
      - [s := x.\(string\) VS s, ok := x.\(string\)](#s--xstring-vs-s-ok--xstring)
    - [Variadic params: Passing arguments to ... parameters](#variadic-params-passing-arguments-to--parameters)
    - [reflection](#reflection)
- [golang ORM: db-first vs code-first](#golang-orm-db-first-vs-code-first)
  - [db-first: sqlboiler](#db-first-sqlboiler)
  - [code-first: gorm](#code-first-gorm)
- [golang GC](#golang-gc)
- [protobuf](#protobuf)
  - [Installing protoc](#installing-protoc)
    - [Mac OS X](#mac-os-x)
    - [Linux](#linux)
- [Getting started: go env](#getting-started-go-env)
  - [GOROOT and GOPATH](#goroot-and-gopath)
  - [GO build](#go-build)
    - [link arguments: for app version](#link-arguments-for-app-version)
- [Go 并发](#go-%E5%B9%B6%E5%8F%91)
  - [协程同步的几种方式：goroutine synchronization](#%E5%8D%8F%E7%A8%8B%E5%90%8C%E6%AD%A5%E7%9A%84%E5%87%A0%E7%A7%8D%E6%96%B9%E5%BC%8F%EF%BC%9Agoroutine-synchronization)
    - [time.Sleep](#timesleep)
    - [channel: 管道](#channel-%E7%AE%A1%E9%81%93)
    - [sync.WaitGroup](#syncwaitgroup)
- [RPC example in go](#rpc-example-in-go)

<!-- /MarkdownTOC -->

# Golang spec

## Expressions
An expression specifies the computation of a value by applying __operators__ and __functions__ to operands.

### [Type assertions](https://golang.org/ref/spec#Type_assertions)

For an expression x of __interface type__ and a type T, the primary expression
```
x.(T)
```
asserts that x is not nil and that the value stored in x is of type T. The notation x.(T) is called a __type assertion__.

#### s := x.(string) VS s, ok := x.(string)

* s := x.(string) may lead to panic
* s, ok := x.(string) may lead to `zero value` and `false ok`.

* E.g.
```golang
package main

import (
    "fmt"
)

func main() {
    var x interface{} = 7          // x has dynamic type int and value 7
    i := x.(int)                   // i has type int and value 7
    fmt.Printf("i: %v\n", i)
    // s := x.(string)                // panic: interface conversion: interface {} is int, not string
    s, ok := x.(string)
    fmt.Printf("s: %v, ok: %v\n", s, ok) // s: , ok: false
}

```

### Variadic params: Passing arguments to ... parameters

If f is variadic with a final parameter p of type ...T, then within f the type of p is equivalent to type []T

Given the function and calls
```golang
func Greeting(prefix string, who ...string)
Greeting("nobody") // who is nil
Greeting("hello:", "Joe", "Anna", "Eileen") // who is []string{"Joe", "Anna", "Eileen"}
```

Given the slice s and call
```golang
s := []string{"James", "Jasmine"}
Greeting("goodbye:", s...)
```

* E.g.
```golang
package main

import (
    "fmt"
)

func Greeting(prefix string, who ...string) {
    fmt.Printf("========== %v ==========\n", prefix)
    if who == nil {
        return
    }

    for _, person := range who {
        fmt.Printf("%v: %v\n", prefix, person)
    }
}

func main() {
    Greeting("nobody") // who is nil
    Greeting("hello", "Joe", "Anna", "Eileen") // who is []string{"Joe", "Anna", "Eileen"}
    s := []string{"James", "Jasmine"}
    Greeting("goodbye", s...)
}
```

### reflection

* example

```golang
import (
    "reflect"
)

func (s *SuperAgent) Query(content interface{}) *SuperAgent {
    switch v := reflect.ValueOf(content); v.Kind() {
    case reflect.String:
        s.queryString(v.String())
    case reflect.Struct:
        s.queryStruct(v.Interface())
    case reflect.Map:
        s.queryMap(v.Interface())
    default:
    }
    return s
}
```

# golang ORM: db-first vs code-first

## db-first: [sqlboiler](https://github.com/volatiletech/sqlboiler)
## code-first: [gorm](https://github.com/jinzhu/gorm)

# golang GC

[Getting to Go: The Journey of Go's Garbage Collector](https://blog.golang.org/ismmkeynote)

# protobuf

## Installing protoc

### Mac OS X

```sh
brew install protobuf
```

Alternately, run the following commands:
```sh
PROTOC_ZIP=protoc-3.3.0-osx-x86_64.zip
curl -OL https://github.com/google/protobuf/releases/download/v3.3.0/$PROTOC_ZIP
sudo unzip -o $PROTOC_ZIP -d /usr/local bin/protoc
rm -f $PROTOC_ZIP
```


### Linux

```sh
PROTOC_ZIP=protoc-3.3.0-linux-x86_64.zip
curl -OL https://github.com/google/protobuf/releases/download/v3.3.0/$PROTOC_ZIP
sudo unzip -o $PROTOC_ZIP -d /usr/local bin/protoc
rm -f $PROTOC_ZIP
```


# Getting started: go env

## GOROOT and GOPATH

When importing, Go tools searches for the packages inside $GOROOT and $GOPATH/src directories.

__$GOPATH__ is called as the __workspace directory__ for Go programs.

* Go source-code, belongs to you and to others lives here.
* So, when you use import, Go looks inside this directory’s __src directory__ to find the packages it searches for
* $GOPATH could contain more than one separated with `colons`, like /path/1:/path/2


* See __all of the environment variables Go uses__ by typing: `go env` in your CLI.

## GO build

### [link arguments](https://golang.org/cmd/link/): for app version

* -ldflags
```
-X importpath.name=value
    Set the value of the string variable in importpath named name to value.
```

* E.g.
```sh
export GIT_BRANCH=$(git rev-parse --abbrev-ref HEAD) \
    GIT_COMMIT=$(git rev-parse HEAD) \
    BUILD_TIME=`date -u '+%Y-%m-%d_%H:%M:%S_%Z'` && \
    go build -ldflags "-X main.GitBranch=$GIT_BRANCH -X main.GitCommit=$GIT_COMMIT -X main.BuildTime=$BUILD_TIME"
```

```golang
// version.go
package main

import (
    "github.com/golang/glog"
)

var (
    AppVersion   = "0.1.0"
    GitBranch = "No git branch provided"
    GitCommit = "No git commit provided"
    BuildTime = "No build time provided"
)

func version() {
    if len(GitCommit) > 7 {
        GitCommit = GitCommit[:7]
    }

    glog.V(0).Infof("App XXX %v, Git Branch: %v, Git Commit: %v, Build Time: %v",
        AppVersion,
        GitBranch,
        GitCommit,
        BuildTime)
}
```

# Go 并发

## 协程同步的几种方式：goroutine synchronization

执行下面代码很可能看不到输出。

```golang
package main

import (
    "fmt"
)

func main() {
    go func() {
        fmt.Println("Goroutine 1")
    }()

    go func() {
        fmt.Println("Goroutine 2")
    }()
}
```

We have the following possible approaches.

### time.Sleep

```golang
package main

import (
    "fmt"
    "time"
)

func main() {
    go func() {
        fmt.Println("Goroutine 1")
    }()

    go func() {
        fmt.Println("Goroutine 2")
    }()

    time.Sleep(time.Second * 1) // 睡眠1秒，等待上面两个协程结束
}
```

问题所在：`我们无法确定需要睡眠多久`.


### channel: 管道

```golang
package main

import (
    "fmt"
)

func main() {

    ch := make(chan struct{})
    count := 2 // count 表示活动的协程个数

    go func() {
        fmt.Println("Goroutine 1")
        ch <- struct{}{} // 协程结束，发出信号
    }()

    go func() {
        fmt.Println("Goroutine 2")
        ch <- struct{}{} // 协程结束，发出信号
    }()

    for range ch {
        // 每次从ch中接收数据，表明一个活动的协程结束
        count--
        // 当所有活动的协程都结束时，关闭管道
        if count == 0 {
            close(ch)
        }
    }
}
```

这种方式是一种比较完美的解决方案， goroutine / channel 它们也是在 go 里面经常搭配在一起的一对。


### sync.WaitGroup

WaitGroup 顾名思义，就是用来等待一组操作完成的。WaitGroup 内部实现了一个计数器，用来记录未完成的操作个数，它提供了三个方法：

* Add() 用来添加计数
* Done() 用来在操作结束时调用，使计数减一
* Wait() 用来等待所有的操作结束，即计数变为 0，该函数会在计数不为 0 时等待，在计数为 0 时立即返回

```golang
package main

import (
    "fmt"
    "sync"
)

func main() {

    var wg sync.WaitGroup

    wg.Add(1) // 每个go routine，增加1个计数
    go func() {
        fmt.Println("Goroutine 1")
        wg.Done() // 操作完成，减少一个计数
    }()

    wg.Add(1) // 每个go routine，增加1个计数
    go func() {
        fmt.Println("Goroutine 2")
        wg.Done() // 操作完成，减少一个计数
    }()

    wg.Wait() // 等待，直到计数为0
}
```

# [RPC example in go](https://ops.tips/gists/example-go-rpc-client-and-server/)
