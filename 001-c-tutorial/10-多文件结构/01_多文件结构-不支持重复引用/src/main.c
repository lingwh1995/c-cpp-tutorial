// 从系统中引入头文件
#include <stdio.h>
// 从当前的执行目录中引入头文件
#include "../inc/a.h"

// 第二次引入的a.h的时候会报错，这是由于重复引入导致的
//#include "a.h"

/**
 * #include :本质是拷贝，把头文件中的内容拷贝到当前文件
 * 头文件
 *      xxx.h 相当于java中的导包
 * #include <>和 #include "" 区别?
 *      使用<>: 编译器会在系统路径下查找头文件
 *      使用"": 编译器会先在当前目录下查找头文件，如果没有找到，再到系统路径下查找
 * C语言编译链接过程
 *      .c->.i->.obj->.exe
*/

int main()
{
    int i = add(3, 5);
    printf("i = %d\n", i);
    return 0;
}
