#if 0

Linux系统environ环境变量

1. 在终端通过 man 7 environ 获取环境变量的相关信息：

NAME
     environ -- user environment

SYNOPSIS
     extern char **environ;

DESCRIPTION
       The  variable  environ points to an array of pointers to strings called the "environment". 
	The last pointer in this array has the value NULL.  
    By convention these strings have the form ``name=value''.


#endif


#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char const *argv[])
{
	for (int i = 0; environ[i] != nullptr; ++i)
	{
		printf("%s\n", environ[i]);
	}
	
	return 0;
}


#if 0
g++ -std=c++11 environ.cpp -o environ

TEST_ENV=test_value ./environ

// output:
USER=xqzhang
LOGNAME=xqzhang
HOME=/home/xqzhang

...

GOOS=linux
GOPATH=/home/xqzhang/golang

...

TEST_ENV=test_value
_=/home/xqzhang/./environ

#endif

