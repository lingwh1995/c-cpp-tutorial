#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * 章节内容：C语言数据类型
 *
 * 1. 基本数据类型
 *    - 整型数据类型：short、int、long、long long
 *      注意：short就是short int, long就是long int, long long就是long long int
 *    - 字符数据类型：char
 *    - 浮点型数据类型：float、double
 *    - 布尔类型：false=0、 true=1/非0
 *
 * 2. 构造数据类型
 *    - 数组(array)：一组相同类型元素的集合，可以是一维或多维。
 *    - 结构体(struct)：允许将不同类型的数据组合在一起，每个成员拥有独立的内存空间。
 *    - 联合体(union)：所有成员共享同一块内存空间，同一时间只能存储一种类型的数据。
 *    - 枚举(enum)：用于定义一组命名的整数常量。
 *
 * 3. 指针类型
 *    - 指针(pointer)：指向特定类型数据的指针，用于存储变量的内存地址，如int *p表示指向整数的指针。
 *
 * 4. 空类型
 *    - void：表示没有类型，通常用于函数返回值、函数参数或通用指针。
 *
 * 5. 数据类型转换注意事项和转换方式
 *    - 从小范围数据类型转换为大范围数据类型，符号位扩展取决于原数据类型，而不是目标数据类型
 *    - 小类型转大类型时，要转换为补码后再给补码的左边补齐，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1
 *    - 同一种数据类型从有符号转换为无符号数，二进制完全不变，只是把最高位从符号位变成数值位
 *      如 char => unsigned char
 *    - 同一种数据类型从无符号转换为有符号数，二进制完全不变，只是把最高位从数值位变成符号位
 *      如 unsigned char => char
 *    - 不同数据类型从有符号转换为无符号数(小类型转为大类型时)，先扩展小类型为合理的大类型(如有需要，要截取扩展后的大类型为目标小类型)，再把最高位从符号位变成数值位
 *      如 char => unsigned short 需要先把 char 转换为 int 作为中转类型，而不能直接把 char 转换为 unsigned short
 *         char => int => unsigned short
 *
 * 6. 比 int 范围小的整数数(char、unsigned char、short、unsigned short)，会自动提升为 int 然后再进行计算
 * 	  - 程序代码
 * 	    char a = 10;
 * 	    char b = 20;
 * 	    char c = a + b;
 *
 * 	  - 执行过程
 * 	    char a => 自动提升为 int a
 * 	    char b => 自动提升为 int b
 * 	    在 int 里完成加法
 * 	    结果再赋值回 char c
 */


/**
 * 定义一个结构体Person
 */
struct Student
{
	// 学生id
	int id;
	// 学生姓名
	char name[20];
	// 学生年龄
	int age;
};


/**
 * 颜色枚举
 */
enum Color
{
	COLOR_RED,	//默认为 0
	COLOR_GREEN,	//默认为 1
	COLOR_BLUE	//默认为 2
};


/**
 * 打印颜色
 *   使用枚举约束了case后面的值
 */
void print_color(enum Color color)
{
    switch (color)
    {
        case COLOR_RED:
            printf("红色\n");
            break;
        case COLOR_GREEN:
            printf("绿色\n");
            break;
        case COLOR_BLUE:
            printf("蓝色\n");
            break;
        default:
            printf("参数不合法\n");
    }
}

/**
 * 数据类型注意事项
 *
 * 1. c语言标准只规定了各种数据类型的占据空间的大小关系，没有规定各种数据类型占据的具体字节数
 * 2. long类型在window平台，占据4个字节，在linux/macos平台占据8个字节，因为window为了兼容16位系统中编写的代码，只能将long的长度规定为4字节
 * 3. 永远不要依赖long是4字节还是8字节，跨平台最安全写法
 * 	  #include<stdint.h>
 *
 * 	  int32_t // 一定是4字节
 * 	  int64_t // 一定是8字节
 *
 * 4. c语言设计时规定
 * 	  int  尽量接近机器字长(机器字长 = CPU一次能处理的二进制位数，可以理解为CPU的天生带宽)，方便运算
 * 	  	   16 位机器		int = 16位(2字节)
 * 	  	   32 位机器	    int = 32位(4字节)
 * 	  	   64 位机器     int = 32位(4字节，为了兼容旧程序)
 * 	  long 设计初衷是更长一些
 * 	  	   windows		4字节
 * 	  	   linux/unix	8字节
 * 	  long doubole
 * 	  	   windows		8字节
 * 	  	   linux/unix	12或16字节
 * 5. sizeof()返回的数据类型是size_t，输出时使用 %zu
 */
