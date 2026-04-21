#include <stdio.h>
#include <string.h>
#include <stdint.h>

/**
 * 共用体/联合体特征： 所有的成员变量共用同一段内存空间
 */

/**
 * 共用体/联合体 入门
 */
void union_test_1()
{
	union
	{
		int i;
		char ch[4];
	} data;
	
	// 一般情况下，要使用哪个类型的数据初始化共用体，定义共用体就把哪个类型放在最前面定义，也可以不放在前面
	data.i = 0x12345678;
	printf("data.i = 0x%x\n", data.i);
	printf("data.ch[0] = 0x%x, data.ch[1] = 0x%x\n", data.ch[0], data.ch[1]);
	
	data.ch[0] = 'a';
	data.ch[1] = 'b';
	printf("data.i = 0x%x\n", data.i);
	
	/**
	 * 16进制数
	 * 0x30 -> '0'
	 * 0x31 -> '1'
	 * 0x32 -> '2'
	 * 0x33 -> '3'
	 */
	data.i = 0x30313233;
	printf("data.ch[0] = %c, data.ch[1] = %c\n", data.ch[0], data.ch[1]);
	printf("-------------------------------------\n");
}

/**
 * 共用体/联合体 共用同一段内存空间
 */
void union_test_2()
{
	union
	{
		int i;
		short s;
		char c;
	} data;

	// 一般情况下，要使用哪个类型的数据初始化共用体，定义共用体就把哪个类型放在最前面定义，也可以不放在前面
	data.i = 0x12345678;
	printf("data.i = 0x%x\n", data.i);
	printf("data.s = 0x%x\n", data.s);
	printf("data.c = 0x%x\n", data.c);
	printf("-------------------------------------\n");
}

/**
 * 使用 共用体/联合体 判断大小端
 */
void union_test_3()
{
	union
	{
		short s;
		char ch[2];
	} data;

	data.s = 0x0001;
	if(data.ch[0] == 1)
	{
		printf("LITTLE_END\n");
	}
	else
	{
		printf("BIG_END\n");
	}
	printf("-------------------------------------\n");
}

/**
 * 共用体/联合体 + 结构体 经典用法，类似与js/python中对 addr 进行解构，想实现这个目的，但是没成功实现
 */
void union_test_4()
{
	union
	{
		unsigned int addr;
		unsigned char seg_4, seg_3, seg_2, seg_1;
	} data;

	data.addr = 0x12345678;
	printf("%u %u %u %u\n", data.seg_4, data.seg_3, data.seg_2, data.seg_1);
	printf("-------------------------------------\n");
}

/**
 * 共用体/联合体 + 结构体(哑元) 经典用法，实现类似与js/python中对 addr 进行解构，想实现这个目的，也成功实现了
 */
void union_test_5()
{
	union
	{
		unsigned int addr;
		// 这是一个匿名结构体，官方术语称为结构
		struct
		{
			unsigned char seg_4, seg_3, seg_2, seg_1;
		};
	} data;

	data.addr = 0x12345678;
	printf("%u %u %u %u\n", data.seg_4, data.seg_3, data.seg_2, data.seg_1);
	printf("-------------------------------------\n");
}

/**
 * 共用体/联合体 + 结构体(哑元) 经典用法，实现把 int 格式 ip 地址转换为字符串格式 ip 地址
 * 自己的写法，仅实现了功能，总体来说不够专业
 */
union
{
	unsigned int addr;
	// 这是一个匿名结构体，官方术语称为结构
	struct
	{
		unsigned char seg_4, seg_3, seg_2, seg_1;
	};
} ip;

/**
 * 整型 ip 转换为字符串型 ip
 */
void int_ip_to_str_ip_1(unsigned int int_ip, char *str_ip)
{
	if(str_ip == NULL)
	{
		return;
	}
	ip.addr = int_ip;
	sprintf(str_ip, "%u.%u.%u.%u", ip.seg_1, ip.seg_2, ip.seg_3, ip.seg_4);
}

void union_test_6()
{
	unsigned int int_ip = 2148205343;
	printf("int_ip = %x\n", int_ip);
	char str_ip[20] = { 0 };
	int_ip_to_str_ip_1(int_ip, str_ip);
	printf("str_ip = %s\n", str_ip);
	printf("-------------------------------------\n");
}

/**
 * 共用体/联合体 + 结构体(哑元) 经典用法，实现把 int 格式 ip 地址转换为字符串格式 ip 地址
 * 最经典最专业的写法
 */
