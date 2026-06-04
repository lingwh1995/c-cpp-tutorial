#include <stdio.h>
#include "../inc/glib_locale_fix.h"
#include <glib-object.h>
#include <gio/gio.h>
//#include <glib/gstdio.h>      // 如果要引入子模块，这种是标准写法
#include <string.h>
#include <sys/stat.h>

// 默认环境修复编码
FIX_GLIB_UTF8_LOCALE();

// 英文环境修复编码
// FIX_GLIB_LOCALE("en_US.UTF-8");
// 中文环境修复编码
//FIX_GLIB_LOCALE("zh_CN.UTF-8");

/**
 * GLib - GNOME 基础库
 *
 * 1. 官网
 *    https://developer.gnome.org/glib/
 * 2. 官方文档
 *    glib 核心库文档：https://docs.gtk.org/glib/
 *    gobject 系统文档：https://docs.gtk.org/gobject/
 *    gio 输入输出库文档：https://docs.gtk.org/gio/
 *    gmodule 动态加载文档：https://docs.gtk.org/gmodule/
 *    ibm技术博客 https://developer.ibm.com/tutorials/l-glib/
 * 3. 功能
 *    数据结构、实用函数、事件循环、线程等
 * 4. 普通方式安装
 *    - windows(打开 MSYS2 UCRT64 的终端，执行以下命令)
 *       pacman -Syu                                # 更新系统
 *       pacman -S mingw-w64-ucrt-x86_64-glib2 -y   # 安装glib2
 *       pacman -Qs glib2                           # 检查是否安装成功
 *    - linux
 *       sudo apt-get update
 *       sudo apt-get install libglib2.0-dev
 * 4. clion中如果配置 ToolSet 失败，出现无法是被出 ucrt64 的问题，使用管理员账户打开 clion 再进行配置
 */

// // 打印链表数据的辅助函数
// void print_list_item(gpointer data, gpointer user_data)
// {
//     g_print(" -> %s", (char*)data);
// }
//
// int main()
// {
//     g_print("--- 1. GLib 跨平台数据类型 ---\n");
//     gint g_int = 10;
//     gchar* g_str = "Hello gLib in ucrt64!";
//     g_print("Integer: %d, String: %s\n\n", g_int, g_str);
//
//
//     // ------------------------------------------
//     // 2. 测试 动态数组 (GArray)
//     // ------------------------------------------
//     g_print("--- 2. GArray Test ---\n");
//     // 创建一个存储 int 类型的动态数组，清零并设置边界安全检查
//     GArray *array = g_array_new(FALSE, FALSE, sizeof(gint));
//
//     // 牢记：g_array_append_val 必须传入变量（左值）
//     gint val1 = 10, val2 = 20, val3 = 30;
//     g_array_append_val(array, val1);
//     g_array_append_val(array, val2);
//     g_array_append_val(array, val3);
//
//     g_print("GArray length: %d\n", array->len);
//     for (guint i = 0; i < array->len; i++)
//     {
//         // 使用 g_array_index 宏安全读取数据
//         g_print("  Index %d: %d\n", i, g_array_index(array, gint, i));
//     }
//
//     // 释放数组内存
//     g_array_free(array, TRUE);
//     g_print("\n");
//
//     // ------------------------------------------
//     // 3. 测试 双向链表 (GList)
//     // ------------------------------------------
//     g_print("--- 3. GList Test ---\n");
//     GList *list = NULL;
//
//     // 往链表中追加字符串数据
//     list = g_list_append(list, "Apple");
//     list = g_list_append(list, "Banana");
//     list = g_list_append(list, "Cherry");
//
//     g_print("GList current items:");
//     // 遍历链表
//     g_list_foreach(list, print_list_item, NULL);
//     g_print("\n");
//
//     // 查找测试
//     GList *found = g_list_find_custom(list, "Banana", (GCompareFunc)g_strcmp0);
//     if (found)
//     {
//         g_print("  Find custom success: %s exists in list.\n", (char*)found->data);
//     }
//
//     // 释放整个链表
//     g_list_free(list);
//     g_print("---------------------------------=\n");
//
//     return 0;
// }

/**
 * 第1章：GLib 基础数据类型与常用宏
 */
