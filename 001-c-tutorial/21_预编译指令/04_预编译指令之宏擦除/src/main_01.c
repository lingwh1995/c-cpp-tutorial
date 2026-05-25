#include <stdlib.h>

// 使用 宏定义 + calloc 实现 简化calloc
#define CALLOC(num,type) ((type*)calloc((num),sizeof(type)))
#define malloc void // 如果要禁用系统库函数，只使用宏定义
#undef malloc   // 如果要再次使用系统库函数，则需要释放掉宏定义

#if 0
#endif
int main()
{
    int *ip_calloc = (int*)calloc(10, sizeof(int));
    // 使用系统库函数 malloc
    int *ip_malloc = (int *)malloc(sizeof(int) * 10);
    int *ip_CALLOC = CALLOC(10, int);

    char *cp_calloc = (char*)calloc(10, sizeof(char));
    // 使用系统库函数 malloc
    char *cp_malloc = (char *)malloc(sizeof(char) * 10);
    char *cp_CALLOC = CALLOC(10, char);
    return 0;
}