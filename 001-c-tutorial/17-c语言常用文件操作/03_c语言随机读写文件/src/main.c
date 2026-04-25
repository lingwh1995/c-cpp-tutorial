#include<stdio.h>
#include<stdlib.h>

/**
* 将整数数组数据以二进制格式写入文件
 *
 * 该函数创建一个包含10个整数的数组，并使用fwrite函数将其以二进制格式写入到file_int.txt文件中。
 * 演示了C语言中二进制文件的写入操作，与文本文件写入不同，二进制写入直接保存内存中的原始数据，
 * 不使用格式化转换，效率更高且占用空间更小。适用于需要快速读写大量数据的场景。
 */
void fwrite_bin_int_data_to_file()
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
 * 从二进制文件中随机读取指定位置的整数
 *
 * 该函数打开file_bin.txt二进制文件，通过用户输入的位置索引实现随机访问读取。
 * 用户使用fseek定位到指定位置后，用fread读取一个整数并显示其十进制和十六进制值。
 * 输入负数时退出循环。演示了二进制文件的随机访问操作方法。
 */
void seek_fread_bin_int_data_from_file()
{
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
        printf("%d %x \n", val, val);
    }
    fclose(fp);
    fp = NULL;
}

/**
 * 向二进制文件的指定位置随机写入数组数据
 *
 * 该函数打开file_bin.txt二进制文件，通过用户输入的位置索引实现随机访问写入。
 * 用户使用fseek定位到指定位置后，用fwrite将预定义数组的所有元素写入文件。
 * 演示了二进制文件的随机写入操作方法。
 */
void seek_fwrite_bin_int_data_to_file()
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
     * 第三个参数 SEEK_SET 是文件定位的起始位置
     */
    fseek(fp, pos, SEEK_SET);
    fwrite(arr, sizeof(int), len, fp);
    fclose(fp);
    fp = NULL;
}

void seek_fread_bin_int_data_get_file_len()
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
    printf("file size is = %d byte!", len);
    fclose(fp);
    fp = NULL;
}

int main()
{
    //fwrite_bin_int_data_to_file();
    //seek_fread_bin_int_data_from_file();
    //seek_fwrite_bin_int_data_to_file();
    seek_fread_bin_int_data_get_file_len();
    return 0;
}