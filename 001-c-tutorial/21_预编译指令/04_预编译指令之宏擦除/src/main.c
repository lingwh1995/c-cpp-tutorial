#include <stdio.h>
#define LEN 100 // 定义宏

/**
 * 宏定义和宏擦除(撤销)宏定义
 */
#if 0
int main()
{
    printf("LEN = %d\n", LEN);
    return 0;
}
#endif

//#undef LEN  // 擦除宏定义，放开后运行会报错
int fun()
{
    printf("LEN = %d\n", LEN);
}