void chapter1_basic_types_and_macros_test()
{
    g_print("--- 第1章：GLib 基础数据类型 ---\n\n");

    // 1.1. 基本数据类型 官方文档：https://docs.gtk.org/glib/types.html
    g_print("1.1 基本数据类型\n");

    // gchar - char
    const gchar c = 'a';
    g_print("gchar c = %c\n", c);

    // guchar - unsigned char
    const guchar uc = 'a';
    g_print("gchar uc = %c\n", uc);

    // gint - int
    const gint i = 25;
    g_print("gint i = %d\n", i);

    // guint - unsigned int
    const guint ui = 100;
    g_print("guint ui = %u\n", ui);

    // glong - long
    const glong l = 123456789L;
    g_print("glong l = %ld\n", l);

    // gulong - unsigned long
    const glong ul = 123456789L;
    g_print("glong ul = %lu\n", ul);

    // gboolean - 布尔类型，取值为 TRUE 或 FALSE
    const gboolean bt = TRUE;
    const gboolean bf = FALSE;
    g_print("gboolean bt = %s\n", bt ? "TRUE" : "FALSE");
    g_print("gboolean bf = %s\n", bf ? "TRUE" : "FALSE");
    g_print("gboolean TRUE = %d, FALSE = %d\n", TRUE, FALSE);

    // gpointer - void*
    const gint value = 42;
    gpointer ptr = &value;
    g_print("gpointer 指向值 %d\n", *(gint *)ptr);

    // gconstpointer - const void *
    gconstpointer cptr = &value;
    g_print("gconstpointer 指向值 %d\n", *(gint *)cptr);

    // gsize - sizeof(无符号类型)
    const gsize gs = sizeof(gint);
    g_print("gsize sizeof(gint) = %" G_GSIZE_FORMAT "\n", gs);

    // gssize - sizeof(有符号类型)
    const gssize gss = sizeof(guint);
    g_print("gssize sizeof(guint) = %" G_GSIZE_FORMAT "\n", gss);

    // gint8/gint16/gint32/gint64 - 固定宽度整型
    const gint8  i8  = 127;
    const gint16 i16 = 32767;
    const gint32 i32 = 2147483647;
    const gint64 i64 = G_GINT64_CONSTANT(9223372036854775807);
    g_print("gint8 = %d, gint16 = %d, gint32 = %d\n", i8, i16, i32);
    g_print("gint64 = %" G_GINT64_FORMAT "\n", i64);

    // guint8/guint16/guint32/guint64 - 固定宽度无符号整型
    const guint8  u8  = 255;
    const guint16 u16 = 65535;
    const guint32 u32 = 4294967295U;
    const guint64 u64 = G_GUINT64_CONSTANT(18446744073709551615);
    g_print("guint8 = %u, guint16 = %u, guint32 = %u\n", u8, u16, u32);
    g_print("guint64 = %" G_GUINT64_FORMAT "\n", u64);

    // gfloat/gdouble - 浮点类型
    const gfloat  f = 3.14f;
    const gdouble d = 3.141592653589793;
    g_print("gfloat = %.2f, gdouble = %.15f\n", f, d);

    // 1.2. 常用宏定义 官方文档：https://docs.gtk.org//glib/#constants
    g_print("\n1.2 常用宏定义\n");

    // G_MININT/G_MAXINT 取值范围宏
    g_print("gint 取值范围 %d ~ %d\n", G_MININT, G_MAXINT);
    // G_MAXUINT 取值范围宏
    g_print("G_MAXUINT = %u\n", G_MAXUINT);

    // G_MINLONG/G_MAXLONG 取值范围宏
    g_print("glong 取值范围 %ld ~ %ld\n", G_MINLONG, G_MAXLONG);
    // G_MAXULONG 取值范围宏
    g_print("G_MAXULONG = %lu\n", G_MAXULONG);

    // G_MININT64/G_MAXINT64 取值范围宏（64 位整数）
    g_print("gint64 取值范围 %" G_GINT64_FORMAT " ~ %" G_GINT64_FORMAT "\n", G_MININT64, G_MAXINT64);
    g_print("guint64 最大值 %" G_GUINT64_FORMAT "\n", G_MAXUINT64);

    // G_MINSSIZE/G_MAXSSIZE 取值范围宏
    g_print("gssize 取值范围 %" G_GSSIZE_FORMAT " ~ %" G_GSSIZE_FORMAT "\n", G_MINSSIZE, G_MAXSSIZE);
    g_print("gsize 最大值 %" G_GSIZE_FORMAT "\n", G_MAXSIZE);

    // 布尔值
    g_print("TRUE: %d, FALSE: %d\n", TRUE, FALSE);

    // NULL指针
    g_print("NULL: %p\n", NULL);

    // 类型转换宏
    gint a = 10;
    gpointer ptr_a = GINT_TO_POINTER(a);
    gint b = GPOINTER_TO_INT(ptr_a);
    g_print("GINT_TO_POINTER/GPOINTER_TO_INT: %d -> %p -> %d\n", a, ptr_a, b);

    // 数学宏
    g_print("ABS(-10) = %d\n", ABS(-10));
    g_print("MIN(5, 10) = %d\n", MIN(5, 10));
    g_print("MAX(5, 10) = %d\n", MAX(5, 10));
    g_print("CLAMP(15, 5, 10) = %d\n", CLAMP(15, 5, 10));

    // 字节序宏
    g_print("G_BYTE_ORDER = %d (G_LITTLE_ENDIAN: %d, G_BIG_ENDIAN: %d)\n",
            G_BYTE_ORDER, G_LITTLE_ENDIAN, G_BIG_ENDIAN);

    // 字符串化宏
    g_print("G_STRINGIFY(hello) = %s\n", G_STRINGIFY(hello));

    // 结构体成员偏移宏
    g_print("G_STRUCT_OFFSET(struct stat, st_size) = %zu\n", (size_t)G_STRUCT_OFFSET(struct stat, st_size));

    // 数组元素个数宏
    gint g_array[] = { 1, 2, 3, 4, 5 };
    g_print("G_N_ELEMENTS(g_array) = %zu\n", G_N_ELEMENTS(g_array));

    // G_LIKELY 和 G_UNLIKELY 是编译器优化提示宏，通常用于条件判断
    if (G_LIKELY(1))
    {
        g_print("G_LIKELY(1): 分支很可能执行\n");
    }
    if (G_UNLIKELY(0))
    {
        g_print("G_UNLIKELY(0): 分支不太可能执行\n");
    }
}

/**
 * 第2章：内存管理
 */
void chapter2_memory_management_test()
{
    g_print("--- 第2章：内存管理 ---\n\n");

    // 2.1. 基本内存分配 官方文档：https://docs.gtk.org/glib/memory.html
    g_print("2.1 基本内存分配\n");
    // 分配内存
    const gpointer mem1 = g_malloc(100);
    g_print("g_malloc(100) = %p\n", mem1);
    g_free(mem1);   // 释放内存

    // 分配并初始化为0
    const gpointer mem2 = g_malloc0(100);
    g_print("g_malloc0(100) = %p, 第一个字节: %d\n", mem2, ((guchar*)mem2)[0]);
    // 释放内存
    g_free(mem2);

    // 等价于 g_malloc(100)
    const gpointer mem3 = g_realloc(NULL, 100);
    g_print("g_realloc(NULL, 100) = %p\n", mem3);
    // 重新分配
    const gpointer mem4 = g_realloc(mem3, 200);
    g_print("g_realloc(mem3, 200) = %p\n", mem4);
    // 释放内存
    g_free(mem4);

    // 2.2. 对齐内存分配（GLib 2.72+）
    g_print("\n2.2 对齐内存分配\n");
    gpointer aligned_mem = g_aligned_alloc(1, 100, 16);  // 1块 × 100字节，16字节对齐
    g_print("g_aligned_alloc(1, 100, 16) = %p\n", aligned_mem);
    // 必须使用对应的释放函数
    g_aligned_free(aligned_mem);

    // 2.3. 临时内存分配（栈分配）
    g_print("\n2.3 临时内存分配\n");
    // 从栈分配，自动释放
    gchar *stack_mem = g_alloca(100);
    g_print("g_alloca(100) = %p\n", stack_mem);

    // 2.4. 内存切片分配器（高效小内存分配）
    /**
     * g_slice_alloc() 和 malloc() 分配方式区别
     * 1. 性能差异
     *    g_slice_alloc()
     *      使用预分配的内存池
     *      分配速度更快，特别是对于小内存块
     *      减少了系统调用次数
     *    malloc()
     *      每次都需要向操作系统请求内存
     *      相对较慢，尤其是频繁调用时
     *
     * 2. 内存管理方式
     *    g_slice_alloc()
     *      gpointer slice = g_slice_alloc(64);  // 从64字节池中获取
     *      g_slice_free1(64, slice);            // 返回到池中而非真正释放
     *    malloc()/free()
     *      void *ptr = malloc(64);   // 直接向系统申请
     *      free(ptr);                // 直接归还给系统
     *
     * 3. 内存碎片处理
     *    g_slice_alloc()
     *      通过重用相同大小的内存块减少碎片
     *      更适合大量相同大小对象的场景
     *    malloc()/free()
     *      容易产生内存碎片
     *      长时间运行后可能影响性能
     *
     * 4. 应用场景对比
     *    g_slice_alloc()
     *      小对象频繁分配: 如链表节点、结构体等小对象
     *      typedef struct Node {
     *          int data;
     *          struct Node *next;
     *      } Node;
     *
     *      Node* node = g_slice_alloc(sizeof(Node));  // 快速分配
     *      // ... 使用节点 ...
     *      g_slice_free1(sizeof(Node), node);         // 快速释放
     *      // 使用传统分配
     *      Node* node = malloc(sizeof(Node));         // 相对较慢
     *      // ... 使用节点 ...
     *      free(node);                                // 相对较慢
     *
     *    malloc()/free()
     *      不同大小混合分配
     */
    g_print("\n2.4 内存切片分配器\n");
    // 分配64字节的内存块
    gpointer slice = g_slice_alloc(64);
    /**
     * 首次调用 gpointer slice = g_slice_alloc(64);  时， glib 内部会执行如下操作：
     *
     * 1. 检查是否有64字节的内存池
     * 2. 如果没有，则创建64字节规格的池，具体操作是 向系统申请一大块内存（比如几KB），将这块大内存分割成多个64字节的小块，建立空闲链表管理这些小块
     * 3. 如果有，则从空闲链表中取出一个小块，并返回给调用者
     * 4. 如果池中64字节块用完了，触发再次向系统申请大块内存，然后分割成更多64字节块
     *
     * // 第一次调用 - 只创建64字节的池
     * gpointer s1 = g_slice_alloc(64);   // 创建64字节池
     * // 第二次调用不同规格 - 创建新的池
     * gpointer s2 = g_slice_alloc(128);  // 创建128字节池
     * // 第三次调用已有规格 - 直接使用现有池
     * gpointer s3 = g_slice_alloc(64);   // 直接使用64字节池
     * // ... 假设池中64字节块用完了 ...
     * gpointer s3 = g_slice_alloc(64);   // 触发再次向系统申请大块内存，然后分割成更多64字节块
     */
    g_print("g_slice_alloc(64) = %p\n", slice);
    // 释放内存块
    g_slice_free1(64, slice);
}

