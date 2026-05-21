#include <stdio.h>

// 在全局位置处声明
int gi_1;
extern int gi_2;

#if 0
#endif
int main()
{
	// 在局部位置出声明
	extern int gi_3;

	printf("gi_1 = %d\n", gi_1);
	printf("gi_2 = %d\n", gi_2);
	printf("gi_3 = %d\n", gi_3);
	return 0;
}

int gi_1 = 10;
int gi_2 = 20;
int gi_3 = 30;
