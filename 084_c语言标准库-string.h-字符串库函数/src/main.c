#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/**
 * 计算字符串的长度，直到空结束字符，但不包括末尾的空字符'\0'
 *
 * size_t strlen(const char *str)
 * @param  str 要计算长度的字符串
 * @return 字符串str的长度
 */
void strlen_test()
{
    char *s1 = "hello";
    printf("strlen(s1) = %u\n", strlen(s1));

    // 特别注意：使用strlen()计算下面字符串的长度，返回的是50而不是5
    char s2[50] = "hello";
    printf("strlen(s2) = %u\n", strlen(s2));
    printf("sizeof(s2) = %u\n", sizeof(s2));
}

/**
 * 自定义的字符串长度计算函数一：利用循遍历思想
 *
 * @param  str 要计算长度的字符串
 * @return 字符串str的长度
 */
int my_strlen_1(const char *str)
{
    if(NULL == str)
    {
        return -1;
    }
    // 或
    //assert(NULL != str);
    int l = 0;
    while (str[l] != '\0')
    {
        l++;
    }
    return l;
}

/**
 * 测试自定义的字符串长度计算函数一
 */
void my_strlen_1_test()
{
    const char *str = "hello world";
    int len = my_strlen_1(str);
    printf("自定义函数 len = %d\n", len);
}

/**
 * 自定义的字符串长度计算函数二：利用指针相减的特性
 *
 * @param  str 要计算长度的字符串
 * @return 返回字符串str的长度
 */
int my_strlen_2(const char *str)
{
    if(NULL == str)
    {
        return -1;
    }
    // 或
    //assert(NULL != str);
    char *pc = (char *)str;
    while(*pc != '\0')
    {
    	pc++;
    }
    return (int)(pc - str);
}

/**
 * 测试自定义的字符串长度计算函数二
 */
void my_strlen_2_Test()
{
    const char *str = "hello world";
    int len = my_strlen_2(str);
    printf("自定义函数 len = %d\n", len);
}

/**
 * 字符串拷贝函数
 *
 * char *strcpy(char *dest, const char *src)
 * @param  dest 目的字符串数组
 * @param  src 源字符串数组
 * @return 返回一个指向最终的目标字符串dest的指针（返回拷贝后的目的地内存块的起始地址）
 * @tips   1.必须要保证第一个参数的长度不小于第二个参数，否则虽然不会报错，但会溢出第一个字符串变量的边界，发生难以预料的结果。
 * @tips   2.第二个参数被const修饰，表示这个函数不会修改第二个字符串。
 */
void strcpy_test()
{
    // 错误的字符串复制方式一：因为字符串一旦定义，字符串的地址值不能再发生改变，定义后再去赋值编译无法通过
    /*
    char str1[10];
    char str2[10];
    str1 = "abc"; // 报错
    str2 = str1;  // 报错
    */

    // 错误的字符串复制方式二：只是将s1所代表的地址值赋值给s2了，并没有将s1指向的内容复制给s2
    /*
    char *s1;
    char *s2;
    s1 = "abc";
    s2 = s1;
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);
    */

    char *p = NULL;

    // 使用strcpy()完成字符串赋值
    char src_1[] = "Hello, world!";
    // 特别注意：dest_1数组的长度要大于等于sizeof(src_1)，否则会出问题
    char dest_1[100];
    p = strcpy(dest_1, src_1);
    dest_1[0] = 'X';
    // 使用puts()输出字符串
    /*
    puts(src_1);
    puts(dest_1);
    puts(p);
    */
    // 使用printf()输出字符串
    printf("src_1 = %s\n", src_1);
    printf("dest_1 = %s\n", dest_1);
    printf("p = %s\n", p);
    printf("---------------------\n");

    // 使用strcpy()完成字符串赋值：从s2的第7个位置开始接收拷贝过来的字符串 BEST
    char *src_2 = "BEST";
    char dest_2[40] = "Be the best that you can be.";
    p = strcpy(dest_2 + 7, src_2);
    // 使用puts()输出字符串
    /*
    puts(src_2);
    puts(dest_2);
    puts(p);
    */
    // 使用printf()输出字符串
    printf("src_2 = %s\n", src_2);
    printf("dest_2 = %s\n", dest_2);
    printf("p = %s\n", p);

    /**
     * strcpy()的第一个参数最好是一个已经声明的数组，而不是声明后没有进行初始化的字符指针。
     */
    /*
    char *str;
    strcpy(str, "hello world"); // 错误
    */
    /**/
    // strcpy()的连续赋值
    char s1[] = "a1";
    char s2[] = "b2";
    char s3[] = "c3";
    strcpy(s1, strcpy(s2, s3));
    puts(s1);
    //printf("s1 = %s\n", s1);
}

/**
 * 自定义的字符串拷贝函数一
 *
 * @param  dest 目的字符串数组
 * @param  src 源字符串数组
 * @return 返回一个指向最终的目标字符串dest的指针（返回拷贝后的目的地内存块的起始地址）
 * @tips   1.必须要保证第一个参数的长度不小于第二个参数，否则虽然不会报错，但会溢出第一个字符串变量的边界，发生难以预料的结果。
 * @tips   2.第二个参数被const修饰，表示这个函数不会修改第二个字符串。
 */
