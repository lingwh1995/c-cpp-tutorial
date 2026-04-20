#include <stdio.h>

/**
 * 为什么枚举常量可以模拟bool类型?
 * 	1.枚举常量的数据类型是int类型
 * 	2.如果不进行设置，枚举中第一个枚举常量值是0，第二个枚举常量值是1
 */
typedef enum bool
{
    false,
    true
} bool;

/*
 * 使用 枚举+typedef 实现自定义bool
 */
#if 0
#endif
int main()
{
    bool b = true;
    if(b)
    {
    	printf("为真...\n");
    }
    else
    {
    	printf("为假...\n");
    }
    return 0;
}
