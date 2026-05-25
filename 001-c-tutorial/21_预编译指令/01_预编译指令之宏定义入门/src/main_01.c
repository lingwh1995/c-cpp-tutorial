#include <stdio.h>
#define ONE 1
#define TWO (ONE + ONE)
#define THREE (ONE + TWO)

/**
 * 演示正确的宏定义（宏的本质是展开，这个没有宏定义时没有加括号，展开就会报错）
 */
#if 0
#endif
int main()
{
    printf("宏 ONE = %d\n", ONE);
    printf("宏 TWO = %d\n", TWO);
    printf("宏 THREE = %d\n", THREE);

    // int a = 1;
    int a = ONE;
    // int b = 1 + 1 * 2;
    int b = TWO * 2;
    // int c = 1 + 1 + 1 * 3;
    int c = THREE * 3;
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    return 0;
}