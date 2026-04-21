#include <stdio.h>

int add_num(int a, int b)
{
	return a + b;
}

int sub_num(int a, int b)
{
	return a - b;
}

int inc(int a)
{
	return a++;
}

#if 0
int main()
{
	int (*pfun)(int, int) = add_num;
	printf("sizeof(pfun) = %d\n", sizeof(pfun));
	printf("sizeof(*pfun) = %d\n ", sizeof(*pfun));
	printf("sizeof(*pfun) = %d\n ", sizeof(add_num));
	// 函数指针不能执行+1操作，虽然执行+1操作不报错，但是不能这样，因为函数占据空间的大小是不确定的
	//	pfun = pfun + 1;
}
#endif
