#include <stdio.h>

/**
 * 结构体成员变量内存对齐专题
 * 1. 每个成员的偏移量，必须是「自身类型大小」的整数倍。
 *    struct test_s
 *    {
 *    	char a;    // 1 字节
 *    	int b;     // 4 字节
 *	  };
 *	  偏移：  0   1     2     3   4   5   6   7
 *    ---------------------------------------------
 *	  内容：  a [pad] [pad] [pad] b   b   b   b
 *    ---------------------------------------------
 *
 * 2. 结构体的最终总大小，必须是「结构体里最大的成员类型大小」的整数倍。
 * 	  struct test_s
 * 	  {
 *    	int a;     // 4
 *    	char b;    // 1
 *    	char c;    // 1
 *	  };
 *	  偏移：  0   1   2   3   4   5   6     7
 *    ------------------------------------------
 *	  内容：  a   a   a   a   b   c [pad] [pad]
 *    ------------------------------------------
 *
 * 3. 嵌套的结构体，它的偏移量必须是「嵌套结构体内部最大成员类型大小」的整数倍；同时，整个结构体的总大小，必须是「所有成员里最大的类型大小」的整数倍。
 *	  struct test_s
 *	  {
 *      char a;           // 1
 *
 *      struct
 *      {
 *        int b;          // 4
 *        short c;        // 2
 *      } d;
 *
 *   	long long e;      // 8
 *    };
 *    偏移： 0   1     2     3   4   5   6   7   8   9  10    11    12    13    14    15   16  17  18  19  20  21  22 23
 *    ------------------------------------------------------------------------------------------------------------------
 *	  内容： a [pad] [pad] [pad] b   b   b   b   c   c [pad] [pad] [pad] [pad] [pad] [pad]  e   e   e   e   e   e   e  e
 *    ------------------------------------------------------------------------------------------------------------------
 */
/**
 * 结构体对齐
 */
void structure_alignment_1()
{
    typedef struct
    {
        char ca;
        int i;
        char cb;
    } Data;

    Data data = { 'a', 1, 'b' };
    printf("sizeof (data) = %d\n", sizeof (data));
    printf("&(data.ca) = %p, &(data.i) = %p, &(data.cb) = %p\n", &(data.ca), &(data.i), &(data.cb));
    printf("-------------------------------------\n");
}

/**
 * 结构体对齐
 */
void structure_alignment_2()
{
	/**
	 * 结构体名		student_s
	 * 结构体类型 名	struct student_s
	 * 特别注意		最后的分号必须写，否则会报错
	 */
	struct Student
	{
		char id[20];	// 20字节
		char name[20];	// 20字节
		char sex[10];	// 10字节
		int age;		// 4字节
	};

	struct Student student = { "001", "张三", "男", 20 };
	//printf("id = %s, name = %s, sex = %s, age = %d\n", student.id, student.name, student.sex, student.age);

	/**
	 * 1. 为什么 sizeof(student) = 56 而不是 54 ?
	 *    为了提高 CPU 处理速度，CPU 读取数据之前就做了内存对齐(结构体补齐)
	 * 2. 如何内存对齐?
	 * 	  看下一个成员变量的数据类型，前面的成员变量数据类型连续的都是char，这些成员变量视为一个整体
	 * 3. 案例说明
	 * 	  计算出来的 20+20+10+4 = 54 是纯数据大小，但C语言会自动做内存对齐
	 *
	 * 	  int 类型要求起始地址是4的倍数
	 *    前三个成员总大小：20+20+10 = 50
	 *    50 不是 4 的倍数，编译器自动补齐 2 个空字节 → 变成 52
	 *    再加上 age 的 4 字节 → 56 字节
	 */
	printf("sizeof(student) = %d\n", sizeof(student));
	printf("-------------------------------------\n");
}

/**
 * 结构体对齐
 */
void structure_alignment_3()
{
    typedef struct
    {
        // 学科编号
        int no;
        // 学科排名
        int rank;
        // 学科分数
        double scores;
    } Subject;

    typedef struct
    {
        int no;
        int age;
        char name[10];
        Subject subject;
    } Student;

    Subject subject = { 1, 1, 100 };
    Student student = { 1, 18, "张三", subject };
    printf("sizeof(subject) = %d\n", sizeof(subject));
    printf("sizeof(student) = %d\n", sizeof(student));
    printf("&(student.no) = %p, &(student.age) = %p, &(student.name) = %p, &(student.subject) = %p\n",
           &(student.no), &(student.age), &(student.name), &(student.subject));
    printf("-------------------------------------\n");
}

#pragma pack(1)
/**
 * 结构体对齐
 * 使用预编译指令设置内存对齐宽度
 */
void structure_alignment_4()
{
    typedef struct
    {
        char ca;
        int i;
        char cb;
    } Data;

    Data data = { 'a', 1, 'b' };
    printf("sizeof (data) = %d\n", sizeof (data));
    printf("&(data.ca) = %p, &(data.i) = %p, &(data.cb) = %p\n", &(data.ca), &(data.i), &(data.cb));
    printf("-------------------------------------\n");
}
#pragma pack()

void structure_alignment_5()
{
    typedef struct
    {
        int number;
        char ch[2];
    } Data;

    Data data = { 0x12345678, {'a'} };
    // 为什么结构体的大小是8，因为结构体大小必须是最大基本类型成员的整数倍
    printf("sizeof (data) = %d\n", sizeof (data));
    printf("-------------------------------------\n");
}

#if 0
int main()
{
	// 结构体对齐(本质是为了不浪费CPU的计算资源)
    structure_alignment_1();
    structure_alignment_2();
    structure_alignment_3();
    structure_alignment_4();
    structure_alignment_5();
    return 0;
}
#endif