/**
 * 第3章：字符串处理
 */
void chapter3_glib_string_handling_test()
{
    g_print("\n--- 第3章：字符串处理 ---\n\n");

    // 3.1. 普通字符串操作（官方文档：https://docs.gtk.org/glib/string-utils.html）
    g_print("3.1 基本字符串操作\n");
    const gchar *str1 = "Hello";
    const gchar *str2 = "World";

    // 字符串拼接
    gchar *concat = g_strconcat(str1, ", ", str2, "!", NULL);
    g_print("g_strconcat = %s\n", concat);
    g_free(concat);

    // 字符串复制
    gchar *dup = g_strdup(str1);
    g_print("g_strdup = %s\n", dup);
    g_free(dup);

    // 字符串复制（复制前n个字符串）
    gchar *substr = g_strndup(str1, 3);
    g_print("g_strndup(3) = %s\n", substr);
    g_free(substr);

    gchar *upper = g_ascii_strup(str1, -1);
    g_print("g_ascii_strup = %s\n", upper);
    g_free(upper);

    // 字符串转小写 第二个参数 -1：整串全部转为小写  >0：仅转换前面 length 个字符
    gchar *lower = g_ascii_strdown(str1, -1);
    g_print("g_ascii_strdown = %s\n", lower);
    g_free(lower);

    // 字符串复制（复制前n个字符）
    gchar buffer[20];
    gsize cpy = g_strlcpy(buffer, "Hello", sizeof(buffer));
    g_print("g_strlcpy: copied %zu bytes, buffer = \"%s\"\n", cpy, buffer);

    // 字符串拼接
    gsize cat = g_strlcat(buffer, ", World!", sizeof(buffer));
    g_print("g_strlcat: appended %zu bytes, buffer = \"%s\"\n", cat, buffer);

    // 字符串分割成数组
    const gchar *str = "apple,banana,cherry,orange";
    gchar **split = g_strsplit(str, ",", -1);
    g_print("original str: %s\n", str);
    g_print("split str: ");
    for (gint i = 0; split[i] != NULL; i++)
    {
        g_print("[%s]", split[i]);
    }
    g_print("\n");

    // 字符串拼接
    gchar *join = g_strjoin(" - ", "Red", "Green", "Blue", NULL);
    g_print("joined with ' - ': %s\n", join);
    g_free(join); // 释放拼接后的字符串

    // 字符串拼接
    gchar *joinv = g_strjoinv(" | ", split);
    g_print("joinv with ' | ': %s\n", joinv);
    g_free(joinv); // 释放拼接后的字符串
    g_strfreev(split); // 释放字符串数组

    // 字符串比较
    gint cmp0 = g_strcmp0("hello", "world");
    g_print("g_strcmp0(\"hello\", \"world\") = %d\n", cmp0);
    cmp0 = g_strcmp0(NULL, "");
    g_print("g_strcmp0(NULL, \"\") = %d\n", cmp0);
    cmp0 = g_strcmp0("test", "test");
    g_print("g_strcmp0(\"test\", \"test\") = %d\n", cmp0);

    // 3.2. 动态字符串操作（官方文档：https://docs.gtk.org/glib/struct.String.html）
    g_print("\n3.2 GString 动态字符串\n");
    // 创建一个 GString
    GString *gstr = g_string_new("Hello");
    // 追加字符串
    g_string_append(gstr, ", ");
    g_string_append(gstr, "GLib!");
    g_print("gstr 内容: %s, 长度: %zu, 分配大小: %zu\n", gstr->str, gstr->len, gstr->allocated_len);

    // 在头部插入字符串
    g_string_prepend(gstr, "Wow! ");
    g_print("prepend: %s\n", gstr->str);

    // 插入字符串
    g_string_insert(gstr, 5, " amazing ");
    g_print("insert: %s\n", gstr->str);

    // g_string_printf() ≈ sprintf() + 自动内存管理
    g_string_printf(gstr, "格式化: %d, %s", 42, "test");
    g_print("gsprintf: %s\n", gstr->str);

    /**
    * g_string_free() 有两个参数：
    *   第一个参数：GString* 指针
    *   第二个参数：gboolean free_segment
    *     TRUE：同时释放 GString 结构体 和 内部的字符串数据
    *     FALSE：只释放 GString 结构体，保留字符串数据（返回字符串指针）
     */
    g_string_free(gstr, TRUE);

    // 3.3. UTF-8 字符串处理（官方文档：https://docs.gtk.org/glib/unicode.html）
    g_print("\n3.3 UTF-8 字符串处理\n");
    const gchar *utf8_str = "你好，世界！";
    g_print("UTF-8字符串: %s\n", utf8_str);
    g_print("字节长度(strlen): %zu\n", strlen(utf8_str));
    g_print("字符长度(g_utf8_strlen): %ld\n", g_utf8_strlen(utf8_str, -1));
    g_print("是否有效UTF-8: %s\n", g_utf8_validate(utf8_str, -1, NULL) ? "是" : "否");
}

