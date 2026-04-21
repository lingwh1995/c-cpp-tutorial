#ifndef MYLIB_H
#define MYLIB_H
// 声明其他文件中的一个全局变量
extern int gi_in_other_file;
// 声明其他文件中的一个全局常量
extern const int gc_in_other_file;
// 声明其他文件中的一个方法
extern int add_in_other_file(int, int);
#endif // !MYLIB_H
