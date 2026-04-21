#include <stdio.h>

int main()
{
	/**
	 * 转义字符串输出
	 */
	char c1 = '\t';
	printf("+%c+\n", c1);
	// 输出反斜杠
	printf("\\");
	printf("\n");
	// 输出双引号
	printf("\"");
	printf("\n");

	/**
	 * 8进制和16进制转义
	 *      8进制: \102
	 *      16进制: \x42
	 */
	printf("字符'B'的十进制表示:%d\n", 'B');
	printf("字符'B'(八进制数0102)的十进制表示:%d\n", 0102);
	printf("8进制的转义:\102\n");
	printf("16进制的转义:\x42\n");
	return 0;
}