void data_type_size()
{

	// short就是short int
    printf("short类型所占字节大小: %zu\n", sizeof(short));
    printf("int类型所占字节大小: %zu\n", sizeof(int));
    // long就是long int
    printf("long类型所占字节大小: %zu\n", sizeof(long));
    printf("long int类型所占字节大小: %zu\n", sizeof(long int));
    // long long就是long long int
    printf("long long类型所占字节大小: %zu\n", sizeof(long long));
    printf("long long int类型所占字节大小: %zu\n", sizeof(long long int));
    // 字符数据类型
    printf("char类型所占字节大小: %zu\n", sizeof(char));
    // 浮点型数据类型
    printf("float类型所占字节大小: %zu\n", sizeof(float));
    printf("double类型所占字节大小: %zu\n", sizeof(double));
    printf("long double类型所占字节大小: %zu\n", sizeof(long double));
    // 使用bool类型,C99中要引用 stdbool.h
    printf("bool类型所占字节大小: %zu\n", sizeof(bool));
    printf("-------------------------------------\n");
}

/**
 * 定义基本的数据类型
 */
void define_basic_data_type()
{
    // short类型
    short s = -100;
    unsigned short us = 100;
    printf("有符号 short: s = %hd\n", s);
    printf("无符号 short: us = %hu\n", us);

    // int类型
    int i = -200;
    unsigned int ui = 200;
    printf("有符号 int: i = %d\n", i);
    printf("无符号 int: ui = %u\n", ui);

    // long类型
    long l = -300L;  // 后缀L表示long类型
    unsigned long ul = 300L;  // 后缀L表示long类型
    printf("有符号 long: l = %ld\n", l);
    printf("无符号 long: ul = %lu\n", ul);

    // long long类型
    long long ll = -400LL;  // 后缀LL表示long long类型
    unsigned long long ull = 400LL;  // 后缀LL表示long long类型
    printf("有符号 long long: ul = %lld\n", ul);
    printf("无符号 long long: ull = %llu\n", ull);

    // float类型
    float f = 0.234f;
    printf("float 值 (默认): f = %f\n", f);
    printf("float 值 (2位小数): f = %.2f\n", f);
    printf("科学计数法: f = %e\n", f);
    float fa = 0.1f;
    float fb = 0.2f;
    float fc = fa + fb;
    printf("float 值 (默认): fc = %f\n", fc);
    printf("float 值 (2位小数): fc = %.2f\n", fc);
    printf("科学计数法: fc = %e\n", fc);
    // 特别注意: 下面写法会报错，因为 float 类型数据自身就带有符号位
    //unsigned float uf = 0.234f;

    // double类型
    float d = 0.456;
    printf("double 值 (默认): d = %lf\n", d);
    printf("double 值 (2位小数): d = %.2lf\n", d);
    printf("科学计数法: d = %e\n", d);
    // 特别注意: 下面写法会报错，因为 double 类型数据自身就带有符号位
    //unsigned float ud = 0.456;

    // char类型
    char c1 = 'A'; // 等同于 char a = 65;
    char c2 = 'B'; // 等同于 char b = 66;
    printf("c1 + c2 = %d\n", c1 + c2); // 输出 131
    // 字符 '0'
    char c3 = '0';
    printf("c3 = %c\n", c3);
    printf("c3 = %d\n", c3);
    // 字符 '\0'，常用于标记字符串的结束位置
    char c4 = '\0';
    printf("c4 = %c\n", c4);
    printf("c4 = %d\n", c4);

    // 使用转义字符输出单引号
    char t = '\'';
    printf("%c\n", t);
    printf("-------------------------------------\n");
}

/**
 * 定义数组数据类型
 */
void define_array_data_type()
{
    // 数组(Array)
    int nums[] = { 10, 20, 30 };
    int i;
	int size = sizeof(nums)/sizeof(nums[0]);
    for(i = 0; i < size; i++)
    {
    	printf("%d ",nums[i]);
    }
    printf("\n");
    printf("-------------------------------------\n");
}

/**
 * 定义结构体数据类型
 */
void define_struct_data_type()
{
    // 结构体(struct)
    struct Student alice = { 1,"Alice",18 };
    struct Student bob = { 2,"Bob",23 };
    struct Student students[] = {
    		alice,
    		bob,
    		{ 3, "Charile", 29 }
    };
    int len = sizeof(students)/sizeof(students[0]);
    for(int i = 0; i < len; i++)
    {
    	printf("学生编号：%d,学生姓名：%s,学生年龄：%d\n", students[i].id, students[i].name, students[i].age);
    }
    printf("-------------------------------------\n");
}