/**
 * 第4章：数据结构
 */
void chapter4_data_structures_test()
{
    g_print("\n--- 第4章：数据结构 ---\n\n");

    // 4.1. 单向链表 GList（官方文档：https://docs.gtk.org/glib/struct.SList.html）
    g_print("\n-- GSList 单向链表 --\n");
    GSList *slist = NULL;
    slist = g_slist_append(slist, "first");
    slist = g_slist_append(slist, "second");
    slist = g_slist_prepend(slist, "zero");
    g_print("GSList 长度: %u\n", g_slist_length(slist));
    g_print("GSList 内容: ");
    for (GSList *iter = slist; iter != NULL; iter = iter->next) {
        g_print("[%s] ", (gchar *)iter->data);
    }
    g_print("\n");
    g_print("GSList 第2个元素: %s\n", (gchar *)g_slist_nth_data(slist, 1));
    slist = g_slist_remove(slist, "second");
    g_print("删除 \"second\" 后长度: %u\n", g_slist_length(slist));
    g_slist_free(slist);

    // 4.2. 双向链表 GList（官方文档：https://docs.gtk.org/glib/struct.List.html）
    g_print("4.1 单链表 GList\n");
    GList* list = NULL;
    // 添加元素
    list = g_list_append(list, "apple");
    list = g_list_append(list, "banana");
    list = g_list_append(list, "cherry");

    g_print("链表长度: %u\n", g_list_length(list));
    g_print("第一个元素: %s\n", (gchar*)g_list_first(list)->data);
    g_print("最后一个元素: %s\n", (gchar*)g_list_last(list)->data);
    g_print("索引1的元素: %s\n", (gchar*)g_list_nth_data(list, 1));

    // 正向遍历链表
    g_print("GList 正向遍历链表: ");
    for (GList *iter = list; iter != NULL; iter = iter->next) {
        g_print("[%s] ", (gchar *)iter->data);
    }
    g_print("\n");

    // 反向遍历链表
    GList *last = g_list_last(list);
    g_print("GList 反向遍历链表: ");
    for (GList *iter = last; iter != NULL; iter = iter->prev) {
        g_print("[%s] ", (gchar *)iter->data);
    }
    g_print("\n");

    // 排序链表
    list = g_list_sort(list, (GCompareFunc)g_strcmp0);
    g_print("排序后: ");
    for (GList* l = list; l != NULL; l = l->next)
    {
        g_print("%s ", (gchar*)l->data);
    }
    g_print("\n");

    // 只释放链表节点，不释放数据
    g_list_free(list);

    // 4.3. 指针数组 GPtrArray（官方文档：https://docs.gtk.org/glib/struct.PtrArray.html）
    g_print("\n4.2 指针数组 GPtrArray\n");
    GPtrArray* ptr_array = g_ptr_array_new();
    g_ptr_array_add(ptr_array, g_strdup("first"));
    g_ptr_array_add(ptr_array, g_strdup("second"));
    g_ptr_array_add(ptr_array, g_strdup("third"));

    g_print("数组长度: %u\n", ptr_array->len);
    g_print("索引为 1 的元素: %s\n", (gchar*)g_ptr_array_index(ptr_array, 1));

    // 遍历数组
    g_print("遍历数组: ");
    for (guint i = 0; i < ptr_array->len; i++)
    {
        g_print("%s ", (gchar*)g_ptr_array_index(ptr_array, i));
    }
    g_print("\n");

    // 释放数组及其元素
    g_ptr_array_foreach(ptr_array, (GFunc)g_free, NULL);
    g_ptr_array_free(ptr_array, TRUE);

    // 4.4. 哈希表 GHashTable（官方文档：glib-Hash-Tables.html）
    g_print("\n4.3 哈希表 GHashTable\n");
    // 创建哈希表
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(hash, "apple", "red");
    g_hash_table_insert(hash, "banana", "yellow");
    g_hash_table_insert(hash, "cherry", "red");
    g_hash_table_insert(hash, "orange", "orange");

    g_print("哈希表大小（删除前）: %u\n", g_hash_table_size(hash));
    g_print("apple的颜色: %s\n", (gchar*)g_hash_table_lookup(hash, "apple"));
    g_print("grape是否存在: %s\n", g_hash_table_contains(hash, "grape") ? "是" : "否");

    // 根据 key 删除
    g_hash_table_remove(hash, "orange");
    g_print("哈希表大小（删除后）: %u\n", g_hash_table_size(hash));

    // 遍历哈希表
    g_print("遍历哈希表: ");
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, hash);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_print("%s = %s ", (gchar*)key, (gchar*)value);
    }
    g_print("\n");

    // 根据 key 替换值
    g_hash_table_replace(hash, g_strdup("apple"), g_strdup("green"));
    g_print("替换后 \"apple\": %s\n", (gchar *)g_hash_table_lookup(hash, "apple"));

    // 释放哈希表
    g_hash_table_destroy(hash);

    // 4.5. 队列 GQueue（官方文档：glib-Double-Ended-Queues.html）
    g_print("\n4.4 队列 GQueue\n");
    // 创建队列
    GQueue* queue = g_queue_new();
    // 给队列尾部添加元素
    g_queue_push_tail(queue, "first");
    g_queue_push_tail(queue, "second");
    g_queue_push_tail(queue, "third");

    g_print("队列长度: %u\n", g_queue_get_length(queue));
    g_print("队头元素: %s\n", (gchar*)g_queue_peek_head(queue));
    g_print("出队: %s\n", (gchar*)g_queue_pop_head(queue));
    g_print("出队后长度: %u\n", g_queue_get_length(queue));

    // 释放队列
    g_queue_free(queue);

    // 4.6. GArray: 动态数组
    g_print("\n-- GArray 动态数组 --\n");
    GArray *arr = g_array_new(FALSE, FALSE, sizeof(gint));
    gint val;
    val = 10; g_array_append_val(arr, val);
    val = 20; g_array_append_val(arr, val);
    val = 30; g_array_append_val(arr, val);
    g_print("GArray 长度: %u\n", arr->len);
    g_print("GArray 内容: ");
    for (guint i = 0; i < arr->len; i++) {
        g_print("%d ", g_array_index(arr, gint, i));
    }
    g_print("\n");
    // 在指定位置插入元素
    val = 15; g_array_insert_val(arr, 1, val);
    g_print("插入后: ");
    for (guint i = 0; i < arr->len; i++) {
        g_print("%d ", g_array_index(arr, gint, i));
    }
    g_print("\n");

    // 在指定位置删除元素
    g_array_remove_index(arr, 2);
    g_print("删除索引2后: ");
    for (guint i = 0; i < arr->len; i++) {
        g_print("%d ", g_array_index(arr, gint, i));
    }
    g_print("\n");

    // 释放动态数组
    g_array_free(arr, TRUE);
}

