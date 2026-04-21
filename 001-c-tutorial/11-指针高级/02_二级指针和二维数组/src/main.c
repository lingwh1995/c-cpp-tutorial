#include <stdio.h>

/**
 * 1.二级指针
 * 	 指向指针的指针
 * 2.二维数组
 * 	 定义：
 *   	二维数组可以看作是"数组的数组"，它在内存中以行优先的方式存储
 *   重要特性：
 *   	内存布局：二维数组在内存中是连续存储的，按行优先顺序排列
 *   	数组名含义：数组名代表第一行的首地址
 *   	传递给函数：传递二维数组给函数时，第二维的大小必须指定
 *   	索引从0开始：行索引和列索引都从0开始
 */


/*
	 使用typedef关键字简化二维数组定义，语法格式：typedef 数据类型 数组别名[行数][列数];

	 // 定义一个3行4列的整型二维数组类型
	 typedef int Matrix[3][4];

	 // 使用定义的类型创建数组
	 Matrix arr1;  // 等价于 int arr1[3][4];
	 Matrix arr2;  // 等价于 int arr2[3][4];
 */
#define ROWSSIZE 3
#define COLSSIZE 4
typedef int grad_type_t[ROWSSIZE][COLSSIZE];
#define N 5

/**
 * 二级指针基础知识
 */
void double_pointer_test()
{
	int a = 10, b = 20;
	printf("a = %d, &a = %p\n", a, &a);
	printf("b = %d, &b = %p\n", b, &b);
	int *p1 = &a;
	printf("p1 = %p, &p1 = %d\n", p1, &p1);
	int *p2 = NULL;
	printf("p2 = %d, &p2 = %d\n", p2, &p2);

	int **s = &p1;
	printf("*s = %p\n", *s);
	printf("**s = %d\n", **s);

	// *s => *&p1 => p1
	*s = &a;
	// **s = **&p1 => *p1 => a
	**s = 100; // a = 10;
	printf("*s = %p\n", *s);
	printf("a = %d, &a = %p\n", a, &a);

	s = &p2;
	// *s => *&p2 => p2
	*s = &b; // p2 = &b;
	printf("p2 = %p, &p2 = %d\n", p2, &p2);
	// **s => **&p2 => *p2 => b
	**s = 200;	// b = 200;
	printf("b = %d, &b = %p\n", b, &b);

	s = &p1;
	printf("s = %p\n", s);
	// s + 1 = s + sizeof(int *) * 1
	printf("s + 1 = %p\n", s + 1);
	printf("**s = %d\n", **s);

    int c = 30;
    int *p3 = &c;
    int **pp3 = &p3;
    printf("二级指针演示:\n");
    printf("c的值: %d， 地址: %p\n", c, &c);
    printf("p3的值: %p， 地址: %p\n", p3, &p3);
    printf("pp3的值: %p， pp3指向的值: %p, 二级指针解引用: %d\n", pp3, *pp3, **pp3);
}

/**
 * 二维数组基础知识
 */