// 专业写法：用 typedef 定义IP联合体
typedef union {
    uint32_t addr;
    struct {
        uint8_t seg_4;
        uint8_t seg_3;
        uint8_t seg_2;
        uint8_t seg_1;
    } seg;
} IP;

/**
 * 整型 ip 转换为字符串型 ip
 */
void int_ip_to_str_ip_2(uint32_t int_ip, char *str_ip, int len)
{
    if (str_ip == NULL || len < 16)
    {
        return;
    }

    IP ip;
    ip.addr = int_ip;

    // 安全的格式化输出
    snprintf(str_ip, len, "%u.%u.%u.%u",
             ip.seg.seg_1,
             ip.seg.seg_2,
             ip.seg.seg_3,
             ip.seg.seg_4);
}

/**
 * 字符串型 ip 转换为整型 ip
 */
uint32_t str_ip_to_int_ip(const char *str_ip)
{
    if (str_ip == NULL)
    {
        return 0;
    }

    uint32_t uint_seg_1, uint_seg_2, uint_seg_3, uint_seg_4;
    IP ip;

    sscanf(str_ip, "%u.%u.%u.%u", &uint_seg_1, &uint_seg_2, &uint_seg_3, &uint_seg_4);

    // 用你的 union 装回去
    ip.seg.seg_1 = (uint8_t)uint_seg_1;
    ip.seg.seg_2 = (uint8_t)uint_seg_2;
    ip.seg.seg_3 = (uint8_t)uint_seg_3;
    ip.seg.seg_4 = (uint8_t)uint_seg_4;

    // 直接返回 32 位整数IP
    return ip.addr;
}

void union_test_7()
{
    uint32_t int_ip = 2148205343;
    printf("int_ip = %x\n", int_ip);
    char str_ip[20] = { 0 };
    int_ip_to_str_ip_2(int_ip, str_ip, sizeof(str_ip));
    printf("str_ip = %s\n", str_ip);

    // 重新给 str_ip 赋值
    strcpy(str_ip, "128.11.3.32");
    int_ip = str_ip_to_int_ip(str_ip);
    printf("int_ip = %u\n", int_ip);
    printf("-------------------------------------\n");
}

/**
 * 定义一个联合体，用于 int 和位域的转换
 */
void union_test_8()
{
	typedef union {
	    int i;               // 原始整型数据 (通常为 32 位)
	    struct {
	        // C 语言位域：从低位 (LSB) 开始定义
	        unsigned int bit00 : 1; unsigned int bit01 : 1; unsigned int bit02 : 1; unsigned int bit03 : 1;
	        unsigned int bit04 : 1; unsigned int bit05 : 1; unsigned int bit06 : 1; unsigned int bit07 : 1;
	        unsigned int bit08 : 1; unsigned int bit09 : 1; unsigned int bit10 : 1; unsigned int bit11 : 1;
	        unsigned int bit12 : 1; unsigned int bit13 : 1; unsigned int bit14 : 1; unsigned int bit15 : 1;
	        unsigned int bit16 : 1; unsigned int bit17 : 1; unsigned int bit18 : 1; unsigned int bit19 : 1;
	        unsigned int bit20 : 1; unsigned int bit21 : 1; unsigned int bit22 : 1; unsigned int bit23 : 1;
	        unsigned int bit24 : 1; unsigned int bit25 : 1; unsigned int bit26 : 1; unsigned int bit27 : 1;
	        unsigned int bit28 : 1; unsigned int bit29 : 1; unsigned int bit30 : 1; unsigned int bit31 : 1;
	    } BITS;
	} IntBitConverter;

	IntBitConverter int_bit_converter;
	int_bit_converter.i = 0xAAAA5555; // 示例数据：二进制为 1010...0101

    printf("原始整数 (Hex): 0x%08X\n", int_bit_converter.i);

    // 打印其中几个位测试
    printf("第 0 位: %u\n", int_bit_converter.BITS.bit00);
    printf("第 31 位: %u\n", int_bit_converter.BITS.bit31);

    // 循环打印所有 32 位 (从高位到低位)
    printf("二进制完整排列: ");
    // 注意：位域成员无法通过数组下标访问，手动打印如下
    printf("bit00 = %u, bit01 = %u, bit02 = %u, bit03 = %u\n",
    		int_bit_converter.BITS.bit00, int_bit_converter.BITS.bit01, int_bit_converter.BITS.bit02, int_bit_converter.BITS.bit03);
    printf("-------------------------------------\n");
}

int main()
{
	union_test_1();
	union_test_2();
	union_test_3();
	union_test_4();
	union_test_5();
	union_test_6();
	union_test_7();
	union_test_8();
	return 0;
}
