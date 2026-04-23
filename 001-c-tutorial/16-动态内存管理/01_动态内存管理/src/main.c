#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 1. 动态内存管理指的是在程序运行的过程中，在堆区动态的请求一定大小的内存，并在用完之后归还给堆区
 *
 * 2. c语言中动态管理内存的函数有四个
 *    // 分配指定大小的内存块，不初始化(内容随机)
 *    void *malloc(size_t size);
 *    // 分配数组形式的内存，自动清零
 *    void *calloc(size_t num, size_t size);
 *    // 调整已分配内存的大小(扩大/缩小)
 *    void *realloc(void *ptr, size_t new_size);
 *    // 释放堆空间(非栈空间)中动态分配的内存，避免泄漏
 *    void free(void *ptr);
 */

/**
 * 野指针/空悬指针
 */
void dangling_pointer()
{
	int *p = malloc(4);
	*p = 10;

	free(p);

	*p = 20;  // 编译不报错！但这是违法操作！
}

void *my_calloc(size_t n, size_t size)
{
    if (n == 0 || size == 0)
    {
        return NULL;
    }
	void *vp = malloc(n * size);
	if(NULL != vp)
	{
		memset(vp, 0, n *size);
	}
	return vp;
}

/**
 * 两种动态内存分配方式 + 如何正确的释放指针(free() 配合 p = NULL;)
 */
void dynamic_memory_manage_malloc_1()
{
	int n = 0;
	int i = 0;
	int *ip = NULL;
	int *is = NULL;
	printf("请输入要申请的空间个数:\n");
	scanf("%d", &n);
	// 注意事项：使用 sizeof(int) 而非 4，因为不同平台int类型占据大小不一样
	ip = malloc(sizeof(int) * n);
	is = calloc(n, sizeof(int));
	if(ip == NULL)
	{
		exit(1);
	}
	for(i = 0; i < n; i++)
	{
		ip[i] = i + 10;
	}
	// 空悬指针(特别注意：这里只是释放了堆空间中分配的内存)
	free(ip);
	free(is);
	// 释放栈空间中分配的内存
	ip = NULL;
	is = NULL;
}

/**
 * 没有正确释放指针会出现的问题，这里以数据覆盖为例进行展示
 */
void dynamic_memory_manage_malloc_2()
{
	int *ip = malloc(sizeof(int));
	if(ip == NULL)
	{
		exit(1);
	}
	printf("%p => %x\n", ip, *ip);

	*ip = 0xff;
	printf("%p => %x\n", ip, *ip);

	/**
	 * free()之后还被使用的指针，称为野指针/空悬指针(dangling pointer)，使用这种指针会出现三种恐怖后果
	 * 1. 悄悄覆盖别的程序数据
	 * 2. 程序突然崩溃
	 * 3. 有时候正常，有时候炸
	 *
	 */
	free(ip);
	printf("%p => %x\n", ip, *ip);

	int *is = malloc(sizeof(int));

	// 测试free()只是释放了指针指向的对空间，没有删除指针本身，所以要让指针指向NULL
	*ip = 0x100;
	printf("%p => %x\n", ip, *ip);
	*is = 0x200;
	printf("%p => %x\n", is, *is);
	// 虽然没有报错，不过 ip 代表的值已经被 is 代表的值覆盖了
	printf("%p => %x\n", ip, *ip);
}

/**
 * maclloc()进阶
 * maclloc()分配的空间包括三部分，并非只有数据部分
 *
 * int *p = malloc(32);  // 申请 32 字节
 * 低地址 -----------------------------------------------------------------> 高地址
 *
 * +-------------------------+
 * |  chunk 头部（16~24字节） |  <-- 系统内部用，记录大小、是否分配、prev/next
 * +-------------------------+
 * |  上越界标记 8字节        |  <-- 固定魔术数，防止向前越界
 * +-------------------------+
 * |                         |
 * |    用户可用区 32字节     |  <-- 返回给你的指针 p 就指向这里！
 * |                         |
 * +-------------------------+
 * |  下越界标记 8字节        |  <-- 固定魔术数，防止向后越界
 * +-------------------------+
 *
 * ↑                                     ↑
 * 系统管理区                         你能合法使用的区域
 */
void dynamic_memory_manage_malloc_3()
{
	int n = 10;
	int *ip = malloc(sizeof(int) * n);
	if(ip == NULL)
	{
		exit(1);
	}

	for(int i = 0; i < n; i++)
	{
		ip[i] = i;
	}

	// 不能加，加了程序会出现严重问题
	ip += 5;
	// 为什么无法正确释放对空间内存呢？因为下越界标志被改了，程序运行可能会报错
	free(ip);
}

void get_mem_1(const char *p, const int n)
{
	p = malloc(sizeof(char) *n);
	// 非常重要，必须要有这个判断，因为c语言很自由
	if(p == NULL)
	{
		exit(1);
	}
}

/**
 * 使用二级指针直接把分配的地址赋值给cp
 */
void get_mem_2(char **p, const int n)
{
	*p = malloc(sizeof(char) *n);
}

/**
 * 直接返回分配的地址
 */
char *get_mem_3(int n)
{
	char *p = malloc(sizeof(char) *n);
	// 非常重要，必须要有这个判断，因为c语言很自由
	if(p == NULL)
	{
		exit(1);
	}
	return p;
}

void dynamic_memory_manage_malloc_4()
{
	int n = 100;
	char *cp = NULL;
//	get_mem_1(cp, n);
//	get_mem_2(&cp, n);
	cp = get_mem_3(n);
	strcpy(cp, "hello");
	printf("%s \n", cp);
	free(cp);
	cp = NULL;
}

void dynamic_memory_manage_malloc_5()
{
	// 全部在栈中完成
	char s1[] = "hello";
	// 字符串在 只读常量区(.data) ，指针 s2 在栈区
	// 最推荐的写法，一般直接用这种写法，不要用上面的写法，vs编译器定时字符串时如果不加const，会直接报错
	const char *s2 = "hello";
}

void dynamic_memory_manage_realloc_1()
{
	int n = 4;
	int m = 8;
	int s = 2;
	// 共分配20个字节的空间
	int *ip = malloc(sizeof(int) * n);
    printf("ip = %p\n", ip);
	if(ip == NULL)
	{
		exit(1);
	}
	for(int i = 0; i < n; i++)
	{
		ip[i] = 0xFFFFFFFF;
	}
	// 扩容为40个字节的空间
	ip = (int*)realloc(ip, sizeof(int) * m);
    printf("ip = %p\n", ip);
	if(ip == NULL)
	{
		exit(1);
	}
	for(int i = 0; i < m; i++)
	{
        ip[i] = 0xFFFFFFFF;
	}
	// 缩容为8个字节的空间
	ip = (int*)realloc(ip, sizeof(int) * 2);
    printf("ip = %p\n", ip);
    for(int i = 0; i < s; i++)
    {
        ip[i] = 0xFFFFFFFF;
    }
	free(ip);
	ip = NULL;
}

int main()
{
	//dangling_pointer();
	dynamic_memory_manage_malloc_1();
	dynamic_memory_manage_malloc_2();
	// 不测试时要注释掉，不然会影响后面的内存分配，这个程序已经破坏了正常的内存分配
	//dynamic_memory_manage_malloc_3();
	dynamic_memory_manage_malloc_4();
	dynamic_memory_manage_malloc_5();

	dynamic_memory_manage_realloc_1();
	return 0;
}
