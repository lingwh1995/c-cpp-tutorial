#include<stdio.h>
#include<stdbool.h>
#include <stdint.h>
#include <string.h>

/**
 * 1. 判断大端和小端
 * 	  小端：返回1，说明数据的低字节在内存的低地址存放，简记：小低低
 *	  大端：返回0，说明数据的低字节在内存的高地址存放，简记：大低高
 * 2. 注意事项
 *    大小端逆转的是单位是字节，不是bit位
 * 3. 速记速判
 *    按地址方向记(十六进制和十进制一样，低位(低字节)在右边)
 *    小低低(低地址放低字节)，大低高(低地址放高字节)
 *
 * 4. x86架构的CPU（包括Intel和AMD的处理器）采用‌小端模式（Little-Endian）‌存储数据
 */
void big_end_or_little_end_1()
{
	int i = 1;
	// 获取整形指针
	int *pi = &i;
	// 整形指针转为char类型指针
	char *pc = (char *)pi;
	char c = *pc;
	// 等同于 char *pc = (char *)&pi;

	if(c == 0)
	{
		printf("BIG_END\n");
	}
	if(c == 1)
	{
		printf("LITTLE_END\n");
	}
    printf("-------------------------------------\n");
}

/**
 * 判断大端和小端
 * 	小端：返回1，说明数据的低字节在内存的低地址存放
 *	大端：返回0，说明数据的低字节在内存的高地址存放
 */
void big_end_or_little_end_2()
{
	int i = 1;
	// (char)i : 强转为 char 类型，实际就是取 i 在内存中第一个字节的数据
	char c = (char)i;

	if(c == 0)
	{
		printf("BIG_END\n");
	}
	if(c == 1)
	{
		printf("LITTLE_END\n");
	}
    printf("-------------------------------------\n");
}

void big_end_or_little_end_3()
{
	int i = 0x12345678;
	// (char)i : 强转为 char 类型，实际就是取 i 在内存中第一个字节的数据
	char c = (char)i;

	if(c == 0x12)
	{
		printf("BIG_END\n");
	}
	if(c == 0x78)
	{
		printf("LITTLE_END\n");
	}
    printf("-------------------------------------\n");
}

void big_end_or_little_end_4()
{
	int i = 0x12345678;
	// (char*)i : 强转为 char 类型，实际就是取 i 在内存中第一个字节的数据
	char *pc = (char*) &i;

	if(*pc == 0x12)
	{
		printf("BIG_END\n");
	}
	if(*pc == 0x78)
	{
		printf("LITTLE_END\n");
	}
    printf("-------------------------------------\n");
}

/**
 * 判断大小端
 */
void big_end_and_little_end_test()
{
	int a = 10, b = 20, c = 30, d = 40;
	printf("&a = %p\n", &a);
	printf("&b = %p\n", &b);
	printf("&c = %p\n", &c);
	printf("&d = %p\n", &d);
    printf("-------------------------------------\n");
}



/**
 * 通用的大小端转换函数：将 src 中的 n 字节反转到 dst 中
 */
void swap_endian(void *dst, const void *src, size_t n)
{
    uint8_t* dst_bytes = (uint8_t*)dst;
    const uint8_t* src_bytes = (const uint8_t*)src;

    for (size_t i = 0; i < n; ++i)
    {
        dst_bytes[i] = src_bytes[n - 1 - i];
    }
}

/**
 * 测试大小端转换
 */
void swap_endian_test()
{
    uint16_t val16 = 0x1234;
    uint16_t val16_swap_endian;
    swap_endian(&val16_swap_endian, &val16, sizeof(val16));
    printf("原始16位数据: 0x%04x, 转换大小端后16位数据: 0x%04x\n", val16, val16_swap_endian);

    uint32_t val32 = 0x12345678;
    uint32_t val32_swap_endian;
    swap_endian(&val32_swap_endian, &val32, sizeof(val32));
    printf("原始32位数据: 0x%08x, 转换大小端后32位数据: 0x%08x\n", val32, val32_swap_endian);

    uint64_t val64 = 0x0102030405060708;
    uint64_t val64_swap_endian;
    swap_endian(&val64_swap_endian, &val64, sizeof(val64));
    printf("原始64位数据: 0x%016llx, 转换大小端后64位数据: 0x%016llx\n", val64, val64_swap_endian);
    printf("-------------------------------------\n");
}


int main()
{
	/**
	 * 高低字节
	 * 	十六进制： 0x80 00 00 0a
	 * 	0x80就是高字节，0x0a就是低字节
	 *
	 * 高低地址
	 * 	低地址：内存中数据的起始位置，存储数据的开始部分。
	 * 	高地址：内存中数据的结束位置，存储数据的末尾部分。
	 *
	 * 大小端
	 * 	大端模式：低址存放高位字节，高地址存放低字节（大低高），0x12345678存储为12 34 56 78
	 * 	小端模式：低地址存放低字节，高地址存放高字节（小低低），0x12345678存储为78 56 34 12
	 */

	/**
	 * 大小端判断
	 * 	int i = 1;
	 * 	大端模式：低址存放高位字节，高地址存放低字节
	 * 	int i = 0x00000001;
	 * 	高字节 <------------------ 低字节
	 * 	低地址 ------------------> 高地址
	 * 	0x00  |  0x00  |  0x00  |  0x01
	 *
	 * 	小端模式：低地址存放低字节，高地址存放高字节
	 * 	int i = 0x01000000;
	 * 	高字节 <------------------ 低字节
	 * 	低地址 ------------------> 高地址
	 * 	0x01  |  0x00  |  0x00  |  0x00
	 */
	big_end_or_little_end_1();
	big_end_or_little_end_2();
	big_end_or_little_end_3();
	big_end_or_little_end_4();
    big_end_and_little_end_test();

	swap_endian_test();
	return 0;
}
