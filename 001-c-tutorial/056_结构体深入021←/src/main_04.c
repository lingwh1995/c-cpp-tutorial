#include <stdio.h>

// 使用宏定义简化求结构体成员变量偏移量
#define my_offset(type, exp) ((int)(&((type*)0) -> exp))

struct data_s {
    char cha;
    int ia;
    char chb;
    double dx;
    char str[5];
    int ib;
};

#if 0
int main()
{
    struct data_s data;
    // 不使用 sizeof() 求结构体结构体成员的字节偏移量的方式一
    // 为什么要把指针类型转化为 char* 类型，因为两个指针类型不同，不能相减
    int offset = (char*)&data.ib - (char*)&data;
    printf("offset = %d \n", offset);

    /**
	 *	1. (struct data_s*)0
	 *	把 数字 0 强制转换成 struct data_s* 类型的指针，假想结构体变量放在地址 0 处。
	 *	2. ((struct data_s*)0)->ib
	 *	访问这个 “假想在 0 地址” 的结构体的成员 ib。
	 *	3. &(...)
	 *	取这个成员的地址。
	 *	因为结构体基地址是 0，所以这个地址数值 = ib 的偏移字节数。
	 *	4. (int)
	 *	把地址强制转成整数，就是最终偏移量。
     */
    // 不使用 sizeof() 求结构体结构体成员的字节偏移量的方式二
    offset = (int)(&((struct data_s*)0) -> ib);
    printf("offset = %d \n", offset);

    int my_offset_ia = my_offset(struct data_s, ia);
    printf("my_offset_ia = %d \n", my_offset_ia);

    int my_offset_ib = my_offset(struct data_s, ib);
    printf("my_offset_ib = %d \n", my_offset_ib);
    return 0;
}
#endif
