# include <stdio.h>

/**
 * 在终端执行 .\main.exe 1 2
 *
 * 控制台打印出来的内容是
 * 参数总个数 argc = 3
 * 第 0 个参数 = E:\repository\workspace\clion\personal\c-cpp-tutorial\001-c-tutorial\19_c语言接收外部参数\01_c语言接收外部参数示例\src\main.exe
 * 第 1 个参数 = 1
 * 第 2 个参数 = 2
 *
 * @param argc 参数个数
 * @param argv 参数列表
 * @return
 */
int main(const int argc, char *argv[])
{
    printf("参数总个数 argc = %d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("第 %d 个参数 = %s\n", i, argv[i]);
    }
    return 0;
}