<!-- MarkdownTOC -->

- [Syntax](#syntax)
- [Examples](#examples)
  - [Get file/partent dir](#get-filepartent-dir)
- [References](#references)

<!-- /MarkdownTOC -->

# Syntax

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
