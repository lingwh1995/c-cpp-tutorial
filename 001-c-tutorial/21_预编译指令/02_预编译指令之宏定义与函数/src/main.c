#include <stdio.h>
// 求绝对值
#define ABS(a) (a) < 0 ? -(a) : (a)

int abs(int a)
{
    return a < 0 ? -a : a;
}

/**
 * 类函数宏和普通函数
 *
 * 1. 宏元和变元之间不能有空格
 * 2. 可以提高函数运行速度
 * 3. 简单的函数用优先考虑类函数宏，复杂的函数用优先考虑普通函数
 * 4. 不关心参数的类型，优先考虑类函数宏
 */
#if 0
#endif
int main()
{
    int a = -10;
    printf("ABS(a) = %d, ABS(-a) = %d\n", ABS(a), ABS(-a));
    printf("abs(a) = %d, abs(-a) = %d\n", abs(a), abs(-a));
    return 0;
}