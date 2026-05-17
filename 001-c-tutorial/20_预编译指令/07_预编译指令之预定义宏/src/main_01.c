#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 自定义的 ASSERT 类函数宏
#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s\n", #expr); \
            fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__); \
            fprintf(stderr, "Function: %s\n", __func__); \
            fprintf(stderr, "Date: %s %s\n", __DATE__, __TIME__); \
            abort(); \
        } \
    } while (0)


/**
 * 基于编译器提供的预定义宏实现自定义的 ASSERT 类函数宏
 */

void print_arr(const int *arr, int len);

#if 0
int main()
{
    const int nums[] = { 1, 3, 5, 7, 9 };
    const int len = sizeof(nums) / sizeof(nums[0]);

    // 传递一个正确的参数
    //print_arr(nums, len);

    // 传递一个错误参数
    print_arr(NULL, len);
    return 0;
}
#endif

void print_arr(const int *arr, const int len)
{
    // 系统提供的 assert 类函数宏
    //assert(arr != NULL);
    // 自定义的 assert 类函数宏
    ASSERT(arr != NULL);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}