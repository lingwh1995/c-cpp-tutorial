#include <stdio.h>
#include <limits.h>

/**
 * 函数指针配合表驱动方式调用方法
 */
// 定义函数指针
typedef double (*p_fun_t)(double, double);

double add_number_2(double, double);
double sub_number_2(double, double);
double mul_number_2(double, double);
double div_number_2(double, double);

#if 0
int main()
{
	// 解决eclipse无法使用scanf()从控制台接收参数的问题
	setbuf(stdout, NULL);

//	int a = 10, b = 20, c = 30, d = 40;
//	int *arr[] = { &a, &b, &c, &d };

	double a = 12.0, b = 6.0, c = 0.0;
	// 普通方式定义函数指针数组：注意 函数指针数组这个 [] 的书写位置
	//double (*p_fun[])(double, double) = { &add_number_2, &sub_number_2, &mul_number_2, &div_number_2 };
	// typedef方式定义函数指针数组 => 可读性更强，推荐这种写法
	p_fun_t p_fun[] = { &add_number_2, &sub_number_2, &mul_number_2, &div_number_2 };
	int index = 0;
	printf("请输入表中函数索引：\n");
	scanf("%d", &index);
	printf("index = %d\n", index);
	if(index >= 0 && index <= 3)
	{
		c = p_fun[index](a, b);
		printf("c = %.2f\n", c);
	}
	else
	{
		printf("您输入的索引不符合规范！");
	}
	return 0;
}
#endif

/**
 * 加法
 */
double add_number_2(double a, double b)
{
	return a + b;
}

/**
 * 减法
 */
double sub_number_2(double a, double b)
{
	return a - b;
}

/**
 * 乘法
 */
double mul_number_2(double a, double b)
{
	return a * b;
}

/**
 * 除法
 */
double div_number_2(double a, double b)
{
	if(b == 0)
	{
		return INT_MAX;
	}
	return a / b;
}
