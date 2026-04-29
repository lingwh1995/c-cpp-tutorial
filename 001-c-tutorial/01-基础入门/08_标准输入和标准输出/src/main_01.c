#include <stdio.h>
#include <string.h>

/**
 * 标准输入和EOF
 */

 /**
 * 标准输入经典写法测试
 */
void getchar_and_eof_test_1()
{
    printf("请输入,按回车结束:\n");
    char ch = 0;
    while ((ch = getchar()) != EOF)
    {
        // 打印方式一
        printf("%c\n", ch);
        // 打印方式二
        putchar(ch);
    }
}

 /**
 * 标准输入测试
 *   不推荐通过判断换行符来判断输入结束
 *   换行符常用来把缓冲区中的数据输出到标准输出中，然后清空缓冲区
 */
void getchar_and_eof_test_2()
{
    printf("请输入,按回车结束:\n");
    int sum = 0;
    while (getchar() != '\n')
    {
        sum++;
    }
    printf("sum = %d\n", sum);
}

/**
 * 标准输入和EOF测试
 *    推荐通过判断EOF来判断输入结束
 */
void getchar_and_eof_test_3()
{
    printf("请输入,输入 Ctrl+Z 结束:\n");
    int sum = 0;
    while (getchar() != EOF)
    {
        sum++;
    }
    printf("sum = %d\n", sum);
}

/**
 * 标准输入测试
 *  接收单个字符: 不管输入多少个字符，都只会接收第一个字符
 */
void getchar_and_eof_test_4()
{
    printf("请输入:\n");
    char ch = getchar();
    printf("ch = %c\n", ch);
}

/**
 * 标准输入测试：接收多个字符(输入Ctrl+Z结束)
 *
 */
void getchar_and_eof_test_5()
{
    printf("请输入:\n");
    char ch = '\0';
    //为什么getchar()可以放在while后面的大括号中，来接收多个字符，因为getchar()有一个缓冲区机制

    //错误写法
    //while (ch = getchar() != '\n')
    //{
    //正确写法
    //while ((ch = getchar()) != '\n')
    //{
    while ((ch = getchar()) != EOF)
    {
        printf("ch = %c\n", ch); 
    }
}

/**
 * 标准输入测试：接收多个字符串(输入Ctrl+C结束)
 *    输入水果名称，通过水果名称判断是不是最喜爱的运动，如果输入的是 apple 就是最喜爱的水果
 */
void scanf_and_eof_test_1()
{
    printf("请输入名称:\n");
    char fruit_name;
    while (scanf("%s", &fruit_name) != EOF)
    {
        if(strcmp(&fruit_name,"apple") == 0)
        {
            printf("是最喜爱的水果\n");
        }
        else
        {
            printf("不是最喜爱的水果\n");
        }
    }
}

/**
 * 标准输入测试：接收多个数字(输入Ctrl+C结束)
 *    输入IQ值，通过IQ值判断是不是Genius，IQ>=140是Genius
 */
void scanf_and_eof_test_2()
{
    printf("请输入IQ值:\n");
    int IQ;
    while (scanf("%d", &IQ) != EOF)
    {
        if(IQ >= 140)
        {
            printf("Genius\n");
        }
        else
        {
            printf("Not Genius\n");
        }
    }
}

/**
 * 打印时左对齐和右对齐
 */
void stdin_and_format_output_test()
{
	// 左对齐
	printf("%2d\n", 1);
	printf("%2d\n", 5);
	printf("%2d\n", 10);
	printf("%2d\n", 20);
	printf("----------------------\n");

	// 右对齐
	printf("%-2d\n", 1);
	printf("%-2d\n", 5);
	printf("%-2d\n", 10);
	printf("%-2d\n", 20);
	printf("----------------------\n");

	printf("%-10s -%-20s %-10s\n", "姓名", "学校", "分数");
	printf("%-10s -%-20s %-10d\n", "张三", "西安财经大学", 100);
}

#if 0
int main()
{
    //getchar_and_eof_test_1();
	getchar_and_eof_test_2();
    //getchar_and_eof_test_3();
    //getchar_and_eof_test_4();
    //getchar_and_eof_test_5();
	//scanf_and_eof_test_1();
	//scanf_and_eof_test_2();
	//stdin_and_format_output_test();
}
#endif
