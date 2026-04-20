#include<stdio.h>

/**
 * 根据数组在内存中占据着连续空间这一特性，计算每种数据类型数据占据空间的大小
 */ 
int main()
{
    // char类型数据
    char arr_char[] = { 1, 2, 3, 4, 5 };
    printf("第一个元素内存地址 => %p\n",&arr_char[0]);
    printf("第二个元素内存地址 => %p\n",&arr_char[1]);
    int size_char = (long)&arr_char[1] - (long)&arr_char[0];
    printf("一个char类型数据占据的内存空间大小 =  %d\n", size_char);

    // short类型数据
    short arr_short[] = { 1, 2, 3, 4, 5 };
    printf("第一个元素内存地址 => %p\n",&arr_short[0]);
    printf("第二个元素内存地址 => %p\n",&arr_short[1]);
    int size_short = (long)&arr_short[1] - (long)&arr_short[0];
    printf("一个short类型数据占据的内存空间大小 =  %d\n", size_short);

    // int类型数据
    int arr_int[] = { 1, 2, 3, 4, 5 };
    printf("第一个元素内存地址 => %p\n",&arr_int[0]);
    printf("第二个元素内存地址 => %p\n",&arr_int[1]);
    int size_int = (long)&arr_int[1] - (long)&arr_int[0];
    printf("一个int类型数据占据的内存空间大小 =  %d\n", size_int);

    // double类型数据
    double arr_double[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    printf("第一个元素内存地址 => %p\n",&arr_double[0]);
    printf("第二个元素内存地址 => %p\n",&arr_double[1]);
    int size_double = (long)&arr_double[1] - (long)&arr_double[0];
    printf("一个double类型数据占据的内存空间大小 =  %d\n", size_double);

    return 0;
}
