### 假设你的数据时存储在一个文件中，文件名字为test.txt
* 第一列的和：
```
cat test.txt | awk '{sum1+= $1}END{print sum1}'
```
* 第一列和第二列的平均值：
```
cat test.txt | awk '{sum1+=$1;sum2+=$2;count++}END{print sum1/count,sum2/count}'
```

### References
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
[]()<br/>
