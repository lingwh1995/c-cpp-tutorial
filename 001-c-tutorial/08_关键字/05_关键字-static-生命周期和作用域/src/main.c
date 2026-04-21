#include <stdio.h>

/**
 * static关键字:
 *  static修饰局部变量：
 *  	当函数第一次被调用，函数中静态局部变量开始被初始化，再次调用这个函数，这个static变量也不会被再次初始化，这个值在多次调用之间保持不变。(作用域不变，生存期改变)
 *  static修饰全局变量：
 *  	static修饰的全局变量和函数只可以在当前c程序文件中使用(作用域受到限制，生存期不变)
 *  static修饰函数：
 *  	static修饰的函数称为记忆函数，只可以在当前c程序文件中使用(作用域受到限制，生存期不变)
 *
 *  被static修饰的全局变量和函数，作用域受到限制,只在本文件中有效,在其他文件中使用extern声明,虽然可以通过编译，但
 *      是无法正常调用,生存期不会改变，详细见 mylib.h、mylib.c、main_01.c，也就是说extern不能和static连用
 */


/*
 * 普通函数
 */
void ordinary_function_test()
{
	// 定义一个普通变量a,本方法每次调用时变量a都会被初始化
    int a = 0;
    // 定义一个普通变量b,本方法每次调用时变量b都会被初始化
    int b = 0;
    a++;
    b++;
    printf("a = %d,b = %d\n", a, b);
}

/*
 * 记忆函数
 */
void memory_function_test()
{
	// 定义一个普通变量a,本方法每次调用时变量a都会被初始化
    int a = 0;
    // 定义一个静态变量b,只有本方法第一次调用时变量b都会被初始化,且b变量的生存期一直到程序结束运行
    static int b = 0; // 等同于 static int b; 因为被static修饰的变量的默认值是0
    a++;
    b++;
    printf("a = %d,b = %d\n", a, b);
}

#if 0
int main()
{
    for (int i = 0; i < 5; i++)
    {
    	//ordinary_function_test();
        memory_function_test();
    }
    return 0;
}
#endif
