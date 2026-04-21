#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/**
 * c语言实现常见算法
 *    1.冒泡排序
 *    2.二分查找（要求数组数有序数组）
 *    3.反转一维数组
 */

void left_move_arr_step_k_2(int *, int, int);
void right_move_arr_step_k_2(int *, int, int);
void print_arr(const int *, const int);
void reverse_arr(int *, int, int);
void left_move_arr_step_k_3(int *, int, int);

/**
 * @param ap a元素的地址
 * @param bp b元素的地址
 */
void swap_number(int *pa, int *pb)
{
	if(pa == NULL || pb == NULL)
	{
		return;
	}
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

/**
 * 打印数组
 */
void print_arr(const int *arr, const int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%-4d", arr[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
}

/**
 * 冒泡排序算法模型
 *    外层循环控制比较轮数            比较轮数(从0开始) = 数组的长度 - 1
 *    内层循环控制每一轮比较次数       每一轮比较次数 = 数组长度 - 当前比较轮数(从0开始) -1
 */
void bubble_sort_1()
{
	int nums[] = { 3, 9, 7, 1, 5 };
	int len = sizeof(nums) / sizeof(nums[0]);
	// 获取比较轮数
	int round = len - 1;
	for(int r = 0; r < round; r++)
	{
        // 获取每一轮比较次数
        int compareTimes = len - r - 1;
        for(int c = 0; c < compareTimes; c++)
        {
            if(nums[c] > nums[c+1])
            {
                swap_number(&nums[c],&nums[c+1]);
            }
        }
	}

	// 打印数组
	print_arr(nums, len);
}

/**
 * 定义大小为100的整形数组，使用随机函数给数组元素赋值，数值范围1-100，数组中元素可以重复，并且使用冒泡排序对数组元素进行排序（基础版）
 */
void bubble_sort_2()
{
    int nums[100] = { 0 };
    int len = sizeof(nums) / sizeof(nums[0]);
    srand((unsigned)time(NULL));
    // 生成100个可重复随机数
    for (int i = 0; i < len; i++)
    {
        nums[i] = rand() % len + 1;
    }
    // 冒泡排序
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                swap_number(&nums[j], &nums[j + 1]);
            }
        }
    }

	// 打印数组
	print_arr(nums, len);
}

/**
 * 定义大小为100的整形数组，使用随机函数给数组元素赋值，数值范围1-100，数组中元素可以重复，并且使用冒泡排序对数组元素进行排序（优化版）
 */
void bubble_sort_3()
{
    int nums[100] = { 0 };
    int len = sizeof(nums) / sizeof(nums[0]);
    // 生成100个可重复随机数
    srand((unsigned)time(NULL));
    for (int i = 0; i < len; i++)
    {
        nums[i] = rand() % len + 1;
    }
    // 冒泡排序
    for (int i = 0; i < len - 1; i++)
    {
    	// 本轮循环是否没有进行元素交换，如果没有进行元素交换，说明当前数组是有序数组
    	bool swapped = true;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (nums[j] > nums[j + 1])
            {
            	swapped = false;
                swap_number(&nums[j], &nums[j + 1]);
            }
        }
        if (swapped)
        {
            break;
        }
    }

	// 打印数组
	print_arr(nums, len);
}

/**
 * @param nums 数组nums的地址
 * @param k 查找重复元素结束索引
 * @param value 需要判断是否重复的元素
 */
int find_value(int *nums, int k, int value)
{
	int position = -1;
	for(int i = 0; i < k; i++)
	{
		if(nums[i] == value)
		{
			position = i;
		}
	}
	return position;
}

/**
 * 定义大小为100的整形数组，使用随机函数给数组元素赋值，数值范围1-100，数组中元素不可以重复，并且使用冒泡排序对数组元素进行排序（for循环版）
 */
void bubble_sort_4()
{
	int nums[100] = { 0 };
	int len = sizeof(nums) / sizeof(nums[0]);
	// 生成100个不重复随机数
	srand((unsigned)time(NULL));
	for(int i = 0; i < len; i++)
	{
		int r = rand() % len + 1;
		if(find_value(nums, i, r) == -1)
		{
			nums[i] = r;
		}
		else
		{
			// 如果find_value()返回值不为-1,则说明数组中已经有一个元素的值和r相等,则让i--,这是很巧妙的处理方法
			i--;
		}
	}
	// 冒泡排序
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(nums[j] > nums[j+1])
			{
				swap_number(&nums[j], &nums[j+1]);
			}
		}
	}

	// 打印数组
	print_arr(nums, len);
}

