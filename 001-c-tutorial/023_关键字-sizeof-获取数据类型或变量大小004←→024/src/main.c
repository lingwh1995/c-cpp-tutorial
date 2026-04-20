#include <stdio.h>
#include <string.h>

/**
 * sizeof: 返回一个无符号的整型数据
 *   1.sizeof(pointer) 只反映指针自身的大小，不是它指向的数据的大小
 *   2.sizeof(数组名) 返回数组大小，在sizeof()函数中，数组名代表整个数组
 */

int main()
{
    int a = 10;
    //指针类型的数据在32位系统下占4个字节，64位系统下占8个字节
    char *pc = NULL;
    double *pd = NULL;
    char str[10];
    int arr[10];
    printf("sizeof(a) = %d\n", sizeof(a));
    printf("sizeof(pc) = %d\n", sizeof(pc));
    printf("sizeof(char *) = %d\n", sizeof(char *));
    printf("sizeof(pd) = %d\n", sizeof(pd));
    printf("sizeof(double *) = %d\n", sizeof(double *));
    printf("sizeof(str) = %d\n", sizeof(str));
    //字符串(字符数组)类型末尾有一个额外的\0,会多占据一个字节
    printf("sizeof(\"ufe\") = %d\n", sizeof("ufe"));
    printf("sizeof(arr) = %d\n", sizeof(arr));
    printf("----------------------------------------\n");

    int nums[] = { 10, 20, 30, 40, 50 };
    printf("sizeof(nums[0]) = %d\n", sizeof(nums[0]));
    printf("sizeof(nums) = %d\n", sizeof(nums));
    printf("----------------------------------------\n");

    char stra[10] = { "tulun" };
    char strb[10] = { 't', 'u', 'l', 'u', 'n' };
    char strc[] = { "tulun" };
    char strd[] = { 't', 'u', 'l', 'u', 'n' };
    printf("sizeof(stra) = %d\n", sizeof(stra));
    printf("sizeof(strb) = %d\n", sizeof(strb));
    printf("sizeof(strc) = %d\n", sizeof(strc));
    printf("sizeof(strd) = %d\n", sizeof(strd));

    printf("strlen(stra) = %d\n", strlen(stra));
    printf("strlen(strb) = %d\n", strlen(strb));
    printf("strlen(strc) = %d\n", strlen(strc));
    // 为什么打印的长度值是10，因为是 strc长度 + strd长度，因为 strd 没有 '\0'，这里最后是使用了 strc 中的 '\0' 作为结束符
    printf("strlen(strd) = %d\n", strlen(strd));
    printf("----------------------------------------\n");
	return 0;
}
