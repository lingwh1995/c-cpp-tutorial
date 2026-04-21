#include "../inc/mylib_1.h"
#include <time.h>
#include <assert.h>

/*
 * 初始化数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void init_arr_2(int *arr, int len)
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
void swap_number_2(int *pa, int *pb)
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
void bubble_sort_2(int *arr, int len)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == arr || len < 1) return;
	//使用断言判断参数是否合法，表达式为真，继续向下执行，表达式为假，弹出窗提示
	assert(NULL != arr && len >= 1);
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap_number_2(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/*
 * 打印数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void print_arr_2(const int *arr, const int len)
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
