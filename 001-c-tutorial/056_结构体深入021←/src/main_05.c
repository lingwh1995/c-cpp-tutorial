#include <stdio.h>
#include <stdint.h>

/**
 * c 语言中的位域及其应用
 */

/**
 * 字节序转换函数(不依赖任何系统库)
 */
// 判断系统字节序：1=小端(x86/ARM)，0=大端
static inline int is_little_endian()
{
    uint16_t val = 0x0001;
    return *(uint8_t *)&val;
}

// 16位：主机字节序 -> 网络字节序（大端）
uint16_t my_htons(uint16_t hostshort)
{
    if (is_little_endian())
    {
        // 小端：交换高低字节
        return (hostshort << 8) | (hostshort >> 8);
    }
    else
    {
        // 大端：直接返回
        return hostshort;
    }
}

// 32位：主机字节序 -> 网络字节序（大端）
uint32_t my_htonl(uint32_t hostlong)
{
    if (is_little_endian())
    {
        // 小端：4字节倒序
        return ((hostlong & 0x000000FF) << 24) |
               ((hostlong & 0x0000FF00) << 8)  |
               ((hostlong & 0x00FF0000) >> 8)  |
               ((hostlong & 0xFF000000) >> 24);
    }
    else
    {
        return hostlong;
    }
}

// 16位/32位：网络字节序 -> 主机字节序(和上面逻辑完全一样)
#define my_ntohs my_htons
#define my_ntohl my_htonl

/**
 * 结构体 Data 的位域内存结构图：
 * -------------------------------------- 小端格式 --------------------------------------
 *              高地址										        低地址
 *           Byte2(0x08)               Byte1(0x11)               Byte0(0x17)
 *        ┌─┬─┬─┬─┬─┬─┬─┬─┐         ┌─┬─┬─┬─┬─┬─┬─┬─┐         ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * Bit No |7|6|5|4|3|2|1|0|         |7|6|5|4|3|2|1|0|         |7|6|5|4|3|2|1|0|
 *        ├─┼─┼─┼─┼─┼─┼─┼─┤         ├─┼─┼─┼─┼─┼─┼─┼─┤         ├─┼─┼─┼─┼─┼─┼─┼─┤
 * Value  |0|0|0|0|1|0|0|0|         |0|0|0|1|0|0|0|1|         |0|0|0|1|0|1|1|1|
 *        └───┬───┴───┬───┘         └──┬──┴────┬────┘         └──┬──┴─┬─┴──┬──┘
 *            │       │                │       │                 │    │    │
 *            │       └── d:4(1000)    │       └── c:3(10001)    │    │    └── a:3(111)
 *            │                        │                         │    │
 *            │                        │                         │    └── b:2(10)
 *            │                        │                         │
 *            └────── Padding(0000)    └──── Padding(000)        └──── Padding(000)
 * -------------------------------------- 小端格式 --------------------------------------
 *
 * -------------------------------------- 大端格式 --------------------------------------
 *               低地址                                                高地址
 *           Byte0(0x17)              Byte1(0x11)                 Byte2(0x08)
 *        ┌─┬─┬─┬─┬─┬─┬─┬─┐        ┌─┬─┬─┬─┬─┬─┬─┬─┐           ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * Bit No |7|6|5|4|3|2|1|0|        |7|6|5|4|3|2|1|0|           |7|6|5|4|3|2|1|0|
 *        ├─┼─┼─┼─┼─┼─┼─┼─┤        ├─┼─┼─┼─┼─┼─┼─┼─┤           ├─┼─┼─┼─┼─┼─┼─┼─┤
 * Value  |0|0|0|1|0|1|1|1|        |0|0|0|1|0|0|0|1|           |0|0|0|0|1|0|0|0|
 *        └──┬──┴─┬─┴──┬──┘        └──┬──┴────┬────┘           └───┬───┴───┬───┘
 *           │    │    │              │       │                    │       │
 *           │    │    └─ a:3(111)    │       └─ c:5(10001)        │       └─ d:4(1000)
 *           │    └─ b:2(10)          │                            │
 *           │                        │                            │
 *           └─ Padding(000)          └─ Padding(000)              └─ Padding(0000)
 * -------------------------------------- 小端格式 --------------------------------------
 */
