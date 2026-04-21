#include <stdio.h>
#include <time.h>
#include <assert.h>
#define ARSIZE 100

/*
 * 使用函数实现模块化设计 V1.0：使用单文件结构，所有工具函数提取到当前文件中
 * 使用断言校验参数
 *	断言和if else区别: 断言不通过会弹出窗口，if else不会弹出窗口
 *
 * 函数设计基本原则
 *  1.封装功能，对外隐藏内部实现
 *  2.参数校验，如一定要对指针类型参数进行判空
 *  3.函数的规模要小（代码量小于80行）
 *  4.函数的功能要单一，一个函数只完成一个功能
 *  5.函数的接口定义要清晰
 */

/*
 * 初始化数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void init_arr_1(int *arr, int len)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == arr || len < 1) return;
	//使用断言判断参数是否合法，表达式为真，继续向下执行，表达式为假，弹出窗提示
	assert(NULL != arr && len >= 1);
	srand((unsigned)time(NULL));
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % 100 + 1;
	}
}

/*
 * 交换两个数
 * @param *pa 代表第一个数的指针
 * @param *pb 代表第二个数的指针
 */
void swap_number_1(int *pa, int *pb)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == pa || NULL == pb) return;
	//使用断言判断参数是否合法,表达式为真，继续向下执行，表达式为假，弹出窗提示
	assert(NULL != pa && NULL != pb);
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

/*
 * 冒泡排序
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void bubble_sort_1(int *arr, int len)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == arr || len < 1) return;
	//使用断言判断参数是否合法，表达式为真，继续向下执行，表达式为假，弹出窗提示
	assert(NULL != arr && len >= 1);
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 -i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				swap_number_1(&arr[j], &arr[j+1]);
			}
		}
	}
}

/*
 * 打印数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void print_arr_1(const int *arr, const int len)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == arr || len < 1) return;
	//使用断言判断参数是否合法，表达式为真，继续向下执行，表达式为假，弹出窗提示
	assert(NULL != arr && len >= 1);
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
}

#if 0
#endif
int main()
{
	int arr[ARSIZE] = { 0 };
	int *p_arr = NULL;
	int val = 0;
	if (0 == val)
	{
		p_arr = arr;
	}
	init_arr_1(p_arr, ARSIZE);
	bubble_sort_1(p_arr, ARSIZE);
	print_arr_1(p_arr, ARSIZE);
	return 0;
}