void two_dimensional_arr_definition_test()
{
    // 方式1：使用一维数组方式进行初始化，系统会自动将一维数组识别成为二维数组
    int arr_1[2][3] = { 1, 2, 3, 4, 5, 6 };
    printf("二维数组arr_1中一维数组个数 = %d，一维数组中元素个数 = %d\n", sizeof(arr_1) / sizeof(arr_1[0]), sizeof(arr_1[0])/sizeof(arr_1[0][0]));

    // 方式2：完全初始化
    int arr_2[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
    printf("二维数组arr_2中一维数组个数 = %d，一维数组中元素个数 = %d\n", sizeof(arr_2) / sizeof(arr_2[0]), sizeof(arr_2[0])/sizeof(arr_2[0][0]));

    // 方式3：部分初始化（未初始化元素默认为0）
    int arr_3[2][3] = { { 1, 2 }, { 4 } };
    printf("二维数组arr_3中一维数组个数 = %d，一维数组中元素个数 = %d\n", sizeof(arr_3) / sizeof(arr_3[0]), sizeof(arr_3[0])/sizeof(arr_3[0][0]));

    // 方式4：省略第一维大小（二维数组第一维的大小可以计算得到，所以第一维大小可以省略）
    int arr_4[][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
    printf("二维数组arr_4中一维数组个数 = %d，一维数组中元素个数 = %d\n", sizeof(arr_4) / sizeof(arr_4[0]), sizeof(arr_4[0])/sizeof(arr_4[0][0]));

    // 方式4：逐个赋值
    int arr_5[2][3];
    printf("二维数组arr_5中一维数组个数 = %d，一维数组中元素个数 = %d\n", sizeof(arr_5) / sizeof(arr_5[0]), sizeof(arr_5[0])/sizeof(arr_5[0][0]));
    arr_5[0][0] = 1;
    arr_5[0][1] = 2;
    arr_5[0][2] = 3;
    arr_5[1][0] = 4;
    arr_5[1][1] = 5;
    arr_5[1][2] = 6;
}

/**
 * 一维数组和一级指针
 */
void one_dimensional_arr_add_one_pointer_test()
{
	// 使用一维数组演示使用指针指向整个数组，而不是使用指针指向数组的首元素
	int arr[4] = { 1, 2, 3, 4 };
	printf("sizeof(arr) = %d\n", sizeof(arr));
	// p指向的是数组首元素地址，而非整个数组
	int *p = arr; // 等同于 int *p = &arr;
	printf("sizeof(p) = %d\n", sizeof(p)); // 4个字节，32位系统指针占据4个字节，64位系统指针占据8个字节
	printf("sizeof(*p) = %d\n", sizeof(*p)); // 4个字节，*p 这里代表一维数组中第一个元素
	printf("p = %p\n", p);
	printf("p + 1 = %p\n", p + 1); // p + 1 增加了4个字节
	// s指向整个数组的地址，使用debug模式观察 *s 的值可以看到 *s 的值就是整个数组
	int (*s)[4] = &arr;
	printf("sizeof(s) = %d\n", sizeof(s)); // 4个字节，32位系统指针占据4个字节，64位系统指针占据8个字节
	printf("sizeof(*s) = %d\n", sizeof(*s)); // 16个字节，*s 这里代表整个一维数组
	printf("s = %p\n", s);
	printf("s + 1 = %p\n", s + 1); // s + 1增加了16个字节，因为s指向的是整个一维数组
}

/**
 * 二维数组和二级指针
 */
void two_dimensional_arr_add_double_pointer_test_1()
{
    int arr[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };
    // p代表二维数组首元素地址，使用debug模式观察可以看到 *p 的值就是二维数组中第一个元素
    int (*p)[4] = &arr[1];
    // s代表二维数组中第一个一维数组的首元素的地址，使用debug模式观察可以看到 *s 的值就是二维数组中第一个一维数组的首元素
    int *s = arr[1];
    printf("二维数组中第一个一维数组的首元素 = %d\n", *s);
    printf("p[1][3] = %d \n", p[1][3]); // p[1][3] => *(p[1] + 3) => *(*(p + 1) + 3)
    printf("s[3] = %d \n", s[3]); // s[3] => *(s + 3)
}

/**
 * 二维数组和二级指针
 */
void two_dimensional_arr_add_double_pointer_test_2()
{
    int arr[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };
    printf("sizeof(arr) = %d\n", sizeof(arr));
    // p代表二维数组首元素地址，使用debug模式观察可以看到 *p 的值就是整个二维数组中第一个元素
    int (*p)[4] = arr;
    printf("sizeof(*p) = %d\n", sizeof(*p));
    // 整个二维数组地址，使用debug模式观察 *s 的值可以看到 *s 的值就是整个二维数组
    int (*s)[3][4] = &arr;
    printf("sizeof(*s) = %d\n", sizeof(*s));
    // 二维数组中第一个一维数组的大小
    printf("sizeof(**s) = %d\n", sizeof(**s));
    // 4个字节，二维数组中第一个一维数组中第一个整形元素的大小
    printf("sizeof(***s) = %d\n", sizeof(***s));
}

/**
 * 二维数组和二级指针
 */
void two_dimensional_arr_add_double_pointer_test_3()
{
    int arr[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };

    // 不同的访问方式
    printf("二维数组元素访问方式:\n");

    // 1. 数组下标方式
    printf("arr[1][2] = %d\n", arr[1][2]);

    // 2. 指针方式
    printf("*(*(arr+1)+2) = %d\n", *(*(arr+1)+2));

    // 3. 混合方式
    printf("*(arr[1]+2) = %d\n", *(arr[1]+2));
    printf("*(*(arr+1)+2) = %d\n", *(*(arr+1)+2));

    printf("二维数组地址演示:\n");
    // 数组首地址
    printf("arr地址: %p\n", arr);
    // 第一行首地址
    printf("arr[0]地址: %p\n", arr[0]);
    // 第一行第一个元素地址
    printf("arr[0][0]地址: %p\n", &arr[0][0]);
    // 第一行第二个元素地址
    printf("&arr[0][0] + 1地址: %p\n", &arr[0][0] + 1);
}

/**
 * 遍历二维数组方式一-使用二维数组作为参数（注意：第二维必须指定大小）
 * 		二维数组指针的退化： int arr[3][4] => int arr[][4]
 */
void two_dimensional_arr_traverse_1(int arr[][4], int rows)
{
    printf("方式1:\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //printf("%d ", arr[i][j]);
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

/**
 * 遍历二维数组方式二-使用指针作为参数
 * 		二维数组指针的退化： int arr[3][4] => int arr[][4] => int (*)arr[4]
 */
void two_dimensional_arr_traverse_2(int (*arr)[4], int rows)
{
    printf("方式2:\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

/**
 * 遍历二维数组方式三-指针作为函数参数
 */
void two_dimensional_arr_traverse_3(int *arr, int rows, int cols)
{
	printf("方式3:\n");
	if(NULL == arr)
	{
		return;
	}
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%d ", *(arr + i * cols + j));
        }
        printf("\n");
    }
}

/**
 * 遍历二维数组方式四-使用typedef简化二维数组定义并且遍历该二维数组
 */
void two_dimensional_arr_traverse_4(grad_type_t matrix, int rows, int cols)
{
	printf("方式4:\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * 遍历二维数组
 */
void two_dimensional_arr_traverse_test()
{
    int arr[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };
    two_dimensional_arr_traverse_1(arr, 3);
    two_dimensional_arr_traverse_2(arr, 3);
    two_dimensional_arr_traverse_3(*arr, 3, 4);

    // 使用grad_type_t类型定义二维数组
    grad_type_t matrix = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };
	two_dimensional_arr_traverse_4(matrix, 3, 4);
}

/**
 * 二维数组经典应用场景-存放多个字符串
 */
void two_dimensional_arr_classic_application_scenarios_test()
{
	char names[3][10] = { "张三", "李四", "王五" };
	for(int i = 0; i < sizeof(names) / sizeof(names[0]); i++)
	{
		printf("%s\n", names[i]);
	}
}

/**
 * 二维数组和字符串
 */
void two_dimensional_arr_and_string_test()
{
	// 数组中每个元素存放的是一个字符数组（字符串），最直观的方式是使用debug模式观察 arr[0] 代表的值
	char arr[N][10] = { "tulun", "complex", "newdata", "math", "locale" };
	printf("sizeof(arr[0]) = %d\n", sizeof(arr[0]));
	printf("sizeof(arr[1]) = %d\n", sizeof(arr[1]));
	printf("sizeof(arr[2]) = %d\n", sizeof(arr[2]));
	for(int i = 0; i < N; i++)
	{
		printf("%s\n", arr[i]);
	}
	printf("-----------------------------\n");


	// 数组中每个元素存放的是一个指向只读数据区首元素地址的指针变量，最直观的方式是使用debug模式观察 arr[0] 代表的值
	const char *p_arr[N] = { "tulun", "complex", "newdata", "math", "locale" };
	/**
	 *  二维数组p_arr内存结构图简化版
	 *
	 *  +-------------------------- 栈区（低地址 → 高地址） -------------------------+
	 *	| 地址: 0xbffff400 | p_str[0] = 0x08048500  ←→  指向只读段的 "tulun" 首地址 |
	 *	| 地址: 0xbffff404 | p_str[1] = 0x08048506  ←→  指向只读段的 "complex" 首地址 |
	 *	| 地址: 0xbffff408 | p_str[2] = 0x0804850E  ←→  指向只读段的 "newdata" 首地址 |
	 *	| 地址: 0xbffff40C | p_str[3] = 0x08048515  ←→  指向只读段的 "math" 首地址 |
	 *	| 地址: 0xbffff410 | p_str[4] = 0x08048519  ←→  指向只读段的 "locale" 首地址 |
	 *	+---------------------------------------------------------------------------+
	 *
	 *	+------------------------ 只读数据段（.rodata，低地址 → 高地址） -------------+
	 *	| 地址: 0x08048500 | 't' 'u' 'l' 'u' 'n' '\0'  →  字符串 "tulun"             |
	 *	| 地址: 0x08048506 | 'c' 'o' 'm' 'p' 'l' 'e' 'x' '\0'  →  字符串 "complex"   |
	 *	| 地址: 0x0804850E | 'n' 'e' 'w' 'd' 'a' 't' 'a' '\0'  →  字符串 "newdata"   |
	 *	| 地址: 0x08048515 | 'm' 'a' 't' 'h' '\0'  →  字符串 "math"                 |
	 *	| 地址: 0x08048519 | 'l' 'o' 'c' 'a' 'l' '\0'  →  字符串 "locale"             |
	 *	+---------------------------------------------------------------------------+
	 */
	printf("sizeof(p_arr[0]) = %d\n", sizeof(p_arr[0]));
	printf("sizeof(p_arr[1]) = %d\n", sizeof(p_arr[1]));
	printf("sizeof(p_arr[2]) = %d\n", sizeof(p_arr[2]));
	for(int i = 0; i < N; i++)
	{
		printf("%s\n", p_arr[i]);
	}
}

#if 0
int main()
{
	//double_pointer_test();
	//two_dimensional_arr_definition_test();
	//one_dimensional_arr_add_one_pointer_test();
	//two_dimensional_arr_add_double_pointer_test_1();
	//two_dimensional_arr_add_double_pointer_test_2();
	//two_dimensional_arr_add_double_pointer_test_3();
	//two_dimensional_arr_traverse_test();
	//two_dimensional_arr_classic_application_scenarios_test();
    two_dimensional_arr_and_string_test();
	return 0;
}
#endif
