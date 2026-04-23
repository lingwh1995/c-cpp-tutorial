#include<stdio.h>

void write_int_data_to_file()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int n = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_int.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    for (int i = 0; i < n; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%d ", arr[i]);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

void write_double_data_to_file()
{
    const double arr[] = { 1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.0, 10.0 };
    const int n = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_double.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    for (int i = 0; i < n; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%.2f ", arr[i]);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

void write_str_data_to_file()
{
    const char arr[3][10] = {
        { "tulun" },
        { "hello" },
        { "world" }
    };
    const int n = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_str.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    for (int i = 0; i < n; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%s ", arr[i]);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

/**
 * 打印相对于文件开头的当前偏移量（以字节为单位）
 */
void ftell_test()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int n = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    printf("%p\n", fp);
    for (int i = 0; i < n; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%d ", arr[i]);
        const long pos = ftell(fp);
        printf("当前偏移：%ld\n", pos);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

int main()
{
    //write_int_data_to_file();
    //write_double_data_to_file();
    //write_str_data_to_file();
    ftell_test();
    return 0;
}