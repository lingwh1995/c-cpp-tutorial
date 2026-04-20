#include <stdio.h>
#include "../inc/mylib.h"

//定义一个被static修饰的全局变量
int gi_in_other_file_static = 10;

//定义一个被static修饰的全局常量
const int gc_in_other_file_static = 20;

//定义一个被static修饰的函数
int add_in_other_file_static(int a, int b)
{
    printf("我是mylib.c中的普通函数......(来自其他文件,被static修饰)\n");
    return a + b;
}

//定义一个没有被static修饰的全局变量
int gi_in_other_file_ordinary = 100;

//定义一个没有被static修饰的全局常量
const int gc_in_other_file_ordinary = 200;

//定义一个没有被static修饰的函数
int add_in_other_file_ordinary(int a, int b)
{
    printf("我是mylib.c中的普通函数......(来自其他文件,没有被static修饰)\n");
    return a + b;
}
