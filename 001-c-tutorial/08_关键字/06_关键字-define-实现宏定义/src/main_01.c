#include <stdio.h>

#define MIN(a,b) (a)<(b) ? (a) : (b)
#define MAX(a,b) (a)>(b) ? (a) : (b)
// 错误定义求中间值的带参数宏MID
//#define MID(a,b,c) (a) + (b) + (c)- MIN(MIN(a,b),c) - MAX(MAX(a,b),c)
// 正确定义求中间值的带参数宏MID
#define MID(a,b,c) (a) + (b) + (c) - MAX(MAX(a,b),c) - MIN(MIN(a,b),c)


/**
 * 输入三个整型数据，求最小值
 */ 
void get_min_value()
{
	printf("请输入三个整型数据，使用空格分隔:\n");
	int a, b, c, min;
	scanf("%d %d %d", &a, &b, &c);
	min = MIN(a, b);
	min = MIN(min, c);
	printf("min = %d\n", min);
}

/**
 * 输入三个整型数据，求最大值
 */ 
void get_max_value()
{
	printf("请输入三个整型数据，使用空格分隔:\n");
	int a, b, c, max;
	scanf("%d %d %d", &a, &b, &c);
	max = MAX(a, b);
	max = MAX(max, c);
	printf("max = %d\n", max);
}

/**
 * 输入三个整型数据，求中间值
 */ 
void get_mid_value()
{
	printf("请输入三个整型数据，使用空格分隔:\n");
	int a, b, c, mid;
	scanf("%d %d %d", &a, &b, &c);
	mid = MID(a, b, c);
	printf("mid = %d\n", mid);
}

#if 0
#endif
int main()
{
	//get_min_value();
	//get_max_value();
	get_mid_value();
	return 0;
}