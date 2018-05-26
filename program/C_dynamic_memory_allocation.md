C dynamic memory allocation refers to performing manual memory management for dynamic memory allocation in the C programming language via a group of functions in the C standard library, namely 
* malloc, -- allocates the specified number of bytes
* realloc, 
* calloc -- allocates the specified number of bytes and initializes them to zero
* and free.<br/>

In C++, operators __new__ and __delete__ are recommended by the language's authors.br/
<br/>
The C programming language manages memory
* statically, -- allocated in main memory
* automatically, -- allocated on the stack
* or dynamically -- from the free store, called __heap__ <br/>

### Usage Example
___
Creating an array of ten integers with automatic scope is straightforward in C:
```
int array[10];
```
However, the size of the array is fixed at compile time. <br/>
Allocate a similar array dynamically:
```
int *array = malloc(10 * sizeof(int));
if (array == NULL) {
  fprintf(stderr, "malloc failed\n");
  return -1;
}

array = realloc(array, 11 * sizeof(int));
array[10] = 13;

free(array);
```

### Type Safety
---
