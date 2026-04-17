#include <stdio.h>
#include <stdint.h>

/**
 * 部分可移植数据类型展示
 *
 * int8_t：8位有符号整数
 * int16_t：16位有符号整数
 * int32_t：32位有符号整数
 * int64_t：64位有符号整数
 * uint8_t：8位无符号整数
 * uint16_t：16位无符号整数
 * uint32_t：32位无符号整数
 * uint64_t：64位无符号整数
 */
int main()
{
  int32_t x32 = 45933945;
  printf("x32 = %d\n", x32);
  return 0;
}
