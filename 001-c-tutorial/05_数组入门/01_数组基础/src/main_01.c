#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * 打印数组
 */
void print_arr(const int *arr, const int len)
{
	if(arr == NULL || len == 0)
	{
		return;
	}
	for(int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
	printf("----------------\n");
}


/**
 * 复制数组方式一：自己写算法实现
 */
int *copy_array1(int *src,int len)
{
	// 下面方式定义的数组返回会报错，因为函数执行完成后，这个函数占用的栈内存就被释放了，最后会导致数组占用的内存空间无法访问
	//int dest[len] = { };

	// 动态分配空间
	int *dest = (int *)malloc(sizeof(int) * len);
	for(int i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	return dest;
}


/**
 * 复制数组方式二：使用复制内存块函数实现
 */
int *copy_array2(int *src,int len)
{
	int *dest = (int *)malloc(sizeof(int) * len);
	/**
	 * void *memcpy(void *dest, const void *src, size_t n);
	 * dest-- 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针。
     * src -- 指向要复制的数据源，类型强制转换为 void * 指针。
     * n-- 要被复制的字节数。 
	 */ 
	memcpy(dest, src, sizeof(int) * len);
	return dest;
}

#if 0
int main()
{
	int arr[] = { 1, 3, 5, 7, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);

	// 方式一复制数组
	int *arr_copy = copy_array1(arr, len);
	// 打印数组
	print_arr(arr_copy, len);

	// 方式二复制数组
	arr_copy = copy_array2(arr, len);
	// 打印数组
	print_arr(arr_copy, len);
	return 0;
}
#endif
