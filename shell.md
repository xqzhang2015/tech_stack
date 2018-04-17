<a href="awk">awk</a>

[]()<br/>
[]()<br/>

### Pretty Print JSON With Python

```
echo '{"one":1,"two":[{"foo":1,"bar":2}]}' | python -m json.tool
```
<br/>
[Pretty Print JSON With Python](http://www.hashbangcode.com/blog/pretty-print-json-python)<br/>

[]()<br/>

[]()<br/>


### awk
- pattern-directed scanning and processing language <br>
an associated action that will be performed when a line of a file matches the pattern.<br/>
* SYNOPSIS
```
       awk [ -F fs ] [ -v var=value ] [ 'prog' | -f progfile ] [ file ...  ]
```
假设你的数据时存储在一个文件中，文件名字为test.txt<br/>
* 第一列的和：
```
cat test.txt | awk '{sum1+= $1}END{print sum1}'
```
* 第一列和第二列的平均值：
```
cat test.txt | awk '{sum1+=$1;sum2+=$2;count++}END{print sum1/count,sum2/count}'
```
* EXAMPLES
```
       length($0) > 72
              Print lines longer than 72 characters.

       { print $2, $1 }
              Print first two fields in opposite order.

       BEGIN { FS = ",[ \t]*|[ \t]+" }
             { print $2, $1 }
              Same, with input fields separated by comma and/or blanks and tabs.

            { s += $1 }
       END  { print "sum is", s, " average is", s/NR }
              Add up first column, print sum and average.

       /start/, /stop/
              Print all lines between start/stop pairs.

       BEGIN     {    # Simulate echo(1)
            for (i = 1; i < ARGC; i++) printf "%s ", ARGV[i]
            printf "\n"
            exit }
 ```           

<br/><br/>
### References
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
