#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 伪随机数：每次生成的随机数是一样的
 * 种子随机数：每次生成的随机数是不一样的
 */

/**
 * 伪随机数：每次生成的随机数是一样的
 */
void get_random_number_1()
{
    printf("r = %d\n", rand());
    printf("r = %d\n", rand());
    printf("r = %d\n", rand());
    printf("r = %d\n", rand());
    printf("r = %d\n", rand());
}

/**
 * 伪随机数,每次生成的随机数是相同的
 */
void get_random_number_2()
{
    int r = rand();
    printf("r = %d\n", r);
    printf("请输入:\n");
    int i = 0;
    while (1)
    {
        scanf("%d", &i);
        if (i > r)
        {
            printf("你猜大了,当前输入值:%d\n", i);
        }
        else if (i < r)
        {
            printf("你猜小了,当前输入值:%d\n", i);
        }
        else
        {
            printf("你猜正确了,当前输入值:%d\n", i);
            break;
        }
    }
}


/**
 * 种子随机数,每次生成的随机数是不同的
 */
void get_random_number_3()
{
    srand((unsigned)time(NULL));
    int r = rand() % 10;
    printf("r = %d\n", r);
    printf("请输入:\n");
    int i = 0;
    while (1)
    {
        scanf("%d", &i);
        if (i > r)
        {
            printf("你猜大了,当前输入值:%d\n", i);
        }
        else if (i < r)
        {
            printf("你猜小了,当前输入值:%d\n", i);
        }
        else
        {
            printf("你猜正确了,当前输入值:%d\n", i);
            break;
        }
    }
}


/**
 * 生成10个随机数
 */
void get_random_number_4()
{
    //初始化随机数
    srand((unsigned)time(NULL));
    //打印出10个随机数
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", rand());
    }
}


/**
 * 生成一个0-1的随机数
 */
void get_random_number_5()
{
    //初始化随机数
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        printf("%.2f\n", rand() / 32767.0);
    }
}


/**
 * 生成一个1-10的随机数
 * 原理:
 *  五位数:
 *      10022 = 10 * 1002 + 2
 *      10022 % 10 = 2
 *  六位数:
 *      100022 = 10 * 10002 + 2
 *      100022 % 10 = 2
 *  用100取余可以得到最后一位数,最后一位数的范围为: 0-9,所以  rand()+1 的范围是 0-10
 */
void get_random_number_6()
{
    //初始化随机数
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int r = rand();
        printf("rand() = %d, r = %d\n", r, r % 10 + 1);
    }
}


/**
 * 生成一个1-100的随机数
 * 原理:
 *  五位数:
 *      10022 = 100 * 100 + 22
 *      10022 % 100 = 22
 *  六位数:
 *      100022 = 1000 * 100 + 22
 *      100022 % 100 = 22
 *  用100取余可以得到最后两位数,最后两位数的范围为: 00-99,所以  rand()+1 的范围是 00-100
 */
void get_random_number_7()
{
    //初始化随机数
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int r = rand();
        printf("rand() = %d, r = %d\n", r, r % 100 + 1);
    }
}


int main()
{
	//get_random_number_1();
    //get_random_number_2();
	//get_random_number_3();
    get_random_number_4();
    //get_random_number_5();
    //get_random_number_6();
    //get_random_number_7();
    return 0;
}
