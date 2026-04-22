#include <stdio.h>

/**
 * 章节内容:
 *  1.C语言开发环境搭建
 *  2.C语言参考手册
 *  3.第一个C语言程序
 *  4.Visual Studio 2022常用快捷键
 *      剪贴当前行                   Ctrl+X
 *      复制当前行                   Ctrl+Y
 *      删除当前行                   Ctrl+L
 *      复制当前行到下一行            Ctrl+D
 *      移动当前行到上一行            Alt+向上箭头
 *      移动当前行到下一行            Alt+向下箭头
 *      将光标移动到下一行            Ctrl+Shift+Enter
 *      将光标移动到上一行            Ctrl+Enter
 *      将选中字母转换为大写格式       Ctrl+Shift+U
 *      将选中字母转换为小写格式       Ctrl+U
 *		格式化代码                   Ctrl+K+D
 *		折叠或展开代码块              Ctrl+M+M
 *		跳转行号                     Ctrl+G
 *	5.用于注释的预处理指令
 *		#if 0
 *			...
 *		#endif
 *
 *		#if 0
 *		int main()
 *		{
 *			return 0;
 *		}
 *		#endif
 *  6.system函数
 *		暂停程序	system("pause")
 *		调用计算器	system("calc")
 * 
 *  MinGw
 *      https://sourceforge.net/projects/mingw-w64/
 *  c语言参考网站
 *      https://zh.cppreference.com/w/
 *      https://cplusplus.com/
 *      https://wangdoc.com/clang/			推荐
 *      https://www.dotcpp.com/course/
 *  c语言命名规范
 *  	https://blog.csdn.net/qq_43582136/article/details/148142720
 *  c语言在线运行
 *  	https://www.tutorialspoint.com/compilers/online-c-compiler.htm
 */

#if 0
int main()
{
	system("calc");
	system("pause");
	return 0;
}
#endif

#if 0
int main()
{
	printf("hello world~\n");
	printf("你好世界~\n");
	return 0;
}
#endif

/**
 * 1.main()的返回值就是程序的返回值
 * 2.main()的返回值可以省略不写，编译器会自动加上 return 0;
 */
#if 0
#endif
int main(void)
{
	printf("hello world~\n");
}