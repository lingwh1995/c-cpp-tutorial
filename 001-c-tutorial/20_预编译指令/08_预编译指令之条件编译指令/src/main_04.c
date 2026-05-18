#include <stdio.h>

/**
 * 条件编译指令之判断宏是否定义
 *    #ifdef MACRO_NAME     - 如果宏已定义，则编译下面的代码
 *    #ifndef MACRO_NAME    - 如果宏未定义，则编译下面的代码
 */

// 示例1：#ifdef 基本用法
#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define LOG(msg) printf("[DEBUG] %s\n", msg)
#else
    #define LOG(msg)
#endif

// 示例2：#ifndef 防止重复包含（模拟头文件保护）
#ifndef MY_HEADER_GUARD
#define MY_HEADER_GUARD

#define VERSION "1.0.0"
#define AUTHOR  "TestUser"

#endif

// 示例3：多分支判断
#define OS_WINDOWS

#ifdef OS_WINDOWS
    #define PATH_SEPARATOR '\\'
    #define NEWLINE "\r\n"
#elif defined(OS_LINUX)
    #define PATH_SEPARATOR '/'
    #define NEWLINE "\n"
#elif defined(OS_MACOS)
    #define PATH_SEPARATOR '/'
    #define NEWLINE "\r"
#else
    #define PATH_SEPARATOR '/'
    #define NEWLINE "\n"
#endif

// 示例4：嵌套使用
#define FEATURE_A
#define FEATURE_B

#ifdef FEATURE_A
    #ifdef FEATURE_B
        #define COMBINED_FEATURE "A+B"
    #else
        #define COMBINED_FEATURE "A only"
    #endif
#else
    #ifdef FEATURE_B
        #define COMBINED_FEATURE "B only"
    #else
        #define COMBINED_FEATURE "none"
    #endif
#endif

int main(void)
{
    printf("=== #ifdef 和 #ifndef 示例 ===\n\n");

    // 测试日志宏
    LOG("调试模式已启用");
    printf("普通消息\n\n");

    // 测试版本信息
    printf("版本: %s\n", VERSION);
    printf("作者: %s\n\n", AUTHOR);

    // 测试路径分隔符
    printf("路径分隔符: '%c'\n", PATH_SEPARATOR);
    printf("换行符: \"%s\"\n\n", NEWLINE);

    // 测试组合功能
    printf("启用的功能: %s\n\n", COMBINED_FEATURE);

    // 测试宏是否定义
#ifdef DEBUG_MODE
    printf("[✓] DEBUG_MODE 已定义\n");
#else
    printf("[×] DEBUG_MODE 未定义\n");
#endif

#ifndef RELEASE_MODE
    printf("[✓] RELEASE_MODE 未定义\n");
#else
    printf("[×] RELEASE_MODE 已定义\n");
#endif

    return 0;
}