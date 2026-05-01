//使用多文件结构(模块化设计)编写计算器程序:头文件部分
//#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H

//声明其他文件中的函数
extern void calc(int a, int b, char op);
extern int add_int(int a, int b);
extern int sub_int(int a, int b);
extern int mul_int(int a, int b);
extern int div_int(int a, int b);
extern void show(int a, int b, char op, int result);
#endif // !CALCULATOR_H

