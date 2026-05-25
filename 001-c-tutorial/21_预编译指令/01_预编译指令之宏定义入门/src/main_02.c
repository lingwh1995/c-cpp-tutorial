#include <stdio.h>
#define ERROR_MSG "standard error on input!"

/**
 * 两种输出宏值的方法
 *
 * 1. 使用 %s 形式输出宏值
 * 2. 当宏代表的值是字符串类型时，可以直接输出宏值
 */
#if 0
int main()
{
    // 拼接字符串和宏值错误写法：这种写法编译器无法正确解析
    //char stra[] = { "hello "ERROR_MSG };
    // 拼接字符串和宏值正确写法：C语言支持相邻字符串字面量的自动连接
    char stra[] = "hello " ERROR_MSG;
    printf("%s \n", stra);

    // C语言支持两个字符串的自动连接
    char strb[] = "hello " "world!";
    printf("%s \n", strb);

    // 使用 %s 形式输出宏值
    printf("%s \n", ERROR_MSG);

    // 特别注意： 宏值可以不使用 %s，直接就输出
    printf(ERROR_MSG);
    return 0;
}
#endif