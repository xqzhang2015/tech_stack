<!-- MarkdownTOC -->

- [Shell script](#shell-script)
  - [Loops: for](#loops-for)
  - [Loops: While](#loops-while)
  - [func args](#func-args)
  - [string split](#string-split)
- [Syntax](#syntax)
  - [String 替换命令](#string-%E6%9B%BF%E6%8D%A2%E5%91%BD%E4%BB%A4)
- [Examples](#examples)
  - [Get file/partent dir](#get-filepartent-dir)
- [References](#references)

<!-- /MarkdownTOC -->
# Shell script

### Loops: for

```shell
#!/bin/sh
for i in 1 2 3 4 5
do
  echo "Looping ... number $i"
done
```

```shell
for runlevel in 0 1 2 3 4 5 6 S
do
  mkdir rc${runlevel}.d
done
```

### Loops: While

```shell
#!/bin/sh
INPUT_STRING=hello
while [ "$INPUT_STRING" != "bye" ]
do
  echo "Please type something in (bye to quit)"
  read INPUT_STRING
  echo "You typed: $INPUT_STRING"
done
```

```shell
#!/bin/sh
while :
do
  echo "Please type something in (^C to quit)"
  read INPUT_STRING
  echo "You typed: $INPUT_STRING"
done
```

### func args

* $0 is shell script name
* $1 is the 1st param

```shell
func test()
{
  local arg=${1:-"quick"}
  # ...
}
```

### string split

```shell
[test ~]$ test=a,b,c
[test ~]$ IFS=',' read -r -a array <<< "$test"
```

* To iterate over the elements:

```shell
[test ~]$ for element in ${array[@]}; do     echo ${element}; done
a
b
c
```

* To get both the index and the value:

```shell
for index in ${!array[@]}
do
    echo "$index ${array[index]}"
done
```

* or using __string replacement__

```shell
string="1:2:3:4:5"
set -f                      # avoid globbing (expansion of *).
array=(${string//:/ })
for i in "${!array[@]}"
do
    echo "$i=>${array[i]}"
done
```

The idea is using string replacement:

${string//substring/replacement}

# Syntax

### String 替换命令

```
${变量/查找/替换值}  一个'/'表示替换第一个'//'表示替换所有，当查找出中出现了："/"需要转移成"\/"
```

* Examples
```
${version//./-}
${volume_id//\"/}
```

# Examples

### Get file/partent dir

`test.sh`

```
#!/bin/bash

echo $0

ROOT_DIR=$(dirname $(dirname $0))

echo ${ROOT_DIR} && cd ${ROOT_DIR}
pwd

# ➜  shell git:(master) ✗ source ${HOME}/Desktop/codes/tech_stack/program/shell/test.sh
# ${HOME}/Desktop/codes/tech_stack/program/shell/test.sh
# ${HOME}/Desktop/codes/tech_stack/program
# ${HOME}/Desktop/codes/tech_stack/program
```

# References

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>

[]()<br/>