char *my_strcpy_1(char *dest, const char *src)
{
    if(NULL == dest || NULL == src)
    {
        return NULL;
    }
    // 或
    //assert(NULL != str1 && NULL != str2);
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

/**
 * 测试自定义的字符串拷贝函数一
 */
void my_strcpy_1_test()
{
    char src[] = "hello world";
    char dest[25];
    my_strcpy_1(dest, src);
    printf("dest = %s\n", dest);
}

/**
 * 自定义的字符串拷贝函数二
 *
 * @param  dest 目的字符串数组
 * @param  src 源字符串数组
 * @return 返回一个指向最终的目标字符串dest的指针（返回拷贝后的目的地内存块的起始地址）
 * @tips   1.必须要保证第一个参数的长度不小于第二个参数，否则虽然不会报错，但会溢出第一个字符串变量的边界，发生难以预料的结果。
 * @tips   2.第二个参数被const修饰，表示这个函数不会修改第二个字符串。
 */
char *my_strcpy_2(char *dest, const char *src)
{
    if(NULL == dest || NULL == src)
    {
        return NULL;
    }
    // 或
    //assert(NULL != str1 && NULL != str2);
    // 把const char *类型转为char *
    char *ptr = (char *)dest;
    // 当复制到结尾符 '\0' 的时候，代码相当于 while('\0')， '\0' 的ASCII码是0，所以为假
    while (*dest++ = *src++);
    return ptr;
}

/**
 * 测试自定义的字符串拷贝函数二
 */
void my_strcpy_2_test()
{
    char src[] = "hello world";
    char dest[25];
    my_strcpy_2(dest, src);
    printf("dest = %s\n", dest);
}

/**
 * 字符串拷贝函数（最多拷贝n字节）
 *
 * char *strncpy(char *dest, const char *src, size_t n)
 * @param  dest 目的字符串数组
 * @param  src  源字符串数组
 * @param  n    要从源字符串中复制的字符数
 * @return 返回一个指向最终的目标字符串dest的指针（返回拷贝后的目的地内存块的起始地址）
 * @tips   1.第三个参数n定义了复制的最大字符数。如果达到最大字符数以后，源字符串仍然没有复制完，就会停止复制，这时目的
 * 			 字符串结尾将没有终止符'\0'，这一点务必注意。如果源字符串的字符数小于n，则strncpy()的行为与strcpy()完全
 * 			 一致。需要手动在dest字符串中添加结尾符'\0'
 * @tips   2.第二个参数被const修饰，表示这个函数不会修改第二个字符串。
 * @tips   3.此函数可以用来拷贝全部字符串或者部分字符串
 */
void strncpy_test_1()
{
    char *p = NULL;

    // 使用strncpy()完成字符串赋值
    char src_1[] = "Hello, world!";
    // 特别注意：dest_1数组的长度要大于等于sizeof(src_1)，否则会出问题
    char dest_1[100];
    p = strncpy(dest_1, src_1, 14);
    dest_1[0] = 'X';
    // 使用puts()输出字符串
    /*
    puts(src_1);
    puts(dest_1);
    puts(p);
    */
    // 使用printf()输出字符串
    printf("src_1 = %s\n", src_1);
    printf("dest_1 = %s\n", dest_1);
    printf("p = %s\n", p);
    printf("---------------------\n");

    // 使用strncpy()完成字符串赋值：从s2的第7个位置开始接收拷贝过来的字符串 BEST
    char *src_2 = "BEST";
    char dest_2[40] = "Be the best that you can be.";
    p = strncpy(dest_2 + 7, src_2, 4);
    // 使用puts()输出字符串
    /*
    puts(src_2);
    puts(dest_2);
    puts(p);
    */
    // 使用printf()输出字符串
    printf("src_2 = %s\n", src_2);
    printf("dest_2 = %s\n", dest_2);
    printf("p = %s\n", p);
}

/**
 * 字符串拷贝函数（最多拷贝n字节）：演示src字符串的长度超过了dest字符串的长度，参数n的最大值 sizeof(dest) - 1，因为要留一个字节的空间存储结尾符 '\0'
 *
 * char *strncpy(char *dest, const char *src, size_t n)
 * @param  dest 目的字符串数组
 * @param  src  源字符串数组
 * @param  n    要从源字符串中复制的字符数
 * @return 返回一个指向最终的目标字符串dest的指针（返回拷贝后的目的地内存块的起始地址）
 * @tips   1.第三个参数n定义了复制的最大字符数。如果达到最大字符数以后，源字符串仍然没有复制完，就会停止复制，这时目的
 * 			 字符串结尾将没有终止符'\0'，这一点务必注意。如果源字符串的字符数小于n，则strncpy()的行为与strcpy()完全
 * 			 一致。需要手动在dest字符串中添加结尾符'\0'
 * @tips   2.第二个参数被const修饰，表示这个函数不会修改第二个字符串。
 * @tips   3.此函数可以用来拷贝全部字符串或者部分字符串
 */
void strncpy_test_2()
{
    char src[] = "Hello, world!";
    char dest[5];
    strncpy(dest, src, sizeof(dest) - 1);
    // 手动在结尾添加 '\0'
    dest[4] = '\0';
    printf("dest = %s\n", dest);
}

/**
 * 字符串拷贝函数（最多拷贝n字节）：演示拷贝部分字符串
 *
 * char *strncpy(char *dest, const char *src, size_t n)
 * @param  dest 目的字符串数组
 * @param  src  源字符串数组
 * @param  n    要从源字符串中复制的字符数
 * @return 返回一个指向最终的字符串dest的指针（返回拷贝后的目的地内存块的起始地址）
 * @tips   1.第三个参数n定义了复制的最大字符数。如果达到最大字符数以后，源字符串仍然没有复制完，就会停止复制，这时目的
 * 			 字符串结尾将没有终止符'\0'，这一点务必注意。如果源字符串的字符数小于n，则strncpy()的行为与strcpy()完全
 * 			 一致。需要手动在dest字符串中添加结尾符'\0'
 * @tips   2.第二个参数被const修饰，表示这个函数不会修改第二个字符串。
 * @tips   3.此函数可以用来拷贝全部字符串或者部分字符串
 */
void strncpy_test_3()
{
    char src[] = "Hello, world!";
    char dest[50];
    strncpy(dest, src, 5);
    // 手动在结尾添加 '\0'
    dest[5] = '\0';
    printf("dest = %s\n", dest);
}


/**
 * 字符串拼接函数（接受两个字符串作为参数，把第二个字符串的副本添加到第一个字符串的末尾。这个函数会改变第一个字符串，但是第二个字符串不变。）
 *
 * char *strcat(char *str1, const char *str2);
 * @param  dest 目的字符串
 * @param  src 源字符串
 * @return 该函数返回一个指向最终的目标字符串 dest 的指针
 * @tips   参数要为字符数组类型的字符串变量，不能为指针类型的字符串变量，如果使用指针类型的字符串变量，会报错
 */
void strcat_test()
{
    char str1[12] = "hello";
    char str2[6] = "world";
    strcat(str1, str2);
    puts(str1); // "helloworld"

    char str3[12] = "hello";
    char str4[6] = "world";
    char str5[6] = "abc";
    strcat(strcat(str3, str4), str5);
    puts(str3); // "helloworldabc"
}

/**
 * 自定义的字符串拼接函数一
 *
 * @param  dest 目的字符串
 * @param  src 源字符串
 * @return 该函数返回一个指向最终的目标字符串 dest 的指针
 */
char *my_strcat_1(char *dest, const char *src)
{
    if(NULL == dest || NULL == src)
    {
        return NULL;
    }
    char *pc = dest + strlen(dest);
    strcpy(pc, src);
    return dest;
}

/**
 * 测试自定义的字符串拼接函数一
 */
void my_strcat_1_test()
{
    char str1[12] = "hello";
    char str2[6] = "world";
    my_strcat_1(str1, str2);
    // 使用puts()输出字符串
    puts(str1); // "helloworld"
}


/**
 * 自定义的字符串拼接函数二
 *
 * @param  dest 目的字符串
 * @param  src 源字符串
 * @return 该函数返回一个指向最终的目标字符串 dest 的指针
 */
char *my_strcat_2(char *dest, const char *src)
{
    if(NULL == dest || NULL == src)
    {
        return NULL;
    }
    while(*dest != '\0')
    {
        dest++;
    }
    while(*dest = *src)
    {
        // 打印的是右边的值，因为是将右边的值赋值给左边的值
        printf("%c\n", (*dest = *src));
        dest++;
        src++;
    }
    return dest;
}

/**
 * 测试自定义的字符串拼接函数二
 */
void my_strcat_2_test()
{
    char str1[12] = "hello";
    char str2[6] = "world";
    my_strcat_2(str1, str2);
    puts(str1); // "helloworld"
}

/**
 * 字符串拼接函数
 *
 * char *strncat(char *dest, const char *src, size_t n);
 * @param  dest 指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串，包括额外的空字符
 * @param  src 要追加的字符串
 * @param  n 要追加的最大字符数
 * @return 该函数返回一个指向最终的目标字符串 dest 的指针
 * @tips   1.参数要为字符数组类型的字符串变量，不能为指针类型的字符串变量，如果使用指针类型的字符串变量，会报错
 * @tips   2.strncat()总是会在拼接结果的结尾，自动添加空字符\0，所以第三个参数的最大值，应该是str1的变量长度减去str1的字符串长度，再减去1
 */
void strncat_test_1()
{
    char str1[12] = "hello";
    char str2[6] = "world";
    strncat(str1, str2, 3);
    puts(str1); // "hellowor"
}

/**
* 字符串拼接函数
*
* char *strncat(char *dest, const char *src, size_t n);
* @param  dest 指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串，包括额外的空字符
* @param  src 要追加的字符串
* @param  n 要追加的最大字符数
* @return 该函数返回一个指向最终的目标字符串 dest 的指针
* @tips   1.参数要为字符数组类型的字符串变量，不能为指针类型的字符串变量，如果使用指针类型的字符串变量，会报错
* @tips   2.strncat()总是会在拼接结果的结尾，自动添加空字符\0，所以第三个参数的最大值，应该是str1的变量长度减去str1的字符串长度，再减去1
 *
 * 下面示例中，str1的变量长度是10，字符长度是6，两者相减后再减去1，得到3，表明str1最多可以再添加3个字符，所以得到的结果是MondayTue。
 * 注意：即使count的值设置为5，大于3了，程序可执行，并且不会报错，但是拼接出来的str1没有结尾符'\0'，这个只是一个字符数组，并不是一个字符串，由此可见，c语言很自由，很多地方依赖程序员自己控制
*/
void strncat_test_2()
{
    char str1[10] = "Monday";
    char str2[8] = "Tuesday";
    strncat(str1, str2, 3);
    puts(str1); // "MondayTue"
}

/**
 * 内存拷贝函数（将指定内存空间的内容拷贝到你想要存放的内存空间处。但前提是你想要存放的内存空间大小得容纳得下待拷贝的内容。）
 *
 * void *memcpy(void *dest, const void *src, size_t n)
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 */
void memcpy_test_1()
{
	int src[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int dest[20] = { 0 };
	memcpy(dest, src, 16); // 会复制 1,2,3,4 这四个数，因为一个int类型数据占4个字节
	//此处的16代表着16个字节，而我们访问的数组是int型，所以此处拷贝的是4个元素
	for (int i = 0; i < 20; i++)
	{
		printf("%d ", dest[i]);
	}
}

/**
 * 内存拷贝函数（将指定内存空间的内容拷贝到你想要存放的内存空间处。但前提是你想要存放的内存空间大小得容纳得下待拷贝的内容。）
 *
 * void *memcpy(void *dest, const void *src, size_t n)
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 */
void memcpy_test_2()
{
	char src[] = "hello world";
	char *dest = (char *)malloc((int)sizeof(char) * (int)sizeof(src));;

	/**
	 * void *memcpy(void *dest, const void *src, size_t n)
	 * dest-- 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
     * src -- 指向要复制的数据源，类型强制转换为 void * 指针
     * n-- 要被复制的字节数
	 */
	memcpy(dest, src, (int)sizeof(char) * (int)sizeof(src));
	printf("dest = %s\n", dest);
}

struct student_s
{
    char stu_name[20];
    int age;
};

/**
 * 内存拷贝函数（将指定内存空间的内容拷贝到你想要存放的内存空间处。但前提是你想要存放的内存空间大小得容纳得下待拷贝的内容。）
 *
 * void *memcpy(void *dest, const void *src, size_t n)
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 */
void memcpy_test_3()
{
    int arr_1[5] = { 1, 2, 3, 4, 5 };
    int arr_2[5];
    int arr_3[5];
    memcpy(arr_2, arr_1, sizeof(arr_2));
    for(int i = 0; i < sizeof(arr_2) / sizeof(arr_2[0]); i++)
    {
        printf("%d ", arr_2[i]);
    }
    printf("\n");

    memcpy(arr_3, memcpy(arr_2, arr_1, sizeof(arr_1)), sizeof(arr_2));
    for(int i = 0; i < sizeof(arr_3) / sizeof(arr_3[0]); i++)
    {
        printf("%d ", arr_3[i]);
    }
    printf("\n");

    struct student_s stus[3] = { { "zhangsan", 23 }, { "lisi", 24 }, { "wangwu", 25 } };
    struct student_s stus_cpy[3];
    memcpy(stus_cpy, stus, sizeof(stus));
    for(int i = 0; i < sizeof(stus) / sizeof(stus[0]); i++)
    {
        printf("stu_name：%s， stu_age：%d\n", stus_cpy[i].stu_name, stus_cpy[i].age);
    }
}

/**
 * 自定义的内存拷贝函数
 *
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 */
char *my_memcpy(void *dest,const void *src, size_t n)
{
    assert(dest != NULL && src != NULL);
    if(0 == n)
    {
        return dest;
    }
    char *dcp = (char *)dest;
    const char *scp = (const char *)src;
    while(n != 0)
    {
        *dcp = *scp;
        dcp++;
        scp++;
        n--;
    }
    return dest;
}

/**
 * 测试自定义的内存拷贝函数
 */
void my_memcpy_test()
{
    int arr_1[5] = { 1, 2, 3, 4, 5 };
    int arr_2[5];
    int arr_3[5];
    my_memcpy(arr_2, arr_1, sizeof(arr_2));
    for(int i = 0; i < sizeof(arr_2) / sizeof(arr_2[0]); i++)
    {
        printf("%d ", arr_2[i]);
    }
    printf("\n");

    my_memcpy(arr_3, memcpy(arr_2, arr_1, sizeof(arr_1)), sizeof(arr_2));
    for(int i = 0; i < sizeof(arr_3) / sizeof(arr_3[0]); i++)
    {
        printf("%d ", arr_3[i]);
    }
    printf("\n");

    struct student_s stus[3] = { {"zhangsan",23}, {"lisi",24}, {"wangwu",25} };
    struct student_s stus_cpy[3];
    my_memcpy(stus_cpy, stus, sizeof(stus));
    for(int i = 0; i < sizeof(stus) / sizeof(stus[0]); i++)
    {
        printf("stu_name：%s， stu_age：%d\n", stus_cpy[i].stu_name, stus_cpy[i].age);
    }
}

/**
 * 内存移动函数（用于处理把自身内容拷贝给自身）
 *
 * void *memmove(void *dest, const void *src, size_t n);
 * @param dest 目的字符串
 * @param src  源字符串
 * @param n    要拷贝的字节数
 * @tips       正向自拷贝 => dest < src
 * @tips       反向自拷贝 => dest > src
 * 与memcpy的区别：memmove能安全处理目标区域和源区域重叠的情况，而memcpy不一定能
 *   -当内存区域重叠时，memmove 会先拷贝重叠部分到目标区域，避免数据丢失
 *   -由于编译器兼容性问题，memcpy在处理重叠区域时可能导致不可预测行为
 *
 */
void memmove_test()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	// 一个int类型数据占4个字节，2个int类型数据占8个字节
	memmove(arr, arr + 2, 8);
	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	// 正向自拷贝
	char str1[] = "12345";
	// 推荐使用memmove
	memmove(str1, str1 + 2, 3);
	//memcpy(str1, str1 + 2, 2);
	puts(str1);

	// 反向自拷贝
	char str2[] = "12345";
	// 推荐使用memmove
	memmove(str2 + 2, str2, 3);
	//memcpy(str2 + 2, str2, 3);
	puts(str2);

	// 原地自拷贝 => 功能正常
	char str3[] = "12345";
	memmove(str3, str3, 3);
	puts(str3); // 预期正确输出值 => 12345，实际输出值 => 12345
}

/**
 * 自定义的内存移动函数1：正向自拷贝功能正常，反向自拷贝功能错误
 *
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 * @tips       正向自拷贝 => dest < src
 * @tips       反向自拷贝 => dest > src
 */
char *my_memove_1(void *dest,const void *src,size_t n)
{
    assert(dest != NULL && src != NULL);
    if(0 == n)
    {
        return dest;
    }
    char *dcp = (char *)dest;
    const char *scp = (const char *)src;
    while(n--)
    {
        *dcp = *scp;
        dcp++;
        scp++;
    }
    return dest;
}

/**
 * 自定义的内存移动函数测试（正向自拷贝功能正常，反向自拷贝功能错误）
 */
void my_memove_1_test()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	// 一个int类型数据占4个字节，2个int类型数据占8个字节
	my_memove_1(arr, arr + 2, 8);
	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	// 正向自拷贝 => 功能正常
	char str1[] = "12345";
	my_memove_1(str1, str1 + 2, 3);
	/**
	 * 函数执行过程分析=>
	 *
	 * 目标数组 => 12345 => 32345 => 34345 => 34545
	 * 移动位置 => ↑     =>  ↑    =>   ↑   =>
	 * 移动部分 => 345** => 345** => 345**
	 */
	puts(str1); // 预期正确输出值 => 34545，实际输出值 => 34545

	// 反向自拷贝 => 功能错误
	char str2[] = "12345";
	my_memove_1(str2 + 2, str2, 3);
	/**
	 * 函数执行过程分析=>
	 *
	 * 目标数组 => 12345 => 12145 => 12125 => 12121
	 * 移动位置 =>   ↑   =>    ↑  =>     ↑ =>
	 * 移动部分 => **123 => **121 => **121
	 */
	puts(str2);	// 预期正确输出值 => 12123，实际输出值 => 12121

	// 原地自拷贝 => 功能正常
	char str3[] = "12345";
	my_memove_1(str3, str3, 3);
	/**
	 * 函数执行过程分析=>
	 *
	 * 目标数组 => 12345 => 12345 => 12345 => 12345
	 * 移动位置 => ↑     =>  ↑    =>   ↑ =>
	 * 移动部分 => 123** => 123** => 123**
	 */
	puts(str3); // 预期正确输出值 => 12345，实际输出值 => 12345
}

