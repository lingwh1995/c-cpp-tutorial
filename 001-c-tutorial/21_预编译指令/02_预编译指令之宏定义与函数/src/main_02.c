#include <stdio.h>
// 求绝对值
#define ABS(a) (a) < 0 ? -(a) : (a)
// 求最大值
#define MAX(a,b)  ((a)>(b)?(a):(b))
// 求最小值
#define MIN(a,b)  ((a)<(b)?(a):(b))
// 平方
#define SQR(x)    ((x)*(x))
// 置位第n位
#define SET_BIT(x,n)   ((x) |=  (1<<(n)))
// 清零第n位
#define CLR_BIT(x,n)   ((x) &= ~(1<<(n)))
// 判断第n位是否为1
#define CHECK_BIT(x,n) (((x)>>(n)) & 1)
// 数组元素个数
#define ARR_LEN(arr)  (sizeof(arr)/sizeof((arr)[0]))
//结构体偏移
#define OFFSET_OF(type, member)  ((size_t)&((type*)0)->member)
// 字符串化
#define STR(x)  #x  // STR(123)  →  "123"
// 拼接两个参数
#define CONCAT(a,b)  a##b // CONCAT(num,1) → num1

/**
 * 宏定义经典应用场景
 *
 * 1. 定义常量，替代魔法数字，如圆周率、数组的大小
 *      #define PI       3.141
 *      #define MAX_LEN  1024
 *      #define OK       0
 *      #define ERROR    1
 *
 * 3. 定义一些简单类函数宏
 *      // 求最大值
 *      #define MAX(a,b)  ((a)>(b)?(a):(b))
 *      // 求最小值
 *      #define MIN(a,b)  ((a)<(b)?(a):(b))
 *      // 平方
 *      #define SQR(x)    ((x)*(x))
 *
 * 4. 多行代码宏（封装代码块），用 do{}while(0) 包裹，解决 if 不分号、代码断块问题，工程标准写法。
 *      #define PRINT_HELLO()  \
 *      do{                   \
 *         printf("hello\n");\
 *         printf("c语言宏\n");\
 *      }while(0)
 *
 * 5. 跨平台兼容
 *      #define WIN_SYSTEM
 *
 *      #ifdef WIN_SYSTEM
 *      #include <windows.h>
 *      #else
 *      #include <unistd.h>
 *
 * 6. 防止重复引入头文件
 *      #ifndef 文件名全大写_H
 *      #define 文件名全大写_H
 *
 *      // 这里放函数声明、结构体、宏、全局变量声明
 *
 *      #endif
 *
 * 7. 定义别名，屏蔽关键字
 *      #define UINT unsigned int
 *      #define TRUE 1
 *      #define FALSE 0
 *
 * 8. 模拟bool和true, false
 *      // 使用宏定义模拟bool类型
 *      #define bool int
 *      #define true 1
 *      #define false 0
 */

/**
 * 演示一些常用的类函数宏
 */
#if 0
int main()
{
    const int a = -10;
    const int b = 10;
    printf("ABS(a) = %d, ABS(-a) = %d\n", ABS(a), ABS(-a));

    printf("MAX(a,b) = %d\n", MAX(a,b));
    printf("MIN(a,b) = %d\n", MIN(a,b));
    printf("SQR(b) = %d\n", SQR(b));

    int arr[] = { 1, 3, 5, 7, 9 };
    const int len = ARR_LEN(arr);
    printf("len = %d\n", len);
    return 0;
}
#endif