#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define LEN 20

// 跨平台延迟函数（单位：毫秒）
void delay_ms(long ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

/**
 * fgetc() 用法测试： 每次读取一个字符
 *
 * fgetc() 返回值：
 *   - 成功：返回读取字符的 ASCII 值（int 类型）
 *   - 失败或到达文件末尾：返回 EOF（-1）
 */
void fgetc_test()
{
    FILE *fp = fopen("file_input.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        // 跨平台睡眠
        delay_ms(100);

        // 打印方式一
        putchar(c);
        // 打印方式二
        // printf("%c", c);

        // 强制刷新标准输入输出缓冲区，实现打字机效果，否则会在程序运行一段时间后(实际上是所有内容都写入到缓冲区之后)一次性显示完所有内容
        fflush(stdout);
    }
    fclose(fp);
    fp = NULL;
}

/**
 * feof() 用法测试
 *
 * 假设文件内容是 "AB"
 * fgetc(fp);  // 读到 'A'，feof(fp) 返回 0
 * fgetc(fp);  // 读到 'B'，feof(fp) 返回 0  ← 关键！还是0
 * fgetc(fp);  // 读到 EOF，feof(fp) 返回 1  ← 这时才变1
 */
void feof_test()
{
    FILE *fp = fopen("file_input.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    int c;
    while (1)
    {
        // 跨平台睡眠
        delay_ms(100);

        c = fgetc(fp);
        if (feof(fp))
        {
            break;
        }
        // 打印方式一
        putchar(c);
        // 打印方式二
        // printf("%c", c);

        // 强制刷新标准输入输出缓冲区，实现打字机效果，否则会在程序运行一段时间后(实际上是所有内容都写入到缓冲区之后)一次性显示完所有内容
        fflush(stdout);
    }
    fclose(fp);
    fp = NULL;
}

/**
 * fgets() 用法测试：按行读取并显示
 *
 * 功能：从 file_input.txt 逐行读取内容并输出到屏幕
 * 注意：fgets 每次读取一行（最多 LEN-1 个字符），保留换行符
 */
void fgets_test()
{
    FILE *fp = fopen("file_input.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char buf[LEN];

    /**
     * 循环逻辑 v1.0 写法
     */
    /*
    while (1)
    {
        // 跨平台睡眠
        delay_ms(200);

        // 特别注意： 每个 buf 中只能存放 LEN-1 个字符，最后一个是字符串结尾符 '\0'
        // 要验证，把 LEN 的值设置为5，执行程序就可以查看到效果了
        fgets(buf, LEN, fp);
        if (feof(fp))
        {
            break;
        }

        // 打印方式一
        //puts(buf);
        // 打印方式二
        printf("%s", buf);

        // 强制刷新标准输入输出缓冲区，实现打字机效果，否则会在程序运行一段时间后(实际上是所有内容都写入到缓冲区之后)一次性显示完所有内容
        fflush(stdout);
    }*/

    /**
     * 循环逻辑 v2.0 写法
     */
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        delay_ms(200);
        printf("%s", buf);
        fflush(stdout);
    }
    fclose(fp);
    fp = NULL;
}

/**
 * fputc() 用法测试：按字符读取并写入文件
 *
 * 功能：从 file_input.txt 逐字符读取内容，写入到 file_output.txt
 * 注意：fgetc 每次读取一个字符，返回 int 类型（EOF 或字符 ASCII 值）
 */
void fputc_test()
{
    FILE *fpi = fopen("file_input.txt", "r");
    FILE *fpo = fopen("file_output.txt", "w");
    if (fpi == NULL || fpo == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    printf("%s", "开始写入......\n");

    int c;
    while ((c = fgetc(fpi)) != EOF)
    {
        fputc(c, fpo);
    }

    fclose(fpi);
    fpi = NULL;
    fclose(fpo);
    fpo = NULL;
    printf("%s", "完成写入......\n");
}

/**
 * fputs() 用法测试：按行读取并写入文件
 *
 * 功能：从 file_input.txt 逐行读取内容，写入到 file_output.txt
 * 注意：fgets 每次读取一行（最多 sizeof(buf)-1 个字符），保留换行符
 */
void fputs_test()
{
    FILE *fpi = fopen("file_input.txt", "r");
    FILE *fpo = fopen("file_output.txt", "w");
    if (fpi == NULL || fpo == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char buf[LEN];
    printf("%s", "开始写入......\n");

    /**
     * 循环逻辑 v1.0 写法
     */
    /*
    while (1)
    {
        // 特别注意： 每个 buf 中只能存放 LEN-1 个字符，最后一个是字符串结尾符 '\0'
        // 要验证，把 LEN 的值设置为5，执行程序就可以查看到效果了
        fgets(buf, sizeof(buf), fpi);
        if (feof(fpi))
        {
            break;
        }

        fputs(buf, fpo);
    }*/

    /**
     * 循环逻辑 v2.0 写法
     */
    // fgets 返回 NULL 表示读到文件末尾或出错
    while (fgets(buf, sizeof(buf), fpi) != NULL)
    {
        fputs(buf, fpo);
    }
    fclose(fpi);
    fpi = NULL;
    fclose(fpo);
    fpo = NULL;
    printf("%s", "完成写入......\n");
}

int main()
{
    //fgetc_test();
    //feof_test();
    fgets_test();

    //fputc_test();
    //fputs_test();
    return 0;
}
