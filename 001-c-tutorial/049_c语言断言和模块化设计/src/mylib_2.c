#include "../inc/mylib_2.h"
#include <time.h>
#include <assert.h>

/*
 * 从数组中查找当前值，查找到返回数组索引，查找不到返回-1
 * @param *arr 代表数组的指针
 * @param n 当前元素在目标数组中的索引
 * @param val 要确定是否存在于当前数组中的值
 */
/*
int find_value_3(const int *arr, int n, int val)
{
	assert(NULL != arr);
	if (n < 1) return -1;
	int position = -1;
	for (int i = 0; i < n; i++)
	{
		if (val == arr[i])
		{
			position = i;
		}
	}
	return position;
}
*/
int find_value_3(const int *arr, int n, int val)
{
	assert(NULL != arr);
	if (n < 1) return -1;
	int position = n - 1;
	while (position >= 0 && arr[position] != val)
	{
		position--;
	}
	return position;
}

/*
 * 初始化数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void init_arr_3(int *arr, int len)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == arr || len < 1) return;
	//使用断言判断参数是否合法，表达式为真，继续向下执行，表达式为假，弹出窗提示
	assert(NULL != arr && len >= 1);
	srand((unsigned)time(NULL));
	int i = 0;
	while (i < 100)
	{
		int r = rand() % 100 + 1;
		int position = find_value_3(arr, i, r);
		if (position == -1)
		{
			arr[i] = r;
			i++;
		}
	}
}

/*
 * 交换两个数
 * @param *pa 代表第一个数的指针
 * @param *pb 代表第二个数的指针
 */
void swap_number_3(int *pa, int *pb)
{
	//使用传统if else 判断参数是否合法
	//if (NULL == pa || NULL == pb) return;
	//使用断言判断参数是否合法，表达式为真，继续向下执行，表达式为假，弹出窗提示
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
void bubble_sort_3(int *arr, int len)
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
				swap_number_3(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/*
 * 打印数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
void print_arr_3(const int *arr, const int len)
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
