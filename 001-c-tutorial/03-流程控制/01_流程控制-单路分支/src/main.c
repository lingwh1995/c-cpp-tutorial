#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
 * 单分支
 *	if else
 *  三元表达式
 */

/*
 * 单分支测试
 */
void single_branch_test()
{
    printf("请输入i和j的值,使用空格隔开:\n");
    int i, j, max;
    scanf("%d %d", &i, &j);
    if (i > j)
    {
        max = i;
    }
    else
    {
        max = j;
    }
    printf("两个值中最大的值 max = %d\n", max);
}

/*
 * 三元表达式测试
 */
void ternary_expression()
{
    printf("请输入i和j的值,使用空格隔开:\n");
    int i, j, max;
    scanf("%d %d", &i, &j);
    max = i > j ? i : j;
    printf("两个值中最大的值 max = %d\n", max);
}

#if 0
#endif
int main()
{
	//single_branch_test();
    ternary_expression();
    return 0;
}
