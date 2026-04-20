#include <stdio.h>

/**
 * 通用类型指针使用
 */
void void_type_pointer_1()
{
    int a = 10;
    int arr[10] = { 12, 23, 34, 45, 56 };
    double dx = 12.23;
    char *pc;
    int *s = &a;

    // 定义一个无类型指针
    void *pv = NULL;
    pv = &a;
    pv = &arr;
    pv = arr;
    pv = &dx;

    pv = pc;
    pv = &s; // 二级指针
}

/**
 * 通用类型指针使用
 */
void void_type_pointer_2()
{
    int a = 10;
    int *pi = NULL;
    char ch = 'a';
    char *pc = NULL;
    // 定义一个无类型指针
    void *pv = NULL;

    //*pv = 100;    // void * 不能解引用
    //pv = pv + 1;  // pv不能加1

    pv = &a;
    // 把无类型指针转为int *类型指针
    pi = (int *)pv;
    printf("pi = %p\n", pi);

    pv = &ch;
    // 把无类型指针转为char *类型指针
    pc = (char *)pv;
    printf("pc = %p\n", pc);
}

int main()
{
    void_type_pointer_1();
    void_type_pointer_2();
    return 0;
}
