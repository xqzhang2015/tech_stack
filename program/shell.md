<!-- MarkdownTOC -->

- [Shell script](#shell-script)
  - [String: empty check](#string-empty-check)
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

### String: empty check

```shell
if [ -z "$var" ]
then
      echo "\$var is empty"
else
      echo "\$var is NOT empty"
fi
```

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

* All function parameters or arguments can be accessed via $1, $2, $3,..., $N.
  * $0 is shell script name
  * $1 is the 1st param
* $* or $@ holds all parameters or arguments passed to the function.
* $# holds the number of positional parameters passed to the function.



```sh
func test()
{
  local arg=${1:-"quick"}
  # ...
}
```

example

```sh
#!/bin/bash
 
# write a function
fresh(){
   # t stores $1 argument passed to fresh()
   t=$1
   echo "fresh(): \$0 is $0"
   echo "fresh(): \$1 is $1"
   echo "fresh(): \$t is $t"
   echo "fresh(): total args passed to me $#"
   echo "fresh(): all args (\$@) passed to me -\"$@\""
   echo "fresh(): all args (\$*) passed to me -\"$*\""
}
 
# invoke the function with "Tomato" argument
echo "**** calling fresh() 1st time ****"
fresh Tomato
 
# invoke the function with total 3 arguments
echo "**** calling fresh() 2nd time ****"
fresh Tomato Onion Paneer
```

`chmod +x fresh.sh`


output

```sh
**** calling fresh() 1st time ****
fresh(): $0 is ./fresh.sh
fresh(): $1 is Tomato
fresh(): $t is Tomato
fresh(): total args passed to me 1
fresh(): all args ($@) passed to me -"Tomato"
fresh(): all args ($*) passed to me -"Tomato"
**** calling fresh() 2nd time ****
fresh(): $0 is ./fresh.sh
fresh(): $1 is Tomato
fresh(): $t is Tomato
fresh(): total args passed to me 3
fresh(): all args ($@) passed to me -"Tomato Onion Paneer"
fresh(): all args ($*) passed to me -"Tomato Onion Paneer"

```


example: 

Create a shell script to determine if given name is file or directory (cmdargs.sh):


```sh
#!/bin/bash
file="$1"

# User-defined function
is_file_dir(){
        # $f is local variable
  local f="$1"
        # file attributes comparisons using test i.e. [ ... ]
  [ -f "$f" ] && { echo "$f is a regular file."; exit 0; }
  [ -d "$f" ] && { echo "$f is a directory."; exit 0; }
  [ -L "$f" ] && { echo "$f is a symbolic link."; exit 0; }
  [ -x "$f" ] && { echo "$f is an executeble file."; exit 0; }
}

# make sure filename supplied as command line arg else die
[ $# -eq 0 ] && { echo "Usage: $0 filename"; exit 1; }

# invoke the is_file_dir and pass $file as arg
is_file_dir "$file"
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