/**
 * 第5章：GObject 类型系统基础
 */
// ------------------------- GObject入门程序开始 -------------------------

// -------------------------- 第一部分：定义类的"结构" --------------------------

// 1. 声明：我们要创建一个叫Person的类
#define PERSON_TYPE (person_get_type())
// GObject 类型系统的核心安全保障 - 安全的类型转换
#define PERSON(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), PERSON_TYPE, Person))

// 2. 定义Person对象长什么样（实例结构体）
typedef struct _Person Person;
struct _Person {
    // 父类必须放第一行位置，这是GObject继承体系的硬性要求
    GObject parent;
    // 我们自己加的属性：名字
    gchar* name;
};

// 3. 定义Person类的"公共信息"（类结构体）
typedef struct _PersonClass PersonClass;
struct _PersonClass {
    // 结构体首成员必须是父类的结构体，依靠结构体内存布局实现继承，GObject硬性规范
    GObjectClass parent_class;
};

/**
 * 4. 这个宏帮我们自动完成90%的类型注册工作（定义的函数名必须与 G_DEFINE_TYPE 中的前缀匹配，前缀 "person"）
 * @param Person            大写类型名
 * @param person            小写前缀
 * @param G_TYPE_OBJECT     父类类型
 */
G_DEFINE_TYPE(Person, person, G_TYPE_OBJECT)

// -------------------------- 第二部分：类的初始化 --------------------------

// 实例初始化函数（定义的函数名必须与 G_DEFINE_TYPE 中的前缀匹配） - 每个新Person对象创建时，都会调用这个函数
static void person_init(Person* self)
{
    // 默认名字是 "张三"
    self->name = g_strdup("张三");
    g_print("一个新的Person对象诞生了\n");
}

// 类初始化函数（定义的函数名必须与 G_DEFINE_TYPE 中的前缀匹配） - 整个Person类第一次被使用时，调用一次这个函数
static void person_class_init(PersonClass* klass)
{
    g_print("Person类初始化完成（整个程序只执行一次）\n");
}

// -------------------------- 第三部分：给类添加"方法" --------------------------

// 方法1：设置名字（不是必须以 person 开头或以 set_name 结尾，只是推荐这样命名）
void person_set_name(Person* self, const gchar* new_name)
{
    // 安全检查：确保传入的确实是Person对象
    g_return_if_fail(PERSON(self));

    // 安全检查：新旧值相同则不做任何操作
    if (self->name && new_name && strcmp(self->name, new_name) == 0) {
        return;
    }

    // 释放旧名字，保存新名字
    g_free(self->name);
    self->name = g_strdup(new_name);
}

// 方法2：获取名字（不是必须以 person 开头或以 get_name 结尾，只是推荐这样命名）
const gchar* person_get_name(Person* self)
{
    g_return_val_if_fail(PERSON(self), NULL);
    return self->name;
}

// -------------------------- 第四部分：测试程序 --------------------------

void chapter5_gobject_basics_test_1()
{
    g_print("\n--- 第5章：GObject 类型系统基础 ---\n\n");

    g_print("----- GObject入门程序开始 -----\n\n");
    // 1. 创建一个Person对象
    Person* zhangsan = g_object_new(PERSON_TYPE, NULL);

    // 2. 使用对象的方法
    g_print("默认名字: %s\n", person_get_name(zhangsan));
    person_set_name(zhangsan, "张三");
    g_print("修改后的名字: %s\n", person_get_name(zhangsan));

    // 3. 用完一定要释放
    g_object_unref(zhangsan);
    g_print("对象已释放\n");

    g_print("\n----- GObject入门程序结束 -----\n");
}

// ------------------------- GObject入门程序结束 -------------------------

// ------------------------- GObject高级程序开始 -------------------------

/*
 * MY_TYPE_OBJECT: 获取MyObject对象对应的GType类型值
 * 本质调用my_object_get_type()，该函数完成GObject类型注册并返回唯一类型ID
 * 后续类型判断、类型转换宏都依赖这个类型ID
 *
 * 宏标准命名规范 [大写前缀]_TYPE_[大写类名
 * 宏参数命名规范 [小写模块名]_[小写类名]_get_type(void)
 */
#define MY_TYPE_OBJECT (my_object_get_type())

/*
 * MY_OBJECT(obj): 安全类型转换宏，将GObject*指针转为MyObject*
 * 参数obj: GObject基类对象指针
 * 内部先校验obj的实际类型，类型不符触发断言异常、程序终止；校验通过则强制转型
 */
#define MY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_OBJECT, MyObject))

// 转成类结构体MyObjectClass*
#define MY_OBJECT_CLASS(klass)   G_TYPE_CHECK_CLASS_CAST((klass),MY_TYPE_OBJECT,MyObjectClass)

/*
 * IS_MY_OBJECT(obj): 判断obj是否为MyObject类型的实例对象
 * 参数obj: 待检测的GObject对象指针
 * 返回布尔值，TRUE表示是MyObject实例，FALSE表示不是；仅做判断不会使程序崩溃
 */
#define IS_MY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_OBJECT))

/*
 * 前向声明实例结构体别名：_MyObject是结构体内部标签名，MyObject是对外使用的类型名
 * 用于代表MyObject的实例对象（每个g_object_new创建出来的实体）
 */
typedef struct _MyObject MyObject;

/*
 * 前向声明类结构体别名：_MyObjectClass是内部标签，MyObjectClass对外使用
 * Class结构体存放类信息、虚函数、方法，所有MyObject实例共用同一份Class
 */
typedef struct _MyObjectClass MyObjectClass;

struct _MyObject {
    // 父类必须放首位置，这是GObject继承体系的硬性要求
    GObject parent_instance;

    // 实例私有数据
    gint value;
};

struct _MyObjectClass {
    GObjectClass parent_class;

    // 类级别的虚函数可以在这里声明
    // void (*some_virtual_method)(MyObject *self);
};

/*
 * G_DEFINE_TYPE 宏自动完成以下工作：
 * 1. 声明并实现 my_object_get_type() 函数
 * 2. 定义父类指针 my_object_parent_class
 * 3. 注册类型到GObject类型系统
 * 4. 关联实例初始化函数和类初始化函数
 */
G_DEFINE_TYPE(MyObject, my_object, G_TYPE_OBJECT)

