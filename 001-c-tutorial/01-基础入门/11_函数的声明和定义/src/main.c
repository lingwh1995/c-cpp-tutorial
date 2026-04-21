#include <stdio.h>
#include <math.h>

// 函数的声明（完整版）
//float calc_area_of_triangle(float a, float b, float c);

// 函数的声明（简化版）
float calc_area_of_triangle(float, float, float);

/**
 * 1.如果被调用的函数定义在main()之前，那么要在main()之前对这个函数声明
 * 2.执行函数中逻辑之前，要对这个函数传递的参数进行校验
 */
int main()
{
	printf("请输入三角形的三条边的长度:\n");
	float a = 0, b = 0, c = 0, s = 0;
	scanf("%f %f %f", &a, &b, &c);
	s = calc_area_of_triangle(a,b,c);
	printf("三角形面积 s = %f", s);
	return 0;
}

/**
 * 函数的定义
 * 计算三角形面积
 */
float calc_area_of_triangle(float a, float b, float c)
{
	float s = -1;
	if(a+b>c && a+c>b && b+c>a)
	{
		float p = 0;
		p = (a + b + c) / 2;
		s = sqrt(p * (p - a) * (p - b) * (p - c));
	}
	return s;
}
