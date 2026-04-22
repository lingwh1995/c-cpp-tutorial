#include <stdio.h>
#include <string.h>
#define LEN 10

/**
 * 一维数组的定义
 * 一维数组的长度
 * 一维数组的两个属性
 * 不同数据类型数组中每一个元素在内存中的物理地址
 */

/**
 * 一维数组的定义
 */
void define_one_dimensional_array()
{
    // 错误的定义数组，演示一：n必须为一个常量，这里n不是一个常量
	/*
	 int n = 3;
	 int arr_1[n] = { 1, 2, 3 };
	 */

	// 错误的定义数组 演示二：c语言规定，数组变量一旦声明，就不能修改变量指向的地址，修改会报错，重新为数组变量赋值，改变原来的内存地址，就会报错
	/*
	 int arr_2[] = { 1, 2, 3 };
	 // 数组变量一旦定义好，就是一个常量，再去改变常量的值，会报错
	 //arr_2 = { 4, 5, 6 };
	 // 如果要给定义好的数组重新赋值，使用string.h中的memcpy()函数实现这个需求，如果是字符串，使用strcpy()处理
     */

    // 错误的定义数组 演示三：像这种数组的长度为5，但却初始化了10个元素，后面的五个元素是无法访问到的
    //int arr_2[5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 正确定义数组演示一
    int arr_3[3];
    // 正确定义数组演示二：使用宏来定义数组的长度
    int arr_4[LEN] = { 1, 2, 3 };
    // 正确定义数组演示三
    int arr_5[3] = { 1, 2, 3 };
    // 正确定义数组演示四
    int arr_6[3] = { 5 }; // 等同于 int arr_6[3] = { 5, 0, 0 };
    // 正确定义数组演示五
    int arr_7[3] = { 0 }; // 等同于 arr_7[3] = { 0, 0, 0 };
    // 正确定义数组演示六：可变长数组
    int n = 5;
    int arr_8[n];
    // 正确定义数组演示七
    // 指定为哪些位置的成员赋值
    int arr_9[6] = { [1] = 1, [3] = 3, [5] = 5 };
    // 指定位置的赋值可以不按照顺序，下面的写法与上面的例子是等价的
    int arr_10[6] = { [3] = 3, [1] = 1, [5] = 5 };
    // 指定位置的赋值与顺序赋值，可以结合使用
    int arr_11[6] = { 10, [1] = 1, 20, [3] = 3, 40, [5] = 5 };

    // 省略成员数量时，如果同时采用指定位置的赋值，那么数组长度将是最大的指定位置再加1
    int arr_12[] = { [2] = 2, [9] = 9 };
    printf("arr_11的长度 = %llu\n", sizeof(arr_11)/sizeof(arr_11[0]));
    int arr_13[] = { [9] = 9, [2] = 2 };
    printf("arr_12的长度 = %llu\n", sizeof(arr_12)/sizeof(arr_12[0]));

    // 正确定义数组演示八
    //c语言允许省略方括号里面的数组成员数量，这时将根据大括号里面的值的数量，自动确定数组的长度
    int arr_14[3] = { 1, 2, 3 }; // 等同于 int arr_13[] = { 1, 2, 3 };

    // 定义一个长度为5的整形数组，这里的长度是系统自动计算出来的
    int nums_1[] = { 1, 2, 3, 4, 5 };
    int len1 = sizeof(nums_1) / sizeof(nums_1[0]);
    printf("数组长度: len1 = %d\n", len1);
    for (int i = 0; i < len1; i++)
    {
        printf("%d\n", nums_1[i]);
    }
    printf("--------------------------------\n");

    // 定义一个长度为5的整形数组
    int nums_2[5] = { 1, 2, 3, 4, 5 };
    int len2 = sizeof(nums_2) / sizeof(nums_2[0]);
    printf("数组长度: len2 = %d\n", len2);
    for (int i = 0; i < len2; i++)
    {
        printf("%d\n", nums_2[i]);
    }
    printf("--------------------------------\n");

    // 数组长度为5,里面只包含三个元素,第4个和第5个元素因为没有被初始化,所以为值为0
    int nums_3[5] = { 1, 2, 3 };
    int len4 = sizeof(nums_3) / sizeof(nums_3[0]);
    printf("数组长度:%d\n", len4);
    for (int i = 0; i < len4; i++)
    {
        printf("%d\n", nums_3[i]);
    }
    printf("--------------------------------\n");
}

/**
 * 一维数组的长度
 */