/**
 * 定义大小为100的整形数组，使用随机函数给数组元素赋值，数值范围1-100，数组中元素不可以重复，并且使用冒泡排序对数组元素进行排序（while循环版）
 */
void bubble_sort_5()
{
	int nums[100] = { 0 };
	int len = sizeof(nums) / sizeof(nums[0]);
	// 生成100个不重复随机数
	srand((unsigned)time(NULL));
	int i = 0;
	while(i < len)
	{
		int r = rand() % len + 1;
		if(find_value(nums,i,r) == -1)
		{
			nums[i] = r;
			i++;
		}
	}

	// 冒泡排序
	for(i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(nums[j] > nums[j+1])
			{
				swap_number(&nums[j], &nums[j+1]);
			}
		}
	}

	// 打印数组
	print_arr(nums, len);
}

/**
 * 定义大小为100的整形数组，使用随机函数给数组元素赋值，数值范围1-100，数组中元素不可以重复，并且使用冒泡排序对数组元素进行排序（查表版 方式一）
 */
void bubble_sort_6()
{
	int nums[100] = { 0 };
	int len = sizeof(nums) / sizeof(nums[0]);
	// 创建表
	int table[101] = { 0 };

	// 生成100个不重复随机数
	srand((unsigned)time(NULL));
	int i = 0;
	while(i < len)
	{
		int r = rand() % len + 1;
		if(table[r] == 0)
		{
			nums[i] = r;
			i++;
			table[r] = 1;
		}
	}

	// 冒泡排序
	for(i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(nums[j] > nums[j+1])
			{
				swap_number(&nums[j], &nums[j+1]);
			}
		}
	}

	// 打印数组
	print_arr(nums, len);
}

/**
 * 定义大小为100的整形数组，使用随机函数给数组元素赋值，数值范围1-100，数组中元素不可以重复，并且使用冒泡排序对数组元素进行排序（查表版 方式二）
 */
void bubble_sort_7()
{
	int nums[100] = { 0 };
	int len = sizeof(nums) / sizeof(nums[0]);
	// 创建表
	int table[101] = { 0 };

	// 生成100个不重复随机数
	srand((unsigned)time(NULL));
	int i = 0;
	while(i < len)
	{
		int r = rand() % len + 1;
		if(table[r] == 0)
		{
			i++;
			table[r] = r;
		}
	}

	// 不需要排序，因为按照上面的操作流程，table数组中存放的数据天然是有序的

	// 复制数组
	for(i = 0; i < len; i++)
	{
		nums[i] = table[i+1];
	}


	// 打印数组
	print_arr(nums, len);
}

/**
 * 冒泡排序 => 相邻两两比，一直交换
 */
void algorithm_01_bubble_sort()
{
	//bubble_sort_1();
	//bubble_sort_2();
	bubble_sort_3();
	//bubble_sort_4();
	//bubble_sort_5();
	//bubble_sort_6();
	//bubble_sort_7();
}

/**
 * 二分查找法：在数组中查询输入值的索引位置，如果没有查询到返回-1
 */
int binary_search_find_value(const int *arr, int n, int val)
{
	if(NULL == arr || n < 1)
	{
		return -1;
	}
	int position = -1;
	int left = 0, right = n - 1;
	while(left <= right)
	{
		// 注意： 这里的mid定义成局部变量就可以
		int mid = (left + right) / 2;
		printf("left = %d, right = %d, mid = %d\n", left, right, mid);
		if(arr[mid] > val)
		{
			right = mid - 1;
		}
		else if(arr[mid] < val)
		{
			left = mid + 1;
		}
		else
		{
			position = mid;
			break;
		}

	}
	return position;
}

/**
 * 测试二分查找 => 查找108在数组中的位置
 *
 *  0    1    2    3    4    5    6    7    8    9    10   11
 *
 * 第一轮： left = 0, right = 11, mid = (left + right) / 2 = (0 + 11) / 2 = 5
 * 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112
 *  ↑						 ▲				  		       ↑
 *
 * 第二轮： left = mid + 1 = 5 + 1 = 6, right = 11, mid = (left + right) / 2 = (6 + 11) / 2 = 8
 * 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112
 *  						      ↑			▲  		       ↑
 *
 * 第三轮： left = 6, right = mid - 1 = 8 - 1 = 7, mid = (left + right) / 2 = (6 + 7) / 2 = 6
 * 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112
 *  						     ↑ ▲   ↑
 *
 * 第四轮： left = mid + 1 = 6 + 1 = 7, right  7, mid = (left + right) / 2 = (7 + 7) / 2 = 7
 * 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112
 *  						          ↑▲↑
 *
 */
