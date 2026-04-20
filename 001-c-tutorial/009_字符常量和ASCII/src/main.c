#include <stdio.h>

/**
 * ASCII码的意义
 * 		每一个字符在ASCII码表中都对应着一个值，这个值可以转换为一个8位二进制数，这个8位二进制数可以在网络传输中直接传输
 */
int main()
{
	printf("字符 a 对应的ASCII值 %d\n", 'a');
	printf("字符 z 对应的ASCII值 %d\n", 'z');
	printf("字符 A 对应的ASCII值 %d\n", 'A');
	printf("字符 Z 对应的ASCII值 %d\n", 'Z');
	printf("字符 0 对应的ASCII值 %d\n", '0');
    // 特别注意
	printf("字符 '\\0' 对应的ASCII值 %d\n", '\0');
	printf("字符 空格 对应的ASCII值 %d\n", ' ');

	int c = 'a';
	// 输出字符常量
	printf("原字符a = %c\n", c);
	// 以ASCII码形式输出
	printf("字符 a 对应的ASCII值 %d\n", c);
	printf("S T A R T对应的ASCII值 0x%x 0x%x 0x%x 0x%x 0x%x\n",(int)'S',(int)'T',(int)'A',(int)'R',(int)'T');
	return 0;
}


