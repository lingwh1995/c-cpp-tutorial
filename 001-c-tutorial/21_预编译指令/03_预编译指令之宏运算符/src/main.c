#include <stdio.h>
#define STR(s) #s
#define CONCAT(a,b) a##b
#define CHAR(x) char ch_##x[]=#x

/**
 * 宏运算符
 * #  字符串化运算符（stringify operator），将整个参数转换为字符串，只能用于单个参数
 * #@ 字符串运算符
 * ## 链接运算符（token pasting operator），将两个参数直接拼接成一个记号
 */
#if 0
#endif
int main()
{
    /**
     * 演示 # 会将宏参数字符串化
     */
    printf(STR(hello world!\n));
    // 输出：hello world!
    //        （这里会换行）✓

    printf(STR(path\to\file\n));
    // 输出：path	o ile
    //        （\t 被解释为制表符，\f 被解释为换页符）

    int xy = 100;
    printf("%d\n", CONCAT(x, y));
    printf("%s\n", "hello", "world");

    CHAR(a);
    // char ch_a[]="a";
    printf("%s\n", ch_a);

    const char* str = STR(b);
    printf("%c\n", str[0]);
    return 0;
}
