#include <stdio.h>
#define ONE 1
#define TWO ONE + ONE
#define THREE ONE + TWO

/**
 * 预编译指令
 *
 * 1. 每个预编译指令都能要以#开头
 * 2. 每个预编译指令都要独占一行
 *
 * 预编译指令之宏定义
 *
 * 1. 宏定义的值在预处理阶段进行文本替换，不是字符串
 * 2. 宏在预处理阶段进行简单的文本替换，不涉及类型检查或语法分析，不占用运行时间，只占用编译时间
 * 3. 宏定义是全局性的，必要时可以取消宏定义
 * 4. 宏替换后的代码运行时，无法在逐语句调试时进入 debug 状态，调试时会直接显示反汇编代码
 * 5. 宏替换比直接执行函数速度快，因为避免了函数调用的开销（压栈、跳转、返回等），宏不关注数据类型，函数关注数据类型
 * 6. 编译器会提供一些预定义的宏
 */

/**
 * 演示错误的宏定义（宏的本质是展开，这个没有宏定义时没有加括号，展开就会报错）
 */
#if 0
int main()
{
    printf("宏 ONE = %d\n", ONE);
    printf("宏 TWO = %d\n", TWO);
    printf("宏 THREE = %d\n", THREE);

    // int a = 1;
    int a = ONE;
    // int b = 1 + 1 * 2;
    int b = TWO * 2;
    // int c = 1 + 1 + 1 * 3;
    int c = THREE * 3;
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    return 0;
}
#endif