/**
 * 定义枚举数据类型
 */
void define_enum_data_type()
{
    // 枚举(enum)
    enum Color color = COLOR_RED;
    printf("%d\n", color);
    print_color(color);
    // 注意：枚举可以像整型数组一样使用
    for(int i = COLOR_RED; i <= COLOR_BLUE; i++)
    {
    	printf("%d\n", i);
    }
    printf("-------------------------------------\n");
}

/**
 * 定义指针数据类型
 */
void define_pointer_data_type()
{
    int a = 100;
    // 指针
    int *p = &a;
    printf("a的地址 = %p\n", p);
    int arr[5] = { 1, 2, 3, 4, 5 };
    // 数组的地址
    printf("数组的地址 = %p\n", &arr);
    printf("-------------------------------------\n");
}


/**
 * 数据类型转换案例1
 */
void data_type_conversion_1()
{
	int i = 0x12345678;
	// 显式转换
//	short s = (short)i;
//	char c = (char)i;
	// 隐式转换
	short s = i;
	char c = i;
	printf("i = %x, s = %x, c = %x\n", i, s ,c);
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例2: char 和 unsigned int 运算或比较时，char 先转换为 unsigned int，再进行运算或比较
 */
void data_type_conversion_2()
{
	/**
	 * char a = -5         => char a         => 原码 1000 0101
	 * 					   => char a         => 反码 1111 1010
	 * 					   => char a         => 补码 1111 1011
	 * 					   => char a 的补码左边补齐位数(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)后转为 unsigned int a 的补码
	 * 					   => unsigned int a => 补码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => unsigned int a => 反码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => unsigned int a => 原码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => unsigned int a = 4294967291
	 *
	 * unsigned int b = 10 => unsigned int b = 10
	 *
	 * 进行比较			   => 4294967291 > 10 => 得出 unsigned a > unsigned b => 打印 a > b
	 */
	char a = -5;
	unsigned int b = 10;
	if(a > b)
	{
		printf("unsigned int a = %u, unsigned int b = %u\n", a, b);
		printf("%u > %u => unsigned int a > unsigned int b => a > b\n", a, b);
	}
	else
	{
		printf("unsigned int a = %u, unsigned int b = %u\n", a, b);
		printf("%u < %u => unsigned int a < unsigned int b => a < b\n", a, b);
	}
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例3: int 和 unsigned int 运算或比较时，int 先转换为 unsigned int，再进行运算或比较
 *
 * 为什么是把有符号数转换为无符号数，而不是把无符号数转换为有符号数?
 *     因为这个整数运算依赖于ALU运算器完成，而ALU运算器只支持补码加法运算，首先要把被操作转换为补码，才能进行加法运算
 * 	   而-1由原码转换成补码后，ALU会将所有位视为数值位，就相当于把有符号数转换为无符号数，类型转换不是修改补码，而是
 * 	   改变补码的解析规则
 */
void data_type_conversion_3()
{
	/**
	 * int a = -5          => int a          => 原码 1000 0000 0000 0000 0000 0000 0000 0101
	 * 					   => int a          => 反码 1111 1111 1111 1111 1111 1111 1111 1010
	 * 					   => int a          => 补码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => int a 的补码左边补齐位数(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)后转为 unsigned int a 的补码
	 * 					   => unsigned int a => 补码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => unsigned int a => 反码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => unsigned int a => 原码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 					   => unsigned int a = 4294967291
	 *
	 * unsigned int b = 10 => unsigned int b = 10
	 *
	 * 进行比较			   => 4294967291 > 10 => 得出 unsigned int a > unsigned int b => 打印 a > b
	 */
	int a = -5;
	unsigned int b = 10;
	if(a > b)
	{
		printf("unsigned int a = %u, unsigned int b = %u\n", a, b);
		printf("%u > %u => unsigned int a > unsigned int b => a > b\n", a, b);
	}
	else
	{
		printf("unsigned int a = %u, unsigned int b = %u\n", a, b);
		printf("%u < %u => unsigned int a < unsigned int b => a < b\n", a, b);
	}
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例4: char/unsigned char 和 short/unsigned short 运算或比较时，两个操作数先转换为 int，再进行运算或比较
 */
void data_type_conversion_4()
{
	/**
	 * char a = -5           => char a           => 原码 1000 0101
	 * 						 => char a           => 反码 1111 1010
	 * 						 => char a           => 补码 1111 1011
	 * 						 => char a 的补码左边补齐位数(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)后转为 int a 的补码
	 * 						 => int a 		     => 补码 1111 1111 1111 1111 1111 1111 1111 1011
	 * 						 => int a 		     => 反码 1000 0000 0000 0000 0000 0000 0000 0100
	 * 						 => int a 		     => 原码 1000 0000 0000 0000 0000 0000 0000 0101
	 * 						 => int a = -5
	 *
	 * unsigned short b = 10 => unsigned short b => 原码 0000 0000 0000 1010
	 * 						 => unsigned short b => 反码 0000 0000 0000 1010
	 * 						 => unsigned short b => 补码 0000 0000 0000 1010
	 * 						 => unsigned short b 的补码左边补齐位数后(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)转为 int b 的补码
	 * 						 => int b            => 补码 0000 0000 0000 0000 0000 0000 0000 1010
	 * 						 => int b            => 反码 0000 0000 0000 0000 0000 0000 0000 1010
	 * 						 => int b            => 原码 0000 0000 0000 0000 0000 0000 0000 1010
	 * 						 => int b = 10
	 *
	 * 进行比较				 => -5 < 10 => 得出 int a < int b => 打印 a < b
	 */
	char a = -5;
	unsigned short b = 10;
	if(a > b)
	{
		printf("int a = %d, int b = %d\n", a, b);
		printf("%d > %d => int a > int b => a > b\n", a, b);
	}
	else
	{
		printf("int a = %d, int b = %d\n", a, b);
		printf("%d < %d => int a < int b => a < b\n", a, b);
	}
	printf("-------------------------------------\n");
}


/**
 * 数据类型转换案例5: char 和 char, unsigned char 和 unsigned char 运算或比较时，两个操作数先转换为 int，再进行运算或比较
 */
void data_type_conversion_5()
{
	/**
	 * char a = 100 => char a => 原码   0110 0100
	 * 			    => char a => 反码   0110 0100
	 * 				=> char a => 补码   0110 0100
	 * 				=> char a 的补码左边补齐位数后(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)转为 int a 的补码
	 * 				=> int a  => 补码   0000 0000 0000 0000 0000 0000 0110 0100
     *
	 * char b = 200 => char b => 原码   1100 1000
	 * 				=> char b => 反码   1100 1000
	 * 				=> char b => 补码   1100 1000
	 *				=> char b 的补码左边补齐位数后(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)转为 int b 的补码
	 *				=> int b  => 补码   1111 1111 1111 1111 1111 1111 1100 1000
	 *
	 * int a        => int a  => 补码   0000 0000 0000 0000 0000 0000 0110 0100
	 * 	+								 								    +
	 * int b	    => int b  => 补码   1111 1111 1111 1111 1111 1111 1100 1000
	 *	=							 									    =
	 * 运算结果  	=> int c  => 补码 1 0000 0000 0000 0000 0000 0000 0010 1100
	 * 				=> int c  => 反码 1 0000 0000 0000 0000 0000 0000 0010 1100
	 * 				=> int c  => 原码 1 0000 0000 0000 0000 0000 0000 0010 1100
	 *				=> int c = 44
	 *
	 *				=> int c 的补码截取低8位后 转换为 char c 的补码
	 *				=> char c => 补码 0010 1100
	 *				=> char c => 反码 0010 1100
	 *				=> char c => 原码 0010 1100
	 *				=> char c = 44
	 */
	char a = 100;
	char b = 200;
	char c = a + b;
	printf("c = %d, a + b = %d\n", c, a + b);

	/**
	 * unsigned char x = 100 => unsigned char x => 原码   0110 0100
	 * 			             => unsigned char x => 反码   0110 0100
	 * 				         => unsigned char x => 补码   0110 0100
	 * 				         => unsigned char x 的补码左边补齐位数后(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)转为 int x 的补码
	 * 				         => int a  => 补码   0000 0000 0000 0000 0000 0000 0110 0100
     *
	 * unsigned char y = 200 => unsigned char y => 原码   1100 1000
	 * 				         => unsigned char y => 反码   1100 1000
	 * 				         => unsigned char y => 补码   1100 1000
	 *				         => unsigned char y 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int y 的补码
	 *				         => int b           => 补码   0000 0000 0000 0000 0000 0000 1100 1000
	 *
	 * int x                 => int x           => 补码   0000 0000 0000 0000 0000 0000 0110 0100
	 * 	+								 								                      +
	 * int y	             => int y           => 补码   0000 0000 0000 0000 0000 0000 1100 1000
	 *	=							 									                      =
	 * 运算结果  	         => int z           => 补码   0000 0000 0000 0000 0000 0001 0010 1100
	 * 				         => int z           => 反码   0000 0000 0000 0000 0000 0001 0010 1100
	 * 				         => int z           => 原码   0000 0000 0000 0000 0000 0001 0010 1100
	 *				         => int z = 300
	 *
	 *						 => int z 的补码截取低8位后 转换为 unsigned char z 的补码
	 *						 => unsigned char z => 补码 0010 1100
	 *						 => unsigned char z => 反码 0010 1100
	 *						 => unsigned char z => 原码 0010 1100
	 *						 => unsigned char z = 44
	 *
	 *						 => unsigned char z 的补码左边补齐位数后(小类型转大类型时，无符号数一律补0，有符号数，最高位为0补0，最高位为1补1)转为 int z 的补码
	 *						 => int z           => 补码   0000 0000 0000 0000 0000 0000 0010 1100
	 *						 => int z           => 反码   0000 0000 0000 0000 0000 0000 0010 1100
	 *						 => int z           => 原码   0000 0000 0000 0000 0000 0000 0010 1100
	 *						 => int z = 44
	 */
	unsigned char x = 100;
	unsigned char y = 200;
	unsigned char z = x + y;
	printf("z = %d, x + y = %d\n", z, x + y);
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例6
 */
void data_type_conversion_6()
{
	// 可以打印出 -4 到 3 之间的整数
	for(int i = -4; i < 4; i++)
	{
		printf("%d\n", i);
	}
	printf("---------\n");
	/**
	 * for 循环一次也无法执行，所以无法打印出任何内容
	 *
	 * 因为 sizeof(int) 返回的数据类型是 unsigned int 类型，i 和 sizeof(int)比较时，首先要把 i 转换为 unsigned int 类型
	 * int i = -4 => int i          => 原码 1000 0000 0000 0000 0000 0000 0000 0100
	 *            => int i          => 反码 1111 1111 1111 1111 1111 1111 1111 1011
	 *            => int i          => 补码 1111 1111 1111 1111 1111 1111 1111 1100
	 *            => int i 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 unsigned int i 的补码
	 *            => unsigned int i => 补码 1111 1111 1111 1111 1111 1111 1111 1100
	 *            => unsigned int i => 反码 1111 1111 1111 1111 1111 1111 1111 1100
	 *            => unsigned int i => 原码 1111 1111 1111 1111 1111 1111 1111 1100
	 *            => unsigned int i = 4294967292
	 *
	 * 比较结果    => 4294967292 < 4 => i < 4 不成立 => i < sizeof(int) 不成立 => for 循环一次也无法执行
	 */
	for(int i = -4; i < sizeof(int); i++)
	{
		printf("%d\n", i);
	}
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例7
 */
void data_type_conversion_7()
{
	char c = 128;
	unsigned char uc = 128;
	unsigned short us = 0;
	/**
	 * char c = 128 	      => char c 		  => 原码   1000 0000
	 * 					      => char c 		  => 反码   1000 0000
	 * 						  => char c 		  => 补码   1000 0000
	 * 						  => char c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int c 的补码
	 * 						  => int c  		  => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 *
	 * unsigned char uc = 128 => unsigned char uc => 原码   1000 0000
	 * 						  => unsigned char uc => 反码   1000 0000
	 * 						  => unsigned char uc => 补码   1000 0000
	 * 						  => unsigned char c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int uc 的补码
	 * 						  => int uc			  => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *
	 * int c				  => int c			  => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 *  +													  								    +
	 * int uc       		  => int uc			  => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *  =																					    =
	 * 计算结果 				  => int us		      => 补码 1 0000 0000 0000 0000 0000 0000 0000 0000
	 *
	 *  					  => int us 的补码截取低16位后 转换为 unsigned short us 的补码
	 *  					  => unsigned short us => 补码  0000 0000 0000 0000
	 *  					  => unsigned short us => 反码  0000 0000 0000 0000
	 *  					  => unsigned short us => 原码  0000 0000 0000 0000
	 *  					  => int us = 0x0
	 */
	us = c + uc;
	printf("us = %x\n", us);

	/**
	 * char c = 128 	      => char c 		  => 原码   1000 0000
	 * 					      => char c 		  => 反码   1000 0000
	 * 						  => char c 		  => 补码   1000 0000
	 * 						  => char c 转换为 unsigned char c(同一数据类型由有符号转换为无符号类型时，二进制完全不变，只是把最高位从符号位变成数值位)
	 * 						  => unsigned char c  => 补码   1000 0000
	 * 						  => unsigned char c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int c 的补码
	 * 						  => int c  		  => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *
	 * unsigned char uc = 128 => unsigned char uc => 原码   1000 0000
	 * 						  => unsigned char uc => 反码   1000 0000
	 * 						  => unsigned char uc => 补码   1000 0000
	 * 						  => unsigned char c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int uc 的补码
	 * 						  => int uc			  => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *
	 * int c				  => int c			  => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *  +													  								    +
	 * int uc       		  => int uc			  => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *  =																					    =
	 * 计算结果 				  => int us		      => 补码   0000 0000 0000 0000 0000 0001 0000 0000
	 *
	 *  					  => int us 的补码截取低16位后 转换为 unsigned short us 的补码
	 *  					  => unsigned short us => 补码  0000 0001 0000 0000
	 *  					  => unsigned short us => 反码  0000 0001 0000 0000
	 *  					  => unsigned short us => 原码  0000 0001 0000 0000
	 *  					  => int us = 0x100
	 */
	us = (unsigned char)c + uc;
	printf("us = %x\n", us);

	/**
	 * char c = 128 	      => char c 		  => 原码   1000 0000
	 * 					      => char c 		  => 反码   1000 0000
	 * 						  => char c 		  => 补码   1000 0000
	 * 						  => char c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int c 的补码
	 * 						  => int c  		  => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 *
	 * unsigned char uc = 128 => unsigned char uc => 原码   1000 0000
	 * 						  => unsigned char uc => 反码   1000 0000
	 * 						  => unsigned char uc => 补码   1000 0000
	 * 						  => unsigned char uc 转换为 char uc(同一数据类型由无符号转换为有符号类型时，二进制完全不变，只是把最高位从数值位变成符号位)
	 * 						  => char uc		  => 补码   1000 0000
	 * 						  => char uc 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int uc 的补码
	 * 						  => int uc			  => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 *
	 * int c				  => int c			  => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 *  +													  								    +
	 * int uc       		  => int uc			  => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 *  =																					    =
	 * 计算结果 				  => int us		      => 补码 1 1111 1111 1111 1111 1111 1111 0000 0000
	 *
	 *  					  => int us 的补码截取低16位后 转换为 unsigned short us 的补码
	 *  					  => unsigned short us => 补码  1111 1111 0000 0000
	 *  					  => unsigned short us => 反码  1111 1111 0000 0000
	 *  					  => unsigned short us => 原码  1111 1111 0000 0000
	 *  					  => int us = 0xFF00
	 */
	us = c + (char)uc;
	printf("us = %x\n", us);

	/**
	 * char c = 128 	      => char c 		   => 原码   1000 0000
	 * 					      => char c 		   => 反码   1000 0000
	 * 						  => char c 		   => 补码   1000 0000
	 * 						  => char c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int c 的补码
	 * 						  => int c  		   => 补码   1111 1111 1111 1111 1111 1111 1000 0000
	 * 						  => int c 的补码截取低16位后 转换为 unsigned short c 的补码
	 * 						  => unsigned short c  => 补码   1111 1111 1000 0000
	 * 						  => unsigned short c 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int c 的补码
	 * 				          => int c			   => 补码   0000 0000 0000 0000 1111 1111 1000 0000
	 *
	 * unsigned char uc = 128 => unsigned char uc  => 原码   1000 0000
	 * 						  => unsigned char uc  => 反码   1000 0000
	 * 						  => unsigned char uc  => 补码   1000 0000
	 * 						  => unsigned char uc 的补码左边补齐位数后(小类型转大类型时，无符号数补0，有符号数，最高位为0补0，最高位为1补1)转为 int uc 的补码
	 * 						  => int uc			   => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *
	 * int c				  => int c			   => 补码   0000 0000 0000 0000 1111 1111 1000 0000
	 *  +													  								    +
	 * int uc       		  => int uc			   => 补码   0000 0000 0000 0000 0000 0000 1000 0000
	 *  =																					    =
	 * 计算结果 				  => int us		       => 补码   0000 0000 0000 0001 0000 0000 0000 0000
	 *
	 *  					  => int us 的补码截取低16位后 转换为 unsigned short us 的补码
	 *  					  => unsigned short us  => 补码  0000 0000 0000 0000
	 *  					  => unsigned short us  => 反码  0000 0000 0000 0000
	 *  					  => unsigned short us  => 原码  0000 0000 0000 0000
	 *  					  => int us = 0x0
	 */
	// 特别注意： 符号位的扩展取决于原数据类型而不是目标数据类型，如这里将 char(原数据类型) => unsigned short(目标数据类型)，符号位的扩展取决于 原数据类型char
	us = (unsigned short)c + uc;
	printf("us = %x\n", us);
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例8
 */
void data_type_conversion_8()
{
	int i = 10;
	char c = 'a';
	//printf("c = %d\n", c);
	// i 和 c 比较时首先把 char类型数据c 转换为整型数据 97，再做比较
	if(i > c)
	{
		printf("i > c\n");
	}
	else
	{
		printf("i < c\n");
	}
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例9
 */
void data_type_conversion_9()
{
	int i = 10;
    double d = 12.23;
	printf("d = %.2f\n", d);
	// i 和 d 比较时首先把 整形数据 i 转换为double型数据 10.00，再做比较
	if(i > d)
	{
		printf("i > d\n");
	}
	else
	{
		printf("i < d\n");
	}
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例10
 */
void data_type_conversion_10()
{
    double d = 100.23;
	char ch = 'a';
    ch = d;
    printf("ch = %c\n", ch);
}

// 运算时 char c 先转换为 int 类型数据 97， int i 转换为 char 类型数据 d
double fun(int a, char ch)
{
    // 然后把 char ch 转换为 int 类型数据 100，最后再把计算结果整形数据 197 转换为 double 类型数据 197.000000
    double d = a + ch;
    return d;
}

/**
 * 数据类型转换案例11
 */
void data_type_conversion_11()
{
	char c = 'a';
	int i = 100;
    double d = fun(c, i);
    printf("%f\n", d);
	printf("-------------------------------------\n");
}

/**
 * 数据类型转换案例12
 *
 *
 * C语言中的数据类型在变量定义时确定后，不能直接更改其类型。这是C语言作为静态类型语言的基本特性之一。
 * 关键要点：
 *    类型固定性：一旦声明了变量的数据类型（如 int, float, char 等），该变量的类型在整个作用域内是固定的
 *    内存分配：不同类型占用不同的内存大小和布局，编译时就已经确定
 *    类型安全：这种限制保证了类型安全和内存访问的正确性
 * 示例说明：
 *   变量定义为 ft 是浮点型后，就一直是浮点类型，变量定义为 i 是整型后，就一直是整型
 *   即使将 ft 转换为整型，也不会改变 ft 本身的类型，也只是将 ft 的整数部分的值截取下来赋值给i
 *   	float ft = 3.14;    // ft 是浮点型
 *   	int i = (int)ft;    // i 是整型，这里是并不是把 ft 转为了 int 类型数据，而是把一个临时变量 (int)ft 赋值给了变量 i ，并不是把 ft 赋值给了变量i
 */

void data_type_conversion_12()
{
	float ft = 12.25;
	int a = 10;
	int *pi = &a;
	float *pf = &ft;

	printf("i = %d\n", a);
	printf("f = %f\n", ft);
	printf("pi = %p\n", pi);
	printf("pf = %p\n", pf);

	// 隐式转换
	a = ft;
	// 显示转换
	a = (int)ft;

	/**
	 * int * 和 float * 是不同类型的指针，编译器不允许隐式转换（会直接报错），即使通过强制类型转换 (int *)fp 编译通过，也会产生未定义行为。
	 * 例如： 对赋值后的 ip 解引用得到的不是 ft 的整数部分12，而是一个很大数
	 *
	 */
	pi = pf; // 错误语法，即使能通过运行，得出的结果也是错误的，c语言不支持指针类型隐式转换为另一个指针类型
	printf("*pi = %d\n", *pi);
	pi = (int *)pf; // 错误语法，即使能通过运行，得出的结果也是错误的，c语言不支持指针类型显式转换为另一个指针类型
	printf("*pi = %d\n", *pi);
	printf("-------------------------------------\n");
}

/**
 * float类型数据入门
 */
void float_hello_world()
{
	int a = 0x41440000;
	int *pi = &a;
	float *pf = (float *)&a;

	printf("%x \n", *pi);
	printf("%f \n", *pf);
	printf("-------------------------------------\n");
}

/**
 * 查看float的二进制表示
 *
 * IEEE 754 为什么规定指数部分用移码(指数+127)存储 ，而不用补码存储?
 *
 * 1. 使用补码存储分析
 *    - 用补码存储时两个浮点数的比较大小不方便，如 当指数分别为 5、-5、3 时
 *      5 => 原码 0000 0101
 *        => 反码 0000 0101
 *        => 补码 0000 0101
 *
 *     -5 => 原码 1000 0101
 *        => 反码 1111 1010
 *        => 补码 1111 1011
 *
 *      3 => 原码 0000 0011
 *        => 反码 0000 0011
 *        => 补码 0000 0011
 *
 *    - 按二进制补码从高位到低位比较
 *	      =>  5 > 3 正确
 *	      => -5 > 3 错误
 *    可以发现同一套比较逻辑不能正确的处理所有情况
 *
 * 2. 使用移码存储分析
 *    - 用移码存储时两个浮点数的比较大小很方便，如 当指数分别为 5、-5、3 时
 *      5 => 127 + 5 = 132 => 原码 1000 0100
 *        => 127 + 5 = 132 => 反码 1000 0100
 *        => 127 + 5 = 132 => 补码 1000 0100
 *
 *     -5 => 127 - 5 = 122 => 原码 0111 1010
 *        => 127 - 5 = 122 => 反码 0111 1010
 *        => 127 - 5 = 122 => 补码 0111 1010
 *
 *      3 => 127 + 3 = 130 => 原码 1000 0010
 *        => 127 + 3 = 130 => 反码 1000 0010
 *        => 127 + 3 = 130 => 补码 1000 0010
 *
 *    - 按二进制补码从高位到低位比较
 *	      =>  5 > 3 正确
 *	      => -5 < 3 正确
 *    可以发现同一套比较逻辑可以正确的处理所有情况，这样一个设计，使得硬件层面上不用设计多套比较逻辑，一套比较逻辑就通用的，非常优秀精巧的设计
 *
 */
void print_float_ieee_754_bits(float f)
{
    uint32_t* ptr = (uint32_t*)&f;

    printf("Float value: %f\n", f);
    printf("Hex representation: 0x%08X\n", *ptr);

    // 解析IEEE 754单精度格式
    uint32_t sign = (*ptr >> 31) & 1;
    uint32_t exponent = (*ptr >> 23) & 0xFF;
    uint32_t mantissa = *ptr & 0x7FFFFF;

    printf("Sign: %u (%s)\n", sign, sign ? "negative" : "positive");
    printf("Exponent: %u (biased), %d (actual)\n", exponent, (int)exponent - 127);
    printf("Mantissa: 0x%06X\n", mantissa);
    printf("Binary: ");

    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (*ptr >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n---------\n");
}

/**
 * 使用IEEE 754格式打印浮点数
 */
void print_float_ieee_754()
{
    float numbers[] = { 12.25f, 1.0f, -2.5f, 0.0f, 0.125f };
    for (int i = 0; i < 4; i++)
    {
        print_float_ieee_754_bits(numbers[i]);
    }
	printf("-------------------------------------\n");
}

typedef struct
{
    unsigned int mantissa : 23;  // 尾数部分
    unsigned int exponent : 8;   // 指数部分
    unsigned int sign : 1;       // 符号位
} FloatComponents;

/**
 * 用结构体模拟浮点数表示
 * @param f
 */
void print_float_struct()
{
    float f = -12.375f;
    FloatComponents* fc = (FloatComponents*)&f;

    printf("Float value: %f\n", f);
    printf("Sign: %u\n", fc -> sign);
    printf("Exponent: %u\n", fc -> exponent);
    printf("Mantissa: %u\n", fc -> mantissa);
    // 使用二进制形式表示浮点数
    print_float_ieee_754_bits(f);
	printf("\n-------------------------------------\n");
}

int main()
{
	data_type_size();
	define_basic_data_type();
	define_array_data_type();
	define_struct_data_type();
	define_enum_data_type();
	define_pointer_data_type();
	data_type_conversion_1();
	data_type_conversion_2();
	data_type_conversion_3();
	data_type_conversion_4();
	data_type_conversion_5();
    data_type_conversion_6();
    data_type_conversion_7();
    data_type_conversion_8();
    data_type_conversion_9();
    data_type_conversion_10();
    data_type_conversion_11();
    data_type_conversion_12();
    float_hello_world();
    print_float_ieee_754();
    //print_float_struct();
    return 0;
}
