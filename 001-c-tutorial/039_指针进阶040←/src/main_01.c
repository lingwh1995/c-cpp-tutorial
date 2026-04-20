#include <stdio.h>

/**
 * 指针类型决定了指针的两个特性
 *  1.指针的类型决定了取址的范围（指针对象+1的能力，指针对象 p+1 = p + 1 * sizeof(类型)）
 *  	int类型指针+1地址偏移4个字节
 *  		{
 *  			int *p = 0x00000004;
 *  			p+1;
 *  		}
 *  		p + 1 => p + 1 * sizeof(int) => p + 4 => 0x00000004 + 4 => 0x00000008
 *      char类型指针+1地址偏移1个字节
 *      	{
 *  			char *p = 0x00000001;
 *  			p+1;
 *  		}
 *  		p + 1 => p + 1 * sizeof(char) => p + 1 => 0x00000001 + 1 => 0x00000002
 *  2.解引用能力
 *  	int类型指针一次可以取4个字节的地址对应的数据， 如: 78 56 34 12
 *      char类型指针一次只能取1个字节的地址对应的数据，如: 78
 * 指针大小补充
 * 	32位系统下指针的大小都是4字节，64位系统下指针的大小都是8字节，与指针的类型无关
 * 大小端补充
 *  x86架构的CPU（包括Intel和AMD的处理器）采用‌小端模式（Little-Endian）‌存储数据
 */

/**
 * 1.整形指针转换为char类型指针，再将char类型指针换为整形指针转
 * 2.char类型指针的+1
 * 3.大端和小端
 */
void int_pointer_to_char_pointer_and_char_pointer_to_int_pointer()
{
    int a = 0x12345678;
    int *pi = &a;
    printf("sizeof(pi) = %d\n", sizeof(pi));
    printf("&pi = %p\n", pi);
    printf("pi = %x\n", *pi);
    // 整形指针转换为char类型指针
    printf("整形指针转换为char类型指针：\n");
    char *pc = (char *)&a;
    printf("sizeof(pc) = %d\n", sizeof(pc));
    printf("&pc = %p\n", pc);
    printf("pc = %x\n", *pc);
    // 再将char类型指针换为整形指针转
    printf("再将char类型指针换为整形指针转：\n");
    pi = (int *)pc;
    printf("sizeof(pi) = %d\n", sizeof(pi));
    printf("&pi = %p\n", pi);
    printf("pi = %x\n", *pi);
    *pc = 'a'; //97  0x61
    pc = pc + 1;
    *pc = 'b'; //98  0x62
    pc = pc + 1;
    *pc = 'c'; //99  0x63
    pc = pc + 1;
    *pc = 'd'; //100  0x64
    printf("pi = %x\n", *pi);
    printf("*pc = %x\n", *pc);
}

/**
 * int类型指针的+1，每次指针+1后内存地址偏移4个字节
 */
void int_pointer_plus_one()
{
    int arr[5] = { 10, 20, 30, 40, 50 };
    for(int i = 0; i < 5; i++)
    {
    	printf("&arr[%d] = %p\n", i, arr + i);
    	//printf("arr[%d] = %d\n", i, *(arr + i));
    	printf("arr[%d] = %d\n", i, arr[i]);
    }
}

/**
 * char类型指针的+1，每次指针+1后内存地址偏移1个字节
 */
void char_pointer_plus_one()
{
    char arr[5] = { 'h', 'e', 'l', 'l', 'o' };
    for(int i = 0; i < 5; i++)
    {
    	printf("&arr[%d] = %p\n", i, arr + i);
    	//printf("arr[%d] = %c\n", i, *(arr + i));
    	printf("arr[%d] = %c\n", i, arr[i]);
    }
}

/**
 * double类型指针的+1，每次指针+1后内存地址偏移8个字节
 */
void double_pointer_plus_one()
{
    double arr[5] = { 10.1, 20.2, 30.3, 40.4, 50.5 };
    for(int i = 0; i < 5; i++)
    {
    	printf("&arr[%d] = %p\n", i, arr + i);
    	//printf("arr[%d] = %.1f\n", i, *(arr + i));
    	printf("arr[%d] = %.1f\n", i, arr[i]);
    }
}

#if 0
#endif
int main()
{
	int_pointer_to_char_pointer_and_char_pointer_to_int_pointer();
	//int_pointer_plus_one();
	//char_pointer_plus_one();
	//double_pointer_plus_one();
    return 0;
}
