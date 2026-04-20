#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

/*
 * 多分支
 *  if else
 *  switch case
 */

void multiple_branch_test_1()
{
    printf("请输入i的值，输入0退出:\n");
    int i;
    while(true)
    {
        scanf("%d", &i);
        if(i == 0)
        {
            printf("您输入了0，即将退出!\n");
            break;
        }
        if(i == 1)
        {
            printf("您输入的值是: 1\n");
        }
        else if(i == 2)
        {
            printf("您输入的值是: 2\n");
        }
        else if(i == 3)
        {
            printf("您输入的值是: 3\n");
        }
        else if(i == 4)
        {
            printf("您输入的值是: 4\n");
        }
        else if(i == 5)
        {
            printf("您输入的值是: 5\n");
        }
        else
        {
            printf("您输入的值是其他值!\n");
        }
    }
}

/*
 * 多分支测试
 */
void multiple_branch_test_2()
{
    printf("请输入i的值，输入0退出:\n");
    int i;
    while(true)
    {
        scanf("%d",&i);
        switch (i)
        {
            case 0:
                printf("您输入了0，即将退出!\n");
                return;            
            case 1:
                printf("您输入的值是: 1\n");
                break;
            case 2:
                printf("您输入的值是: 2\n");
                break;
            case 3:
                printf("您输入的值是: 3\n");
                break;
            case 4:
                printf("您输入的值是: 4\n");
                break;
            case 5:
                printf("您输入的值是: 5\n");
                break;
            default:
                printf("您输入的值是其他值!\n");
                break;
        }        
    }
}

/*
 * 多分支测试
 *  只能匹配大写字母
 */
void multiple_branch_test_3()
{
    printf("请输入分数等级 (A B C D E F)，输入Q退出:\n");
    while(true)
    {
        char c = getchar();
        // 检查是否为换行符
        if (c == '\n')
        {
            // 退出本次循环
            continue;
        }
        switch (c)
        {
            case 'A':
                printf("score: 80 - 100\n");
                break;
            case 'B':
                printf("score: 60 - 80\n");
                break;
            case 'C':
                printf("score: 40 - 60\n");
                break;
            case 'D':
                printf("score: 20 - 40\n");
                break;
            case 'E':
                printf("score: 0 - 20\n");
                break;
            case 'Q':
                printf("您输入了Q，即将退出!\n");
                return;
            default:
                printf("输入数据不合法.....\n");
                break;
        }
    }
}

/*
 * 多分支测试
 *  匹配大小写字母
 */
void multiple_branch_test_4()
{
    printf("请输入分数等级 (A B C D E F)，输入Q/q退出:\n");
    while(true)
    {
        char c = getchar();
        // 检查是否为换行符
        if (c == '\n')
        {
            // 退出本次循环
            continue;
        }
        switch (c)
        {
            case 'A':
            case 'a':
                printf("score: 80 - 100\n");
                break;
            case 'B':
            case 'b':
                printf("score: 60 - 80\n");
                break;
            case 'C':
            case 'c':
                printf("score: 40 - 60\n");
                break;
            case 'D':
            case 'd':
                printf("score: 20 - 40\n");
                break;
            case 'E':
            case 'e':
                printf("score: 0 - 20\n");
                break;
            case 'Q':
            case 'q':
                printf("您输入了%c，即将退出!\n", c);
                return;
            default:
                printf("输入数据不合法.....\n");
                break;
        }
    }
}

/*
 * 多分支测试
 *  switch的嵌套使用
 */
void multiple_branch_test_5()
{
    int a = 1;
    int b = 0;
    switch (a)
    {
        case -1:
            printf("a = -1\n");
            break;
        case 0:
            printf("a = 0\n");
            break;
        case 1:
            printf("a = 1\n");
            switch (b)
            {
                case -1:
                    printf("b = -1\n");
                    break;
                case 0:
                    printf("b = 0\n");
                    break;
                case 1:
                    printf("b = -1\n");
                    break;
            }
    }
}

#if 0
#endif
int main()
{
	//multiple_branch_test_1();
    //multiple_branch_test_2();
    //multiple_branch_test_3();
	//multiple_branch_test_4();
    multiple_branch_test_5();
    return 0;
}
