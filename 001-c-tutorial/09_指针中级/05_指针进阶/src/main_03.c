#include <stdio.h>
#include <string.h>

/**
 * 指针的加减
 */


/**
 * 指针相减运算结果 = 十六进制地址相减之差转换为十进制数 / sizeof(数据类型)
 */
void pointer_subInt_arr()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    // 数组首元素地址
    int *p_first = &arr[0];
    // 数组尾元素地址
    int *p_last = &arr[4];
    printf("pL - pF = %d\n", (int)(p_last - p_first));
    printf("pF - pL = %d\n", (int)(p_first - p_last));

    // 数组结束位置（尾元素地址+1）地址
    int *p_end = &arr[5];
    printf("pE - pF = %d\n", (int)(p_end - p_first));
}

/**
 * 指针相减运算结果 = 十六进制地址相减之差转换为十进制数 / sizeof(数据类型)
 */
void pointer_sub_str()
{
    const char *str = "hello";
    char *pc = (char *)str;
    // 这个变量和循环遍历无关，只是为了更方便的查看打印信息
    int index = 0;
    // 注意观察字符串中最后一个字符的地址
    while(*pc != '\0')
    {
        // printf("str[%d] = %c\n", index, *pc);
        printf("str[%d] = %p\n", index, pc);
        pc++;
        index++;
    }
    printf("str = %p\n", str);
    // 注意观察pc的地址是字符串中最后一个字符的地址再+1
    printf("pc = %p\n", pc);
    // 所以这里可以直接使用 pc 和 str 的差值作为字符串长度
    int len = (int)(pc - str);
    printf("字符串长度 = %d", len);
}

#if 0
int main()
{
    // 使用整型数组 1.观察遍历数组时指针的变化 2.观察指针的相减
    pointer_subInt_arr();
    // 使用字符串 1.观察遍历数组时指针的变化 2.观察指针的相减
    //pointer_sub_str();
    return 0;
}
#endif
