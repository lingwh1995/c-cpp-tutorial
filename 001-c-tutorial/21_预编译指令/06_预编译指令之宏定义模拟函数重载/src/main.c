#include <stdio.h>

#define swap_(type) swap_##type
#define SWAP(type) \
void swap_##type(type *pa, type *pb) \
{ \
    type tmp = *pa; \
    *pa = *pb; \
    *pb = tmp; \
}

// 必须要有下两行代码
SWAP(int)
SWAP(double)

/**
 * 使用宏定义实现类似于java中函数重载的效果
 */
#if 0
#endif
int main()
{
    int a = 10, b = 20;
    //swap_int(&a, &b);     // 直接调用宏定义的函数
    swap_(int)(&a, &b); // 把数据类型作为参数传递给宏定义
    printf("a = %d, b = %d\n", a, b);


    double x = 10.10, y = 20.20;
    //swap_double(&x, &y);   // 直接调用宏定义的函数
    swap_(double)(&x, &y);  // 把数据类型作为参数传递给宏定义
    printf("x = %.2f, y = %.2f\n", x, y);
    return 0;
}