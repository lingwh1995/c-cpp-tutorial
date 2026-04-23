#include<stdio.h>

int main()
{
    char buffer[26];
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int  n = sizeof(arr) / sizeof(arr[0]);
    FILE *fp = fopen("file.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return 1;
    }
    printf("开始给文件中写入内容......\n");
    for (int i = 0; i < n; i++)
    {
        // printf("%d ", arr[i]);
        // sprintf(buffer, "%d ", arr[i]);

        // 把内容写入到缓冲区
        fprintf(fp, "%d ", arr[i]);
    }

    /**
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     * 这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
    return 0;
}