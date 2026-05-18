#include <stdio.h>
#include <stdlib.h>

#define MALLOC 1

/**
 * 单分支条件编译指令
 *   #if
 *     ......
 *   #else
 *     ......
 *   #endif
 */

int *get_mem(int n)
{
    if (n <= 0)
    {
        return NULL;
    }
    int* s = NULL;
#if MALLOC
    s = (int*)malloc(sizeof(int) * n);
#else
    s = new int[n];
#endif
    return s;
}

void free_mem(int *p)
{
#if MALLOC
    free(p);
#else
    delete []p;
#endif
}

#if 0
int main()
{
    int *p = get_mem(10);
    printf("p = %p\n", p);
    return 0;
}
#endif