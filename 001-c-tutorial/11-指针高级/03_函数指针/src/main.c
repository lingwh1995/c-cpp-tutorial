#include <stdio.h>

/**
 * 1.声明函数以及声明函数的简化形式（形参列表中只保存参数类型）
 * 2.使用 返回值 + 形参列表 描述函数的类型
 * 3.函数指针入门之定义函数指针以及定义函数指针的简化形式（形参列表中只保存参数类型）
 */

// 声明一个函数
int add(int, int); // 相当于 => int add(int a, int b);
int sub(int, int); // 相当于 => int sub(int a, int b);

#if 0
int main()
{
	// 声明一个函数指针
	int (*p_add_1)(int, int) = NULL; // 相当于 => int (*p_add_1)(int a, int b) = NULL;
	int (*p_add_2)(int, int) = NULL; // 相当于 => int (*p_add_2)(int a, int b) = NULL;
	// add是函数的地址
	p_add_1 = add;
	printf("p_add_1 = %p\n", p_add_1);
	// &add也是函数的地址
	p_add_2 = &add;
	printf("p_add_2 = %p\n", p_add_2);

	int a = 25, b = 10, c = 0;
	// 使用函数指针调用函数方式一（推荐）：相较于方式二看起来更直观
	c = (*p_add_1)(a, b);
	printf("c = %d\n", c);
	// 使用函数指针调用函数方式二（不推荐）
	c = p_add_1(a, b);
	printf("c = %d\n", c);

	// 重新给函数指针p_add_2赋值
	p_add_2 = &sub;
	// 使用函数指针调用函数方式一（推荐）
	c = (*p_add_2)(a, b);
	printf("c = %d\n", c);
	return 0;
}
#endif


/**
 * 如何描述函数的类型?
 * 		返回值 + 形参列表
 *
 * 下面 add()函数 和 sub()函数 的类型是相同的
 */

// 加法函数
int add(int a, int b)
{
	return a + b;
}

// 减法函数
int sub(int a, int b)
{
	return a - b;
}
