//使用多文件结构(模块化设计)编写计算器程序:头文件部分
//#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H

extern void calc(int a, int b, char op);

//如果下面的函数不想被外部调用，只需要注释掉即可，这样没有使用extern关键字声明，外部无法调用这些函数
//声明其他文件中的函数
/*
extern int add_int(int a, int b);
extern int sub_int(int a, int b);
extern int mul_int(int a, int b);
extern int div_int(int a, int b);
extern void show(int a, int b, char op, int result);
*/
#endif // !CALCULATOR_H

