#include <stdio.h>


/**
 * 把格式化的数据写入某个字符串
 *
 * int sprintf(char *buffer, const char *format, [ argument] ...);
 * @param buffer 被写入的字符串地址
 * @format 格式化字符串
 * @[argument] 可选参数，可以是任何类型的数据
 * @return 写入到字符串中的字符数（不包括结尾的空字符 \0）。如果在写入数据时发生错误（如缓冲区太小），返回值将是负数。
 */
void sprintf_test()
{
	char str1[] = "hello";
	char str2[] = "world";
	char s1[20];
	int n = sprintf(s1, "%s %s", str1, str2);
	printf("写入字节数 = %d\n", n); // 11（注意：两个%s之间的空格占据了一个字符，所以返回的长度是 str1长度 + str2长度 + 1 ）
	printf("字符串s1 = %s\n", s1); // hello world

	char *str3 = "hello";
	char *str4 = "world~";
	char s2[20];
	n = sprintf(s2, "%s %s", str3, str4);
	printf("写入字节数 = %d\n", n); // 12（注意：两个%s之间的空格占据了一个字符，所以返回的长度是 str1长度 + str2长度 + 1 ）
	printf("字符串s2 = %s\n", s2); // hello world~

	//把整数123打印成一个字符串保存在s3中
	char s3[20];
	n = sprintf(s3, "%s", "123");
	printf("写入字节数 = %d\n", n);
	printf("字符串s3 = %s\n", s3);

	//把整数123打印成一个字符串保存在s4中，并指定宽度为5，宽度不足5时在左边补空格
	char s4[20];
	n = sprintf(s4, "%5s", "123");
	printf("写入字节数 = %d\n", n);
	printf("字符串s4 = %s\n", s4);

	//把整数123打印成一个字符串保存在s5中，并指定宽度为5，宽度不足5时在右边补空格
	char s5[20];
	n = sprintf(s5, "%-5s", "123");
	printf("写入字节数 = %d\n", n);
	printf("字符串s5 = %s\n", s5);

	//把整数123打印成一个字符串保存在s6中，并以16进制格式小写显示
	char s6[20];
	n = sprintf(s6, "%x", 123);
	printf("写入字节数 = %d\n", n);
	printf("字符串s6 = %s\n", s6);

	//把浮点数12.25打印成一个字符串保存在s7中
	char s7[20];
	n = sprintf(s7, "%f", 12.25);
	printf("写入字节数 = %d\n", n);
	printf("字符串s7 = %s\n", s7);

	//把浮点数12.25打印成一个字符串保存在s8中，并设置保留两位小数
	char s8[20];
	n = sprintf(s8, "%2.2f", 12.25);
	printf("写入字节数 = %d\n", n);
	printf("字符串s8 = %s\n", s8);
}

/**
 * 把格式化的数据写入某个字符串（只写入前n个字节）
 *
 * int sprintf(char *buffer, size_t n, const char *format, [ argument] ...);
 * @param buffer 被写入的字符串地址
 * @param n 要写入的字节个数
 * @format 格式化字符串
 * @[argument] 可选参数，可以是任何类型的数据
 * @return 写入到字符串中的字符数（不包括结尾的空字符 \0）。如果在写入数据时发生错误（如缓冲区太小），返回值将是负数。
 * @tips  snprintf()写入时会自动在末尾添加结尾符'\0'
 */
void snprintf_test()
{
	char str1[] = "hello";
	char str2[] = "world";
	char s1[20];
	int n = snprintf(s1, 3, "%s %s", str1, str2);
	printf("写入字节数 = %d\n", n); // 11（注意：两个%s之间的空格占据了一个字符，所以返回的长度是 str1长度 + str2长度 + 1 ）
	printf("字符串s1 = %s\n", s1); // hello world

	char *str3 = "hello";
	char *str4 = "world~";
	char s2[20];
	n = snprintf(s2, 3, "%s %s", str3, str4);
	printf("写入字节数 = %d\n", n); // 12（注意：两个%s之间的空格占据了一个字符，所以返回的长度是 str1长度 + str2长度 + 1 ）
	printf("字符串s2 = %s\n", s2); // hello world~

	//把整数123打印成一个字符串保存在s3中
	char s3[20];
	n = snprintf(s3, 4, "%s", "123");
	printf("写入字节数 = %d\n", n);
	printf("字符串s3 = %s\n", s3);

	//把整数123打印成一个字符串保存在s4中，并指定宽度为5，宽度不足5时在左边补空格
	char s4[20];
	n = snprintf(s4, 6, "%5s", "123");
	printf("写入字节数 = %d\n", n);
	printf("字符串s4 = %s\n", s4);

	//把整数123打印成一个字符串保存在s5中，并指定宽度为5，宽度不足5时在右边补空格
	char s5[20];
	n = snprintf(s5, 6, "%-5s", "123");
	printf("写入字节数 = %d\n", n);
	printf("字符串s5 = %s\n", s5);

	//把整数123打印成一个字符串保存在s6中，并以16进制格式小写显示
	char s6[20];
	n = snprintf(s6, 3, "%x", 123);
	printf("写入字节数 = %d\n", n);
	printf("字符串s6 = %s\n", s6);
}

/**
 * 从缓冲区中（实际上是从字符串中）读取数据
 * @param 缓冲区字符串
 */
void sscanf_test()
{
	int a = 0;
	int b = 0;
	char s[20] = "10 20";
	int len = sscanf(s, "%d %d", &a, &b);
	printf("从缓冲区中读取到的数据个数：%d，读取到的数据：a = %d, b = %d\n", len, a, b);
}

int main()
{
    sprintf_test();
    //snprintf_test();
    //sscanf_test();
	return 0;
}
