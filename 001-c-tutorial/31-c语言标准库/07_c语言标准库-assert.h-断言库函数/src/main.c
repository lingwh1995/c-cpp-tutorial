#include <stdio.h>
#include <assert.h>

/**
 * assert.h
 * 经典应用场景
 * 1. 指针判空
 * 2. 判断参数是否合法
 */

int main()
{
    int a = 10;
    int b = 2;

    // 断言：b 不能为 0（防止除零错误）
    assert(b != 0);
    int c = a / b;
    printf("a / b = %d\n", c);

    // 断言失败示例（解开注释会触发崩溃并打印信息）
    // assert(a == 100);

    // 指针非空断言
    int* p = &a;
    assert(p != NULL);
    printf("*p = %d\n", *p);
    return 0;
}