#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * 1.二维数组版学生管理系统
 * 2.二维数组相加
 * 3.二级指针模拟二维数组
 */

// 学生个数
#define STUDENTS 3
// 课程个数
#define SUBJECTS 4

// 行数
#define ROWS 3
// 列数
#define COLS 3

#define N 5
#define LEN 10

/**
 * 二维数组版学生管理系统测试
 */
void td_arr_sms_test()
{
    // 存储3个学生4门课程的成绩
    char names[STUDENTS][10] = { "张三", "李四", "王五" };
    float scores[STUDENTS][SUBJECTS] = {
        {85.5, 90.0, 78.5, 92.0},
        {76.0, 88.5, 82.0, 79.5},
        {92.5, 85.0, 90.5, 88.0}
    };

    // 计算每个学生的平均成绩
    printf("学生成绩单:\n");
    printf("姓名\t语文\t数学\t英语\t物理\t平均分\n");
    printf("---------------------------------------------\n");

    for(int i = 0; i < STUDENTS; i++)
    {
        float sum = 0;
        printf("%-10s\t", names[i]);
        for(int j = 0; j < SUBJECTS; j++)
        {
            printf("%.1f\t", scores[i][j]);
            sum += scores[i][j];
        }
        float average = sum / SUBJECTS;
        printf("%.2f\n", average);
    }
}

/**
 * 二维数相加测试
 */
void td_arr_add_test()
{
    int arr_1[ROWS][COLS] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    int arr_2[ROWS][COLS] = { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } };
    int arr_result[ROWS][COLS];
    for(int i = 0; i < ROWS; i++)
    {
    	for(int j = 0; j < COLS; j++)
    	{
    		arr_result[i][j] = arr_1[i][j] + arr_2[i][j];
    	}
    }
    printf("二维数组相加结果：\n");
    for(int i = 0; i < ROWS; i++)
    {
    	for(int j = 0; j < COLS; j++)
    	{
    		printf("arr_result[%d][%d] = %d\t", i, j, arr_result[i][j]);
    	}
    	printf("\n");
    }
}

/**
 * 二级指针模拟二维数组
 */
void double_pointer_simulate_td_arr_test()
{
    // 使用二级指针创建类似二维数组的结构
    int rows = 3, cols = 4;

    // 1. 分配二级指针数组
    int **arr = (int **)malloc(rows * sizeof(int *));
    printf("分配了 %d 个指针的空间\n", rows);

    // 2. 为每一行分配内存
    for(int i = 0; i < rows; i++)
    {
    	arr[i] = (int *)malloc(cols * sizeof(int));
        printf("第 %d 行分配了 %d 个整数的空间\n", i, cols);
    }

    // 3. 初始化数据
    int value = 1;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
        	arr[i][j] = value++;
        }
    }

    // 4. 访问数据
    printf("\n使用二级指针访问数据:\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // 5. 展示内存布局(非连续)
    printf("\n内存地址演示(非连续存储):\n");
    for(int i = 0; i < rows; i++)
    {
        printf("第 %d 行起始地址: %p\n", i, arr[i]);
    }

    // 6. 释放内存
    for(int i = 0; i < rows; i++)
    {
    	// 释放每行内存
        free(arr[i]);
        printf("释放第 %d 行内存\n", i);
    }
    // 释放指针数组
    free(arr);
    printf("释放指针数组内存\n\n");
}

/**
 * 根据一维数组还原二维数组
 */
void print_td_arr_by_onetd_arr_test()
{
	int arr[] = { 1, 3, 0, 2 };
	int rows = 4;
	int cols = 4;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			if(arr[i] == j)
			{
				printf("%s\t", "o");
			}
			else
			{
				printf("%s\t", "#");
			}
		}
		printf("\n");
	}
}

/**
 * 打印二维字符数组
 * 	注意： 这里实际上是使用下标方式访问数组，使用下标方式访问数组本质就是使用指针方式访问数组
 */
//void print_td_arr_1(const char **p_str, int n)
void print_td_arr_1(const char *p_str[], int n)
{
	if(NULL == p_str)
	{
		return;
	}
	for(int i = 0; i < n; i++)
	{
		printf("%s\n", p_str[i]); // printf("%s\n", *(p_str + i));
	}
	printf("\n");
}

/**
 * 二维字符数组冒泡排序
 */
void td_arr_bubble_sort_1(const char *p_str[], int n)
{
	if(NULL == p_str)
	{
		return;
	}
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = 0; j < n - 1 - i; j++)
		{
			if(strcmp(p_str[j], p_str[j + 1]) > 0)
			{
				const char *temp = p_str[j];
				p_str[j] = p_str[j + 1];
				p_str[j + 1] = temp;
			}
		}
	}
}

/**
 * 二维字符数组排序测试
 */
void td_arr_bubble_sort_test_1()
{
	const char *p_str[N] = { "tulun", "complex", "newdata", "math", "locale" };
	/**
	 *  二维数组p_str内存结构图简化版
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
	print_td_arr_1(p_str, N);
	td_arr_bubble_sort_1(p_str, N);
	print_td_arr_1(p_str, N);
}

/**
 * 初始化二维数组
 */
void init_td_arr(char (*p_str)[LEN], int rows)
{
	assert(NULL != p_str);
    printf("请输入%d个字符串作为数组内容\n", rows);
	for(int i = 0; i < rows; i++)
	{
		gets(p_str[i]);
	}
    printf("--------------------\n");
}


/**
 * 二维字符数组冒泡排序
 */
void td_arr_bubble_sort_2(char (*p_str)[LEN], int rows, int len)
{
	if(NULL == p_str)
	{
		return;
	}
	if(rows < 1)
	{
		return;
	}
	char *temp = (char *)malloc(sizeof(char) * len);
	for(int i = 0; i < rows - 1; i++)
	{
		for(int j = 0; j < rows - 1 - i; j++)
		{
			if(strcmp(p_str[j], p_str[j + 1]) > 0)
			{
				strcpy(temp, p_str[j]);
				strcpy(p_str[j], p_str[j + 1]);
				strcpy(p_str[j + 1], temp);
			}
		}
	}
	// 释放内存
	free(temp);
	// 手动将指针置为空
	temp = NULL;
}

/**
 * 打印二维数组
 */
void print_td_arr_2(char (*p_str)[LEN], int rows)
{
	for(int i = 0; i < rows; i++)
	{
		printf("%s\n", p_str[i]); // printf("%s\n", *(p_str + i));
	}
	printf("\n");
}

/**
 * 二维字符数组排序测试
 */
void td_arr_bubble_sort_test_2()
{
	char str[N][LEN] = { 0 };
	init_td_arr(str, N);
	td_arr_bubble_sort_2(str, N, LEN);
	print_td_arr_2(str, N);
}

#if 0
#endif
int main()
{
	//td_arr_sms_test();
	//td_arr_add_test();
	//double_pointer_simulate_td_arr_test();
	//print_td_arr_by_onetd_arr_test();
	//td_arr_bubble_sort_test_1();
	td_arr_bubble_sort_test_2();
	return 0;
}
