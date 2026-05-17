#include <stdio.h>

/**
 *  编译器中会提供一些预定义宏，以便于获取一些信息
 *
 *  __FILE__      // 展开成当前文件名，为字符串常量，可用 #line 指令更改
 *  __LINE__      // 展开成源文件行号，为整数常量，可用 #line 指令更改
 *  __DATE__      // 展开成翻译的日期，格式为 "mm dd yyyy" 的字符串常量。若月之日期小于 10 则
 *                // "dd" 的首字符为空格
 *  __TIME__      // 展开成翻译的时间，格式为 "hh:mm:ss" 的字符串常量
 *
 *  __STDC__      // 如果编译器遵循ANSI C，展开成整数常量1，否则未定义。判断当前的编译器是否为标准C编译器
 *
 *  __func__      // 在每个函数体内，拥有块作用域和静态存储期的预定义数组 __func__ 可用，
 *                // 它如同立即通过以下方式定义
 * void fun()
 * {
 *     static const char __func__[]="fun";
 * }
 */

// 可以修改 __FILE__ 和 __LINE__ 输出的内容
#line 100 "tulun.c"

#if 0
#endif
int main()
{
#ifdef __STDC__
    printf("标准C编译器\n");
#else
    printf("非标准C编译器\n");
#endif

#ifdef __STDC__
    // 标准C编译器标识
    printf("标准C编译器\n");
#endif

// C++ 编译器标识宏
#ifdef __cplusplus
    printf("C++编译器\n");
#else
    printf("C编译器\n");
#endif

    // 当前文件名
    printf("%s \n", __FILE__);
    // 源文件行号
    printf("%d \n", __LINE__);
    // 日期
    printf("%s \n", __DATE__);
    // 时间
    printf("%s \n", __TIME__);
    // 标准C编译器标识
    printf("%d \n", __STDC__);

    return 0;
}