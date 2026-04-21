#include <stdio.h>

/**
 * 冒泡排序基础版
 */

/**
 * 交换两个数字
 */
void swap_number_1(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * 冒泡排序
 */
void bubble_sort_1(int *arr, int len)
{
	if(NULL == arr || len < 2)
	{
		return;
	}
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(arr[j] > arr[j + 1])
			{
				swap_number_1(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/**
 * 打印数组
 */
void print_arr_1(const int *arr, const int len)
{
	for(int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
}

#if 0
int main()
{
	int arr[] = { 5, 1, 9, 7, 3 };
	int len = sizeof(arr)/sizeof(arr[0]);
	// 冒泡排序
	bubble_sort_1(arr, len);
	// 打印数组
	print_arr_1(arr, len);
	return 0;
}
#endif

