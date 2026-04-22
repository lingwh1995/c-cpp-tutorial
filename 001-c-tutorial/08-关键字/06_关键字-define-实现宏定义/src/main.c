#include <stdio.h>

/**
 * 宏定义
 * 		1.宏定义的变量会在预编译的时候替换，不会开辟空间，也没有类型，不会进行类型检查
 * 		2.宏名一般用大写
 * 		3.定义宏常量时最后面不要加分号（特别注意）
 * 宏的根本特性: 展开，所以定义宏参时要用括号括起来
 */

//定义一个宏常量,预编译之后会被替换掉
#define PI 3.14f

// 错误定义带参数的宏
//#define SUM(x,y) x*y
// 正确定义带参数的宏
#define SUM(x,y) (x)*(y)

#if 0
int main()
{
    // 打印宏常量
    printf("宏定义的常量PI = %.4f\n", PI);
    printf("-----------------------\n");

    //测试宏参
    int a = 2;
    int b = 3;
    int c = SUM(a, b);
    printf("c = %d\n", c);
    int d = SUM(a + 5, b + 5);
    // int d = a + 5 * b + 5
    printf("d = %d\n", d);
    return 0;
}
#endif