void struct_bit_field_memory_test_1()
{
	struct Data
	{
		unsigned char a:3;
		char b:2;
		unsigned char c:5;
		char d:4;
	};

	struct Data data = { 0 };
	data.a = 7;  //    111 => 7
	data.b = 6;  //    110 => -2
	data.c = 17; // 1 0001 => 17
	data.d = 8;  //   1000 => 8

	// 1. 打印位域成员
	printf("---- 位域成员 ----\n");
	printf("a = %u\n", data.a);
	printf("b = %d\n", data.b);
	printf("c = %u\n", data.c);
	printf("d = %d\n", data.d);

	// 2. 打印内存字节
	printf("\n---- 内存布局 ----\n");
	unsigned char *p = (unsigned char*)&data;
	printf("十六进制：0x%02X 0x%02X 0x%02X\n", p[0], p[1], p[2]);

	printf("二进制小端： ");
	for(int i = 2; i >= 0; i--)
	{
		for(int j = 7; j >= 0; j--)
		{
			/**
			 * 代码 (p[i] >> j) & 1 解释
			 * 1. p[i]
			 * 	你结构体的第 i 个字节
			 * 	比如：0x17 → 00010111
			 *
			 * 2. >> j
			 * 	右移 j 位
			 * 	把你想看的那一位移到最右边
			 *
			 * 3. & 1
			 * 	只保留最后 1 位
			 * 	最后一位是 0 → 输出 0
			 * 	最后一位是 1 → 输出 1
			 *
			 * 4. %d
			 * 	打印 0 或 1
			 *
			 */
			printf("%d", (p[i] >> j) & 1);
		}
		printf(" ");
	}

	printf("\n二进制大端： ");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 7; j >= 0; j--)
		{
			/**
			 * 代码 (p[i] >> j) & 1 解释
			 * 1. p[i]
			 * 	你结构体的第 i 个字节
			 * 	比如：0x17 → 00010111
			 *
			 * 2. >> j
			 * 	右移 j 位
			 * 	把你想看的那一位移到最右边
			 *
			 * 3. & 1
			 * 	只保留最后 1 位
			 * 	最后一位是 0 → 输出 0
			 * 	最后一位是 1 → 输出 1
			 *
			 * 4. %d
			 * 	打印 0 或 1
			 *
			 */
			printf("%d", (p[i] >> j) & 1);
		}
		printf(" ");
	}

	// 3. 打印大小端
	int x = 1;
	printf("\n\n---- 大小端 ----\n");
	printf("当前系统：%s\n", *(char*)&x == 1 ? "小端" : "大端");
}


/**
 * 结构体 Data 的位域内存结构图：
 * -------------------------------------- 小端格式 --------------------------------------
 *              高地址										         低地址
 *           Byte2(0x08)               Byte1(0x70)                Byte0(0x07)
 *        ┌─┬─┬─┬─┬─┬─┬─┬─┐         ┌─┬─┬─┬─┬─┬─┬─┬─┐          ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * Bit No |7|6|5|4|3|2|1|0|         |7|6|5|4|3|2|1|0|          |7|6|5|4|3|2|1|0|
 *        ├─┼─┼─┼─┼─┼─┼─┼─┤         ├─┼─┼─┼─┼─┼─┼─┼─┤          ├─┼─┼─┼─┼─┼─┼─┼─┤
 * Value  |0|0|0|0|1|0|0|0|         |0|1|0|0|0|1|1|0|          |0|0|0|0|0|1|1|1|
 *        └───┬───┴───┬───┘         └┬┴────┬────┴─┬─┘          └────┬────┴──┬──┘
 *            │       │              │     │      │                 │       │
 *            │       └── d:4(1000)  │     │      └── b:2(10)       │       └── a:3(111)
 *            │                      │     │                        │
 *            └────── Padding(0000)  │     └── c:5(10001)           └──── Padding(00000)
 *                                   │
 *                                   └── Padding(0)
 * -------------------------------------- 小端格式 --------------------------------------
 *
 * -------------------------------------- 大端格式 --------------------------------------
 *               低地址                                                高地址
 *           Byte0(0x07)                Byte1(0x70)                 Byte2(0x08)
 *        ┌─┬─┬─┬─┬─┬─┬─┬─┐          ┌─┬─┬─┬─┬─┬─┬─┬─┐         ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * Bit No |7|6|5|4|3|2|1|0|          |7|6|5|4|3|2|1|0|         |7|6|5|4|3|2|1|0|
 *        ├─┼─┼─┼─┼─┼─┼─┼─┤          ├─┼─┼─┼─┼─┼─┼─┼─┤         ├─┼─┼─┼─┼─┼─┼─┼─┤
 * Value  |0|0|0|0|0|1|1|1|          |0|1|0|0|0|1|1|0|         |0|0|0|0|1|0|0|0|
 *        └────┬────┴──┬──┘          └┬┴────┬────┴─┬─┘         └───┬───┴───┬───┘
 *             │       │              │     │      │               │       │
 *             │       └─ a:3(111)    │     │      └─ b:2(10)      │       └─ d:4(1000)
 *             │                      │     │                      │
 *             └──── Padding(00000)   │     └─ c:5(10001)          └──── Padding(0000)
 *                                    │
 *                                    └─ Padding(0)
 * -------------------------------------- 大端格式 --------------------------------------
 */
