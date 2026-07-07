#include <stdio.h>

int main()
{
    // #define NULL  ((void *)0)
    int i = 0;
    printf("数字 0 代表：%s\n", 0 ? "真" : "假");
    printf("表达式 !0 代表：%s\n", !0 ? "真" : "假");
    printf("数字 -1 代表：%s\n", -1 ? "真" : "假");
    printf("字符 '0' 代表：%s\n", '0' ? "真" : "假");
    printf("空字符 '\\0' 代表：%s\n", '\0' ? "真" : "假");
    printf("宏值 NULL 代表：%s\n", NULL ? "真" : "假");
    return 0;
}