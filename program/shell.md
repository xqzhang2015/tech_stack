<!-- MarkdownTOC -->

- [Syntax](#syntax)
  - [String 替换命令](#string-%E6%9B%BF%E6%8D%A2%E5%91%BD%E4%BB%A4)
- [Examples](#examples)
  - [Get file/partent dir](#get-filepartent-dir)
- [References](#references)

<!-- /MarkdownTOC -->

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
