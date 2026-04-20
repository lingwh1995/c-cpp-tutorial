#include "../inc/mylib.h"

// 定义一个全局变量
int gi_in_other_file = 100;

// 定义一个全局常量
const int gc_in_other_file = 200;

// 定义一个函数
int add_in_other_file(int a, int b)
{
    printf("我是mylib.c中的普通函数......(来自其他文件)\n");
    return a + b;
}
