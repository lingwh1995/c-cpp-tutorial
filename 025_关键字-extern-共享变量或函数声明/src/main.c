#include <stdio.h>
#include "../inc/mylib.h"

/**
 * extern关键字:
 *	1.用在全局变量或者函数声明前,用来说明此 变量/常量/函数 是在别处定义的,要在此处引用
 *  2.一般的 变量/常量/函数 是先定义后使用,如果要实现后定义先使用就要使用extern关键字声明一下
 *  3.本文件中的 变量/常量/函数 可以直接声明,也可以使用extern关键字声明,其他文件中的 变量/常量/函数 需要使用extern声明
 *	4.extern声明的 变量/常量，可以是全局的,也可以是局部的
 *
 * 声明：说明变量的性质，但并不分配存储单元
 *	extern int i; //是声明，不是定义，没有分配内存
 *	int i; //是定义
 */

/*
// 使用extern关键字声明定义在本文件中的 变量/常量/函数
// 声明当前文件中的一个全局变量
extern int gi_in_current_file;
// 声明当前文件中的一个全局常量
extern const int gc_in_current_file;
// 声明当前文件中的一个方法
extern int add_in_current_file(int, int);
*/

// 不使用extern关键字声明定义在本文件中的 变量/常量/函数
// 声明当前文件中的一个全局变量
int gi_in_current_file;
// 声明当前文件中的一个全局常量
const int gc_in_current_file;
// 声明当前文件中的一个方法
int add_in_current_file(int, int);

/*
 * 测试使用extern声明其他文件中的 变量/常量/函数
 */
void extern_other_file_variable_and_const_and_function_test()
{
	printf("gi_in_other_file = %d\n", gi_in_other_file);
	printf("gc_in_other_file = %d\n", gc_in_other_file);
	//AddInOtherFile()在mylib.h中使用extern关键字声明,在mylib.c中定义
	add_in_other_file(0, 0);
}

/*
 * 测试使用extern声明当前文件中的 变量/常量/函数
 */
void extern_current_file_variable_and_const_and_function_test()
{
	printf("gi_in_current_file = %d\n", gi_in_current_file);
	printf("gc_in_current_file = %d\n", gc_in_current_file);
	//add_in_current_file()在main.c中使用extern关键字声明,在main.c中定义
	add_in_current_file(0, 0);
}

#if 0
int main()
{
	extern_other_file_variable_and_const_and_function_test();
	//直接调用会报错,因为这个函数中调用的变量、常量和方法都定义在下面,同样需要在当前文件中使用extern声明
	extern_current_file_variable_and_const_and_function_test();
	return 0;
}
#endif

// 定义一个全局变量
int gi_in_current_file = 10;

// 定义一个全局常量
const int gc_in_current_file = 20;

// 定义一个函数
int add_in_current_file(int a, int b)
{
	printf("我是main.c中的普通函数......(来自当前文件)\n");
	return a + b;
}