void length_of_one_dimensional_array()
{
    // 如果定义数组时规定了数组的长度,那么不管真实的长度是多少,求出来的长度都是之前规定好的长度
    int arr_1[10] = { 1, 2, 3, 4, 5 };
    int len1 = sizeof(arr_1) / sizeof(arr_1[0]);

    // 如果定义数组时规定了数组的长度,那么不管真实的长度是多少,求出来的长度都是之前规定好的长度
    int arr_2[5] = { 1, 2, 3, 4, 5 };
    int len2 = sizeof(arr_2) / sizeof(arr_2[0]);

    // 如果定义数组时没有规定数组的长度,等号右边写了几个元素,数组的长度就是几
    int arr_3[] = { 1, 2, 3, 4, 5 };
    int len3 = sizeof(arr_3) / sizeof(arr_3[0]);

    printf("数组arr_1的长度 len1 = %d\n", len1);
    printf("数组arr_2的长度 len2 = %d\n", len2);
    printf("数组arr_3的长度 len3 = %d\n", len3);

    /**
     * strlen()方法深入探究
     *     注意: 为什么 strlen(chars_2) 的不是5?
     *     因为 strlen() 方法统计长度时遇到\0才会结束统计长度,是字符串专用方法,不适用于字符数组
     */
    char str[] = { "hello" };
    char chars_1[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    char chars_2[] = { 'h', 'e', 'l', 'l', 'o' };
    printf("str长度 = %d, chars_1 = %d, chars_2 = %d\n", strlen(str), strlen(chars_1), strlen(chars_2));
}

/**
 * 一维数组的两个属性
 *  数组的类型
 *  数组的大小
 */
void two_attribute_of_one_dimensional_array()
{
    // 计算数组所占空间大小的两种方式
    int arr[5] = { 1, 2, 3, 4, 5 };
    	// 方式一
    int size1 = sizeof(int) * 5;
    printf("数组arr所占空间大小 size1 = %d\n", size1);
    	// 方式二
    int size2 = sizeof(arr);
    printf("数组arr所占空间大小 size2 = %d\n", size2);

    char str1[] = { "hello" };
    // 注意:字符串的大小为 = 字符个数 * 一个char类型所占长度 + \0的大小 = 字符个数 * 1 + 1
    // 注意size3和size4的大小
    int size3 = sizeof(str1);
    printf("字符串str1所占空间大小 size3 = %d\n", size3);
    char str2[5] = { "hello" };
    // 注意size3和size4的大小
    int size4 = sizeof(str2);
    printf("字符串str2所占空间大小 size4 = %d\n", size4);

    // 计算数组长度大小
    int len1 = sizeof(arr) / sizeof(arr[0]);
    printf("数组arr长度 len1 = %d\n", len1);
    char str3[] = { "hello" };
    // 计算字符串长度专用方法
    int len2 = strlen(str3);
    printf("字符串str3长度 len2 = %d\n", len2);
}

/**
 * 查看不同数据类型数组中每一个元素在内存中的物理地址
 */
void view_memory_physical_address_of_one_dimensional_array()
{
    // 可以清晰的观察到一个字符占用一个字节
    char str[] = { "hello" };
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%p => %c\n", &str[i], str[i]);
    }
    printf("-----------------------------\n");

    // 可以清晰观察到一个int类型数据占4个字节
    int nums[] = { 1, 2, 3, 4, 5 };
    int len = sizeof(nums) / sizeof(nums[0]);
    for (int i = 0; i < len; i++)
    {
        printf("%p => %d\n", &nums[i], nums[i]);
    }
}

/**
 * 可变长数组
 */
void variable_length_array()
{
	int n = 10;

	// 注意：下面一行放开会报错
	//int arr_1[n] = { 1, 2, 3 };

	// 下面三行不会报错
	int arr_2[n];
	int arr_3[n + 5];
	int arr_4[n + 10];
	printf("arr_2的长度 = %d\n", sizeof(arr_2)/sizeof(arr_2[0]));
	printf("arr_3的长度 = %d\n", sizeof(arr_3)/sizeof(arr_3[0]));
	printf("arr_4的长度 = %d\n", sizeof(arr_4)/sizeof(arr_4[0]));
}

/**
 * 指针是一个常量，不能修改指针的值
 */
void pointIs_const()
{
	// 创建变量a、b
	int a = 10, b = 20;
	// 把变量a的内存地址存放在指针变量p中
	int *p = &a;
	// 把变量b的内存地址存放在指针变量p中
	p = &b;

	// 数组名就是数组的首元素的内存地址
	int arr = { 1,2,3 };
	// 修改数组的首元素的内存地址，会报错，内存地址一旦分配就是一个常量，不能修改
	//arr = { 4,5,6 };
}

#if 0
#endif
int main()
{
	//define_one_dimensional_array();
	//length_of_one_dimensional_array();
	//two_attribute_of_one_dimensional_array();
	//view_memory_physical_address_of_one_dimensional_array();
	variable_length_array();
    return 0;
}
