#include <stdio.h>

#define MAX 10

/**
 * 条件编译指令入门
 */

void fun_a(int a, int b)
{
// 特别注意，#if 后面使用变量，必须是常量，比如宏常量，字符常量
#if MAX > 9
//#if a > 9   // 当前文件中，并没有宏名为 a 的宏定义，这个 a 的值为默认值 0
    printf("进入了条件编译指令......\n");
#endif
}

void fun_b(int a, int b)
{
    if (a > 9)
    {
        printf("进入了if语句块......\n");
    }
}

#if 0
int main()
{
    fun_a(10, 20);
    fun_b(10, 20);
    return 0;
}
#endif