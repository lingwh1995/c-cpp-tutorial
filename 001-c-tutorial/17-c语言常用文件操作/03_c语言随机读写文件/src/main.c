#include <stdio.h>
#include <stdlib.h>

/**
* 将整数数组数据以二进制格式写入文件
 */
void fwrite_int_to_binary_file()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_bin.txt", "wb");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给文件中写入内容......\n");
    // 一次性把数组中所有内容直接以二进制形式写入到文件中
    fwrite(arr, sizeof(int), len, fp);
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

/**
 * 向二进制文件的指定位置随机写入数组数据
 */
void fwrite_int_to_binary_file_with_seek()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    int pos;
    FILE *fp = fopen("file_bin.txt", "wb");
    if (fp == NULL)
    {
        return;
    }
    printf("请输入要随机写入数组的索引位置:\n");
    scanf("%d", &pos);
    /**
     * 计算字节偏移量并定位文件指针
     * pos为整数索引，需乘以sizeof(int)转换为字节偏移
     * 第三个参数 SEEK_SET 代表偏移时从文件起始位置开始偏移
     */
    fseek(fp, pos, SEEK_SET);
    fwrite(arr, sizeof(int), len, fp);
    fclose(fp);
    fp = NULL;
}

/**
 * 从二进制文件中随机读取指定位置的整数
 */
void fread_int_from_binary_file_with_seek()
{
    int arr[10] = { 0 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    int val = 0;
    int pos;
    FILE *fp = fopen("file_bin.txt", "rb");
    if (fp == NULL)
    {
        return;
    }
    printf("请输入要随机访问数组的索引位置:\n");
    while (scanf("%d", &pos), pos >= 0)
    {
        val = -1;
        /**
         * 计算字节偏移量并定位文件指针
         * pos为整数索引，需乘以sizeof(int)转换为字节偏移
         * 第三个参数 SEEK_SET 是文件定位的起始位置
         */
        fseek(fp, pos * sizeof(int), SEEK_SET);
        fread(&val, sizeof(int), 1, fp);
        fread(arr, sizeof(int), len, fp);
        printf("%d %x \n", val, val);
    }
    fclose(fp);
    fp = NULL;
}

/**
 * 获取二进制文件的长度（字节数）
 */
void fread_get_file_len_use_seek_ftell()
{
    FILE *fp = fopen("file_bin.txt", "rb");
    if (fp == NULL)
    {
        return;
    }
    fseek(fp, 0, SEEK_END);
    /**
     * 计算字节偏移量并定位文件指针
     * pos为整数索引，需乘以sizeof(int)转换为字节偏移
     * 第三个参数 SEEK_END 是文件定位的末尾位置
     */
    int len = ftell(fp);
    printf("file len is = %d byte!", len);
    fclose(fp);
    fp = NULL;
}

/**
 * 使用rewind重置文件指针后从二进制文件读取整数数组
 */
void fread_seek_rewind()
{
    int arr[10] = { 0 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    FILE *fp = fopen("file_bin.txt", "rb");
    if (fp == NULL)
    {
        return;
    }
    // 从文件开头偏移4字节(一个 int 是4个字节，所以效果就是跳过数组的第一个元素)
    fseek(fp, 4, SEEK_SET);
    fread(arr, sizeof(int), len, fp);
    // 重置文件指针到开头
    rewind(fp);
    fread(arr, sizeof(int), len, fp);
    fclose(fp);
    fp = NULL;
}

/**
 * 使用fprintf写出文本文件并演示fflush和rewind效果
 *
 * fflush函数的一个作用
 * 1. 刷新缓冲区，就是把缓冲区的数据立即写入到文件中
 * 注意事项： fflush函数 对于输入流（如stdin），行为是未定义的（不应使用）
 *
 * rewind函数有两个作用
 * 1. 刷新缓冲区，就是把缓冲区的数据立即写入到文件中
 * 2. 将文件指针重新定位到起始位置，不会清除已经写入到数组中的数据
 */
void fprintf_fflush_and_rewind()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    FILE *fp = fopen("file_int.txt", "w");
    if (fp == NULL)
    {
        return;
    }
    // 从文件开头偏移4字节(一个 int 是4个字节，所以效果就是跳过数组的第一个元素)
    fseek(fp, 4, SEEK_SET);
    fprintf(fp, "%d ", arr[0]);
    fprintf(fp, "%d ", arr[1]);
    fprintf(fp, "%d ", arr[2]);
    fprintf(fp, "%d ", arr[3]);
    // 获取没有执行 rewind() 或 fflush() 之前的文件指针偏移量
    int before = ftell(fp);
    printf("没有执行 rewind() 或 fflush() 之前的文件指针偏移量 = %d\n", before);
    // 刷新缓冲区并重置文件指针到开头
    rewind(fp);
    // 刷新缓冲区
    //fflush(fp);
    int after = ftell(fp);
    printf("执行完成 rewind() 或 fflush() 之前的文件指针偏移量 = %d\n", after);
    fprintf(fp, "%d ", arr[6]);
    fprintf(fp, "%d ", arr[7]);
    fclose(fp);
    fp = NULL;
}

/**
 * 使用fscanf读取文本文件并演示fflush和rewind效果
 */
void fscanf_fflush_and_rewind()
{
    int val;
    FILE *fp = fopen("file_int.txt", "r");
    if (fp == NULL)
    {
        return;
    }
    fscanf(fp, "%d ", &val);
    printf("读取到的数字 = %d\n", val);
    // 获取没有执行 rewind() 或 fflush() 之前的文件指针偏移量
    int before = ftell(fp);
    printf("没有执行 rewind() 或 fflush() 之前的文件指针偏移量 = %d\n", before);
    // 刷新缓冲区并重置文件指针到开头
    rewind(fp);
    // 刷新缓冲区
    //fflush(fp);
    int after = ftell(fp);
    printf("执行完成 rewind() 或 fflush() 之前的文件指针偏移量 = %d\n", after);
    fscanf(fp, "%d ", &val);
    printf("读取到的数字 = %d\n", val);
    fclose(fp);
    fp = NULL;
}

int main()
{
    fwrite_int_to_binary_file();
    // fwrite_int_to_binary_file_with_seek();
    // fread_int_from_binary_file_with_seek();
    // fread_get_file_len_use_seek_ftell();
    // fread_seek_rewind();
    // fprintf_fflush_and_rewind();
    fscanf_fflush_and_rewind();
    return 0;
}