#include <stdio.h>
#include <string.h>

/**
 * 循环打印a-g
 *  不使用取模实现
 */
void print_a2g_1()
{
    char str[] = "abcdefg";
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        int k = i;
        for (int j = 0; j < n; j++)
        {
            printf("%c", str[k]);
            k = k + 1;
            if (k == n)
            {
                k = 0;
            }
        }
        printf("\n");
    }
}

/**
 * 循环打印a-g
 *  使用取模实现
 */
void print_a2g_2()
{
    char str[] = "abcdefg";
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        int k = i;
        for (int j = 0; j < n; j++)
        {
            printf("%c", str[k]);
            k = (k + 1) % n;
        }
        printf("\n");
    }
}

/**
 * 死循环
 */
void dead_loop_test_1()
{
    for (;;)
    {
        printf("死循环\n");
    }
}

/**
 * 死循环
 */
void dead_loop_test_2()
{
    while (1)
    {
        printf("死循环\n");
    }
}

#if 0
int main()
{
    print_a2g_1();
    //print_a2g_2();
	//dead_loop_test_1();
    //dead_loop_test_2();
    return 0;
}
#endif
