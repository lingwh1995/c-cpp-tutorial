#include <stdio.h>
#include "../inc/mylib_1.h"
#define ARSIZE 100

/*
 * 使用函数实现模块化设计 V2.0：使用多文件结构，将工具函数提取到mylib_1.h和mylib_1.c中(不去除数组中重复元素版本)
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
#if 0
int main()
{
	int arr[ARSIZE] = { 0 };
	int *p_arr = NULL;
	int val = 0;
	if (0 == val)
	{
		p_arr = &arr;
	}
	init_arr_2(p_arr, ARSIZE);
	bubble_sort_2(p_arr, ARSIZE);
	print_arr_2(p_arr, ARSIZE);
	return 0;
}
#endif
