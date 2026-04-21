#include <stdio.h>
#include <string.h>

/*
 * 字符串: 
 *  1.在C语言中，没有字符串类型数据，可以使用特殊的字符数组来代替字符串，字符串实际上是使用空字符\0结尾的一维字符数组
 *  2.为什么字符串所占的空间大小比字符串长度大1?
 *      因为计算空间大小的时候最后面加了一个\0用于标识字符串这是一个字符串，方便和字符数组进行区分，这
 *      个\0占用了一字节的空间，所以计算出来的字符串的空间大小比长度大了1
 *  3.字符串以\0的好处
 *      a.可以根据字符数组最后一个元素是否是'\0'来判断是该字符数组是字符数组还是字符串
 *      b.C语言不需要知道字符串的长度，就可以读取内存里面的字符串，只要发现有一个字符是'\0'，那么就知道字符串结束了
 *  4.总是把字符串写成数组的形式，是非常麻烦的。C语言提供了一种简写法，双引号之中的字符，会被自动视为字符串，不用自己添加结尾字符'\0'，C语言会自动添加。
 *    {'H', 'e', 'l', 'l', 'o', '\0'}
 *    // 等价于
 *    "Hello"
 *  5.特别补充：结尾标识 '\0' 的ASCII码值为0
 *
 * 字符数组: 由字符组成的数组
 */

/*
 * 字符串的定义：使用 "" 来确定字符串范围，但是计算字符串长度时要根据 '\0' 的位置来确定字符串的结尾位置
 */
void string_basic()
{
    // 定义一个字符串:方式1
	//char s1[] = { "hello" };
    // 定义一个字符串:方式2(字符数组 + \0)
    //char s1[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    // 定义一个字符串:方式3(省略大括号)
    char s1[] = "hello";
    int len = strlen(s1);
    int size = sizeof(s1);
    // 获取字符串的长度
    printf("字符串s的长度 = %d\n", len);
    // 获取字符串所占的空间大小，包括字符串长度和末尾的 '\0'
    printf("字符串s所占的空间大小 = %d\n", size);

    // 输出转义字符+字符串
    char s2[] = { "hello\"C语言\"world" };
    printf("输出转义字符+字符串 = %s\n", s2);

    /**
     * 两种拆分长字符串的方法
     */
     // 1.在需要折行的地方，使用反斜杠（\）结尾，将一行拆成多行（缺点：第二行必须顶格书写，如果想包含缩进，那么缩进也会被计入字符串）
    char s3[] = "hello \
                world";
    printf("s3 = %s\n", s3);
    // 2.C语言允许合并多个字符串字面量，只要这些字符串之间没有间隔，或者只有空格，C语言会将它们自动合并。注意：这种写法支持多行字符串的合并。
    char s5[50] = "Hello, ""how are you ""today" "!";
    // 等同于
    char s6[50] = "Hello, how are you today!";
    // 等同于
    char s7[50] = "Hello, "
                        "how are you "
                        "today!";
    printf("s5 = %s\n", s5);
    printf("s6 = %s\n", s6);
    printf("s7 = %s\n", s7);
}

/*
 * 字符数组的定义 + 字符串和字符数组的区别
 */
void string_and_char_array()
{
    // 普通字符数组
    char c1[] = { 'h', 'e', 'l', 'l', 'o' };
    // 乱码，因为没有'\0'结束符
    printf("c1 = %s\n", c1);

    // 定义一个字符串,以 '\0' 结尾
    char s1[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    printf("s1 = %s\n", s1);

    // 字符串处理以'\0'作为结束符,后面的'c', 'l', 'a', 'n', 'g'不会输出
    char s2[] = { 'h', 'e', 'l', 'l', 'o', '\0', 'c', 'l', 'a', 'n', 'g', '\0' };
    printf("s2 = %s\n", s2);
}

/**
 * 遍历字符串方式一
 */
void foreach_string_1()
{
    char str[] = "hello";
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%c\n", str[i]);
        printf("%p\n", &str[i]);
    }
}

/**
 * 遍历字符串方式二
 */
void foreach_string_2()
{
    char str[] = "world";
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c\n", str[i]);
        printf("%p\n", &str[i]);
    }
}


/**
 * 结尾符 '\0' 的ASCII码是0
 */
void end_flag_ascii_code()
{
    char end_flag = '\0';
    printf("end_flag = %d\n", end_flag);
}

int main()
{
	string_basic();
	//string_and_char_array();
	//foreach_string_1();
	//foreach_string_2();
    end_flag_ascii_code();
	return 0;
}
