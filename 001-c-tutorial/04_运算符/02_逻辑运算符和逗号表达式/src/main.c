#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**
 * 1. 逻辑运算符
 *    && 逻辑与、|| 逻辑或
 *    特性：短路求值（左侧表达式可确定结果时，右侧不再执行）
 *
 * 2. 逗号表达式（comma expression）
 *    - 运算符优先级：所有运算符中**最低**
 *    - 执行规则：从左向右依次执行，加括号是将表达式视为一个整体
 *    - 取值规则：整个表达式结果 = **最后一个表达式的值**
 *    - 重要说明：
 *      无论是否加括号，所有表达式都会执行，执行顺序都是从左到右，结果取最右边的值，有时加括号时结果取最左边的值，是
 *      因为逗号运算符的优先级低于等号运算符
 */
/*
 * 逻辑运算符测试
 */
void relational_operator_test()
{
	int a = 1, b = 2, c = 3;
	int i = a < b < c;
	//a < b => true(1) ,1 < 3 => true => 1
	printf("%d\n", i);

	// 短路 与 expression1 && expression2，只有expression1为真时才执行expression2，expression1为假不会执行expression2
	// 短路 或 同理,同样会短路
	int x = 100, y = 10;
	if (x < 20 && ++y)
	{

	}
	printf("y = %d\n", y);
	printf("-------------------------------------\n");
}

/*
 * 逗号表达式执行顺序测试
 *    执行顺序是从左往右，不加括号结果取最左边值是因为逗号运算符的优先级低于等于运算符
 *    执行顺序是从左往右，结果取最右边值是因为加了括号后整个表达式被视为一个整体
 */
void comma_expression_test_1()
{
	int a = 3, b = 5, c = 7;
	int i = 0;
	// 取最左边的表达式的运算结果
	i = a + b, b += 2, c += 8;
	printf("i = %d, b = %d\n", i, b);

	int x = 3, y = 5, z = 7;
	int j = 0;
	// 取最右边的表达式的运算结果
	j = (x + y, y += 2, z += 8);
	printf("j = %d, y = %d\n", j, y);

	int m = 5, n = -5;
	// 死循环效果
//    while (m > 0)
//    {
//        printf("死循环......\n");
//    }
	// 非死循环效果
	while (m > 0, n > 0)
	{
		printf("死循环......\n");
	}
	printf("-------------------------------------\n");
}

/*
 * 逗号表达式测试
 *
 * 验证并非只是执行最左边或者最右边的表达式，而是执行所有的表达式
 */
void comma_expression_test_2()
{
	int a = 3, b = 5, c = 7;
	int i = 0;
	// 取最左边的表达式的运算结果(执行顺序是从左往右，不加括号结果取最左边值是因为逗号运算符的优先级低于等于运算符)
	i = b = a + b, b += 3, c += 8;
	printf("i = %d, b= %d\n", i, b);

	int x = 3, y = 5, z = 7;
	int j = 0;
	// 取最右边的表达式的运算结果(执行顺序是从左往右，结果取最右边值是因为加了括号后整个表达式被视为一个整体)
	j = (y = x + y, y += 3, z += 8);
	printf("j = %d, y = %d\n", j, y);
	printf("-------------------------------------\n");
}

/*
 * 逗号表达式测试
 *
 * 逗号表达式实际应用
 * 特别注意：不加括号和加括号，表达式执行顺序都是从左往右依次执行，只是根据是否加括号决定取最右边和最左边的表达式的计算结果
 */
void comma_expression_test_3()
{
	int x = 0;
	if (printf("请输入一个数字:\n"), scanf("%d", &x), x > 0)
	{
		printf("输入的值大于0\n");
	}
	else
	{
		printf("输入的值小于0\n");
	}
	printf("-------------------------------------\n");
}

int main()
{
	relational_operator_test();
	comma_expression_test_1();
	//comma_expression_test_2();
	//comma_expression_test_3();
	return 0;
}
