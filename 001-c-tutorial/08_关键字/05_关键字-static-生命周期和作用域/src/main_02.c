#include <stdio.h>
/*
 * const和static配合使用
 */

#if 0
#endif
int main()
{
	// const和static配合使用时，不管谁在前面都可以
	static const int i = 100;
	printf("i = %d\n", i);
	const static int j = 200;
	printf("j = %d\n", j);
	return 0;
}