void struct_bit_field_memory_test_2()
{
	struct Data
	{
		unsigned char a:3;
		unsigned char :0;
		char b:2; // 零位域，位域强制换行符，代表当前字节剩余位作废，后面变量必须新开字节存储
		unsigned char c:5;
		char d:4;
	};

	struct Data data = { 0 };
	data.a = 7;  //    111 => 7
	data.b = 6;  //    110 => -2
	data.c = 17; // 1 0001 => 17
	data.d = 8;  //   1000 => 8

	// 1. 打印位域成员
	printf("---- 位域成员 ----\n");
	printf("a = %u\n", data.a);
	printf("b = %d\n", data.b);
	printf("c = %u\n", data.c);
	printf("d = %d\n", data.d);

	// 2. 打印内存字节
	printf("\n---- 内存布局 ----\n");
	unsigned char *p = (unsigned char*)&data;
	printf("十六进制小端：0x%02X 0x%02X 0x%02X\n", p[2], p[1], p[0]);

	printf("二进制的小端：");
	for(int i = 2; i >= 0; i--)
	{
		for(int j = 7; j >= 0; j--)
		{
			/**
			 * 代码 (p[i] >> j) & 1 解释
			 * 1. p[i]
			 * 	你结构体的第 i 个字节
			 * 	比如：0x17 → 00010111
			 *
			 * 2. >> j
			 * 	右移 j 位
			 * 	把你想看的那一位移到最右边
			 *
			 * 3. & 1
			 * 	只保留最后 1 位
			 * 	最后一位是 0 → 输出 0
			 * 	最后一位是 1 → 输出 1
			 *
			 * 4. %d
			 * 	打印 0 或 1
			 *
			 */
			printf("%d", (p[i] >> j) & 1);
		}
		printf(" ");
	}

	printf("\n十六进制大端：0x%02X 0x%02X 0x%02X\n", p[0], p[1], p[2]);
	printf("二进制的大端：");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 7; j >= 0; j--)
		{
			/**
			 * 代码 (p[i] >> j) & 1 解释
			 * 1. p[i]
			 * 	你结构体的第 i 个字节
			 * 	比如：0x17 → 00010111
			 *
			 * 2. >> j
			 * 	右移 j 位
			 * 	把你想看的那一位移到最右边
			 *
			 * 3. & 1
			 * 	只保留最后 1 位
			 * 	最后一位是 0 → 输出 0
			 * 	最后一位是 1 → 输出 1
			 *
			 * 4. %d
			 * 	打印 0 或 1
			 *
			 */
			printf("%d", (p[i] >> j) & 1);
		}
		printf(" ");
	}

	// 3. 打印大小端
	int x = 1;
	printf("\n\n---- 大小端 ----\n");
	printf("当前系统：%s\n", *(char*)&x == 1 ? "小端" : "大端");
}
/**
 * 标准 TCP 头格式(20 字节固定头)
 *
 * 0-1:   源端口 16bit
 * 2-3:   目的端口 16bit
 * 4-7:   序号 32bit
 * 8-11:  确认号 32bit
 * 12-13: 数据偏移+保留位+标志位 16bit
 * 14-15: 窗口大小 16bit
 * 16-17: 校验和 16bit
 * 18-19: 紧急指针 16bit
 */
