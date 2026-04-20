#include <stdio.h>
#include <stdbool.h>

/**
 * 使用函数指针优化冒泡排序
 */

/**
 * 交换两个数字
 */
void swap_number_2(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * 判断a是否大于b
 */
bool greater(int a, int b)
{
	return a > b;
}

/**
 * 判断a是否小于b
 */
bool less(int a, int b)
{
	return a < b;
}

/**
 * 冒泡排序
 */
void bubble_sort_2(int *arr, int len, int (*compare)(int, int))
{
	if(NULL == arr || len < 2)
	{
		return;
	}
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(compare(arr[j], arr[j + 1]))
			{
				swap_number_2(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/**
 * 打印数组
 */
void print_arr_2(const int *arr, const int len)
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
	//bubble_sort_2(arr, len, greater);
	bubble_sort_2(arr, len, less);
	// 打印数组
	print_arr_2(arr, len);
	return 0;
}
#endif
