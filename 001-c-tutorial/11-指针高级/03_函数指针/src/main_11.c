#include <stdio.h>

int sum(int a, int b)
{
	return a + b;
}

typedef int (*pfun_2)(int, int);

#if 0
int main()
{
	int a = 10;
	printf("&a = %p\n", &a);
	// 把字面常量（十六进制地址）转换为整形指针，注意：每次运行这个字面常量会改变，取的是 &a 的值
	*((int *)0x0064FF1C) = 100;
	printf("a = %d\n", a);

	printf("&sum = %p\n", sum);
	int (*pfun_1)(int, int) = sum;
	a = (*pfun_1)(10, 20);
	printf("a = %d\n", a);

	// 把字面常量（十六进制地址）转换为函数指针，注意：每次运行这个字面常量会改变，取的是 &sum 的值
	a = (*(int (*)(int, int))0x004020D4)(20, 30);
	printf("a = %d\n", a);

	a = (*(pfun_2)0x004020D4)(30, 40);
	printf("a = %d\n", a);
	return 0;
}
#endif
