#include<stdio.h>
#include<limits.h>

int main()
{
	// signed char 的最小值和最大值
	printf("CHAR_MIN = %d, CHAR_MAX = %d\n", CHAR_MIN, CHAR_MAX);
	// signed short 的最小值和最大值
	printf("SHRT_MIN = %d, SHRT_MAX = %d\n", SHRT_MIN, SHRT_MAX);
	// signed int 的最小值和最大值
	printf("INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
	// signed long 的最小值和最大值
	printf("LONG_MIN = %ld, LONG_MAX = %ld\n", LONG_MIN, LONG_MAX);
	// signed long long 的最小值和最大值
	printf("LLONG_MIN = %lld, LLONG_MAX = %lld\n", LLONG_MIN, LLONG_MAX);

	// unsigned char 的最大值
	printf("UCHAR_MAX = %u\n", UCHAR_MAX);
	// unsigned short 的最大值
	printf("USHRT_MAX = %u\n", USHRT_MAX);
	// unsigned int 的最大值
	printf("USHRT_MAX = %u\n", USHRT_MAX);
	// unsigned long 的最大值
	printf("ULONG_MAX = %lu\n", ULONG_MAX);
	// unsigned long long 的最大值
	printf("ULLONG_MAX = %llu\n", ULLONG_MAX);

}
