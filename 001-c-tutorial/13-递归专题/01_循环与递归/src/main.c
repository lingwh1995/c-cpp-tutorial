#include <stdio.h>

/**
 * 递归解决问题
 *
 * 1. 递归的本质
 *    把大问题拆成更小的、相同结构的子问题，直到不能拆（到达终止条件），再回溯计算结果。
 *
 * 2. 递归必须满足的 3 个条件(缺一不可)
 *    有明确的终止条件不然会无限递归 → 栈溢出 → 程序崩溃。
 *    子问题比原问题规模更小例如：sum(n) → sum(n-1)。
 *    子问题能回溯得到原问题解子问题解 + 当前值 = 最终结果。
 */

/**
 * 循环实现累加计算 1 + 2 + 3 + 4 + 5
 */
int sum_loop(int n)
{
	int sum = 0;
	for(int i = 1; i <= n; i++)
	{
		sum += i;
	}
	return sum;
}

/**
 * 递归实现累加计算  1 + 2 + 3 + 4 + 5
 *
 * 1. 函数
 * 	  sum(n) = n + sum(n-1)
 *
 * 2. 终止
 *    sum(0) = 0
 *
 * 3. 递归树(单链，没有分叉)：
 *    sum(5)
 *     ↓
 *    sum(4)
 *     ↓
 *    sum(3)
 *     ↓
 *    sum(2)
 *     ↓
 *    sum(1)
 *     ↓
 *    sum(0) = 0
 *
 * 4. 回溯计算
 *    sum(1) = 1 + sum(0) = 1
 *    sum(2) = 2 + sum(1) = 3
 *    sum(3) = 3 + sum(2) = 6
 *    sum(4) = 4 + sum(3) = 10
 *    sum(5) = 5 + sum(4) = 15
 */
int sum_recursion(int n)
{
    // 终止条件
    if (n == 0)
    {
        return 0;
    }
    // 递归调用
    return n + sum_recursion(n - 1);
}

/**
 * 循环实现求第 n 个斐波那契数  0、1、1、2、3、5、8、13、21 ...
 * F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
 */