void algorithm_02_binary_search_find_value()
{
//	int arr[] = { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112 };
//	int val = 108;
	int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100, 110, 120 };
	int val = 95;
	val = 67;
	int n = sizeof(arr) / sizeof(arr[0]);
	int i = binary_search_find_value(arr, n, val);
	printf("%d在数组中的索引位置i = %d\n", val, i);
}

/**
 * 反转数组方式一（反转整个数组或者部分数组）
 */
void reverse_arr_1(int *arr, int left, int right)
{
	if(NULL == arr)
	{
		return;
	}
	for(int i = 0; i < (right - left) / 2; i++)
	{
		swap_number(&arr[i + left], &arr[right - i - 1]);
	}
}

/**
 * 反转数组方式二（反转整个数组或者部分数组）
 */
void reverse_arr_2(int *arr, int left, int right)
{
	if(NULL == arr)
	{
		return;
	}
	// 此种反转数组方式虽然不是最优，但是思路非常之好
	while(left < right)
	{
		swap_number(&arr[left], &arr[right - 1]);
		left++;
		right--;
	}
}

/**
 * 反转一维数组（反转整个数组或者部分数组）
 */
void algorithm_03_reverse_arr()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	// 反转数组方式一
//	reverse_arr_1(arr, 2, len);
//	print_arr(arr, len);

	// 反转数组方式二
	reverse_arr_2(arr, 2, len);
	print_arr(arr, len);
}

/**
 * 数组元素整体向右移动一位
 */
void right_move_arr_step_1(int *arr, int len)
{
   if(NULL == arr || len < 2)
   {
	   return;
   }
   // 保存最后一个元素，因为它会被覆盖
   int temp = arr[len - 1];

   // 从后往前移动元素（避免数据覆盖）
   for(int i = len - 1; i > 0; i--)
   {
        arr[i] = arr[i - 1];
   }

   // 将原来的最后一个元素放到第一个位置
   arr[0] = temp;
}

/**
 * 数组元素整体向左移动一位
 */
void left_move_arr_step_1(int *arr, int len)
{
   if(NULL == arr || len < 2)
   {
	   return;
   }
   // 保存最后一个元素，因为它会被覆盖
   int temp = arr[0];

   // 从前往后移动元素（避免数据覆盖）
   for(int i = 0; i < len; i++)
   {
        arr[i] = arr[i + 1];
   }

   // 将原来的第一个元素放到最后一个位置
   arr[len - 1] = temp;
}

/**
 * 数组元素整体向右移动k位：方式一
 */
void right_move_arr_step_k_1(int *arr, int len, int k)
{
	if(NULL == arr || len < 2)
	{
		return;
	}
	k = k % len;
	if(k > 0)
	{
		while(k--)
		{
			right_move_arr_step_1(arr, len);
		}
	}
	else
	{
		while(k++) // => 这行代码写的真牛逼
		{
			left_move_arr_step_1(arr, len);
		}
	}
}

/**
 * 数组元素整体向右移动k位：方式二
 */
void right_move_arr_step_k_2(int *arr, int len, int k)
{
	// 如果 k < 0，则调用左移的方法
	if(k < 0)
	{
		left_move_arr_step_k_2(arr, len, -k);
        return;
	}
    if(NULL == arr || len < 2)
    {
	    return;
    }
    // 处理k值大于数组长度的情况
    k = k % len;

    // 创建一个数组用于保存最后k个元素
    int *arr_temp = (int *)malloc(k * sizeof(int));

    // 把最后k个元素保存到临时数组中
    for(int i = 0; i < k; i++)
    {
        arr_temp[i] = arr[len - k + i];
    }

    // 从后往前移动元素（避免数据覆盖）
    for(int i = len; i > 0; i--)
    {
        arr[i] = arr[i - k];
    }

    // 把最后k个元素放到数组的开头
    for(int i = 0; i < k; i++)
    {
        arr[i] = arr_temp[i];
    }
}

/**
 * 数组元素整体向左移动k位：方式一
 */
void left_move_arr_step_k_1(int *arr, int len, int k)
{
	if(NULL == arr || len < 2)
	{
		return;
	}
	k = k % len;
	if(k > 0)
	{
		while(k--)
		{
			left_move_arr_step_1(arr, len);
		}
	}
	else
	{
		while(k++) // => 这行代码写的真牛逼
		{
			right_move_arr_step_1(arr, len);
		}
	}
}

/**
 * 数组元素整体向左移动k位：方式二
 */
