#include <stdio.h>

/**
 * 值传递和地址传递
 *  值传递: 把值复制一份
 *  地址传递: 把指针的值复制一份,不是剪贴一份
 * 总结: 值传递和地址传递本质上都是把值复制一份,只不过值传递复制的字面值,地址传递复制的是地址值
 */

 /**
  * 值传递: 不能实现交换a和b的值
  * @param a
  * @param b
  */
void swap_number_1(int a, int b)
{
    int t = a;
    a = b;
    b = t;
    //printf("a = %d, b = %d\n",a ,b);
}

/**
 * 地址传递
 *  是一种间接改变值的方案
 */
void swap_number_2(int *x, int *y)
{
    //使用指针变量前正确的做法是先对指针进行判空处理
    if (NULL == x || NULL == y)
    {
        return;
    }
    int t = *x;
    *x = *y;
    *y = t;
}

int main()
{
    //值传递调用函数后不能改变a和b的值
    int a = 10, b = 20;
    swap_number_1(a, b);
    printf("a = %d, b = %d\n", a, b);

    //地址传递调用函数后可以改变x和y的值
    int x = 10, y = 20;
    //实参和形参的结合是从右向左,并非从左向右
    swap_number_2(&x, &y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