/**
 * 自定义的内存移动函数2：正向拷贝功能错误，反向拷贝功能正常
 * 核心解决思路：从后向前拷贝，而不是从前向后拷贝（这个思路非常好，没有使用多余的内存空间，而是优化了算法）
 *
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 * @tips       正向自拷贝 => dest < src
 * @tips       反向自拷贝 => dest > src
 */
char *my_memove_2(void * dest,const void * src,size_t n)
{
    assert(dest != NULL && src != NULL);
    if(0 == n)
    {
        return dest;
    }
    char *dcp = (char *)dest + n - 1;
    const char *scp = (const char *)src + n - 1;
    while(n--)
    {
        *dcp = *scp;
        dcp--;
        scp--;
    }
    return dest;
}

/**
 * 自定义的内存移动函数测试2（正向拷贝功能错误，反向拷贝功能正常）
 */
void my_memove_2_test()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	// 一个int类型数据占4个字节，2个int类型数据占8个字节
	my_memove_2(arr, arr + 2, 8);
	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	// 正向自拷贝 => 功能正常
	char str1[] = "12345";
	my_memove_2(str1, str1 + 2, 3);
	/**
	 * 函数执行过程分析=>
	 *
	 * 目标数组 => 12345 => 12545 => 14545 => 54545
	 * 移动位置 =>   ↑   =>  ↑    =>   ↑   =>
	 * 移动部分 => 345** => 545** => 545**
	 */
	puts(str1);	// 预期正确输出值 => 34545，实际输出值 => 54545

	// 反向自拷贝 => 功能错误
	char str2[] = "12345";
	my_memove_2(str2 + 2, str2, 3);
	/**
	 * 函数执行过程分析=>
	 *
	 * 目标数组 => 12345 => 12343 => 12323 => 12123
	 * 移动位置 =>     ↑ =>    ↑  =>   ↑   =>
	 * 移动部分 => **123 => **123 => **123
	 */
	puts(str2); // 预期正确输出值 => 12123，实际输出值 => 12123


	// 原地自拷贝 => 功能正常
	char str3[] = "12345";
	my_memove_2(str3, str3, 3);
	/**
	 * 函数执行过程分析=>
	 *
	 * 目标数组 => 12345 => 12345 => 12345 => 12345
	 * 移动位置 =>   ↑   =>  ↑    => ↑     =>
	 * 移动部分 => 123** => 123** => 123**
	 */
	puts(str3); // 预期正确输出值 => 12345，实际输出值 => 12345
}


