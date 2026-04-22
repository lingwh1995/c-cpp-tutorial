#include <stdio.h>

/**
 * 数组名就是数组首元素地址
 */
void pointer_and_array_test_1()
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    //数组的地址
    printf("获取数组（首元素）的地址（方式一：数组名arr即为数组（首元素）的地址） = %p\n", arr);
    printf("获取数组（首元素）的地址（方式二：直接获取数组（首元素）的地址） = %p\n", &arr[0]);
    //数组的首元素地址
    int *p = &arr[0];
    printf("数组的首元素地址 = %p\n", p);
    printf("数组的首元素 = %d\n", *p);
    p = p + 1;
    printf("数组的第二个元素 = %d\n", *p);

    //下面的代码放开会报错,原因是: 数组的地址值是一个常量,如果要给常量重新赋值,是不合法的
    //arr = arr + 1;

    // 数组名等于数组首元素地址的原因，推导过程如下
    // &arr[0] => &*(arr + 0) => arr + 0 => arr
}

/*
 * 解引用符号*和[]的优先级
 */
void pointer_and_array_test_2()
{
    int a = 1, b = 2, c = 3, d = 4;
    //定义一个指针数组
    int *arr[5] = { &a, &b, &c, &d };
    //使用*+变量名为变量(数组中的元素)赋值，下面两种写法都是可以的
    *(arr[0]) = 100;
    *arr[1] = 200;
    printf("%d,%d\n", *arr[0], *arr[1]);
}

/*
 * 指针的运算
 */
void pointer_and_array_test_3()
{
    int arr_1[5] = { 1, 2, 3, 4, 5 };
    int size_1 = sizeof(arr_1) / sizeof(arr_1[0]);
    //int *pi = &arr_1[0];
    int *pi = arr_1;
    for (int i = 0; i < size_1; i++)
    {
        printf("arr_1[%d] = %d, pi = %p\n", i, *pi, pi);
        //相当于地址的值+4(个字节)
        //pi = pi + 1;
        pi++;
    }
    printf("------------------------\n");

    double arr_2[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    int size_2 = sizeof(arr_2) / sizeof(arr_2[0]);
    //double *pd = &arr_2[0];
    double *pd = arr_2;
    for (int i = 0; i < size_2; i++)
    {
        printf("arr_2[%d] = %f, pd = %p\n", i, *pd, pd);
        //相当于地址的值+8(个字节)
        //pd = pd + 1;
        pd++;
    }
    printf("------------------------\n");

    char arr_3[5] = { 'h', 'e', 'l', 'l', 'o' };
    int size_3 = sizeof(arr_3) / sizeof(arr_3[0]);
    //char *pc = &arr_3[0];
    char *pc = arr_3;
    for (int i = 0; i < size_3; i++)
    {
        printf("arr_3[%d] = %c, pc = %p\n", i, *pc, pc);
        //相当于地址的值+1(个字节)
        //pc = pc + 1;
        pc++;
    }
}


/**
 * 通过数组下标访问数组元素的本质是通过指针访问数组元素
 *
 * 测试arr[i]和i[arr]的执行效果是相同的
 * arr[i]之所以能正确的指向某一个元素，本质上是编译器把 arr[i]翻译成了 *(arr+i)
 * arr[i]和i[arr]都可以正确的打印出数组中的元素的原因?
 *  因为在编译器看来，arr[i]等同于 *(arr+i), i[arr] 等同于 *(i+arr)，所以说通过下标(arr[i])访问数组的方式实际上是通过指针访问数组
 *
 * 总结：	a[b] == *(a + b)
 */
void pointer_and_array_test_4()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < len; i++)
    {
        printf("数组里面第%d个元素的地址 = %p\n", i, (arr + i));
        printf("数组里面第%d个元素 = %d\n", i, arr[i]);
        printf("数组里面第%d个元素 = %d\n", i, i[arr]);
        printf("数组里面第%d个元素 = %d\n", i, *(arr + i));
    }
}


/**
 * 数组名的含义
 */
void pointer_and_array_test_5()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    //在sizeof()表达式中，数组名代表的是整个数组的意义，这包含了两个意义，即数组的类型+数组的大小
    int size = sizeof(arr);
    //在sizeof()表达式除外的其他地方,数组名都代表的是数组的首元素地址值
    printf("size = %d\n", size);
    printf("&arr = %p\n", arr);
}

void print_arr_by_while_pointer(const int *arr, int len)
{
	if(arr == NULL || len == 0)
	{
		return;
	}
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", *arr);
        // arr++;  等同于  arr = arr + 1 * sizeof(int);
        arr++;
    }
}

/**
 * 使用指针和while循环打印数组
 *
 * const int *start 到底限制什么？
 *   限制的是：不能修改 *start（指向的值）
 *   不限制：修改 start 本身（指针地址）
 *
 *   *start = 10;  //  报错（不能改值）
 *   start++;      //  允许（只改指针位置，不改值）
 */
void print_arr_by_while_loop(const int *start, const int *end)
{
    // 判断指针是否为空
    if(NULL == start || NULL == end)
    {
        return;
    }

    // 地址区间判断（防止 start 在 end 后面）
    if (start > end)
    {
        return;
    }

	while(start < end)
	{
		printf("%d\n", *start);
		start++;
	}
}

/**
 * 使用指针访问数组元素
 */
void pointer_and_array_test_6()
{
	// 数组名arr：常量地址，不能修改，a++会报错
    int arr[] = { 1, 2, 3, 4, 5 };
    int len = sizeof(arr) / sizeof(arr[0]);

    // 重点掌握，此用法非常巧妙，arr[i] 等同于 *(arr+i) 等同于 i[arr] 等同于 *(i+arr)
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("----------1-----------\n");

    // 指针变量arr：数组首元素地址，可以修改，a++不会报错
    print_arr_by_while_pointer(arr, len);
    printf("----------2-----------\n");

    for (int i = 0; i < len; i++)
    {
        printf("%p\n", arr + i);
    }
    printf("----------3-----------\n");

    for (int i = 0; i < len; i++)
    {
        printf("%d\n", *(arr + i));
    }
    printf("----------4-----------\n");

    print_arr_by_while_loop(arr, arr+5);
    printf("----------5-----------\n");
}

int main()
{
	//pointer_and_array_test_1();
    //pointer_and_array_test_2();
	//pointer_and_array_test_3();
	//pointer_and_array_test_4();
	//pointer_and_array_test_5();
	pointer_and_array_test_6();
    return 0;
}
