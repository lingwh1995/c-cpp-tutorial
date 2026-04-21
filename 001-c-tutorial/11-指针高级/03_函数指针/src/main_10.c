#include <stdio.h>

typedef void (*p_fun_t)(void);

void (*g_pfun)(void) = NULL;

void funa()
{
	printf("funa \n");
}

void funb()
{
	printf("funb \n");
}

/**
 * 这种写法用来解决内存不足的问题
 */
//void (*get_pfun(void (*p)(void)))(void)
p_fun_t get_pfun(p_fun_t p)
{
	void (*old)(void) = g_pfun;
	g_pfun = p;
	return old;
}

#if 0
int main()
{
	void (*p)(void) = NULL;
	p = get_pfun(funb);
	return 0;
}
#endif