int fib_loop(int n)
{
    if (n < 0)
    {
        return -1;
    }

    if (n <= 1)
    {
    	return n;
    }

    // F(i-2)
    int a = 0;
    // F(i-1)
    int b = 1;
    int c;

    for (int i = 2; i <= n; ++i)
    {
    	// F(i) = F(i-1) + F(i-2)
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

/**
 * 递归实现求第 n 个斐波那契数  0、1、1、2、3、5、8、13、21 ...
 *
 * 1. 函数
 *    fib(n) = fib(n-1) + fib(n-2)
 *
 * 2. 终止
 *    fib(0)=0, fib(1)=1
 *
 * 3. 递归树(二叉树，大量重复计算)
 *                fib(5)
 *             /          \
 *          fib(4)       fib(3)
 *         /     \       /    \
 *      fib(3)  fib(2) fib(2) fib(1)
 *      /    \
 *    fib(2) fib(1)
 *
 * 4. 回溯计算
 *    fib(1)=1, fib(0)=0
 *    fib(2) = fib(0)+fib(1) = 0 + 1 = 1
 *    fib(3) = fib(1)+fib(2) = 1 + 1 = 2
 *    fib(4) = fib(2)+fib(3) = 1 + 2 = 3
 *    fib(5) = fib(3)+fib(4) = 2 + 3 = 5
 */
int fib_recursion(int n)
{
	if(n <= 1)
	{
		return n;
	}
	else
	{
		return fib_recursion(n-2) + fib_recursion(n-1);
	}
}


/**
 * for循环打印数组
 */
void print_arr_for_loop(const int *arr, const int len)
{
	if(arr == NULL || len < 0)
	{
		return;
	}

	for(int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/**
 * while循环打印数组
 */
void print_arr_while_loop(const int *arr, const int len)
{
	if(arr == NULL || len < 0)
	{
		return;
	}

    int i = 0;
    // 最清晰、最安全
    while (i < len)
    {
        printf("%d ", arr[i++]);
    }
    printf("\n");
}

/**
 * 递归正序打印数组
 */
void print_arr_recursion(const int *arr, int len)
{
    // 安全判断
    if (arr == NULL || len <= 0)
    {
        return;
    }

    // 先递归打印前面的元素
    print_arr_recursion(arr, len - 1);

    // 再打印当前最后一个元素（正序输出）
    printf("%d ", arr[len - 1]);
}

/**
 * 递归逆序打印数组
 */
void print_arr_reverse_recursion(const int *arr, int len)
{
    if (arr == NULL || len <= 0)
    {
        return;
    }

    // 先打印当前最后一个
    printf("%d ", arr[len - 1]);

    // 再递归
    print_arr_reverse_recursion(arr, len - 1);
}

/**
 * 递归获取数组中值最大的数
 */
int get_max_num_recursion(const int *arr, int len)
{
    if (len == 1)
    {
    	return arr[0];
    }

    int max = get_max_num_recursion(arr, len-1);
    return arr[len-1] > max ? arr[len-1] : max;
}

/**
 * 递归获取数组中元素的累加和
 */
int get_arr_sum_recursion(const int *arr, int len)
{
    if(arr == NULL || len <= 0)
    {
        return 0;
    }

    return arr[len - 1] + get_arr_sum_recursion(arr, len - 1);
}

/**
 * 递归实现二分查找
 */
int binary_search_recursion(const int *arr, int left, int right, int target)
{
    // 递归结束条件：区间不存在，没找到
    if (left > right)
    {
    	return -1;
    }

    // 中间位置
    int mid = (left + right) / 2;

    if (target == arr[mid])
    {
    	// 找到了
    	return mid;
    }
    else if (target > arr[mid])
    {
        // 去右边找
        return binary_search_recursion(arr, mid + 1, right, target);
    }
    else
    {
        // 去左边找
        return binary_search_recursion(arr, left, mid - 1, target);
    }
}

/**
 * 打印数字 先递归 → 后打印(回溯打印)
 * 	 输入 n，从 1 正序打印到 n
 */
void print_num_recursion(int n)
{
	if(n <= 0)
	{
		return;
	}
	print_num_recursion(n-1);
	printf("%d ", n);
}

/**
 * 打印数字 先打印 → 后递归(递推打印)
 * 	 输入 n，从 n 倒序打印到 1
 */
void print_num_reverse_recursion(int n)
{
	if(n <= 0)
	{
		return;
	}
	printf("%d ", n);
	print_num_reverse_recursion(n-1);
}

/**
 * 求一个数字的位数(如 1234 → 4 位)
 */
int get_num_count_recursion(int n)
{
    // 处理负数
    if(n < 0)
    {
    	n = -n;
    }

	if(n < 10)
	{
		return 1;
	}
	return 1 + get_num_count_recursion(n / 10);
}

int main()
{
	int sum = sum_loop(5);
	printf("循环实现累加计算 sum = %d\n", sum);
	sum = sum_recursion(5);
	printf("递归实现累加计算 sum = %d\n", sum);
	printf("-------------------------------------\n");

	int fib = fib_loop(5);
	printf("循环实现求第 n 个斐波那契数 fib = %d\n", fib);
	fib = fib_recursion(5);
	printf("递归实现求第 n 个斐波那契数 fib = %d\n", fib);
	printf("-------------------------------------\n");

	int arr[] = { 1, 3, 5, 7, 9, 11 };
	int len = sizeof(arr) / sizeof(int);
	// for循环打印数组
	print_arr_for_loop(arr, len);
	// while循环打印数组
	print_arr_while_loop(arr, len);
	// 递归打印数组
	print_arr_recursion(arr, len);
	printf("\n");
	// 递归逆序打印数组
	print_arr_reverse_recursion(arr, len);
	printf("\n");
	printf("-------------------------------------\n");

	// 递归获取数组中的最大元素
	int max = get_max_num_recursion(arr, len);
	printf("递归获取数组中的最大元素 max = %d\n", max);
	printf("-------------------------------------\n");

	// 递归获取数组中元素的累加和
	int arr_sum = get_arr_sum_recursion(arr, len);
	printf("递归获取数组中元素的累加和 arr_sum = %d\n", arr_sum);
	printf("-------------------------------------\n");

	// 递归实现二分查找
    int target = 7;
    int pos = binary_search_recursion(arr, 0, len - 1, target);
    pos != -1 ? printf("找到了，下标是：%d\n", pos) : printf("没找到\n");
    printf("-------------------------------------\n");

    // 输入 n，从 1 正序打印到 n
    print_num_recursion(5);
    printf("\n");
    // 输入 n，从 n 倒序打印到 1
    print_num_reverse_recursion(5);
    printf("\n");
    printf("-------------------------------------\n");

    // 求一个数字的位数(如 1234 → 4 位)
    int num_count = get_num_count_recursion(12345);
    printf("num_count = %d\n", num_count);
    printf("-------------------------------------\n");
	return 0;
}