/**
 * 自定义的内存移动函数2：正向拷贝功能错误，反向拷贝功能正常
 * 核心解决思路：从后向前拷贝，而不是从前向后拷贝（这个思路非常好，没有使用多余的内存空间，而是优化了算法）
 *
 * @param dest 指向用于存储复制内容的目标数组，类型强制转换为 void * 指针
 * @param src  指向要复制的数据源，类型强制转换为 void * 指针
 * @param n    要被复制的字节数
 * @tips       正向自拷贝 => dest < src
 * @tips       反向自拷贝 => dest > src
 */
char *my_memove_3(void * dest,const void * src,size_t n)
{
    assert(dest != NULL && src != NULL);
    if(0 == n)
    {
        return dest;
    }
    char *dcp = (char *)dest;
    const char *scp = (const char *)src;
    if(dcp <= scp || dcp >= (scp + n)) // 正向拷贝
    {
        while(n--)
        {
            *dcp = *scp;
            dcp++;
            scp++;
        }
    }
    else // 反向拷贝
    {
        dcp = (char *)dest + n - 1;
        scp = (const char *)src + n - 1;
        while(n--)
        {
            *dcp = *scp;
            dcp--;
            scp--;
        }
    }
    return dest;
}

/**
 * 自定义的内存移动函数测试2（正向拷贝功能错误，反向拷贝功能正常）
 */