void struct_bit_field_tcp_header_test()
{
	// TCP 头部位域结构体(逻辑对应 RFC 793 标准)
	typedef struct
	{
	    // 0-1 字节：源端口(16bit)
	    uint16_t src_port;
	    // 2-3 字节：目的端口(16bit)
	    uint16_t dest_port;
	    // 4-7 字节：序号(32bit)
	    uint32_t seq_num;
	    // 8-11 字节：确认号(32bit)
	    uint32_t ack_num;

	    // 12-13 字节：数据偏移(4bit) + 保留(6bit) + 标志位(6bit)
	    uint16_t data_off : 4;   // 数据偏移(单位：4字节)
	    uint16_t res      : 6;   // 保留位(必须全0)
	    uint16_t urg      : 1;   // URG 紧急标志
	    uint16_t ack_flag : 1;   // ACK 确认标志(避免与成员 ack_num 重名)
	    uint16_t psh      : 1;   // PSH 推送标志
	    uint16_t rst      : 1;   // RST 重置标志
	    uint16_t syn      : 1;   // SYN 同步标志
	    uint16_t fin      : 1;   // FIN 结束标志

	    // 14-15 字节：窗口大小(16bit)
	    uint16_t window;
	    // 16-17 字节：校验和(16bit)
	    uint16_t checksum;
	    // 18-19 字节：紧急指针(16bit)
	    uint16_t urgent_ptr;
	} tcp_header_t;

    // 1. 定义并初始化 TCP 头部结构体
	tcp_header_t tcp_header;

    // 2. 给字段赋值(注意：多字节字段要先转换网络字节序))
	tcp_header.src_port    = my_htons(8080);          // 源端口：8080
	tcp_header.dest_port   = my_htons(80);            // 目的端口：80 (HTTP)
	tcp_header.seq_num     = my_htonl(123456789);     // 序号：123456789
	tcp_header.ack_num     = my_htonl(0);             // 确认号：0 (SYN 报文无确认)

    // 3. 给位域赋值（无需字节序转换，直接按位操作）
	tcp_header.data_off    = 5;                     // 数据偏移：5 (5*4=20字节，固定头长度)
	tcp_header.res         = 0;                     // 保留位：全0
	tcp_header.urg         = 0;                     // URG：0
	tcp_header.ack_flag    = 0;                     // ACK：0 (SYN 报文)
	tcp_header.psh         = 0;                     // PSH：0
	tcp_header.rst         = 0;                     // RST：0
	tcp_header.syn         = 1;                     // SYN：1 (发起连接)
	tcp_header.fin         = 0;                     // FIN：0

	tcp_header.window      = my_htons(65535);       // 窗口大小：65535 (最大)
	tcp_header.checksum    = my_htons(0x1234);      // 校验和：示例值 (实际需计算)
	tcp_header.urgent_ptr  = my_htons(0);           // 紧急指针：0

    // 4. 验证结构体大小
    printf("----- TCP 头部结构体验证 -----\n");
    printf("结构体大小: %zu 字节 (预期: 20 字节)\n\n", sizeof(tcp_header));

    // 5. 打印字段值 注意：多字节字段要先转回小端(主机字节序)
    printf("----- TCP 头部字段值 -----\n");
    // %-10s 表示：左对齐，占10个字符宽度，不足补空格
    printf("%-10s: %u\n", "源端口", my_ntohs(tcp_header.src_port));
    printf("%-10s: %u\n", "目的端口", my_ntohs(tcp_header.dest_port));
    printf("%-10s: %u\n", "序号", my_ntohl(tcp_header.seq_num));
    printf("%-10s: %u\n", "确认号", my_ntohl(tcp_header.ack_num));
    printf("%-10s: %u (单位: 4字节, 头部长度: %u 字节)\n", "数据偏移", tcp_header.data_off, tcp_header.data_off * 4);
    printf("%-10s: %u\n", "保留位", tcp_header.res);
    printf("%-10s: URG=%u, ACK=%u, PSH=%u, RST=%u, SYN=%u, FIN=%u\n", "标志位", tcp_header.urg, tcp_header.ack_flag, tcp_header.psh, tcp_header.rst, tcp_header.syn, tcp_header.fin);
    printf("%-10s: %u\n", "窗口大小", my_ntohs(tcp_header.window));
    printf("%-10s: 0x%04x\n", "校验和", my_ntohs(tcp_header.checksum));
    printf("%-10s: %u\n", "紧急指针", my_ntohs(tcp_header.urgent_ptr));
}

#if 0
int main()
{
	//struct_bit_field_memory_test_1();
	struct_bit_field_memory_test_2();
	//struct_bit_field_tcp_header_test();
	return 0;
}
#endif
