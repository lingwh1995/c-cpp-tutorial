#include <stdio.h>
#include <limits.h>

/**
 * 使用函数指针将四则运算封装到一个方法中
 */

double add_number_1(double, double);
double sub_number_1(double, double);
double mul_number_1(double, double);
double div_number_1(double, double);
double calc_number(double, double, double (*calculator)(double, double));

#if 0
int main()
{
	double a = 12.0, b = 6.0, c = 0.0;
	c = calc_number(a, b, add_number_1);
	printf("c = %.2f\n", c);
	c = calc_number(a, b, sub_number_1);
	printf("c = %.2f\n", c);
	c = calc_number(a, b, mul_number_1);
	printf("c = %.2f\n", c);
	c = calc_number(a, b, div_number_1);
	printf("c = %.2f\n", c);
	return 0;
}
#endif

/**
 * 加法
 */
double add_number_1(double a, double b)
{
	return a + b;
}

/**
 * 减法
 */
double sub_number_1(double a, double b)
{
	return a - b;
}

/**
 * 乘法
 */
double mul_number_1(double a, double b)
{
	return a * b;
}

/**
 * 除法
 */
double div_number_1(double a, double b)
{
	if(b == 0)
	{
		return INT_MAX;
	}
	return a / b;
}

/*
 * 计算器
 */
double calc_number(double a, double b, double (*calculator)(double, double))
{
	return calculator(a, b);
}