void my_memove_3_test()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	// 一个int类型数据占4个字节，2个int类型数据占8个字节
	my_memove_3(arr, arr + 2, 8);
	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	// 正向自拷贝 => 功能正常
	char str1[] = "12345";
	my_memove_3(str1, str1 + 2, 3);
	puts(str1);	// 预期正确输出值 => 34545，实际输出值 => 34545

	// 反向自拷贝 => 功能正常
	char str2[] = "12345";
	my_memove_3(str2 + 2, str2, 3);
	puts(str2); // 预期正确输出值 => 12123，实际输出值 => 12123

	// 原地自拷贝 => 功能正常
	char str3[] = "12345";
	my_memove_3(str3, str3, 3);
	puts(str3); // 预期正确输出值 => 12123，实际输出值 => 12123
}

/**
 * 字符串比较函数（实际上是按位比较字符的ASCII码）
 *
 * int strcmp(const char *str1, const char *str2)
 * @param str1 要进行比较的第一个字符串
 * @param str2 要进行比较的第二个字符串
 * @return 如果返回值小于 0，则表示 str1 小于 str2。
 *         如果返回值大于 0，则表示 str1 大于 str2。
 *         如果返回值等于 0，则表示 str1 等于 str2。
 */
void strcmp_test()
{
    const char *str1 = "abcde";
    const char *str2 = "abcde";
    int r = strcmp(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abxde";
    r = strcmp(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abcdea";
    r = strcmp(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abxde";
    str2 = "abcde";
    r = strcmp(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcdea";
    str2 = "abcde";
    r = strcmp(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
}

/**
 * 自定义的字符串比较函数一（实际上是按位比较字符的ASCII码）
 *
 * @param str1 要进行比较的第一个字符串
 * @param str2 要进行比较的第二个字符串
 * @return 如果返回值小于 0，则表示 str1 小于 str2。
 *         如果返回值大于 0，则表示 str1 大于 str2。
 *         如果返回值等于 0，则表示 str1 等于 str2。
 */
int my_strcmp_1(const char *str1, const char *str2)
{
    if(NULL == str1 || NULL == str2)
    {
        return -1;
    }
    // 或
    //assert(NULL != str1 && NULL != str2);
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

/**
 * 测试自定义的字符串比较函数一
 */
void my_strcmp_1_test()
{
    const char *str1 = "abcde";
    const char *str2 = "abcde";
    int r = my_strcmp_1(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abxde";
    r = my_strcmp_1(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abcdea";
    r = my_strcmp_1(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abxde";
    str2 = "abcde";
    r = my_strcmp_1(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcdea";
    str2 = "abcde";
    r = my_strcmp_1(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
}

/**
 * 自定义的字符串比较函数二（实际上是按位比较字符的ASCII码）
 *
 * @param str1 要进行比较的第一个字符串
 * @param str2 要进行比较的第二个字符串
 * @return 如果返回值小于 0，则表示 str1 小于 str2。
 *         如果返回值大于 0，则表示 str1 大于 str2。
 *         如果返回值等于 0，则表示 str1 等于 str2。
 */
int my_strcmp_2(const char *str1, const char *str2)
{
    if(NULL == str1 || NULL == str2)
    {
        return -1;
    }
    // 或
    //assert(NULL != str1 && NULL != str2);
    int k = 0;
    while (((k = *str1 -*str2) == 0) && *str1++ && *str2++);
    return k;
}

/**
 * 测试自定义的字符串比较函数二
 */
void my_strcmp_2_test()
{
    const char *str1 = "abcde";
    const char *str2 = "abcde";
    int r = my_strcmp_2(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abxde";
    r = my_strcmp_2(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abcdea";
    r = my_strcmp_2(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abxde";
    str2 = "abcde";
    r = my_strcmp_2(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcdea";
    str2 = "abcde";
    r = my_strcmp_2(str1, str2);
    printf("str1和str2比较结果： %d\n", r);
}

/**
 * 字符串比较函数，最多比较n个字符数（实际上是按位比较字符的ASCII码）
 *
 * int strcmp(const char *str1, const char *str2, size_t n)
 * @param str1 要进行比较的第一个字符串
 * @param str2 要进行比较的第二个字符串
 * @param n    要比较的最大字符数
 * @return 如果返回值小于 0，则表示 str1 小于 str2。
 *         如果返回值大于 0，则表示 str1 大于 str2。
 *         如果返回值等于 0，则表示 str1 等于 str2。
 */
void strncmp_test()
{
    const char *str1 = "abcde";
    const char *str2 = "abcde";
    int r = strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abxde";
    r = strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abcdea";
    r = strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abxde";
    str2 = "abcde";
    r = strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcdea";
    str2 = "abcde";
    r = strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
}

/**
* 自定义的字符串比较函数，最多比较n个字符数（实际上是按位比较字符的ASCII码）
*
* @param str1 要进行比较的第一个字符串
* @param str2 要进行比较的第二个字符串
* @param n    要比较的最大字符数
* @return 如果返回值小于 0，则表示 str1 小于 str2。
*         如果返回值大于 0，则表示 str1 大于 str2。
*         如果返回值等于 0，则表示 str1 等于 str2。
*/
int my_strncmp(const char *str1, const char *str2, size_t n)
{
    if(NULL == str1 || NULL == str2 || 0 == n)
    {
        return -1;
    }
    // 或
    //assert(NULL != str1 && NULL != str2 && 0 != n);
    while (--n > 0 && *str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

/**
 * 测试自定义的字符串比较函数，最多比较n个字符数
 */
void my_strncmp_test()
{
    const char *str1 = "abcde";
    const char *str2 = "abcde";
    int r = my_strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abxde";
    r = my_strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcde";
    str2 = "abcdea";
    r = my_strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abxde";
    str2 = "abcde";
    r = my_strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
    str1 = "abcdea";
    str2 = "abcde";
    r = my_strncmp(str1, str2, 3);
    printf("str1和str2比较结果： %d\n", r);
}

/**
 * 从头到尾在一个字符串中查找给定字符的第一个匹配之处
 *
 * char *strchr(const char *str, int c)
 * @param str 给定字符串
 * @param c   给定字符
 * @return 如果找到字符c，则返回指向该字符在字符串中第一次出现位置的指针。如果未找到字符c，则返回NULL指针。
 * char *strchr (const char *str, int c)
 */
void strchr_test()
{
    const char *str = "abccde";
    char *p = strchr(str, 'c');
    printf("数组地址 = %p\n", str);
    printf("字符地址 = %p\n", p);
    if(NULL != p)
    {
        printf("%c\n", *p);
    }
    else
    {
        printf("字符串中没有这个字符...\n");
    }
}

/**
 * 自定义函数实现从头到尾在一个字符串中查找给定字符的第一个匹配之处
 *
 * @param str 给定字符串
 * @param c   给定字符
 * @return 如果在字符串 str 中找到字符 c，则函数返回指向该字符的指针，如果未找到该字符则返回 NULL。
 */
char *my_strchr(const char *str, int c)
{
    if(NULL == str)
    {
        return NULL;
    }
    // 特别注意这个写法：需要把str做一个类型转化，把const char *转成char *类型
    char *p = (char *)str;
    while ('\0' != *p && *p != c)
    {
        p++;
    }
    if('\0' == *p)
    {
        p = NULL;
    }
    return p;
}

/**
 * 测试自定义函数实现从头到尾在一个字符串中查找给定字符的第一个匹配之处
 */
void my_strchr_test()
{
    const char *str = "abccde";
    char *p = my_strchr(str, 'c');
    printf("数组地址 = %p\n", str);
    printf("字符地址 = %p\n", p);
    if(NULL != p)
    {
        printf("%c\n", *p);
    }
    else
    {
        printf("字符串中没有这个字符...\n");
    }
}

/**
 * 从头到尾在一个字符串中查找给定字符的最后一个匹配之处（从尾到头在一个字符串中查找给定字符的第一个匹配之处）
 *
 * char *strrchr(const char *str, int c)
 * @param str 给定字符串
 * @param c   给定字符
 * @return 从字符串的末尾开始向前搜索，直到找到指定的字符或搜索完整个字符串。如果找到字符，它将返回一个指向该字符的指针，否则返回 NULL。
 */
void strrchr_test()
{
    const char *str = "abccde";
    char *p = strrchr(str, 'c');
    printf("数组地址 = %p\n", str);
    printf("字符地址 = %p\n", p);
    if(NULL != p)
    {
        printf("%c\n", *p);
    }
    else
    {
        printf("字符串中没有这个字符...\n");
    }
}

/**
 * 自定义函数实现从头到尾在一个字符串中查找给定字符的最后一个匹配之处（从尾到头在一个字符串中查找给定字符的第一个匹配之处）一
 *
 * @param str 给定字符串
 * @param c   给定字符
 * @return 从字符串的末尾开始向前搜索，直到找到指定的字符或搜索完整个字符串。如果找到字符，它将返回一个指向该字符的指针，否则返回 NULL。
 */
char *my_strrchr_1(const char *str, int c)
{
    if(NULL == str)
    {
        return NULL;
    }
    // 特别注意这个写法：需要把str做一个类型转化，把const char *转成char *类型
    char *p = (char *)str;
    p = p + strlen(str) - 1;
    // 注意：字符串是以 '\0' 结尾的，所以最后一个字符 = *(str-1)
    while ((str-1) != p)
    {
        if(*p == c)
        {
            return p;
        }
        p--;
    }
    return NULL;
}

/**
 * 测试自定义函数实现从头到尾在一个字符串中查找给定字符的最后一个匹配之处（从尾到头在一个字符串中查找给定字符的第一个匹配之处）一
 */
void my_strrchr_1_test()
{
    const char *str = "abccde";
    char *p = my_strrchr_1(str, 'c');
    printf("数组地址 = %p\n", str);
    printf("字符地址 = %p\n", p);
    if(NULL != p)
    {
        printf("%c\n", *p);
    }
    else
    {
        printf("字符串中没有这个字符...\n");
    }
}

/**
 * 自定义函数实现从头到尾在一个字符串中查找给定字符的最后一个匹配之处（从尾到头在一个字符串中查找给定字符的第一个匹配之处）二
 *
 * @param str 给定字符串
 * @param c   给定字符
 * @return 从字符串的末尾开始向前搜索，直到找到指定的字符或搜索完整个字符串。如果找到字符，它将返回一个指向该字符的指针，否则返回 NULL。
 */
char *my_strrchr_2(const char *str, int c)
{
    if(NULL == str)
    {
        return NULL;
    }
    // 特别注意这个写法：需要把str做一个类型转化，把const char *转成char *类型
    char *p = (char *)str;
    p = p + strlen(str);
    // 注意：字符串是以 '\0' 结尾的，所以最后一个字符 = *(str-1)
    while (str != p)
    {
        if(*(p - 1) == c)
        {
            return p - 1;
        }
        p--;
    }
    return NULL;
}

/**
 * 测试自定义函数实现从头到尾在一个字符串中查找给定字符的最后一个匹配之处（从尾到头在一个字符串中查找给定字符的第一个匹配之处）二
 */
void my_strrchr_2_test()
{
    const char *str = "abccde";
    char *p = my_strrchr_2(str, 'c');
    printf("数组地址 = %p\n", str);
    printf("字符地址 = %p\n", p);
    if(NULL != p)
    {
        printf("%c\n", *p);
    }
    else
    {
        printf("字符串中没有这个字符...\n");
    }
}

/**
 * 从头到尾在一个字符串中查找给定字符串的第一个匹配之处
 *
 * char *strrchr(const char *str, const char subStr)
 * @param str 给定字符串
 * @param substr 给定子字符串
 * @return 返回的是从匹配的子字符串开始到原字符串结束的部分
*/
void strstr_test()
{
    const char *str = "onetwothree";
    const char *substr = "two";
    char *p = strstr(str,substr);
    if(NULL != p)
    {
        printf("%s\n", p);
    }
    else
    {
        printf("不匹配\n");
    }
}

/**
 * 自定义函数实现从头到尾在一个字符串中查找给定字符串的第一个匹配之处一
 *
 * @param str 给定字符串
 * @param substr 给定子字符串
 * @return 返回的是从匹配的子字符串开始到原字符串结束的部分
 */
char *my_strstr_1(const char *str, const char *substr)
{
    if (NULL == str || NULL == substr)
    {
        return NULL;
    }
    if(strlen(str) < strlen(substr))
    {
        return NULL;
    }
    int m = strlen(str);
    int n = strlen(substr);
    for(int i = 0; i < m - n + 1; i++)
    {
        // 每次开始比较时j指针回退到0位置
        int j = 0;
        // 每次开始比较时k指针的值取i指针的之，且将k指针回退到0位置，
        int k = i;
        while (str[k] == substr[j] && j < n)
        {
            k++;
            j++;
        }
        if(j == n)
        {
            return (char *) str + i;
        }
    }
    return NULL;
}


/**
 * 测试自定义函数实现从头到尾在一个字符串中查找给定字符串的第一个匹配之处一
 */
void my_strstr_1_test()
{
    const char *str = "abccabcabbc";
    const char *substr = "abca";
    char *p = my_strstr_1(str,substr);
    if(NULL != p)
    {
        printf("%s\n", p);
    }
    else
    {
        printf("不匹配\n");
    }
}

/**
 * 自定义函数实现从头到尾在一个字符串中查找给定字符串的第一个匹配之处二
 *
 * @param str 给定字符串
 * @param substr 给定子字符串
 * @return 返回的是从匹配的子字符串开始到原字符串结束的部分
 */
char *my_strstr_2(const char *str, const char *substr)
{
    if (NULL == str || NULL == substr)
    {
        return NULL;
    }
    if(strlen(str) < strlen(substr))
    {
        return NULL;
    }
    int m = strlen(str);
    int n = strlen(substr);
    int i = 0, j = 0;
    while (i < m && j < n)
    {
        if(str[i] == substr[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if(j == n)
    {
        return (char *)str + i - j;
    }
    return NULL;
}

/**
 * 测试自定义函数实现从头到尾在一个字符串中查找给定字符串的第一个匹配之处二
 */
void my_strstr_2_test()
{
    const char *str = "abccabcabbc";
    const char *substr = "cca";
    char *p = my_strstr_2(str,substr);
    if(NULL != p)
    {
        printf("%s\n", p);
    }
    else
    {
        printf("不匹配\n");
    }
}

/**
 * 字符串转为小写格式函数
 *
 * char *strlwr(char *str)
 * @param str 要转成小写格式的字符串
 * @return 小写格式的字符串
 */
void strlwr_test()
{
    char s[] = "AbC";
    printf("s = %s\n", strlwr(s));
}

/**
 * 字符串转为大写格式函数
 *
 * char *strupr(char *str)
 * @param str 要转成大写格式的字符串
 * @return 大写格式的字符串
 */
void strupr_test()
{
    char s[] = "AbC";
    printf("s = %s\n", strupr(s));
}

/**
 * 字符串拷贝函数（一般和 free() 函数成对出现）
 *
 * char *strdup(const char *str);
 * @param str 指向要复制的源字符串
 * @return 返回一个指向新分配的、包含复制内容的字符串的指针。如果内存分配失败，则返回 NULL
 * @tips  1.strdup的可移植性：非C标准函数，需确保环境支持（如Windows需 _strdup）
 * @tips  2.strdup可能出现内存泄漏：strdup返回的指针必须用free()释放
 * @tips  3.strdup可能返回NULL，需检查后再使用
 */
void strdup_test()
{
    const char *original = "Hello World!";
    char *duplicate = strdup(original);
    if(NULL != duplicate)
    {
        printf("original  = %s\n", original);
        printf("duplicate = %s\n", duplicate);
        // strdup使用malloc分配内存，因此要使用free函数来释放这块儿内存，以避免内存泄漏
        free(duplicate);
    }
    else
    {
        printf("Memory allocate failed\n");
    }
}

/**
* 自定义的字符串拷贝函数（一般和 free() 函数成对出现）
*
* @param str 指向要复制的源字符串
* @return 返回一个指向新分配的、包含复制内容的字符串的指针。如果内存分配失败，则返回 NULL
* @tips  1.strdup的可移植性：非C标准函数，需确保环境支持（如Windows需 _strdup）
* @tips  2.strdup可能出现内存泄漏：strdup返回的指针必须用free()释放
* @tips  3.strdup可能返回NULL，需检查后再使用
*/
char *my_strdup(const char *str)
{
    if(NULL == str)
    {
        return NULL;
    }
    int len = strlen(str) + 1;
    char *dest = (char *)malloc(sizeof(char) * len);
    strcpy(dest, str);
    return dest;
}

/**
 * 测试自定义的字符串拷贝函数
 */
void my_strdup_test()
{
    const char *original = "Hello World!";
    char *duplicate = my_strdup(original);
    if(NULL != duplicate)
    {
        printf("original  = %s\n", original);
        printf("duplicate = %s\n", duplicate);
        // strdup使用malloc分配内存，因此要使用free函数来释放这块儿内存，以避免内存泄漏
        free(duplicate);
    }
    else
    {
        printf("Memory allocate failed\n");
    }
}

/**
 * 初始化内存空间函数（将dest的前n个字符设置为字符val）
 *
 * void * memset(void * dest, int val, size_t n)
 * @param dest 目标内存地址
 * @param val 要设置的值，虽然它是一个int类型，但实际上它会被解释为unsigned char，即只会用到这个值的最低8位。
 * @param n   要设置的字节数
 */
void memset_test()
{
	char str[10];
	// 使用数字10填充
	memset(str, 10, sizeof(str));
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", str[i]);
	}
	printf("\n");

	// 使用字符'a'填充
	memset(str, 'a', sizeof(str));
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", str[i]);
	}
	printf("\n");

	// 使用数字0填充
	memset(str, 0, sizeof(str));
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", str[i]);
	}
	printf("\n");
}

/**
 * 自定义的初始化内存空间函数（将dest的前n个字符设置为字符val）
 *
 * @param vp 目标字符串
 * @param ch 要设置的值，虽然它是一个int类型，但实际上它会被解释为unsigned char，即只会用到这个值的最低8位。
 * @param n  要设置的字节数
 */
void my_memset(void *pv, unsigned char ch, size_t n)
{
    unsigned char *pc = (unsigned char *)pv;
    for(int i = 0; i < n; i++)
    {
        /*
        *pc = ch;
        pc = pc + 1;
        */
    	pc[i] = ch; // *(ch+i) = ch;
    }
}

/**
 * 测试自定义的初始化内存空间函数（将dest的前n个字符设置为字符val）
 */
void my_memset_test()
{
    int arr[10];
    my_memset(arr, 10, sizeof(arr));
    for(int i = 0; i < 10; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");

    char str[10];
    my_memset(str, 'a', sizeof(str));
    for(int i = 0; i < 10; i++)
    {
        printf("%d  ", str[i]);
    }
    printf("\n");

	// 使用数字10填充
	my_memset(str, 10, sizeof(str));
	for (int i = 0; i < 10; i++)
	{
		printf("%d  ", str[i]);
	}
	printf("\n");
}

/**
 * 比较两块内存区域前n个字节内容的函数
 *
 * int memcmp(const void *str1, const void *str2, size_t n);
 * @param buf1 指向内存块儿buf1的指针
 * @param buf2 指向内存块儿buf2的指针
 * @param n    要被比较的字节数
 * @return     如果返回值 < 0，则表示 str1 小于 str2。
 *             如果返回值 > 0，则表示 str2 小于 str1。
 *             如果返回值 = 0，则表示 str1 等于 str2。
 */
void memcmp_test()
{
    int arr_1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int arr_2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int flag = memcmp(arr_1, arr_2, sizeof(arr_1));
    printf("flag = %d\n", flag);
}

/**
 * 自定义的比较两块内存区域前n个字节内容的函数
 *
 * @param buf1 指向内存块儿buf1的指针
 * @param buf2 指向内存块儿buf2的指针
 * @param n    要被比较的字节数
 * @return     如果返回值 < 0，则表示 str1 小于 str2。
 *             如果返回值 > 0，则表示 str2 小于 str1。
 *             如果返回值 = 0，则表示 str1 等于 str2。
 */
int my_memcmp(const void *buf1, const void *buf2, size_t n)
{
    assert(buf1 != NULL && buf2 != NULL);
    if(0 == n)
    {
        return 0;
    }
    const char *p_buf1 = (const char *)buf1;
    const char *p_buf2 = (const char *)buf2;
    while (n != 1 && *p_buf1 == *p_buf2)
    {
        n--;
        p_buf1++;
        p_buf2++;
    }
    int result = 0;
    int difference = *p_buf1 - *p_buf2;
    if(difference > 0)
    {
        result  = 1;
    }
    if(difference < 0)
    {
        result  = -1;
    }
    return result;
}

/**
 * 测试自定义的比较两块内存区域前n个字节内容的函数
 */
void my_memcmp_test()
{
    int arr_1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int arr_2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int flag = my_memcmp(arr_1, arr_2, sizeof(arr_1));
    printf("flag = %d\n", flag);
}

int main()
{
    //strlen_test();
    //my_strlen_1_test();
    //my_strlen_2_Test();
    //strcpy_test();
    //my_strcpy_1_test();
    //my_strcpy_2_test();
	//strncpy_test_1();
	//strncpy_test_2();
	//strncpy_test_3();
    //strcat_test();
    //my_strcat_1_test();
    //my_strcat_2_test();
    //strncat_test_1();
    //strncat_test_2();
	//memcpy_test_1();
	//memcpy_test_2();
    //memcpy_test_3();
    //my_memcpy_test();
	//memmove_test();
	//my_memove_1_test();
	//my_memove_2_test();
	//my_memove_3_test();
    //strcmp_test();
    //my_strcmp_1_test();
    //my_strcmp_2_test();
    //strncmp_test();
    //my_strncmp_test();
    //strchr_test();
    //my_strchr_test();
    //strrchr_test();
    //my_strrchr_1_test();
    //my_strrchr_2_test();
    //strstr_test();
    //my_strstr_1_test();
    //my_strstr_2_test();
    //my_strstr_2_test();
    //strlwr_test();
    //strupr_test();
    //strdup_test();
    //my_strdup_test();
	//memset_test();
	//my_memset_test();
    //memcmp_test();
    //my_memcmp_test();
	return 0;
}
