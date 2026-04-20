#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../inc/calculator.h"

#if 0
#endif
//使用多文件结构(模块化设计)编写计算器程序:测试部分
int main()
{
	// 解决eclipse无法使用scanf()从控制台接收参数的问题
	setbuf(stdout, NULL);

	printf("请输入表达式: a op b\n");
	int a = 0, b = 0;
	char op = '\0';
	char ch = '\0';
	do
	{
		scanf("%d %c %d", &a, &op, &b); // 1 + 5\n
		calc(a, b, op);
		printf("输入y/Y继续:\n");
		//fflush(stdin);  // 清空缓冲区
		//Visual Studio中可以使用这个函数清空stdin缓冲区
		rewind(stdin);
		ch = getchar();
	} while (ch == 'y' || ch == 'Y');
	return 0;
}
