#ifndef MYLIB_H
#define MYLIB_H
//声明其他文件中的一个被static修饰的全局变量
//static extern int gi_in_other_file_static;
//声明其他文件中的一个被static修饰的全局常量
//static extern const int gc_in_other_file_static;
//声明其他文件中的一个被static修饰的方法
//static extern int AddInOtherFileStatic(int, int);

//声明其他文件中的一个没有被static修饰的全局变量
extern int gi_in_other_file_ordinary;
//声明其他文件中的一个没有被static修饰的全局常量
extern const int gc_in_other_file_ordinary;
//声明其他文件中的一个没有被static修饰的方法
extern int add_in_other_file_ordinary(int, int);
#endif // !MYLIB_H
