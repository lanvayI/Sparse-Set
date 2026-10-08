# SPARSE SET DATA STRUCTURE IN C
Sparse set is a high perfomance data structure that suports O(1) insertion and deletion.

## Installation
Download the .c and .h files and include in your project.

## How to use

- Create a init a __SSET__ structure and get the pointer to it:
```c
SSET* set = ss_init(10,sizeof(int));
```

- Insert data and store in the designated id:
 ```c
static int newId = 0;

int value = 10;
ss_insert(set,newId++,&value);

value = 30;
ss_insert(set,newId++,&value);
```
- Get stored data in the designated id via pointer:
```c
int* valuePtr = ss_getPtr(set,0);
printf("Value of id 0: %d \n",*valuePtr);
```
```shell
$ ./app
Value of id 0: 10 
```

- Remove data:

```c
ss_remove(set,0);
```
- Check if has id:

```c
if(!ss_has(set,0)){puts("Dont have id 0");}
```
```shell
$ ./app
Dont have id 0
```

- Then free set object:
```c
ss_free(set);
```