void left_move_arr_step_k_2(int *arr, int len, int k)
{
	// 如果 k < 0，则调用右移的方法
	if(k < 0)
	{
		right_move_arr_step_k_2(arr, len, -k);
        return;
	}
    if(NULL == arr || len < 2)
    {
	    return;
    }
    // 处理k值大于数组长度的情况
    k = k % len;

    // 创建一个数组用于保存前k个元素
    int *arr_temp = (int *)malloc(k * sizeof(int));

    // 把前k个元素保存到临时数组中
    for(int i = 0; i < k; i++)
    {
        arr_temp[i] = arr[i];
    }

    // 从前往后移动元素（避免数据覆盖）
    for(int i = 0; i < len; i++)
    {
        arr[i] = arr[i + k];
    }

    // 把前k个元素放到数组的结尾
    for(int i = 0; i < k; i++)
    {
        arr[len - k + i] = arr_temp[i];
    }
}

/**
 * 数组元素整体向左移动k位：方式三
 */
void right_move_arr_step_k_3(int *arr, int len, int k)
{
    if(k < 0)
    {
        left_move_arr_step_k_3(arr, len, -k);
        return;
    }
    if(NULL == arr || len < 2 || k < 1)
    {
        return;
    }
    k = k % len;
    reverse_arr(arr, len-k, len-1);
    printf("第一次反转 => 反转 len-k到len-1 ：");
    print_arr(arr, len);
    reverse_arr(arr, 0, len-k-1);
    printf("第二次反转 => 反转 0到len-k-1      ：");
    print_arr(arr, len);
    reverse_arr(arr, 0, len-1);
    printf("第三次反转 => 反转 0到len-1        ：");
    print_arr(arr, len);
}

/**
 * 反转数组
 */
void reverse_arr(int *arr, int left, int right)
{
    if(NULL == arr || left >= right)
    {
        return;
    }
    // 此实现思路非常好
    while(left < right)
    {
        swap_number(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

/**
 * 数组元素整体向右移动k位：方式三
 *  k = 3 => 反转 0-2 => 反转 3-数组末尾 => 反转 0-数组末尾
 */
void left_move_arr_step_k_3(int *arr, int len, int k)
{
    if(k < 0)
    {
        right_move_arr_step_k_3(arr, len, -k);
        return;
    }
    if(NULL == arr || len < 2 || k < 1)
    {
        return;
    }
    reverse_arr(arr, 0, k-1);
    printf("第一次反转 => 反转 0到k-1      ：");
    print_arr(arr, len);
    reverse_arr(arr, k, len-1);
    printf("第二次反转 => 反转 k到len-1 ：");
    print_arr(arr, len);
    reverse_arr(arr, 0, len-1);
    printf("第三次反转 => 反转 0到len-1 ：");
    print_arr(arr, len);
}

/**
 * 循环移动数组
 */
void algorithm_04_cycle_move_arr()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int len = sizeof(arr) / sizeof(arr[0]);
    // 向右移动一位
	//right_move_arr_step_1(arr, len);
    // 向左移动一位
	//left_move_arr_step_1(arr, len);

    int k = -3;
    //k = 3;
    // 向右移动k位：方式一：支持k为正数或负数
    //right_move_arr_step_k_1(arr, len, k);

    // 向右移动k位：方式二：支持k为正数或负数
    //right_move_arr_step_k_2(arr, len, k);

    // 向右移动k位：方式三：支持k为正数或负数
    right_move_arr_step_k_3(arr, len, k);

    // 向左移动k位：方式一：支持k为正数或负数
    //left_move_arr_step_k_1(arr, len, k);

    // 向左移动k位：方式二：支持k为正数或负数
    //left_move_arr_step_k_2(arr, len, k);

    // 向左移动k位：方式三：支持k为正数或负数
    //left_move_arr_step_k_3(arr, len, k);
	print_arr(arr, len);
}

/**
 * 选择排序 => 找到最小或最大值下标，最后只交换一次
 */
void algorithm_05_select_sort()
{
	int arr[] = { 64, 25, 12, 22, 11 };
	int len = sizeof(arr)/sizeof(arr[0]);

	for(int i = 0; i < len - 1; i++)
	{
		int minIndex = i;
		for(int j = i + 1; j < len; j++)
		{
			if(arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}
		swap_number(&arr[i], &arr[minIndex]);
	}
	print_arr(arr, len);
}

int main()
{
	//algorithm_01_bubble_sort();
	//algorithm_02_binary_search_find_value();
	//algorithm_03_reverse_arr();
	//algorithm_04_cycle_move_arr();
	algorithm_05_select_sort();
	return 0;
}
