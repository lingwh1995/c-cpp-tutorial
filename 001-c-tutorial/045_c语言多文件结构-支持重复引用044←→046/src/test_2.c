#include <stdio.h>
#include "../inc/mylib.h"

int fun2()
{
	printf("g = %d\n", g);
	int i = 10, j = 20;
	int k = add(i, j);
	printf("k = %d\n", k);
	return 0;
}
