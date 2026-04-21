#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>

// 奇偶判断
static inline int is_odd(int x)
{
	return x & 1;
}

static inline int is_even(int x)
{
	return !(x & 1);
}

// 乘 2^n / 除 2^n
static inline int mul2(int x, int n)
{
	return x << n;
}

static inline int div2(int x, int n)
{
	return x >> n;
}

// 是否是 2 的幂
static inline int is_power_of_two(uint32_t x)
{
    return x != 0 && (x & (x - 1)) == 0;
}

// 取绝对值（int）
static inline int abs_int(int x)
{
    int sign = x >> 31;
    return (x ^ sign) - sign;
}

// 统计二进制 1 的个数
static inline int count_bits(uint32_t x)
{
    int cnt = 0;
    while (x)
    {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

// 保留最后一个 1
static inline uint32_t last_bit(uint32_t x)
{
    return x & -x;
}

// 清除最后一个 1
static inline uint32_t clear_last_bit(uint32_t x)
{
    return x & (x - 1);
}

// ------------------------------
// 高低位交换 & 翻转
// ------------------------------
// 8 位高低 4 位交换
static inline uint8_t swap_4bits(uint8_t x)
{
    return (x >> 4) | (x << 4);
}

// 16 位高低 8 位交换
static inline uint16_t swap_8bits(uint16_t x)
{
    return (x >> 8) | (x << 8);
}

// 32 位 4 字节翻转（大小端）
static inline uint32_t reverse_32(uint32_t x)
{
    return  ((x >> 24) & 0xFF)       |
            ((x >>  8) & 0xFF00)     |
            ((x <<  8) & 0xFF0000)   |
            ((x << 24) & 0xFF000000);
}

// 8 位整体位翻转（加密常用）
static inline uint8_t reverse8(uint8_t x)
{
    x = ((x >> 4) & 0x0F) | ((x << 4) & 0xF0);
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xCC);
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xAA);
    return x;
}

// ------------------------------
// 状态压缩
// ------------------------------
static inline uint32_t set_bit(uint32_t x, int i)
{
    return x | (1U << i);
}

static inline uint32_t clear_bit(uint32_t x, int i)
{
    return x & ~(1U << i);
}

static inline int get_bit(uint32_t x, int i)
{
    return (x >> i) & 1;
}

static inline uint32_t flip_bit(uint32_t x, int i)
{
    return x ^ (1U << i);
}

#endif
