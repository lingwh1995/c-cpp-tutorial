//使用多文件结构(模块化设计)编写计算器程序:函数实现部分
#include <stdbool.h>
#include <stdio.h>
#include "../inc/calculator.h"

//声明本文件中的函数
static int add_int(int a, int b);
static int sub_int(int a, int b);
static int mul_int(int a, int b);
static int div_int(int a, int b);
static void show(int a, int b, char op, int result);

/*
 * 进行计算的方法,不能使用static修饰,因为这是本程序唯一对外暴露的接口
 * @param a 计算参数1
 * @param b 计算参数2
 * @param op 运算符
 */
void calc(int a, int b, char op)
{
	int result = 0;
	bool b_is_show = true;
	switch (op)
	{
		case '+':
			result = add_int(a, b);
			break;
		case '-':
			result = sub_int(a, b);
			break;
		case '*':
			result = mul_int(a, b);
			break;
		case '/':
			if (b == 0)
			{
                b_is_show = false;
				printf("div by zeron error!\n");
			}
			else
			{
				result = div_int(a, b);
			}
			break;
		default:
            b_is_show = false;
			printf("op input error!\n");
			break;
	}
	if (b_is_show)
	{
		show(a, b, op, result);
	}
}

/*
 * 加法，如果不想被外部调用，使用static修饰
 * @param a 计算参数1
 * @param b 计算参数2
 */
static int add_int(int a, int b)
{
	return a + b;
}

/*
 * 减法，如果不想被外部调用，使用static修饰
 * @param a 计算参数1
 * @param b 计算参数2
 */

static int sub_int(int a, int b)
{
	return a - b;
}

/*
 * 乘法，如果不想被外部调用，使用static修饰
 * @param a 计算参数1
 * @param b 计算参数2
 */
static int mul_int(int a, int b)
{
	return a * b;
}

/*
 * 除法，如果不想被外部调用，使用static修饰
 * @param a 计算参数1
 * @param b 计算参数2
 */
static int div_int(int a, int b)
{
	return a / b;
}

/*
 * 显示结果，如果不想被外部调用，使用static修饰
 * @param a 计算参数1
 * @param b 计算参数2
 * @param op 运算符
 * @param result 计算结果
 */
static void show(int a, int b, char op, int result)
{
	printf("%d %c %d = %d\n", a, op, b, result);
}