/*
 * 实例初始化函数：每个新创建的对象都会调用一次
 * 用于初始化实例的成员变量，分配实例级别的资源
 */
static void my_object_init(MyObject* self)
{
    self->value = 0;
    g_print("MyObject 实例初始化完成: %p\n", self);
}

/*
 * 类初始化函数：该类第一次被使用时调用一次
 * 用于初始化类结构体，设置虚函数、信号、属性等
 */
static void my_object_class_init(MyObjectClass* klass)
{
    GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

    g_print("MyObject 类初始化完成\n");

    // 在这里可以重写GObject的虚函数，例如：
    // gobject_class->finalize = my_object_finalize;
    // gobject_class->set_property = my_object_set_property;
    // gobject_class->get_property = my_object_get_property;
}

/*
 * 公共方法：设置对象的value属性
 * 使用g_return_if_fail进行参数校验，确保传入的是有效的MyObject实例
 */
void my_object_set_value(MyObject* self, gint value)
{
    g_return_if_fail(IS_MY_OBJECT(self));
    self->value = value;
}

/*
 * 公共方法：获取对象的value属性
 * 使用g_return_val_if_fail进行参数校验，失败时返回默认值0
 */
gint my_object_get_value(MyObject* self)
{
    g_return_val_if_fail(IS_MY_OBJECT(self), 0);
    return self->value;
}

/*
 * 弱引用回调函数：当对象被销毁时自动调用
 */
static void weak_ref_notify(gpointer data, GObject* where_the_object_was)
{
    g_print("弱引用回调: 对象 %p 已被销毁\n", where_the_object_was);
}

void chapter5_gobject_basics_test_2()
{
    g_print("\n----- GObject高级程序开始 -----\n\n");

    // 5.1. GObject 基本概念
    g_print("5.1 GObject 基本概念\n");
    g_print("G_TYPE_OBJECT: %s (类型ID: %lu)\n", g_type_name(G_TYPE_OBJECT), (gulong)G_TYPE_OBJECT);
    g_print("MY_TYPE_OBJECT: %s (类型ID: %lu)\n", g_type_name(MY_TYPE_OBJECT), (gulong)MY_TYPE_OBJECT);
    g_print("MyObject 是否继承自 GObject: %s\n", g_type_is_a(MY_TYPE_OBJECT, G_TYPE_OBJECT) ? "是" : "否");
    g_print("GObject 是否继承自 MyObject: %s\n", g_type_is_a(G_TYPE_OBJECT, MY_TYPE_OBJECT) ? "是" : "否");

    // 5.2. 创建和销毁对象
    g_print("\n5.2 创建和销毁对象\n");
    MyObject* obj = g_object_new(MY_TYPE_OBJECT, NULL);
    g_print("创建对象: %p\n", obj);

    my_object_set_value(obj, 42);
    g_print("设置对象值为: %d\n", my_object_get_value(obj));

    g_object_unref(obj);  // 引用计数减为0，对象被销毁
    g_print("对象已释放\n");

    // 5.3. 引用计数
    g_print("\n5.3 引用计数\n");
    MyObject* obj2 = g_object_new(MY_TYPE_OBJECT, NULL);

    // 注意：不推荐直接访问ref_count成员，这是内部实现细节
    // 这里仅用于演示目的，实际代码中应避免这样做
    g_print("初始引用计数: %d\n", (int)obj2->parent_instance.ref_count);

    g_object_ref(obj2);
    g_print("g_object_ref 后引用计数: %d\n", (int)obj2->parent_instance.ref_count);

    g_object_unref(obj2);
    g_print("第一次 g_object_unref 后引用计数: %d\n", (int)obj2->parent_instance.ref_count);

    g_object_unref(obj2);  // 引用计数变为0，对象被销毁
    g_print("第二次 g_object_unref 后，对象已销毁\n");

    // 5.4. 弱引用
    g_print("\n5.4 弱引用\n");
    MyObject* obj3 = g_object_new(MY_TYPE_OBJECT, NULL);

    // 添加弱引用（需要转换为 GObject* 类型）
    g_object_weak_ref(G_OBJECT(obj3), weak_ref_notify, NULL);
    g_print("已为对象 %p 添加弱引用\n", obj3);

    // 释放对象，此时会触发弱引用回调
    g_object_unref(obj3);

    // 5.5. 类型转换和类型检查
    g_print("\n5.5. 类型转换和类型检查\n");
    GObject* generic_obj = g_object_new(MY_TYPE_OBJECT, NULL);

    // 安全类型转换
    MyObject* typed_obj = MY_OBJECT(generic_obj);
    g_print("GObject* 转换为 MyObject* 成功: %p\n", typed_obj);

    // 类型检查
    g_print("generic_obj 是否是 MyObject 类型: %s\n", IS_MY_OBJECT(generic_obj) ? "是" : "否");

    g_object_unref(generic_obj);

    g_print("\n----- GObject高级程序结束 -----\n\n");
}

// ------------------------- GObject高级程序结束 -------------------------

/**
 * 第6章：GObject 属性
 */
// 定义带属性的 GObject 类
#define MY_TYPE_PROPERTY_OBJECT (my_property_object_get_type())
#define MY_PROPERTY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_PROPERTY_OBJECT, MyPropertyObject))
#define IS_MY_PROPERTY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_PROPERTY_OBJECT))

typedef struct _MyPropertyObject MyPropertyObject;
typedef struct _MyPropertyObjectClass MyPropertyObjectClass;

enum {
    PROP_0,
    PROP_NAME,
    PROP_AGE,
    N_PROPERTIES
};

struct _MyPropertyObject {
    GObject parent_instance;
    gchar* name;
    gint age;
};

struct _MyPropertyObjectClass {
    GObjectClass parent_class;
};

static GParamSpec* obj_properties[N_PROPERTIES] = { NULL, };

GType my_property_object_get_type(void);

G_DEFINE_TYPE(MyPropertyObject, my_property_object, G_TYPE_OBJECT)

