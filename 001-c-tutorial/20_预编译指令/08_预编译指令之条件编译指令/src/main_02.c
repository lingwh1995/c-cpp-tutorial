#include <stdio.h>

// 定义平台标识
#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX 2
#define PLATFORM_MACOS 3

// 设置当前平台（实际项目中通常由构建系统定义）
#define CURRENT_PLATFORM PLATFORM_WINDOWS

/**
 * 多分支条件编译指令
 */
int main()
{
#if CURRENT_PLATFORM == PLATFORM_WINDOWS
    printf("当前运行在 Windows 平台\n");
    printf("使用 Windows API\n");
#elif CURRENT_PLATFORM == PLATFORM_LINUX
    printf("当前运行在 Linux 平台\n");
    printf("使用 POSIX API\n");
#elif CURRENT_PLATFORM == PLATFORM_MACOS
    printf("当前运行在 macOS 平台\n");
    printf("使用 Darwin API\n");
#else
    printf("未知平台\n");
#endif

// 根据编译器类型选择不同实现
#if defined(__GNUC__)
    printf("使用 GCC/Clang 编译器\n");
#elif defined(_MSC_VER)
    printf("使用 MSVC 编译器\n");
#else
    printf("使用其他编译器\n");
#endif

// 根据调试模式选择不同行为
#ifdef DEBUG
    printf("调试模式：输出详细信息\n");
    printf("变量值: x = %d\n", 42);
#else
    printf("发布模式：正常运行\n");
#endif

    return 0;
}