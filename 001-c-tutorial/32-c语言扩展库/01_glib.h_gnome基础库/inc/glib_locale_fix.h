#ifndef GLIB_LOCALE_FIX_H
#define GLIB_LOCALE_FIX_H

#include <locale.h>
#include <glib.h>

// 检查编译器是否支持constructor属性（GCC/Clang支持，MSVC不支持）
#if defined(__GNUC__) || defined(__clang__)

// 核心宏：自动生成一个在main之前执行的构造函数
// 优先级101：确保在GLib初始化（通常优先级100）之后、其他代码之前运行
#define FIX_GLIB_UTF8_LOCALE() \
__attribute__((constructor(101))) \
void glib_locale_fix_##__LINE__() { \
    g_setenv("LC_ALL", "zh_CN.UTF-8", TRUE); \
    g_setenv("LANG", "zh_CN.UTF-8", TRUE); \
    setlocale(LC_ALL, "zh_CN.UTF-8"); \
}

// 进阶宏：支持自定义区域设置
#define FIX_GLIB_LOCALE(locale) \
__attribute__((constructor(101))) \
void glib_locale_fix_##__LINE__() { \
    g_setenv("LC_ALL", locale, TRUE); \
    g_setenv("LANG", locale, TRUE); \
    setlocale(LC_ALL, locale); \
}

#else

// 对于不支持constructor属性的编译器，宏展开为空
#define FIX_GLIB_UTF8_LOCALE()
#define FIX_GLIB_LOCALE(locale)
#warning "GLib locale fix is not supported on this compiler"

#endif

#endif // GLIB_LOCALE_FIX_H