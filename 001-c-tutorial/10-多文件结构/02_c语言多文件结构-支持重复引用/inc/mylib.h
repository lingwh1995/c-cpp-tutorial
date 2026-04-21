/*
	防止头文件被多次引用的两种方式:
		1.#pragma once（推荐使用,更优雅）
		2.#ifndef + #define（这是宏定义的使用场景之一，在预编译阶段进行处理）
*/
//#pragma once
#ifndef MYLIB_H
#define MYLIB_H
/*
	正确的使用头文件的方法:
		只在头文件中使用extern关键字声明全局变量和函数，全局变量赋值和函数体写在源文件中
	extren关键字:
		使用extern关键字声明全局变量和函数后，该全局变量和函数可以在其他文件中使用
*/
extern int g;
extern int add(int a, int b);
/*
	错误的使用头文件的方法:
		在头文件中定义了全局变量或函数，这样如果在test_1.c和test_2.c中同时使用 # include "mylib.h" 引入该头文件，生成解决方案时会报错
*/
/*
int g = 0;
int add(int a, int b)
{
	return a + b;
}
*/

#endif // !MYLIB_H