static void my_property_object_set_property(GObject* object, guint property_id,  const GValue* value, GParamSpec* pspec)
{
    MyPropertyObject* self = MY_PROPERTY_OBJECT(object);

    switch (property_id)
    {
        case PROP_NAME:
            g_free(self->name);
            self->name = g_value_dup_string(value);
            break;
        case PROP_AGE:
            self->age = g_value_get_int(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void my_property_object_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
    MyPropertyObject* self = MY_PROPERTY_OBJECT(object);

    switch (property_id)
    {
        case PROP_NAME:
            g_value_set_string(value, self->name);
            break;
        case PROP_AGE:
            g_value_set_int(value, self->age);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void my_property_object_finalize(GObject* object)
{
    MyPropertyObject* self = MY_PROPERTY_OBJECT(object);
    g_free(self->name);
    G_OBJECT_CLASS(my_property_object_parent_class)->finalize(object);
}

static void my_property_object_class_init(MyPropertyObjectClass* klass)
{
    GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

    gobject_class->set_property = my_property_object_set_property;
    gobject_class->get_property = my_property_object_get_property;
    gobject_class->finalize = my_property_object_finalize;

    // 安装属性
    obj_properties[PROP_NAME] = g_param_spec_string(
        "name",
        "Name",
        "The name of the person",
        NULL,  // 默认值
        G_PARAM_READWRITE | G_PARAM_CONSTRUCT
    );

    obj_properties[PROP_AGE] = g_param_spec_int(
        "age",
        "Age",
        "The age of the person",
        0,    // 最小值
        150,  // 最大值
        0,    // 默认值
        G_PARAM_READWRITE | G_PARAM_CONSTRUCT
    );

    g_object_class_install_properties(gobject_class, N_PROPERTIES, obj_properties);
}

static void my_property_object_init(MyPropertyObject* self)
{
    self->name = NULL;
    self->age = 0;
}

void chapter6_gobject_properties_test()
{
    g_print("\n--- 第6章：GObject 属性 ---\n\n");

    // 6.1. 属性基本操作（官方文档：gobject-GObject-Properties.html）
    g_print("6.1 属性基本操作\n");

    // 创建对象并设置属性
    MyPropertyObject* person = g_object_new(
        MY_TYPE_PROPERTY_OBJECT,
        "name", "Alice",
        "age", 25,
        NULL
    );

    // 获取属性
    gchar* name;
    gint age;
    g_object_get(person,
                "name", &name,
                "age", &age,
                NULL);

    g_print("Name: %s\n", name);
    g_print("Age: %d\n", age);
    g_free(name);  // g_object_get 返回的字符串需要释放

    // 设置属性
    g_object_set(person,
                "name", "Bob",
                "age", 30,
                NULL);

    g_object_get(person, "name", &name, NULL);
    g_print("Updated name: %s\n", name);
    g_free(name);

    g_object_unref(person);
}

/**
 * 第7章：GObject 高级特性
 */
void chapter7_gobject_advanced_test()
{
    g_print("\n--- 第8章：GObject 高级特性 ---\n\n");

    // 8.1. 接口（官方文档：gobject-Interfaces.html）
    g_print("8.1 接口\n");
    g_print("G_TYPE_INTERFACE: %s\n", g_type_name(G_TYPE_INTERFACE));
    g_print("G_TYPE_INITIALLY_UNOWNED: %s\n", g_type_name(G_TYPE_INITIALLY_UNOWNED));

    // 8.2. 弱引用
    g_print("\n8.2 弱引用\n");
    GObject* obj = g_object_new(G_TYPE_OBJECT, NULL);
    gpointer weak_data = GINT_TO_POINTER(123);

    g_object_weak_ref(obj, (GWeakNotify)g_print, "对象被销毁了！\n");
    g_object_unref(obj);  // 触发弱引用回调
}

/**
 * 第8章：GObject 信号
 */
// 定义带信号的 GObject 类
#define MY_TYPE_SIGNAL_OBJECT (my_signal_object_get_type())
#define MY_SIGNAL_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_SIGNAL_OBJECT, MySignalObject))
#define MY_IS_SIGNAL_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_SIGNAL_OBJECT))

typedef struct _MySignalObject MySignalObject;
typedef struct _MySignalObjectClass MySignalObjectClass;

enum {
    CLICKED,
    VALUE_CHANGED,
    LAST_SIGNAL
};

struct _MySignalObject {
    GObject parent_instance;
    gint value;
};

struct _MySignalObjectClass {
    GObjectClass parent_class;
    void (*clicked)(MySignalObject* self);
    void (*value_changed)(MySignalObject* self, gint new_value);
};

static guint obj_signals[LAST_SIGNAL] = { 0, };

GType my_signal_object_get_type(void);

static void my_signal_object_class_init(MySignalObjectClass* klass)
{
    GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

    // 注册信号
    obj_signals[CLICKED] = g_signal_new(
        "clicked",
        G_TYPE_FROM_CLASS(klass),
        G_SIGNAL_RUN_FIRST,
        G_STRUCT_OFFSET(MySignalObjectClass, clicked),
        NULL, NULL,
        NULL,
        G_TYPE_NONE,
        0
    );

    obj_signals[VALUE_CHANGED] = g_signal_new(
        "value-changed",
        G_TYPE_FROM_CLASS(klass),
        G_SIGNAL_RUN_FIRST,
        G_STRUCT_OFFSET(MySignalObjectClass, value_changed),
        NULL, NULL,
        NULL,
        G_TYPE_NONE,
        1,
        G_TYPE_INT
    );
}

static void my_signal_object_init(MySignalObject* self)
{
    self->value = 0;
}

G_DEFINE_TYPE(MySignalObject, my_signal_object, G_TYPE_OBJECT)

// 公共方法
void my_signal_object_click(MySignalObject* self)
{
    g_return_if_fail(MY_IS_SIGNAL_OBJECT(self));
    g_signal_emit(self, obj_signals[CLICKED], 0);
}

void my_signal_object_set_value(MySignalObject* self, gint value){
    g_return_if_fail(MY_IS_SIGNAL_OBJECT(self));
    if (self->value != value)
    {
        self->value = value;
        g_signal_emit(self, obj_signals[VALUE_CHANGED], 0, value);
    }
}

// 信号处理函数
static void on_clicked(MySignalObject* self, gpointer user_data)
{
    g_print("信号处理: 按钮被点击了！\n");
}

static void on_value_changed(MySignalObject* self, gint new_value, gpointer user_data)
{
    g_print("信号处理: 值变为 %d\n", new_value);
}

void chapter8_gobject_signals_test()
{
    g_print("\n--- 第7章：GObject 信号 ---\n\n");

    // 7.1. 信号基本操作（官方文档：gobject-Signals.html）
    g_print("7.1 信号基本操作\n");

    MySignalObject* obj = g_object_new(MY_TYPE_SIGNAL_OBJECT, NULL);

    // 连接信号
    g_signal_connect(obj, "clicked", G_CALLBACK(on_clicked), NULL);
    g_signal_connect(obj, "value-changed", G_CALLBACK(on_value_changed), NULL);

    // 发射信号
    g_print("发射 clicked 信号:\n");
    my_signal_object_click(obj);

    g_print("\n发射 value-changed 信号:\n");
    my_signal_object_set_value(obj, 42);
    my_signal_object_set_value(obj, 100);

    g_object_unref(obj);
}

/**
 * 第9章：GIO 基础与文件操作
 */
// 方法1：自己写转换函数（推荐，输出更友好）
static const gchar* file_type_to_string(GFileType type)
{
    switch (type)
    {
        case G_FILE_TYPE_REGULAR:
            return "普通文件";
        case G_FILE_TYPE_DIRECTORY:
            return "目录";
        case G_FILE_TYPE_SYMBOLIC_LINK:
            return "符号链接";
        case G_FILE_TYPE_SPECIAL:
            return "特殊文件";
        case G_FILE_TYPE_SHORTCUT:
            return "快捷方式";
        case G_FILE_TYPE_MOUNTABLE:
            return "可挂载设备";
        default:
            return "未知类型";
    }
}

// 方法2：使用GLib通用枚举转字符串函数
// g_enum_to_string(G_TYPE_FILE_TYPE, g_file_info_get_file_type(info))

void chapter9_gio_file_operations_test()
{
    g_print("\n--- 第9章：GIO 基础与文件操作 ---\n\n");

    // 9.1. GFile 基本操作（官方文档：gio-GFile.html）
    g_print("9.1 GFile 基本操作\n");

    // 创建 GFile 对象
    GFile* file = g_file_new_for_path("test.txt");
    g_print("文件路径: %s\n", g_file_get_path(file));
    g_print("文件URI: %s\n", g_file_get_uri(file));

    // 写入文件
    GError* error = NULL;
    const gchar* content = "Hello, GIO!";
    if (!g_file_replace_contents(file, content, strlen(content), NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, &error))
    {
        g_print("写入文件失败: %s\n", error->message);
        g_error_free(error);
    }
    else
    {
        g_print("文件写入成功\n");
    }

    // 读取文件
    gchar* read_content;
    gsize length;
    if (g_file_load_contents(file, NULL, &read_content, &length, NULL, &error))
    {
        g_print("文件内容: %s\n", read_content);
        g_print("文件大小: %zu 字节\n", length);
        g_free(read_content);
    }
    else
    {
        g_print("读取文件失败: %s\n", error->message);
        g_error_free(error);
    }

    // 检查文件信息
    GFileInfo* info = g_file_query_info(file,
                                       G_FILE_ATTRIBUTE_STANDARD_SIZE ","
                                       G_FILE_ATTRIBUTE_STANDARD_TYPE,
                                       G_FILE_QUERY_INFO_NONE,
                                       NULL, &error);
    if (info)
    {
        g_print("文件大小: %" G_GUINT64_FORMAT " 字节\n",
                g_file_info_get_size(info));
        g_print("文件类型: %s\n",
                file_type_to_string(g_file_info_get_file_type(info)));
        g_object_unref(info);
    }
    else
    {
        g_print("查询文件信息失败: %s\n", error->message);
        g_error_free(error);
    }

    // 删除文件
    if (g_file_delete(file, NULL, &error))
    {
        g_print("文件删除成功\n");
    }
    else
    {
        g_print("删除文件失败: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(file);
}

/**
 * 第10章：GIO 主循环
 */
// 定时器回调函数
static gboolean on_timeout(gpointer user_data)
{
    static gint count = 0;
    g_print("定时器触发: %d\n", ++count);

    if (count >= 3)
    {
        g_print("定时器停止\n");
        return G_SOURCE_REMOVE;  // 返回FALSE停止定时器
    }

    return G_SOURCE_CONTINUE;  // 返回TRUE继续
}

// 空闲回调函数
static gboolean on_idle(gpointer user_data)
{
    g_print("空闲任务执行\n");
    return G_SOURCE_REMOVE;  // 只执行一次
}

void chapter10_gio_main_loop_test()
{
    g_print("\n--- 第10章：GIO 主循环 ---\n\n");

    // 10.1. 主循环基础（官方文档：gio-The-Main-Event-Loop.html）
    g_print("10.1 主循环基础\n");

    GMainLoop* loop = g_main_loop_new(NULL, FALSE);

    // 添加定时器（1秒触发一次）
    guint timeout_id = g_timeout_add(1000, on_timeout, NULL);
    g_print("添加定时器，ID: %u\n", timeout_id);

    // 添加空闲任务
    guint idle_id = g_idle_add(on_idle, NULL);
    g_print("添加空闲任务，ID: %u\n", idle_id);

    // 运行主循环
    g_print("运行主循环...\n");
    g_main_loop_run(loop);

    // 清理
    g_main_loop_unref(loop);
}

/**
 * 第11章：GIO 网络编程
 */
void chapter11_gio_networking_test()
{
    g_print("\n--- 第11章：GIO 网络编程 ---\n\n");

    // 11.1. 网络地址解析（官方文档：gio-GSocketAddress.html）
    g_print("11.1 网络地址解析\n");

    GError* error = NULL;
    GResolver* resolver = g_resolver_get_default();

    g_print("解析 www.baidu.com...\n");
    GList* addresses = g_resolver_lookup_by_name(resolver, "www.baidu.com", NULL, &error);

    if (addresses)
    {
        for (GList* l = addresses; l != NULL; l = l->next)
        {
            GInetAddress* addr = G_INET_ADDRESS(l->data);
            gchar* ip = g_inet_address_to_string(addr);
            g_print("IP地址: %s\n", ip);
            g_free(ip);
        }
        g_resolver_free_addresses(addresses);
    }
    else
    {
        g_print("解析失败: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(resolver);
}

/**
 * 第12章：GIO 高级特性
 */
void chapter12_gio_advanced_test()
{
    g_print("\n--- 第12章：GIO 高级特性 ---\n\n");

    // 12.1. 异步操作（官方文档：gio-Asynchronous-IO.html）
    g_print("12.1. 异步操作\n");
    g_print("GIO 支持异步文件操作、网络操作等\n");
    g_print("异步操作通过 GAsyncResult 和回调函数实现\n");

    // 12.2. 数据流（官方文档：gio-IO-Streams.html）
    g_print("\n12.2. 数据流\n");
    g_print("GInputStream 和 GOutputStream 是所有 I/O 流的基类\n");
    g_print("支持文件流、网络流、内存流等\n");
}

#if 0
#endif
int main()
{
    // 第1-4章：GLib 核心
    // chapter1_basic_types_and_macros_test();
    // chapter2_memory_management_test();
    // chapter3_glib_string_handling_test();
    // chapter4_data_structures_test();

    // 第5-8章：GObject 系统
    // chapter5_gobject_basics_test_1();
    // chapter5_gobject_basics_test_2();
    // chapter6_gobject_properties_test();
    // chapter6_gobject_properties_test();
    // chapter7_gobject_advanced_test();
    // chapter8_gobject_signals_test();

    // 第9-12章：GIO 库
    // chapter9_gio_file_operations_test();
    // chapter10_gio_main_loop_test();
    // chapter11_gio_networking_test();
    chapter12_gio_advanced_test();
    return 0;
}