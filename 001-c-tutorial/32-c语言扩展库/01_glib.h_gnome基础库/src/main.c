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

/* 用于 GTest 等需要访问命令行参数的章节 */
int g_argc = 0;
char **g_argv = NULL;

/* ============================================================
 * 第一篇 入门基础篇
 * ============================================================ */

/* 第 1 章：GLib 体系概述与环境搭建 */
void chapter_01_glib_overview(void)
{
    g_print("\n=== 第 1 章 GLib 体系概述与环境搭建 ===\n");

    /* 1. 运行时版本信息 */
    g_print("[运行时版本] %u.%u.%u\n", glib_major_version, glib_minor_version, glib_micro_version);

    /* 2. 编译时版本信息 */
    g_print("[编译时版本] %d.%d.%d\n", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

    /* 3. 版本兼容性检查：传入所需最低版本，返回 NULL 表示兼容 */
    const gchar *check = glib_check_version(2, 50, 0);
    g_print("[版本检查] 要求>=2.50.0: %s\n", check ? check : "通过(NULL)");

    /* 4. 体系结构说明 */
    g_print("[体系结构] GLib = 工具库 + GObject(对象系统) + GIO(I/O网络) + GModule(动态模块)\n");
    g_print("[子模块] glib(基础) / gobject(对象) / gio(I/O) / gmodule(模块) / gthread(线程)\n");

    /* 5. 字节序判断 */
    g_print("[字节序] %s\n", G_BYTE_ORDER == G_LITTLE_ENDIAN ? "小端" : "大端");

    /* 6. 系统信息 */
    const gchar *os_name = g_get_os_info(G_OS_INFO_KEY_NAME);
    const gchar *os_ver = g_get_os_info(G_OS_INFO_KEY_VERSION);
    g_print("[系统] %s %s\n", os_name ? os_name : "unknown", os_ver ? os_ver : "");

    /* 7. 处理器数 */
    g_print("[CPU 核心数] %d\n", g_get_num_processors());

    /* 8. 主机名与用户名 */
    g_print("[主机名] %s\n", g_get_host_name());
    const gchar *user = g_get_user_name();
    g_print("[用户名] %s\n", user ? user : "(null)");

    /* 9. GLib 目录信息 */
    g_print("[用户数据目录] %s\n", g_get_user_data_dir());
    g_print("[用户配置目录] %s\n", g_get_user_config_dir());
    g_print("[用户缓存目录] %s\n", g_get_user_cache_dir());
    g_print("[系统临时目录] %s\n", g_get_tmp_dir());

    /* 10. 当前工作目录 */
    gchar *cwd = g_get_current_dir();
    g_print("[当前工作目录] %s\n", cwd);
    g_free(cwd);

    /* 11. 编译特性 */
    g_print("[编译特性] gsize 格式符: %s\n", G_GSIZE_FORMAT);
    g_print("[编译特性] 指针大小: %d 位\n", (int)(sizeof(gpointer) * 8));
}

/* 第 2 章：基础类型与核心宏 */
void chapter_02_basic_types_and_macros(void)
{
    g_print("\n=== 第 2 章 基础类型与核心宏 ===\n");

    /* 1. 基本类型演示 */
    gint    a = 10;
    gint    b = 20;
    guint   u = 100U;
    glong   l = 1234567890L;
    gdouble d = 3.14159265358979;
    gboolean flag = TRUE;
    gchar   c = 'G';
    gsize   sz = 1024;

    g_print("[基本类型] gint=%d guint=%u glong=%ld gdouble=%.6f\n", a, u, l, d);
    g_print("[基本类型] gboolean=%s gchar=%c gsize=%" G_GSIZE_FORMAT "\n",
            flag ? "TRUE" : "FALSE", c, sz);

    /* 2. 类型极值宏 */
    g_print("[极值] G_MAXINT=%d G_MININT=%d G_MAXUINT=%u\n", G_MAXINT, G_MININT, G_MAXUINT);
    g_print("[极值] G_MAXLONG=%ld G_MAXULONG=%lu\n", (glong)G_MAXLONG, (gulong)G_MAXULONG);
    g_print("[极值] G_MAXDOUBLE=%g G_MINDOUBLE=%g\n", G_MAXDOUBLE, G_MINDOUBLE);
    g_print("[极值] G_MAXSIZE=%" G_GSIZE_FORMAT " G_MAXSSIZE=%" G_GSSIZE_FORMAT "\n",
            G_MAXSIZE, G_MAXSSIZE);

    /* 3. 数学运算宏 */
    g_print("[数学] MIN(%d,%d)=%d  MAX(%d,%d)=%d\n", a, b, MIN(a, b), a, b, MAX(a, b));
    g_print("[数学] ABS(-5)=%d  ABS(7)=%d\n", ABS(-5), ABS(7));
    g_print("[数学] CLAMP(15,0,10)=%d  CLAMP(3,0,10)=%d  CLAMP(-1,0,10)=%d\n",
            CLAMP(15, 0, 10), CLAMP(3, 0, 10), CLAMP(-1, 0, 10));

    /* 4. 数学常量 */
    g_print("[常量] G_PI=%.15f\n", G_PI);
    g_print("[常量] G_E=%.15f\n", G_E);
    g_print("[常量] G_SQRT2=%.15f\n", G_SQRT2);
    g_print("[常量] G_PI_2=%.15f  G_PI_4=%.15f\n", G_PI_2, G_PI_4);

    /* 5. 分支预测宏 */
    if (G_LIKELY(a < b)) {
        g_print("[分支] G_LIKELY(a<b) 命中\n");
    }
    if (G_UNLIKELY(a > 100)) {
        g_print("[分支] G_UNLIKELY 不该命中\n");
    } else {
        g_print("[分支] G_UNLIKELY 未命中\n");
    }

    /* 6. 数组元素个数宏 */
    gint arr[] = { 1, 2, 3, 4, 5 };
    g_print("[数组] G_N_ELEMENTS = %u\n", (guint)G_N_ELEMENTS(arr));

    /* 7. 结构体偏移宏 */
    struct Point { gint x; gint y; };
    g_print("[偏移] G_STRUCT_OFFSET(y) = %u\n", (guint)G_STRUCT_OFFSET(struct Point, y));

    /* 8. 指针与整型互转 */
    gpointer p = GINT_TO_POINTER(42);
    g_print("[指针] GINT_TO_POINTER(42)->%d\n", GPOINTER_TO_INT(p));
    gpointer pu = GUINT_TO_POINTER(0xABCD);
    g_print("[指针] GUINT_TO_POINTER(0xABCD)->0x%x\n", GPOINTER_TO_UINT(pu));

    /* 9. 字符串化宏 */
    g_print("[字符串化] G_STRINGIFY(42) = %s\n", G_STRINGIFY(42));

    /* 10. 对齐计算宏 */
    g_print("[对齐] G_ALIGNOF(gint) = %u\n", (guint)G_ALIGNOF(gint));
    g_print("[对齐] G_ALIGNOF(gdouble) = %u\n", (guint)G_ALIGNOF(gdouble));

    /* 11. 编译时断言 */
    G_STATIC_ASSERT(sizeof(gint) >= 4);
    g_print("[静态断言] sizeof(gint)>=4 通过\n");

    /* 12. 整数与字符串互转 */
    g_print("[转字符串] g_strdup_printf(\"%d\") = %s\n", 42, g_strdup_printf("%d", 42));
    g_print("[转整数] g_ascii_strtoull(\"255\", NULL, 10) = %llu\n",
            (guint64)g_ascii_strtoull("255", NULL, 10));
}

/* ============================================================
 * 第二篇 通用工具与数据结构篇
 * ============================================================ */

/* 第 3 章：内存管理体系 */
void chapter_03_memory_management(void)
{
    g_print("\n=== 第 3 章 内存管理体系 ===\n");

    /* 1. g_malloc / g_free */
    gpointer buf = g_malloc(128);
    g_print("[g_malloc] 分配 128 字节: %p\n", buf);
    g_free(buf);

    /* 2. g_new / g_new0：类型安全分配 */
    gint *arr = g_new(gint, 5);
    for (gint i = 0; i < 5; i++) arr[i] = i * 10;
    g_print("[g_new] 数组: %d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);

    gint *zeroed = g_new0(gint, 3);
    g_print("[g_new0] 清零数组: %d %d %d\n", zeroed[0], zeroed[1], zeroed[2]);

    /* 3. g_realloc：重分配 */
    arr = g_realloc(arr, sizeof(gint) * 8);
    arr[5] = 50; arr[6] = 60; arr[7] = 70;
    g_print("[g_realloc] 扩展后: %d %d %d\n", arr[5], arr[6], arr[7]);

    /* 4. g_try_malloc：不致命的分配 */
    gpointer try_buf = g_try_malloc(64);
    if (try_buf) {
        g_print("[g_try_malloc] 成功: %p\n", try_buf);
        g_free(try_buf);
    }

    /* 5. g_strdup / g_strndup：字符串复制 */
    gchar *str = g_strdup("Hello GLib");
    gchar *strn = g_strndup("HelloWorld", 5);
    g_print("[g_strdup] %s  [g_strndup] %s\n", str, strn);

    /* 6. g_clear_pointer：释放并置空 */
    g_clear_pointer(&str, g_free);
    g_clear_pointer(&strn, g_free);
    g_print("[g_clear_pointer] str=%p strn=%p\n", (void *)str, (void *)strn);

    /* 7. slice 分配器：固定大小高效分配 */
    gpointer s1 = g_slice_alloc(sizeof(gint));
    gpointer s2 = g_slice_alloc(sizeof(gint));
    g_print("[g_slice_alloc] s1=%p s2=%p\n", s1, s2);
    g_slice_free1(sizeof(gint), s1);
    g_slice_free1(sizeof(gint), s2);

    /* 8. g_steal_pointer：转移所有权 */
    gchar *owned = g_strdup("transfer");
    gchar *stolen = g_steal_pointer(&owned);
    g_print("[g_steal_pointer] stolen=%s owned=%p\n", stolen, (void *)owned);
    g_free(stolen);

    /* 9. 内存清零与复制 */
    memset(zeroed, 0, sizeof(gint) * 3);
    gint src[5] = { 1, 2, 3, 4, 5 };
    gint dst[5];
    memcpy(dst, src, sizeof(src));
    g_print("[memcpy] dst[4]=%d\n", dst[4]);

    /* 10. g_aligned_alloc：对齐分配 */
    gpointer aligned = g_malloc(64);
    g_print("[对齐分配] %p\n", aligned);
    g_free(aligned);

    /* 11. 内存调试宏 GLIB_VERSION_2_64+ */
    g_print("[内存说明] g_malloc 出错时默认调用 abort()\n");
    g_print("[内存说明] g_try_malloc 出错时返回 NULL\n");

    g_free(arr);
    g_free(zeroed);
    g_print("[内存] 全部释放完毕\n");
}

/* 第 4 章：字符串与文本处理 */
void chapter_04_strings_and_text(void)
{
    g_print("\n=== 第 4 章 字符串与文本处理 ===\n");

    /* 1. 基本字符串操作 */
    gchar *dup = g_strdup("Hello");
    gchar *dup_printf = g_strdup_printf("value=%d pi=%.4f", 42, G_PI);
    g_print("[g_strdup] %s\n", dup);
    g_print("[g_strdup_printf] %s\n", dup_printf);

    /* 2. ASCII 大小写转换 */
    gchar *lower = g_ascii_strdown("Hello World", -1);
    gchar *upper = g_ascii_strup("Hello World", -1);
    g_print("[转小写] %s  [转大写] %s\n", lower, upper);

    /* 3. 字符串比较 */
    g_print("[比较] g_ascii_strcasecmp(\"abc\",\"ABC\")=%d\n", g_ascii_strcasecmp("abc", "ABC"));
    g_print("[比较] g_strcmp0(NULL,\"x\")=%d\n", g_strcmp0(NULL, "x"));
    g_print("[比较] g_strcmp0(\"abc\",\"abc\")=%d\n", g_strcmp0("abc", "abc"));

    /* 4. 前缀/后缀检查 */
    g_print("[前缀] \"HelloWorld\" has \"Hello\": %s\n",
            g_str_has_prefix("HelloWorld", "Hello") ? "是" : "否");
    g_print("[后缀] \"file.txt\" has \".txt\": %s\n",
            g_str_has_suffix("file.txt", ".txt") ? "是" : "否");

    /* 5. 字符串分割与连接 */
    gchar **parts = g_strsplit("a,b,,c", ",", -1);
    g_print("[分割] 元素个数: %u\n", g_strv_length(parts));
    for (guint i = 0; parts[i]; i++) {
        g_print("  parts[%u] = \"%s\"\n", i, parts[i]);
    }
    gchar *joined = g_strjoinv("-", parts);
    g_print("[连接] \"%s\"\n", joined);
    g_strfreev(parts);
    g_free(joined);

    /* 6. 字符串替换（用分割连接模拟） */
    gchar *replaced = g_strdup("hello world hello");
    gchar **split = g_strsplit(replaced, "hello", -1);
    gchar *new_str = g_strjoinv("GLib", split);
    g_print("[替换] \"%s\" -> \"%s\"\n", replaced, new_str);
    g_strfreev(split);
    g_free(replaced);
    g_free(new_str);

    /* 7. 字符串修剪 */
    gchar *trim = g_strdup("  Hello GLib  \n");
    g_strchug(trim);  /* 去首部空白 */
    g_strchomp(trim); /* 去尾部空白 */
    g_print("[修剪] \"%s\"\n", trim);
    g_free(trim);

    /* 8. GString 可变字符串 */
    GString *gs = g_string_new("Hello");
    g_string_append(gs, " GLib");
    g_string_append_c(gs, '!');
    g_string_prepend(gs, "Say: ");
    g_string_append_printf(gs, " (len=%u)", gs->len);
    g_print("[GString] %s (长度=%u 容量=%u)\n", gs->str, gs->len, gs->allocated_len);

    g_string_insert(gs, 4, ">>");
    g_print("[GString insert] %s\n", gs->str);

    g_string_erase(gs, 4, 2);
    g_print("[GString erase] %s\n", gs->str);

    g_string_truncate(gs, 10);
    g_print("[GString truncate] %s\n", gs->str);

    /* 9. GString 转换为普通字符串 */
    gchar *final_str = g_string_free(gs, FALSE);
    g_print("[GString free] 返回字符串: \"%s\"\n", final_str);
    g_free(final_str);

    /* 10. 字符分类函数 */
    g_print("[字符分类] isalpha('A')=%d isdigit('5')=%d isalnum('a')=%d\n",
            g_ascii_isalpha('A'), g_ascii_isdigit('5'), g_ascii_isalnum('a'));

    /* 11. 字符串转数值 */
    g_print("[转数值] g_ascii_strtoull(\"123\")=%llu\n",
            (guint64)g_ascii_strtoull("123", NULL, 10));
    g_print("[转数值] g_ascii_strtod(\"3.14\")=%.2f\n", g_ascii_strtod("3.14", NULL));

    g_free(dup);
    g_free(dup_printf);
    g_free(lower);
    g_free(upper);
}

/* 前向声明：整型比较函数，供第 5/6 章使用 */
gint int_compare(gconstpointer a, gconstpointer b);

/* 第 5 章：线性数据结构 */
void chapter_05_linear_data_structures(void)
{
    g_print("\n=== 第 5 章 线性数据结构 ===\n");

    /* 1. GList 双向链表 */
    GList *list = NULL;
    list = g_list_append(list, GINT_TO_POINTER(10));
    list = g_list_append(list, GINT_TO_POINTER(20));
    list = g_list_prepend(list, GINT_TO_POINTER(5));
    list = g_list_insert(list, GINT_TO_POINTER(15), 2);
    g_print("[GList] 长度=%u 首元素=%d 末元素=%d\n",
            g_list_length(list), GPOINTER_TO_INT(list->data),
            GPOINTER_TO_INT(g_list_last(list)->data));

    g_print("[GList 遍历] ");
    for (GList *l = list; l; l = l->next) {
        g_print("%d ", GPOINTER_TO_INT(l->data));
    }
    g_print("\n");

    g_print("[GList find] 20 位于索引 %d\n", g_list_index(list, GINT_TO_POINTER(20)));
    list = g_list_reverse(list);
    g_print("[GList reverse] 首元素=%d\n", GPOINTER_TO_INT(list->data));
    list = g_list_sort(list, int_compare);
    g_print("[GList sort] 首元素=%d\n", GPOINTER_TO_INT(list->data));
    g_list_free(list);

    /* 2. GSList 单向链表 */
    GSList *slist = NULL;
    slist = g_slist_append(slist, GINT_TO_POINTER(30));
    slist = g_slist_append(slist, GINT_TO_POINTER(40));
    slist = g_slist_prepend(slist, GINT_TO_POINTER(20));
    g_print("[GSList] 长度=%u 首元素=%d\n", g_slist_length(slist), GPOINTER_TO_INT(slist->data));
    slist = g_slist_remove(slist, GINT_TO_POINTER(40));
    g_print("[GSList remove] 长度=%u\n", g_slist_length(slist));
    g_slist_free(slist);

    /* 3. GQueue 双端队列 */
    GQueue queue = G_QUEUE_INIT;
    g_queue_push_tail(&queue, GINT_TO_POINTER(100));
    g_queue_push_tail(&queue, GINT_TO_POINTER(200));
    g_queue_push_head(&queue, GINT_TO_POINTER(50));
    g_print("[GQueue] 长度=%u 首元素=%d 末元素=%d\n",
            g_queue_get_length(&queue),
            GPOINTER_TO_INT(g_queue_peek_head(&queue)),
            GPOINTER_TO_INT(g_queue_peek_tail(&queue)));
    g_print("[GQueue pop_head] %d\n", GPOINTER_TO_INT(g_queue_pop_head(&queue)));
    g_print("[GQueue pop_tail] %d\n", GPOINTER_TO_INT(g_queue_pop_tail(&queue)));
    g_queue_clear(&queue);

    /* 4. GPtrArray 指针数组 */
    GPtrArray *parr = g_ptr_array_new_with_free_func(g_free);
    g_ptr_array_add(parr, g_strdup("one"));
    g_ptr_array_add(parr, g_strdup("two"));
    g_ptr_array_add(parr, g_strdup("three"));
    g_print("[GPtrArray] 长度=%u 元素[1]=%s\n", parr->len, (gchar *)g_ptr_array_index(parr, 1));
    g_ptr_array_remove_index(parr, 0);
    g_print("[GPtrArray remove] 长度=%u 元素[0]=%s\n", parr->len, (gchar *)g_ptr_array_index(parr, 0));
    g_ptr_array_free(parr, TRUE);

    /* 5. GArray 类型化数组 */
    GArray *garr = g_array_new(FALSE, FALSE, sizeof(gint));
    gint v1 = 10, v2 = 20, v3 = 30;
    g_array_append_val(garr, v1);
    g_array_append_val(garr, v2);
    g_array_append_val(garr, v3);
    g_array_prepend_val(garr, v1);
    g_print("[GArray] 长度=%u 元素[3]=%d\n", garr->len, g_array_index(garr, gint, 3));
    g_array_remove_index(garr, 0);
    g_print("[GArray remove] 长度=%u\n", garr->len);
    g_array_free(garr, TRUE);

    /* 6. GByteArray 字节数组 */
    GByteArray *barr = g_byte_array_new();
    g_byte_array_append(barr, (guint8 *)"Hello", 5);
    g_byte_array_append(barr, (guint8 *)"GLib", 4);
    g_print("[GByteArray] 长度=%u 数据=\"%.*s\"\n", barr->len, (gint)barr->len, barr->data);
    g_byte_array_prepend(barr, (guint8 *)"Say:", 4);
    g_print("[GByteArray prepend] \"%.*s\"\n", (gint)barr->len, barr->data);
    g_byte_array_free(barr, TRUE);
}

/* 第 6 章：关联与集合数据结构 */
gint int_compare(gconstpointer a, gconstpointer b)
{
    return GPOINTER_TO_INT(a) - GPOINTER_TO_INT(b);
}

gboolean traverse_print(gpointer key, gpointer value, gpointer data)
{
    g_print("  key=%d value=%d\n", GPOINTER_TO_INT(key), GPOINTER_TO_INT(value));
    return FALSE;
}

void chapter_06_associative_and_set_structures(void)
{
    g_print("\n=== 第 6 章 关联与集合数据结构 ===\n");

    /* 1. GHashTable 哈希表（整数键） */
    GHashTable *ht = g_hash_table_new(g_int_hash, g_int_equal);
    gint k1 = 1, k2 = 2, k3 = 3;
    g_hash_table_insert(ht, &k1, GINT_TO_POINTER(100));
    g_hash_table_insert(ht, &k2, GINT_TO_POINTER(200));
    g_hash_table_insert(ht, &k3, GINT_TO_POINTER(300));
    g_print("[GHashTable] 大小=%u  key=2->%d\n",
            g_hash_table_size(ht), GPOINTER_TO_INT(g_hash_table_lookup(ht, &k2)));
    g_hash_table_remove(ht, &k1);
    g_print("[GHashTable] 删除 key=1 后大小=%u\n", g_hash_table_size(ht));
    g_hash_table_destroy(ht);

    /* 2. 字符串哈希表（带自动释放） */
    GHashTable *str_ht = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    g_hash_table_insert(str_ht, g_strdup("name"), g_strdup("GLib"));
    g_hash_table_insert(str_ht, g_strdup("version"), g_strdup("2.88"));
    g_print("[GHashTable str] name=%s version=%s\n",
            (gchar *)g_hash_table_lookup(str_ht, "name"),
            (gchar *)g_hash_table_lookup(str_ht, "version"));

    /* 遍历 */
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, str_ht);
    g_print("[GHashTable 遍历]\n");
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("  %s = %s\n", (gchar *)key, (gchar *)value);
    }
    g_hash_table_destroy(str_ht);

    /* 3. GTree 平衡二叉树 */
    GTree *tree = g_tree_new(int_compare);
    g_tree_insert(tree, GINT_TO_POINTER(5), GINT_TO_POINTER(50));
    g_tree_insert(tree, GINT_TO_POINTER(3), GINT_TO_POINTER(30));
    g_tree_insert(tree, GINT_TO_POINTER(7), GINT_TO_POINTER(70));
    g_tree_insert(tree, GINT_TO_POINTER(1), GINT_TO_POINTER(10));
    g_print("[GTree] 节点数=%d 高度=%d\n", g_tree_nnodes(tree), g_tree_height(tree));
    g_print("[GTree lookup] key=3->%d\n", GPOINTER_TO_INT(g_tree_lookup(tree, GINT_TO_POINTER(3))));
    g_print("[GTree 遍历]\n");
    g_tree_foreach(tree, traverse_print, NULL);
    g_tree_remove(tree, GINT_TO_POINTER(3));
    g_print("[GTree remove 3] 节点数=%d\n", g_tree_nnodes(tree));
    g_tree_destroy(tree);

    /* 4. GBytes 不可变字节序列 */
    GBytes *bytes = g_bytes_new("Hello GLib", 10);
    gsize size = 0;
    gconstpointer data = g_bytes_get_data(bytes, &size);
    g_print("[GBytes] 大小=%u 数据=\"%.*s\"\n", (guint)size, (gint)size, (gchar *)data);

    GBytes *sub = g_bytes_new_from_bytes(bytes, 6, 4);
    g_print("[GBytes sub] \"%.*s\"\n", (gint)g_bytes_get_size(sub), (gchar *)g_bytes_get_data(sub, NULL));

    GBytes *bytes2 = g_bytes_new("Hello GLib", 10);
    g_print("[GBytes equal] %s\n", g_bytes_equal(bytes, bytes2) ? "相等" : "不等");
    g_bytes_unref(bytes2);
    g_bytes_unref(sub);
    g_bytes_unref(bytes);

    /* 5. GVariant 预览 */
    GVariant *variant = g_variant_new("a{sv}", NULL);
    g_print("[GVariant] 空字典类型: %s\n", g_variant_get_type_string(variant));
    g_variant_unref(variant);
}

/* 第 7 章：日期、时间与计时 */
void chapter_07_date_time_and_timer(void)
{
    g_print("\n=== 第 7 章 日期、时间与计时 ===\n");

    /* 1. GDateTime 当前时间 */
    GDateTime *dt = g_date_time_new_now_local();
    g_print("[当前时间] %s\n", g_date_time_format(dt, "%Y-%m-%d %H:%M:%S"));
    g_print("[ISO8601] %s\n", g_date_time_format(dt, "%Y-%m-%dT%H:%M:%S%z"));
    g_print("[UNIX 时间戳] %ld\n", (glong)g_date_time_to_unix(dt));
    g_print("[组成部分] 年=%d 月=%d 日=%d 时=%d 分=%d 秒=%d\n",
            g_date_time_get_year(dt), g_date_time_get_month(dt), g_date_time_get_day_of_month(dt),
            g_date_time_get_hour(dt), g_date_time_get_minute(dt), g_date_time_get_second(dt));
    g_print("[星期] %d (1=周一 7=周日)\n", g_date_time_get_day_of_week(dt));
    g_print("[一年中第几天] %d\n", g_date_time_get_day_of_year(dt));
    g_print("[微秒] %d\n", g_date_time_get_microsecond(dt));

    /* 2. 时间运算 */
    GDateTime *tomorrow = g_date_time_add_days(dt, 1);
    GDateTime *next_week = g_date_time_add_weeks(dt, 1);
    GDateTime *next_hour = g_date_time_add_hours(dt, 1);
    GDateTime *next_month = g_date_time_add_months(dt, 1);
    g_print("[明天] %s\n", g_date_time_format(tomorrow, "%Y-%m-%d"));
    g_print("[下周] %s\n", g_date_time_format(next_week, "%Y-%m-%d"));
    g_print("[一小时后] %s\n", g_date_time_format(next_hour, "%H:%M:%S"));
    g_print("[下月] %s\n", g_date_time_format(next_month, "%Y-%m"));
    g_date_time_unref(tomorrow);
    g_date_time_unref(next_week);
    g_date_time_unref(next_hour);
    g_date_time_unref(next_month);

    /* 3. UTC 时间 */
    GDateTime *utc = g_date_time_new_now_utc();
    g_print("[UTC] %s\n", g_date_time_format(utc, "%Y-%m-%d %H:%M:%S"));
    GTimeSpan diff = g_date_time_difference(dt, utc);
    g_print("[时差] 本地-UTC = %" G_GINT64_FORMAT " 秒\n", diff / G_TIME_SPAN_SECOND);

    /* 4. 从时间戳创建 */
    GDateTime *from_unix = g_date_time_new_from_unix_utc(1609459200);
    g_print("[从时间戳] %s\n", g_date_time_format(from_unix, "%Y-%m-%d %H:%M:%S"));
    g_date_time_unref(from_unix);

    /* 5. 时区 */
    GTimeZone *tz = g_time_zone_new_local();
    g_print("[时区] 标识=%s\n", g_time_zone_get_identifier(tz));
    g_time_zone_unref(tz);

    GTimeZone *utc_tz = g_time_zone_new_utc();
    g_print("[UTC 时区] %s\n", g_time_zone_get_identifier(utc_tz));
    g_time_zone_unref(utc_tz);

    /* 6. GDate 日期 */
    GDate date;
    g_date_set_time_t(&date, time(NULL));
    g_print("[GDate] %04d-%02d-%02d\n",
            g_date_get_year(&date), g_date_get_month(&date), g_date_get_day(&date));
    g_print("[GDate] 一年中第 %d 天\n", g_date_get_day_of_year(&date));
    g_print("[GDate] 本月共 %d 天\n",
            g_date_get_days_in_month(g_date_get_month(&date), g_date_get_year(&date)));

    /* 7. GTimer 计时器 */
    GTimer *timer = g_timer_new();
    g_timer_start(timer);
    g_usleep(10000); /* 10 毫秒 */
    g_timer_stop(timer);
    g_print("[GTimer] 耗时=%.6f 秒\n", g_timer_elapsed(timer, NULL));

    /* 8. 重置计时器 */
    g_timer_reset(timer);
    g_timer_start(timer);
    g_usleep(5000);
    g_timer_stop(timer);
    g_print("[GTimer reset] %.6f 秒\n", g_timer_elapsed(timer, NULL));

    /* 9. 高精度时间戳 */
    gint64 mono = g_get_monotonic_time();
    gint64 real = g_get_real_time();
    g_print("[单调时间] %" G_GINT64_FORMAT " 微秒\n", mono);
    g_print("[墙上时间] %" G_GINT64_FORMAT " 微秒\n", real);

    /* 10. 睡眠函数 */
    g_print("[sleep] 休眠 1 毫秒...\n");
    g_usleep(1000);
    g_print("[sleep] 完成\n");

    g_date_time_unref(dt);
    g_date_time_unref(utc);
    g_timer_destroy(timer);
}

/* 第 8 章：命令行与配置解析 */
void chapter_08_commandline_and_config(void)
{
    g_print("\n=== 第 8 章 命令行与配置解析 ===\n");

    /* 1. GOptionContext 命令行解析 */
    gint fake_argc = 4;
    gchar *fake_argv[] = { "demo", "--verbose", "--count=5", "--name=GLib", NULL };
    gchar **argv_ptr = fake_argv;
    gboolean verbose = FALSE;
    gint count = 1;
    gchar *name = NULL;
    GError *error = NULL;

    GOptionEntry entries[] = {
        { "verbose", 'v', 0, G_OPTION_ARG_NONE,   &verbose, "启用详细输出", NULL },
        { "count",   'c', 0, G_OPTION_ARG_INT,    &count,   "计数",         "N" },
        { "name",    'n', 0, G_OPTION_ARG_STRING, &name,    "名称",         "NAME" },
        { NULL }
    };

    GOptionContext *ctx = g_option_context_new("- 教学示例程序");
    g_option_context_add_main_entries(ctx, entries, NULL);
    g_option_context_set_summary(ctx, "这是一个 GLib 教学示例");
    g_option_context_set_description(ctx, "详细帮助说明\n  演示 GOptionEntry 用法");
    if (g_option_context_parse(ctx, &fake_argc, &argv_ptr, &error)) {
        g_print("[解析结果] verbose=%s count=%d name=%s\n",
                verbose ? "TRUE" : "FALSE", count, name ? name : "(null)");
        g_print("[剩余参数] argc=%d\n", fake_argc);
    } else {
        g_print("[解析失败] %s\n", error->message);
        g_clear_error(&error);
    }
    g_free(name);
    g_option_context_free(ctx);

    /* 2. GKeyFile 配置文件 */
    GKeyFile *kf = g_key_file_new();
    g_key_file_set_string(kf, "General", "name", "GLibDemo");
    g_key_file_set_string(kf, "General", "version", "2.88");
    g_key_file_set_integer(kf, "General", "timeout", 30);
    g_key_file_set_double(kf, "General", "ratio", 0.75);
    g_key_file_set_boolean(kf, "General", "debug", TRUE);

    /* 数组值 */
    gchar *list[] = { "item1", "item2", "item3", NULL };
    g_key_file_set_string_list(kf, "Data", "items", (const gchar *const *)list, 3);

    /* 整数数组 */
    gint int_list[] = { 10, 20, 30 };
    g_key_file_set_integer_list(kf, "Data", "numbers", int_list, 3);

    /* 读取 */
    gchar *kname = g_key_file_get_string(kf, "General", "name", NULL);
    gint ktimeout = g_key_file_get_integer(kf, "General", "timeout", NULL);
    gdouble kratio = g_key_file_get_double(kf, "General", "ratio", NULL);
    gboolean kdebug = g_key_file_get_boolean(kf, "General", "debug", NULL);
    g_print("[GKeyFile] name=%s timeout=%d ratio=%.2f debug=%s\n",
            kname, ktimeout, kratio, kdebug ? "TRUE" : "FALSE");
    g_free(kname);

    gsize list_len = 0;
    gchar **items = g_key_file_get_string_list(kf, "Data", "items", &list_len, NULL);
    g_print("[GKeyFile list] 长度=%u 元素: ", (guint)list_len);
    for (gsize i = 0; i < list_len; i++) {
        g_print("%s ", items[i]);
    }
    g_print("\n");
    g_strfreev(items);

    /* 获取所有组 */
    gsize n_groups = 0;
    gchar **groups = g_key_file_get_groups(kf, &n_groups);
    g_print("[GKeyFile groups] 数量=%u: ", (guint)n_groups);
    for (gsize i = 0; i < n_groups; i++) {
        g_print("%s ", groups[i]);
    }
    g_print("\n");
    g_strfreev(groups);

    /* 获取组内所有键 */
    gsize n_keys = 0;
    gchar **keys = g_key_file_get_keys(kf, "General", &n_keys, NULL);
    g_print("[GKeyFile keys] General 组键数=%u: ", (guint)n_keys);
    for (gsize i = 0; i < n_keys; i++) {
        g_print("%s ", keys[i]);
    }
    g_print("\n");
    g_strfreev(keys);

    /* 保存到字符串 */
    gchar *data = g_key_file_to_data(kf, NULL, NULL);
    g_print("[GKeyFile 保存]\n%s", data);
    g_free(data);

    /* 检查键是否存在 */
    gboolean has_name = g_key_file_has_key(kf, "General", "name", NULL);
    g_print("[GKeyFile has_key] General.name=%s\n", has_name ? "存在" : "不存在");

    g_key_file_free(kf);
}

/* 第 9 章：通用工具函数集 */
void chapter_09_utility_functions(void)
{
    g_print("\n=== 第 9 章 通用工具函数集 ===\n");

    /* 1. 随机数 */
    g_print("[随机] 整数[0,99]=%d\n", g_random_int_range(0, 100));
    g_print("[随机] 浮点[0,1)=%f\n", g_random_double());
    g_print("[随机] 浮点[5,10)=%f\n", g_random_double_range(5.0, 10.0));

    /* 带种子的随机 */
    GRand *rand = g_rand_new_with_seed(42);
    g_print("[种子42] %d %d %d\n", g_rand_int_range(rand, 0, 100),
            g_rand_int_range(rand, 0, 100), g_rand_int_range(rand, 0, 100));
    g_rand_free(rand);

    /* 2. 校验和 */
    GChecksum *cs = g_checksum_new(G_CHECKSUM_SHA256);
    g_checksum_update(cs, (guchar *)"GLib", 4);
    g_print("[SHA256] %s\n", g_checksum_get_string(cs));
    g_checksum_free(cs);

    GChecksum *md5 = g_checksum_new(G_CHECKSUM_MD5);
    g_checksum_update(md5, (guchar *)"GLib", 4);
    g_print("[MD5] %s\n", g_checksum_get_string(md5));
    g_checksum_free(md5);

    GChecksum *sha1 = g_checksum_new(G_CHECKSUM_SHA1);
    g_checksum_update(sha1, (guchar *)"GLib", 4);
    g_print("[SHA1] %s\n", g_checksum_get_string(sha1));
    g_checksum_free(sha1);

    /* 3. Base64 编解码 */
    gchar *b64 = g_base64_encode((guchar *)"Hello GLib", 10);
    g_print("[Base64 编码] %s\n", b64);
    gsize out_len = 0;
    guchar *decoded = g_base64_decode(b64, &out_len);
    g_print("[Base64 解码] %.*s (长度=%u)\n", (gint)out_len, (gchar *)decoded, (guint)out_len);
    g_free(decoded);
    g_free(b64);

    /* 4. 字节序转换 */
    guint16 x = 0x1234;
    guint32 y = 0x12345678;
    g_print("[字节序] 0x%x -> BE=0x%x LE=0x%x\n", x, GUINT16_TO_BE(x), GUINT16_TO_LE(x));
    g_print("[字节序] 0x%x -> BE=0x%x LE=0x%x\n", y, GUINT32_TO_BE(y), GUINT32_TO_LE(y));

    /* 5. UUID */
    gchar *uuid = g_uuid_string_random();
    g_print("[UUID] %s\n", uuid);
    g_free(uuid);

    /* 6. 环境变量 */
    const gchar *home = g_getenv("HOME");
    if (!home) home = g_getenv("USERPROFILE");
    g_print("[环境变量] HOME=%s\n", home ? home : "(null)");

    g_setenv("GLIB_TUTORIAL_VAR", "hello", TRUE);
    g_print("[设置后] GLIB_TUTORIAL_VAR=%s\n", g_getenv("GLIB_TUTORIAL_VAR"));
    g_unsetenv("GLIB_TUTORIAL_VAR");

    /* 7. 用户目录 */
    g_print("[用户目录] 数据=%s\n", g_get_user_data_dir());
    g_print("[用户目录] 配置=%s\n", g_get_user_config_dir());
    g_print("[用户目录] 缓存=%s\n", g_get_user_cache_dir());
    g_print("[系统目录] 临时=%s\n", g_get_tmp_dir());

    /* 8. 程序名与当前目录 */
    g_print("[程序名] %s\n", g_get_prgname());
    g_set_prgname("GLibTutorial");
    g_print("[设置后程序名] %s\n", g_get_prgname());

    gchar *cwd = g_get_current_dir();
    g_print("[当前目录] %s\n", cwd);
    g_free(cwd);

    /* 9. 主机名与用户名 */
    g_print("[主机名] %s\n", g_get_host_name());
    const gchar *user = g_get_user_name();
    g_print("[用户名] %s\n", user ? user : "(null)");

    /* 10. 路径工具 */
    gchar *path = g_build_filename("usr", "local", "bin", NULL);
    g_print("[构建路径] %s\n", path);
    g_free(path);

    gchar *dirname = g_path_get_dirname("/usr/local/bin/file.txt");
    gchar *basename = g_path_get_basename("/usr/local/bin/file.txt");
    g_print("[路径拆分] dir=%s base=%s\n", dirname, basename);
    g_free(dirname);
    g_free(basename);

    /* 11. 字符串转数值 */
    g_print("[转数值] g_ascii_strtoull(\"255\", NULL, 10) = %llu\n",
            (guint64)g_ascii_strtoull("255", NULL, 10));
    g_print("[转数值] g_ascii_strtod(\"3.14\") = %.2f\n", g_ascii_strtod("3.14", NULL));
}

/* ============================================================
 * 第三篇 系统编程与并发篇
 * ============================================================ */

/* 第 10 章：日志与错误处理体系 */
void chapter_10_logging_and_error_handling(void)
{
    g_print("\n=== 第 10 章 日志与错误处理体系 ===\n");

    /* 1. 日志级别 */
    g_print("[日志级别演示]\n");
    g_message("这是一条 message 级别日志");
    g_warning("这是一条 warning 级别日志");
    g_critical("这是一条 critical 级别日志");
    g_debug("这是一条 debug 级别日志（默认不显示）");

    /* 2. 结构化日志字段 */
    g_log_structured(G_LOG_DOMAIN, G_LOG_LEVEL_INFO,
                     "MESSAGE", "结构化日志示例",
                     "MODULE", "chapter_10",
                     "LINE", "10");

    /* 3. 自定义日志处理 */
    guint old_id = g_log_set_handler(NULL, G_LOG_LEVEL_DEBUG, g_log_default_handler, NULL);
    g_debug("这条 debug 现在会显示（设置了 handler）");
    g_log_remove_handler(NULL, old_id);

    /* 4. GError 基本用法 */
    GError *error = NULL;
    g_set_error(&error, G_FILE_ERROR, G_FILE_ERROR_NOENT,
                "文件不存在: %s", "demo.txt");
    g_print("[GError] domain=%s code=%d message=%s\n",
            g_quark_to_string(error->domain), error->code, error->message);
    g_clear_error(&error);

    /* 5. 错误链（嵌套） */
    GError *inner = NULL;
    g_set_error(&inner, G_IO_ERROR, G_IO_ERROR_FAILED, "底层 I/O 失败");
    g_set_error(&error, G_FILE_ERROR, G_FILE_ERROR_IO,
                "读取失败: %s", inner->message);
    g_print("[错误链] 外层: %s\n", error->message);
    g_print("[错误链] 内层: %s\n", inner->message);
    g_clear_error(&error);
    g_clear_error(&inner);

    /* 6. 错误字面量设置 */
    error = NULL;
    g_set_error_literal(&error, G_IO_ERROR, G_IO_ERROR_INVALID_DATA,
                        "数据无效");
    g_print("[g_set_error_literal] %s\n", error->message);
    g_clear_error(&error);

    /* 7. 错误域注册 */
    GQuark my_domain = g_quark_from_static_string("my-error-quark");
    g_set_error(&error, my_domain, 100, "自定义错误域");
    g_print("[自定义域] domain=%s code=%d\n",
            g_quark_to_string(error->domain), error->code);
    g_clear_error(&error);

    /* 8. g_propagate_error 错误传播 */
    GError *src = NULL, *dst = NULL;
    g_set_error(&src, G_IO_ERROR, G_IO_ERROR_PERMISSION_DENIED, "权限不足");
    g_propagate_error(&dst, src);
    g_print("[propagate] dst=%s src=%p\n", dst->message, (void *)src);
    g_clear_error(&dst);

    /* 9. 错误匹配宏 */
    GError *e2 = g_error_new(G_IO_ERROR, G_IO_ERROR_NOT_FOUND, "未找到");
    if (g_error_matches(e2, G_IO_ERROR, G_IO_ERROR_NOT_FOUND)) {
        g_print("[matches] 匹配 G_IO_ERROR_NOT_FOUND\n");
    }
    g_error_free(e2);

    /* 10. 错误复制 */
    GError *e3 = g_error_new(G_FILE_ERROR, G_FILE_ERROR_IO, "I/O 错误");
    GError *e3_copy = g_error_copy(e3);
    g_print("[copy] 原=%s 副本=%s\n", e3->message, e3_copy->message);
    g_error_free(e3);
    g_error_free(e3_copy);
}

/* 第 11 章：主事件循环 GMainLoop */
gint timeout_count = 0;

gboolean timeout_callback(gpointer data)
{
    timeout_count++;
    g_print("[timeout] 第 %d 次回调\n", timeout_count);
    if (timeout_count >= 3) {
        g_main_loop_quit((GMainLoop *)data);
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

gboolean idle_callback(gpointer data)
{
    g_print("[idle] 空闲回调执行\n");
    return G_SOURCE_REMOVE;
}

gboolean seconds_callback(gpointer data)
{
    g_print("[seconds] 秒级定时器触发\n");
    return G_SOURCE_REMOVE;
}

void chapter_11_main_event_loop(void)
{
    g_print("\n=== 第 11 章 主事件循环 GMainLoop ===\n");

    /* 1. 创建主循环 */
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    GMainContext *ctx = g_main_loop_get_context(loop);
    g_print("[主循环] 运行中=%s\n", g_main_loop_is_running(loop) ? "是" : "否");

    /* 2. 添加超时源（毫秒级） */
    guint timeout_id = g_timeout_add(50, timeout_callback, loop);
    g_print("[超时源] id=%u 已添加\n", timeout_id);

    /* 3. 添加空闲源 */
    guint idle_id = g_idle_add(idle_callback, NULL);
    g_print("[空闲源] id=%u 已添加\n", idle_id);

    /* 4. 超时秒数源（开销更小） */
    guint sec_id = g_timeout_add_seconds(1, seconds_callback, NULL);
    g_print("[秒级源] id=%u 已添加\n", sec_id);

    /* 5. 运行主循环 */
    g_print("[主循环] 开始运行...\n");
    g_main_loop_run(loop);

    /* 6. 清理源 */
    g_source_remove(sec_id);
    g_main_loop_unref(loop);
    timeout_count = 0;
    g_print("[主循环] 已退出并清理\n");

    (void)ctx;
    (void)idle_id;
}

/* 第 12 章：线程编程基础 */
gpointer thread_worker(gpointer data)
{
    gchar *msg = (gchar *)data;
    g_print("[线程 %p] 收到: %s\n", (void *)g_thread_self(), msg);
    g_thread_yield();
    g_print("[线程 %p] 执行完毕\n", (void *)g_thread_self());
    g_thread_exit(GINT_TO_POINTER(42));
    return NULL;
}

void chapter_12_thread_basics(void)
{
    g_print("\n=== 第 12 章 线程编程基础 ===\n");

    /* 1. 创建并等待线程 */
    GThread *t1 = g_thread_new("worker1", thread_worker, "hello from main");
    GThread *t2 = g_thread_new("worker2", thread_worker, "second task");
    g_print("[主线程] 等待子线程完成...\n");

    gpointer r1 = g_thread_join(t1);
    gpointer r2 = g_thread_join(t2);
    g_print("[结果] 线程1=%d 线程2=%d\n", GPOINTER_TO_INT(r1), GPOINTER_TO_INT(r2));

    /* 2. 线程自省 */
    g_print("[主线程] self=%p\n", (void *)g_thread_self());

    /* 3. 线程让步 */
    g_print("[主线程] 执行 g_thread_yield()\n");
    g_thread_yield();

    /* 4. 线程私有数据（TSD） */
    static GPrivate priv = G_PRIVATE_INIT(g_free);
    g_private_set(&priv, g_strdup("private data"));
    gchar *pd = (gchar *)g_private_get(&priv);
    g_print("[TSD] 私有数据=%s\n", pd ? pd : "(null)");
    g_private_replace(&priv, NULL);

    /* 5. 一次性初始化 */
    static GOnce once = G_ONCE_INIT;
    g_once(&once, (GThreadFunc)g_thread_self, NULL);
    g_print("[GOnce] 已初始化: %s\n", once.retval ? "是" : "否");

    /* 6. 线程名说明 */
    g_print("[线程] 名称用于调试，g_thread_new 第一个参数\n");
    g_print("[线程] 默认栈大小使用系统默认\n");
}

/* 第 13 章：线程同步原语 */
GMutex mutex;
GRecMutex rec_mutex;
GRWLock rwlock;
GCond cond;
gboolean ready = FALSE;

gpointer cond_producer(gpointer data)
{
    g_mutex_lock(&mutex);
    g_usleep(2000);
    ready = TRUE;
    g_print("[生产者] 数据就绪，发送信号\n");
    g_cond_signal(&cond);
    g_mutex_unlock(&mutex);
    return NULL;
}

gpointer cond_consumer(gpointer data)
{
    g_mutex_lock(&mutex);
    while (!ready) {
        g_print("[消费者] 等待数据...\n");
        g_cond_wait(&cond, &mutex);
    }
    g_print("[消费者] 收到数据\n");
    g_mutex_unlock(&mutex);
    return NULL;
}

void chapter_13_thread_synchronization(void)
{
    g_print("\n=== 第 13 章 线程同步原语 ===\n");

    /* 1. 互斥锁 */
    g_mutex_init(&mutex);
    g_mutex_lock(&mutex);
    g_print("[mutex] 已锁定\n");
    g_mutex_unlock(&mutex);
    g_print("[mutex] 已解锁\n");

    /* 2. 递归锁（同一线程可多次加锁） */
    g_rec_mutex_init(&rec_mutex);
    g_rec_mutex_lock(&rec_mutex);
    g_rec_mutex_lock(&rec_mutex);
    g_print("[rec_mutex] 二次加锁成功\n");
    g_rec_mutex_unlock(&rec_mutex);
    g_rec_mutex_unlock(&rec_mutex);

    /* 3. 读写锁 */
    g_rw_lock_init(&rwlock);
    g_rw_lock_reader_lock(&rwlock);
    g_print("[rwlock] 读锁获取\n");
    g_rw_lock_reader_unlock(&rwlock);
    g_rw_lock_writer_lock(&rwlock);
    g_print("[rwlock] 写锁获取\n");
    g_rw_lock_writer_unlock(&rwlock);

    /* 4. 条件变量（生产者-消费者） */
    g_cond_init(&cond);
    ready = FALSE;

    GThread *consumer = g_thread_new("consumer", cond_consumer, NULL);
    g_usleep(1000);
    GThread *producer = g_thread_new("producer", cond_producer, NULL);

    g_thread_join(consumer);
    g_thread_join(producer);

    /* 5. 带超时的等待 */
    g_mutex_lock(&mutex);
    ready = FALSE;
    gint64 end_time = g_get_monotonic_time() + 100 * G_TIME_SPAN_MILLISECOND;
    gboolean signaled = g_cond_wait_until(&cond, &mutex, end_time);
    g_print("[cond_wait_until] 超时返回=%s\n", signaled ? "信号" : "超时");
    g_mutex_unlock(&mutex);

    /* 6. 广播信号 */
    g_mutex_lock(&mutex);
    ready = TRUE;
    g_cond_broadcast(&cond);
    g_mutex_unlock(&mutex);
    g_print("[cond_broadcast] 已广播\n");

    g_mutex_clear(&mutex);
    g_rec_mutex_clear(&rec_mutex);
    g_rw_lock_clear(&rwlock);
    g_cond_clear(&cond);
    ready = FALSE;
}

/* 第 14 章：并发组件与线程池 */
void thread_pool_func(gpointer data, gpointer user_data)
{
    gint task_id = GPOINTER_TO_INT(data);
    g_print("[线程池] 处理任务 %d (线程=%p)\n", task_id, (void *)g_thread_self());
    g_usleep(1000);
}

void chapter_14_concurrency_and_thread_pool(void)
{
    g_print("\n=== 第 14 章 并发组件与线程池 ===\n");

    /* 1. GThreadPool */
    GError *error = NULL;
    GThreadPool *pool = g_thread_pool_new(thread_pool_func, NULL, 2, FALSE, &error);
    if (pool) {
        g_print("[线程池] 最大线程=%d\n", g_thread_pool_get_max_threads(pool));

        for (gint i = 0; i < 5; i++) {
            g_thread_pool_push(pool, GINT_TO_POINTER(i), NULL);
        }

        g_print("[线程池] 等待任务完成...\n");
        g_thread_pool_free(pool, FALSE, TRUE);
        g_print("[线程池] 已完成所有任务\n");
    }

    /* 2. 配置线程池 */
    GThreadPool *pool2 = g_thread_pool_new(thread_pool_func, NULL, 4, FALSE, NULL);
    g_thread_pool_set_max_unused_threads(2);
    g_thread_pool_set_max_idle_time(1000);
    g_print("[配置] 最大空闲线程=%d 最大空闲时间=%dms\n",
            g_thread_pool_get_max_unused_threads(),
            g_thread_pool_get_max_idle_time());
    g_thread_pool_free(pool2, FALSE, TRUE);

    /* 3. GAsyncQueue 异步队列 */
    GAsyncQueue *queue = g_async_queue_new();
    g_async_queue_push(queue, GINT_TO_POINTER(100));
    g_async_queue_push(queue, GINT_TO_POINTER(200));
    g_async_queue_push(queue, GINT_TO_POINTER(300));

    /* 非阻塞弹出 */
    gpointer item = g_async_queue_try_pop(queue);
    g_print("[AsyncQueue try_pop] %d\n", GPOINTER_TO_INT(item));

    /* 带超时弹出 */
    gpointer item2 = g_async_queue_timeout_pop(queue, 100 * G_TIME_SPAN_MILLISECOND);
    g_print("[AsyncQueue timeout_pop] %d\n", GPOINTER_TO_INT(item2));

    g_print("[AsyncQueue] 剩余长度=%d\n", g_async_queue_length(queue));
    g_async_queue_unref(queue);

    /* 4. 线程数控制 */
    g_print("[系统] CPU 核心数=%d\n", g_get_num_processors());

    /* 5. 原子操作 */
    gint atomic_val = 0;
    g_atomic_int_set(&atomic_val, 10);
    g_atomic_int_inc(&atomic_val);
    g_print("[原子] 值=%d 交换=%d\n",
            g_atomic_int_get(&atomic_val),
            g_atomic_int_exchange(&atomic_val, 99));
    g_print("[原子] 交换后=%d\n", g_atomic_int_get(&atomic_val));
}

/* 第 15 章：子进程管理 */
void chapter_15_subprocess_management(void)
{
    g_print("\n=== 第 15 章 子进程管理 ===\n");

    GError *error = NULL;

    /* 1. 基本子进程 */
    GSubprocess *proc = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_PIPE | G_SUBPROCESS_FLAGS_STDERR_PIPE,
                                         &error,
                                         "echo", "Hello from subprocess", NULL);
    if (!proc) {
        g_print("[错误] %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    /* 2. 同步通信 */
    gchar *stdout_buf = NULL;
    gchar *stderr_buf = NULL;
    g_subprocess_communicate_utf8(proc, NULL, NULL, &stdout_buf, &stderr_buf, &error);
    if (stdout_buf) g_strstrip(stdout_buf);
    gint exit_status = g_subprocess_get_exit_status(proc);
    g_print("[子进程1] 退出码=%d 输出=\"%s\"\n", exit_status, stdout_buf ? stdout_buf : "");
    g_free(stdout_buf);
    g_free(stderr_buf);
    g_object_unref(proc);

    /* 3. 管道输入 */
    GSubprocess *cat = g_subprocess_new(G_SUBPROCESS_FLAGS_STDIN_PIPE | G_SUBPROCESS_FLAGS_STDOUT_PIPE,
                                         &error,
                                         "cat", NULL);
    if (cat) {
        const gchar *input = "piped data";
        g_subprocess_communicate_utf8(cat, input, NULL, &stdout_buf, NULL, &error);
        if (stdout_buf) g_strstrip(stdout_buf);
        g_print("[子进程2 cat] 输入=\"%s\" 输出=\"%s\"\n", input, stdout_buf ? stdout_buf : "");
        g_free(stdout_buf);
        g_object_unref(cat);
    }

    /* 4. 等待子进程 */
    GSubprocess *wait_proc = g_subprocess_new(0, &error, "echo", "wait test", NULL);
    if (wait_proc) {
        gboolean success = g_subprocess_wait(wait_proc, NULL, &error);
        g_print("[子进程3 wait] 成功=%s 退出=%d\n",
                success ? "是" : "否", g_subprocess_get_exit_status(wait_proc));
        g_object_unref(wait_proc);
    }

    /* 5. 获取 PID */
    GSubprocess *pid_proc = g_subprocess_new(0, &error, "echo", "pid test", NULL);
    if (pid_proc) {
        const gchar *pid = g_subprocess_get_identifier(pid_proc);
        g_print("[子进程4] 标识=%s\n", pid ? pid : "(null)");
        g_subprocess_wait(pid_proc, NULL, NULL);
        g_object_unref(pid_proc);
    }

    /* 6. 子进程标志说明 */
    g_print("[标志说明]\n");
    g_print("  G_SUBPROCESS_FLAGS_NONE: 默认\n");
    g_print("  G_SUBPROCESS_FLAGS_STDOUT_PIPE: 捕获标准输出\n");
    g_print("  G_SUBPROCESS_FLAGS_STDERR_PIPE: 捕获标准错误\n");
    g_print("  G_SUBPROCESS_FLAGS_STDIN_PIPE: 可写入标准输入\n");
}

/* 第 16 章：动态模块与插件架构 */
void chapter_16_modules_and_plugins(void)
{
    g_print("\n=== 第 16 章 动态模块与插件架构 ===\n");

    /* 1. 检查模块支持 */
    gboolean supported = g_module_supported();
    g_print("[GModule] 支持动态加载: %s\n", supported ? "是" : "否");

    if (!supported) {
        return;
    }

    /* 2. 模块路径构建（g_module_build_path 已废弃，用 g_build_filename 替代） */
    gchar *mod_path = g_build_filename("libmyplugin.so", NULL);
    g_print("[模块路径] %s (示例)\n", mod_path);
    g_free(mod_path);

    /* 3. 模块打开标志说明 */
    g_print("[标志] G_MODULE_BIND_LAZY=%d G_MODULE_BIND_LOCAL=%d\n",
            G_MODULE_BIND_LAZY, G_MODULE_BIND_LOCAL);

    /* 4. 打开主程序自身（演示符号查找） */
    GModule *mod = g_module_open(NULL, G_MODULE_BIND_LAZY);
    if (mod) {
        g_print("[模块] 主程序自身已打开\n");

        /* 5. 查找符号 */
        gpointer func = NULL;
        if (g_module_symbol(mod, "g_print", &func)) {
            g_print("[符号] g_print 地址=%p\n", (void *)func);
        } else {
            g_print("[符号] 未找到 g_print\n");
        }

        /* 6. 模块名 */
        const gchar *name = g_module_name(mod);
        g_print("[模块名] %s\n", name ? name : "(null)");

        /* 7. 关闭模块 */
        g_module_close(mod);
    } else {
        g_print("[模块] 打开失败（平台相关）\n");
    }

    /* 8. 插件架构设计说明 */
    g_print("[插件架构设计]\n");
    g_print("  1. 定义插件接口结构体（含 init/fini/func 函数指针）\n");
    g_print("  2. 插件用 G_MODULE_EXPORT 导出 init_plugin() 符号\n");
    g_print("  3. 主程序用 g_module_open 加载插件 .so/.dll\n");
    g_print("  4. 用 g_module_symbol 获取 init_plugin 函数指针\n");
    g_print("  5. 通过接口结构体调用插件功能\n");
    g_print("  6. 最后 g_module_close 卸载插件\n");
}

/* ============================================================
 * 第四篇 GObject 对象系统篇
 * ============================================================ */

/* 第 17 章：GType 类型系统基础 */
void chapter_17_gtype_basics(void)
{
    g_print("\n=== 第 17 章 GType 类型系统基础 ===\n");

    /* 1. 基本类型查询 */
    g_print("[基本类型]\n");
    g_print("  G_TYPE_INT:     id=%lu 名称=%s\n", G_TYPE_INT, g_type_name(G_TYPE_INT));
    g_print("  G_TYPE_UINT:    id=%lu 名称=%s\n", G_TYPE_UINT, g_type_name(G_TYPE_UINT));
    g_print("  G_TYPE_STRING:  id=%lu 名称=%s\n", G_TYPE_STRING, g_type_name(G_TYPE_STRING));
    g_print("  G_TYPE_BOOLEAN: id=%lu 名称=%s\n", G_TYPE_BOOLEAN, g_type_name(G_TYPE_BOOLEAN));
    g_print("  G_TYPE_DOUBLE:  id=%lu 名称=%s\n", G_TYPE_DOUBLE, g_type_name(G_TYPE_DOUBLE));
    g_print("  G_TYPE_OBJECT:  id=%lu 名称=%s\n", G_TYPE_OBJECT, g_type_name(G_TYPE_OBJECT));
    g_print("  G_TYPE_BOXED:   id=%lu 名称=%s\n", G_TYPE_BOXED, g_type_name(G_TYPE_BOXED));
    g_print("  G_TYPE_POINTER: id=%lu 名称=%s\n", G_TYPE_POINTER, g_type_name(G_TYPE_POINTER));

    /* 2. 类型判断宏 */
    g_print("[类型判断]\n");
    g_print("  G_TYPE_IS_OBJECT(G_TYPE_OBJECT): %s\n", G_TYPE_IS_OBJECT(G_TYPE_OBJECT) ? "是" : "否");
    g_print("  G_TYPE_IS_FUNDAMENTAL(G_TYPE_INT): %s\n", G_TYPE_IS_FUNDAMENTAL(G_TYPE_INT) ? "是" : "否");
    g_print("  G_TYPE_IS_DERIVABLE(G_TYPE_OBJECT): %s\n", G_TYPE_IS_DERIVABLE(G_TYPE_OBJECT) ? "是" : "否");
    g_print("  G_TYPE_IS_INTERFACE(G_TYPE_OBJECT): %s\n", G_TYPE_IS_INTERFACE(G_TYPE_OBJECT) ? "是" : "否");

    /* 3. GValue 值容器 */
    GValue val = G_VALUE_INIT;
    g_value_init(&val, G_TYPE_INT);
    g_value_set_int(&val, 42);
    g_print("[GValue int] %d\n", g_value_get_int(&val));
    g_value_unset(&val);

    g_value_init(&val, G_TYPE_STRING);
    g_value_set_string(&val, "Hello GType");
    const gchar *s = g_value_get_string(&val);
    g_print("[GValue string] %s\n", s ? s : "(null)");
    g_value_unset(&val);

    g_value_init(&val, G_TYPE_BOOLEAN);
    g_value_set_boolean(&val, TRUE);
    g_print("[GValue boolean] %s\n", g_value_get_boolean(&val) ? "TRUE" : "FALSE");
    g_value_unset(&val);

    /* 4. GValue 类型转换 */
    g_value_init(&val, G_TYPE_INT);
    g_value_set_int(&val, 100);
    GValue str_val = G_VALUE_INIT;
    g_value_init(&str_val, G_TYPE_STRING);
    if (g_value_transform(&val, &str_val)) {
        g_print("[GValue 转换] int->string: %s\n", g_value_get_string(&str_val));
    }
    g_value_unset(&val);
    g_value_unset(&str_val);

    /* 5. GValue 复制 */
    GValue src = G_VALUE_INIT;
    g_value_init(&src, G_TYPE_INT);
    g_value_set_int(&src, 999);
    GValue dst = G_VALUE_INIT;
    g_value_init(&dst, G_TYPE_INT);
    g_value_copy(&src, &dst);
    g_print("[GValue copy] %d\n", g_value_get_int(&dst));
    g_value_unset(&src);
    g_value_unset(&dst);

    /* 6. 类型继承关系 */
    GType parent = g_type_parent(G_TYPE_OBJECT);
    g_print("[继承] GObject 父类型=%s\n", parent ? g_type_name(parent) : "(无)");

    /* 7. 类型子类列表 */
    GType *children = NULL;
    guint n_children = 0;
    children = g_type_children(G_TYPE_OBJECT, &n_children);
    g_print("[子类] GObject 直接子类数量=%u\n", n_children);
    g_free(children);

    /* 8. 类型接口列表 */
    GType *interfaces = NULL;
    guint n_ifaces = 0;
    interfaces = g_type_interfaces(G_TYPE_OBJECT, &n_ifaces);
    g_print("[接口] GObject 实现接口数量=%u\n", n_ifaces);
    g_free(interfaces);
}

/* 第 18 章：GObject 对象基础 */
void chapter_18_gobject_basics(void)
{
    g_print("\n=== 第 18 章 GObject 对象基础 ===\n");

    /* 1. 创建对象 */
    GObject *obj = g_object_new(G_TYPE_OBJECT, NULL);
    g_print("[创建] GObject 地址=%p 引用计数=%d\n", (void *)obj, obj->ref_count);

    /* 2. 引用计数 */
    g_object_ref(obj);
    g_print("[ref] 引用计数=%d\n", obj->ref_count);

    g_object_ref_sink(obj); /* 浮引用转普通引用 */
    g_print("[ref_sink] 引用计数=%d\n", obj->ref_count);

    g_object_unref(obj);
    g_print("[unref] 引用计数=%d\n", obj->ref_count);

    /* 3. qdata 关联数据 */
    GQuark qd_key = g_quark_from_static_string("my-data");
    g_object_set_qdata_full(obj, qd_key, g_strdup("attached data"), g_free);
    gchar *qd = g_object_get_qdata(obj, qd_key);
    g_print("[qdata] key=%s value=%s\n", g_quark_to_string(qd_key), qd ? qd : "(null)");

    /* 4. qdata 替换 */
    g_object_set_qdata_full(obj, qd_key, g_strdup("new data"), g_free);
    gchar *qd2 = g_object_get_qdata(obj, qd_key);
    g_print("[qdata 替换] %s\n", qd2 ? qd2 : "(null)");

    /* 5. 多个 qdata */
    GQuark qd_key2 = g_quark_from_static_string("number");
    g_object_set_qdata(obj, qd_key2, GINT_TO_POINTER(123));
    g_print("[qdata2] number=%d\n", GPOINTER_TO_INT(g_object_get_qdata(obj, qd_key2)));

    /* 6. qdata 重置 */
    g_object_set_qdata(obj, qd_key2, GINT_TO_POINTER(456));
    g_print("[qdata2 重置] number=%d\n", GPOINTER_TO_INT(g_object_get_qdata(obj, qd_key2)));

    /* 7. 弱引用 */
    GObject *weak_ref = NULL;
    g_object_add_weak_pointer(obj, (gpointer *)&weak_ref);
    g_print("[weak] 添加弱引用=%p\n", (void *)weak_ref);

    g_object_unref(obj);
    g_print("[weak] 释放一次后=%p\n", (void *)weak_ref);

    g_object_unref(obj);
    g_print("[weak] 全部释放后=%p (应为 NULL)\n", (void *)weak_ref);

    /* 8. toggle ref 说明 */
    g_print("[toggle] toggle ref 用于实现弱引用持有者的回调通知\n");

    /* 9. 浮引用说明 */
    g_print("[浮引用] g_object_ref_sink 将浮引用转为普通引用\n");
    g_print("[浮引用] 初始创建的对象为浮引用，需 sink 后管理\n");
}

/* 第 19 章：属性系统 */
#define CH19_TYPE_MY_OBJECT chapter_19_my_object_get_type()
G_DECLARE_FINAL_TYPE(Chapter19MyObject, chapter_19_my_object, CH19, MY_OBJECT, GObject)

struct _Chapter19MyObject {
    GObject parent_instance;
    gint value;
    gchar *name;
    gboolean active;
};

G_DEFINE_TYPE(Chapter19MyObject, chapter_19_my_object, G_TYPE_OBJECT)

enum {
    CH19_PROP_0,
    CH19_PROP_VALUE,
    CH19_PROP_NAME,
    CH19_PROP_ACTIVE,
    CH19_N_PROPS
};

static GParamSpec *ch19_props[CH19_N_PROPS] = { NULL };

void chapter_19_my_object_get_property(GObject *obj, guint prop_id, GValue *value, GParamSpec *pspec)
{
    Chapter19MyObject *self = CH19_MY_OBJECT(obj);
    switch (prop_id) {
    case CH19_PROP_VALUE:
        g_value_set_int(value, self->value);
        break;
    case CH19_PROP_NAME:
        g_value_set_string(value, self->name);
        break;
    case CH19_PROP_ACTIVE:
        g_value_set_boolean(value, self->active);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
    }
}

void chapter_19_my_object_set_property(GObject *obj, guint prop_id, const GValue *value, GParamSpec *pspec)
{
    Chapter19MyObject *self = CH19_MY_OBJECT(obj);
    switch (prop_id) {
    case CH19_PROP_VALUE:
        self->value = g_value_get_int(value);
        break;
    case CH19_PROP_NAME:
        g_free(self->name);
        self->name = g_value_dup_string(value);
        break;
    case CH19_PROP_ACTIVE:
        self->active = g_value_get_boolean(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);
    }
}

void chapter_19_my_object_finalize(GObject *obj)
{
    Chapter19MyObject *self = CH19_MY_OBJECT(obj);
    g_free(self->name);
    G_OBJECT_CLASS(chapter_19_my_object_parent_class)->finalize(obj);
}

void chapter_19_my_object_class_init(Chapter19MyObjectClass *klass)
{
    GObjectClass *oc = G_OBJECT_CLASS(klass);
    oc->get_property = chapter_19_my_object_get_property;
    oc->set_property = chapter_19_my_object_set_property;
    oc->finalize = chapter_19_my_object_finalize;

    ch19_props[CH19_PROP_VALUE] = g_param_spec_int("value", "Value", "整型值",
                                                    G_MININT, G_MAXINT, 0, G_PARAM_READWRITE);
    ch19_props[CH19_PROP_NAME] = g_param_spec_string("name", "Name", "名称",
                                                       "default", G_PARAM_READWRITE);
    ch19_props[CH19_PROP_ACTIVE] = g_param_spec_boolean("active", "Active", "是否激活",
                                                          FALSE, G_PARAM_READWRITE);
    g_object_class_install_properties(oc, CH19_N_PROPS, ch19_props);
}

void chapter_19_my_object_init(Chapter19MyObject *self)
{
    self->value = 0;
    self->name = NULL;
    self->active = FALSE;
}

void on_ch19_notify(GObject *obj, GParamSpec *pspec, gpointer user_data)
{
    g_print("  [notify] 属性 '%s' 发生变化\n", g_param_spec_get_name(pspec));
}

void chapter_19_properties(void)
{
    g_print("\n=== 第 19 章 属性系统 ===\n");

    /* 1. 创建对象并设置属性 */
    GObject *obj = g_object_new(CH19_TYPE_MY_OBJECT,
                                 "value", 100,
                                 "name", "GLibObject",
                                 "active", TRUE,
                                 NULL);

    /* 2. 读取属性 */
    gint value;
    gchar *name;
    gboolean active;
    g_object_get(obj, "value", &value, "name", &name, "active", &active, NULL);
    g_print("[属性] value=%d name=%s active=%s\n", value, name, active ? "TRUE" : "FALSE");
    g_free(name);

    /* 3. 监听属性变化 */
    g_print("[监听] 连接 notify 信号\n");
    g_signal_connect(obj, "notify::value", G_CALLBACK(on_ch19_notify), NULL);
    g_object_set(obj, "value", 200, NULL);

    /* 4. 冻结通知 */
    g_object_freeze_notify(obj);
    g_object_set(obj, "value", 300, "active", FALSE, NULL);
    g_print("[冻结] 多次设置不发通知\n");
    g_object_thaw_notify(obj);

    /* 5. 单独获取 */
    gint v = 0;
    g_object_get(obj, "value", &v, NULL);
    g_print("[单独获取] value=%d\n", v);

    /* 6. 属性描述 */
    GParamSpec *pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(obj), "value");
    if (pspec) {
        g_print("[ParamSpec] name=%s nick=%s blurb=%s\n",
                g_param_spec_get_name(pspec),
                g_param_spec_get_nick(pspec),
                g_param_spec_get_blurb(pspec));
        g_print("[范围] min=%d max=%d default=%d\n",
                G_PARAM_SPEC_INT(pspec)->minimum,
                G_PARAM_SPEC_INT(pspec)->maximum,
                G_PARAM_SPEC_INT(pspec)->default_value);
    }

    /* 7. bind（绑定到另一个对象） */
    GObject *obj2 = g_object_new(CH19_TYPE_MY_OBJECT, NULL);
    GBinding *binding = g_object_bind_property(obj, "value", obj2, "value", G_BINDING_DEFAULT);
    g_object_set(obj, "value", 999, NULL);
    gint v2;
    g_object_get(obj2, "value", &v2, NULL);
    g_print("[bind] obj.value=999 -> obj2.value=%d\n", v2);
    g_binding_unbind(binding);
    g_object_unref(obj2);

    g_object_unref(obj);
}

/* 第 20 章：信号系统 */
#define CH20_TYPE_MY_SIGNAL_OBJECT chapter_20_my_signal_object_get_type()
G_DECLARE_FINAL_TYPE(Chapter20MySignalObject, chapter_20_my_signal_object, CH20, MY_SIGNAL_OBJECT, GObject)

struct _Chapter20MySignalObject {
    GObject parent_instance;
};

G_DEFINE_TYPE(Chapter20MySignalObject, chapter_20_my_signal_object, G_TYPE_OBJECT)

enum { CH20_SIGNAL_HELLO, CH20_SIGNAL_CHANGED, CH20_N_SIGNALS };
static guint ch20_signals[CH20_N_SIGNALS] = { 0 };

void chapter_20_my_signal_object_class_init(Chapter20MySignalObjectClass *klass)
{
    ch20_signals[CH20_SIGNAL_HELLO] = g_signal_new("hello",
        G_TYPE_FROM_CLASS(klass), G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0, NULL, NULL, NULL, G_TYPE_NONE, 1, G_TYPE_STRING);

    ch20_signals[CH20_SIGNAL_CHANGED] = g_signal_new("changed",
        G_TYPE_FROM_CLASS(klass), G_SIGNAL_RUN_FIRST,
        0, NULL, NULL, NULL, G_TYPE_NONE, 1, G_TYPE_INT);
}

void chapter_20_my_signal_object_init(Chapter20MySignalObject *self)
{
}

void on_hello_default(GObject *obj, const gchar *msg, gpointer data)
{
    g_print("  [hello 默认] %s (data=%s)\n", msg, (gchar *)data);
}

void on_hello_after(GObject *obj, const gchar *msg, gpointer data)
{
    g_print("  [hello after] %s\n", msg);
}

void on_changed(GObject *obj, gint val, gpointer data)
{
    g_print("  [changed] val=%d\n", val);
}

void chapter_20_signals(void)
{
    g_print("\n=== 第 20 章 信号系统 ===\n");

    GObject *obj = g_object_new(CH20_TYPE_MY_SIGNAL_OBJECT, NULL);

    /* 1. 基本连接与发射 */
    gulong hid1 = g_signal_connect(obj, "hello", G_CALLBACK(on_hello_default), "user-data");
    g_signal_emit_by_name(obj, "hello", "Hello World");
    g_print("[信号] 连接 id=%lu\n", hid1);

    /* 2. after 回调 */
    gulong hid2 = g_signal_connect_after(obj, "hello", G_CALLBACK(on_hello_after), NULL);
    g_signal_emit_by_name(obj, "hello", "Second emit");

    /* 3. 阻断信号 */
    g_signal_handler_block(obj, hid1);
    g_print("[阻断] 已阻断 hello 信号\n");
    g_signal_emit_by_name(obj, "hello", "Blocked");
    g_signal_handler_unblock(obj, hid1);
    g_print("[解除] 已解除阻断\n");

    /* 4. 断开连接 */
    g_signal_handler_disconnect(obj, hid1);
    g_signal_handler_disconnect(obj, hid2);
    g_signal_emit_by_name(obj, "hello", "No handlers");
    g_print("[断开] 信号已无处理器\n");

    /* 5. changed 信号 */
    g_signal_connect(obj, "changed", G_CALLBACK(on_changed), NULL);
    g_signal_emit_by_name(obj, "changed", 42);

    /* 6. 信号详细化（detail） */
    g_signal_connect(obj, "hello::greeting", G_CALLBACK(on_hello_default), "detail");
    g_signal_emit_by_name(obj, "hello::greeting", "Detailed emit");

    /* 7. 查询信号信息 */
    guint signal_id = g_signal_lookup("hello", CH20_TYPE_MY_SIGNAL_OBJECT);
    GSignalQuery query;
    g_signal_query(signal_id, &query);
    g_print("[查询] 信号名=%s 参数数=%d 返回类型=%s\n",
            query.signal_name, query.n_params,
            g_type_name(query.return_type));

    /* 8. 信号列表 */
    guint n_ids = 0;
    guint *ids = g_signal_list_ids(CH20_TYPE_MY_SIGNAL_OBJECT, &n_ids);
    g_print("[信号列表] 数量=%u: ", n_ids);
    for (guint i = 0; i < n_ids; i++) {
        g_print("%s ", g_signal_name(ids[i]));
    }
    g_print("\n");
    g_free(ids);

    g_object_unref(obj);
}

/* 第 21 章：GObject 子类化 */
#define CH21_TYPE_ANIMAL chapter_21_animal_get_type()
G_DECLARE_DERIVABLE_TYPE(Chapter21Animal, chapter_21_animal, CH21, ANIMAL, GObject)

struct _Chapter21AnimalClass {
    GObjectClass parent_class;
    void (*speak)(Chapter21Animal *self);
    const gchar *(*get_type_name)(Chapter21Animal *self);
};

G_DEFINE_TYPE(Chapter21Animal, chapter_21_animal, G_TYPE_OBJECT)

void chapter_21_animal_real_speak(Chapter21Animal *self)
{
    g_print("[Animal] 默认叫声\n");
}

const gchar *chapter_21_animal_real_get_type_name(Chapter21Animal *self)
{
    return "Animal";
}

void chapter_21_animal_class_init(Chapter21AnimalClass *klass)
{
    klass->speak = chapter_21_animal_real_speak;
    klass->get_type_name = chapter_21_animal_real_get_type_name;
}

void chapter_21_animal_init(Chapter21Animal *self)
{
}

void chapter_21_animal_speak(Chapter21Animal *self)
{
    CH21_ANIMAL_GET_CLASS(self)->speak(self);
}

const gchar *chapter_21_animal_get_type_name(Chapter21Animal *self)
{
    return CH21_ANIMAL_GET_CLASS(self)->get_type_name(self);
}

/* Dog 子类 */
#define CH21_TYPE_DOG chapter_21_dog_get_type()
G_DECLARE_FINAL_TYPE(Chapter21Dog, chapter_21_dog, CH21, DOG, Chapter21Animal)

struct _Chapter21Dog {
    Chapter21Animal parent_instance;
    gchar *name;
};

G_DEFINE_TYPE(Chapter21Dog, chapter_21_dog, CH21_TYPE_ANIMAL)

void chapter_21_dog_speak(Chapter21Animal *self)
{
    Chapter21Dog *dog = CH21_DOG(self);
    g_print("[Dog %s] Woof! Woof!\n", dog->name);
}

const gchar *chapter_21_dog_get_type_name(Chapter21Animal *self)
{
    return "Dog";
}

void chapter_21_dog_class_init(Chapter21DogClass *klass)
{
    CH21_ANIMAL_CLASS(klass)->speak = chapter_21_dog_speak;
    CH21_ANIMAL_CLASS(klass)->get_type_name = chapter_21_dog_get_type_name;
}

void chapter_21_dog_init(Chapter21Dog *self)
{
    self->name = g_strdup("Rex");
}

/* Cat 子类 */
#define CH21_TYPE_CAT chapter_21_cat_get_type()
G_DECLARE_FINAL_TYPE(Chapter21Cat, chapter_21_cat, CH21, CAT, Chapter21Animal)

struct _Chapter21Cat {
    Chapter21Animal parent_instance;
};

G_DEFINE_TYPE(Chapter21Cat, chapter_21_cat, CH21_TYPE_ANIMAL)

void chapter_21_cat_speak(Chapter21Animal *self)
{
    g_print("[Cat] Meow!\n");
}

void chapter_21_cat_class_init(Chapter21CatClass *klass)
{
    CH21_ANIMAL_CLASS(klass)->speak = chapter_21_cat_speak;
}

void chapter_21_cat_init(Chapter21Cat *self)
{
}

void chapter_21_subclassing(void)
{
    g_print("\n=== 第 21 章 GObject 子类化 ===\n");

    /* 1. 创建基类和子类实例 */
    Chapter21Animal *animal = g_object_new(CH21_TYPE_ANIMAL, NULL);
    Chapter21Animal *dog = g_object_new(CH21_TYPE_DOG, NULL);
    Chapter21Animal *cat = g_object_new(CH21_TYPE_CAT, NULL);

    /* 2. 虚方法调用（多态） */
    g_print("[多态演示]\n");
    chapter_21_animal_speak(animal);
    chapter_21_animal_speak(dog);
    chapter_21_animal_speak(cat);

    /* 3. 类型名查询 */
    g_print("[类型名] animal=%s dog=%s cat=%s\n",
            chapter_21_animal_get_type_name(animal),
            chapter_21_animal_get_type_name(dog),
            chapter_21_animal_get_type_name(cat));

    /* 4. 类型检查 */
    g_print("[类型检查] dog 是 Animal: %s\n",
            G_TYPE_CHECK_INSTANCE_TYPE(dog, CH21_TYPE_ANIMAL) ? "是" : "否");
    g_print("[类型检查] dog 是 Dog: %s\n",
            G_TYPE_CHECK_INSTANCE_TYPE(dog, CH21_TYPE_DOG) ? "是" : "否");
    g_print("[类型检查] dog 是 Cat: %s\n",
            G_TYPE_CHECK_INSTANCE_TYPE(dog, CH21_TYPE_CAT) ? "是" : "否");

    /* 5. 类型转换 */
    Chapter21Dog *dog_ptr = CH21_DOG(dog);
    g_print("[类型转换] Dog 名字=%s\n", dog_ptr->name);

    /* 6. 继承链查询 */
    GType parent = g_type_parent(CH21_TYPE_DOG);
    g_print("[继承链] Dog 父类型=%s\n", g_type_name(parent));
    g_print("[继承链] Dog 顶层类型=%s\n", g_type_name(G_TYPE_FUNDAMENTAL(CH21_TYPE_DOG)));

    g_object_unref(animal);
    g_object_unref(dog);
    g_object_unref(cat);
}

/* 第 22 章：接口系统 GInterface */
#define CH22_TYPE_GREETER chapter_22_greeter_get_type()
G_DECLARE_INTERFACE(Chapter22Greeter, chapter_22_greeter, CH22, GREETER, GObject)

struct _Chapter22GreeterInterface {
    GTypeInterface parent_iface;
    void (*greet)(Chapter22Greeter *self);
    const gchar *(*get_greeting)(Chapter22Greeter *self);
};

G_DEFINE_INTERFACE(Chapter22Greeter, chapter_22_greeter, G_TYPE_OBJECT)

void chapter_22_greeter_default_init(Chapter22GreeterInterface *iface)
{
}

void chapter_22_greeter_greet(Chapter22Greeter *self)
{
    CH22_GREETER_GET_IFACE(self)->greet(self);
}

const gchar *chapter_22_greeter_get_greeting(Chapter22Greeter *self)
{
    return CH22_GREETER_GET_IFACE(self)->get_greeting(self);
}

/* Person 实现 Greeter 接口 */
#define CH22_TYPE_PERSON chapter_22_person_get_type()
G_DECLARE_FINAL_TYPE(Chapter22Person, chapter_22_person, CH22, PERSON, GObject)

struct _Chapter22Person {
    GObject parent_instance;
    gchar *name;
};

void chapter_22_person_greet(Chapter22Greeter *self);
const gchar *chapter_22_person_get_greeting(Chapter22Greeter *self);

void chapter_22_person_greeter_init(Chapter22GreeterInterface *iface)
{
    iface->greet = chapter_22_person_greet;
    iface->get_greeting = chapter_22_person_get_greeting;
}

G_DEFINE_TYPE_WITH_CODE(Chapter22Person, chapter_22_person, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(CH22_TYPE_GREETER, chapter_22_person_greeter_init))

void chapter_22_person_greet(Chapter22Greeter *self)
{
    Chapter22Person *person = CH22_PERSON(self);
    g_print("[Person %s] Hello!\n", person->name);
}

const gchar *chapter_22_person_get_greeting(Chapter22Greeter *self)
{
    return "Hello from Person";
}

void chapter_22_person_class_init(Chapter22PersonClass *klass)
{
}

void chapter_22_person_init(Chapter22Person *self)
{
    self->name = g_strdup("Alice");
}

/* Robot 也实现 Greeter 接口 */
#define CH22_TYPE_ROBOT chapter_22_robot_get_type()
G_DECLARE_FINAL_TYPE(Chapter22Robot, chapter_22_robot, CH22, ROBOT, GObject)

struct _Chapter22Robot {
    GObject parent_instance;
};

void chapter_22_robot_greet(Chapter22Greeter *self);

void chapter_22_robot_greeter_init(Chapter22GreeterInterface *iface)
{
    iface->greet = chapter_22_robot_greet;
    iface->get_greeting = NULL;
}

G_DEFINE_TYPE_WITH_CODE(Chapter22Robot, chapter_22_robot, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(CH22_TYPE_GREETER, chapter_22_robot_greeter_init))

void chapter_22_robot_greet(Chapter22Greeter *self)
{
    g_print("[Robot] Beep boop! Greetings!\n");
}

void chapter_22_robot_class_init(Chapter22RobotClass *klass)
{
}

void chapter_22_robot_init(Chapter22Robot *self)
{
}

void chapter_22_ginterface(void)
{
    g_print("\n=== 第 22 章 接口系统 GInterface ===\n");

    /* 1. 创建实现了接口的对象 */
    Chapter22Greeter *person = g_object_new(CH22_TYPE_PERSON, NULL);
    Chapter22Greeter *robot = g_object_new(CH22_TYPE_ROBOT, NULL);

    /* 2. 通过接口调用（多态） */
    g_print("[接口调用]\n");
    chapter_22_greeter_greet(person);
    chapter_22_greeter_greet(robot);

    /* 3. 接口方法返回值 */
    const gchar *greeting = chapter_22_greeter_get_greeting(person);
    g_print("[接口返回] Person greeting=%s\n", greeting ? greeting : "(null)");

    /* 4. 接口类型检查 */
    g_print("[类型检查] Person 实现 Greeter: %s\n",
            G_TYPE_CHECK_INSTANCE_TYPE(person, CH22_TYPE_GREETER) ? "是" : "否");
    g_print("[类型检查] Robot 实现 Greeter: %s\n",
            G_TYPE_CHECK_INSTANCE_TYPE(robot, CH22_TYPE_GREETER) ? "是" : "否");

    /* 5. 接口前提类型检查 */
    /* g_type_interface_prerequisites 返回接口的前提类型数组 */
    guint n_prereqs = 0;
    GType *prereqs = g_type_interface_prerequisites(CH22_TYPE_GREETER, &n_prereqs);
    if (prereqs && n_prereqs > 0) {
        g_print("[前提检查] Greeter 前提类型=%s\n", g_type_name(prereqs[0]));
    } else {
        g_print("[前提检查] Greeter 无前提类型\n");
    }
    g_free(prereqs);

    /* 6. 列出类型实现的接口 */
    GType *ifaces = g_type_interfaces(CH22_TYPE_PERSON, NULL);
    g_print("[Person 接口] %s\n", ifaces ? g_type_name(ifaces[0]) : "(无)");
    g_free(ifaces);

    g_object_unref(person);
    g_object_unref(robot);
}

/* 第 23 章：GObject 高级特性 */
void chapter_23_gobject_advanced(void)
{
    g_print("\n=== 第 23 章 GObject 高级特性 ===\n");

    /* 1. 弱引用 */
    GObject *obj = g_object_new(G_TYPE_OBJECT, NULL);
    GObject *weak = NULL;

    g_object_add_weak_pointer(obj, (gpointer *)&weak);
    g_print("[weak] 添加弱引用=%p\n", (void *)weak);
    g_object_unref(obj);
    g_print("[weak] 释放后=%p (应为 NULL)\n", (void *)weak);

    /* 2. qdata 关联数据 */
    GObject *obj2 = g_object_new(G_TYPE_OBJECT, NULL);
    GQuark qd_key = g_quark_from_static_string("mydata");
    g_object_set_qdata_full(obj2, qd_key, g_strdup("attached"), g_free);
    gchar *qd = g_object_get_qdata(obj2, qd_key);
    g_print("[qdata] value=%s\n", qd ? qd : "(null)");

    /* 3. qdata 重设 */
    g_object_set_qdata_full(obj2, qd_key, g_strdup("updated"), g_free);
    gchar *qd2 = g_object_get_qdata(obj2, qd_key);
    g_print("[qdata 更新] %s\n", qd2 ? qd2 : "(null)");

    /* 4. qdata steal */
    gchar *stolen = g_object_steal_qdata(obj2, qd_key);
    g_print("[qdata steal] %s\n", stolen ? stolen : "(null)");
    g_free(stolen);

    /* 5. toggle ref（切换引用） */
    GObject *obj3 = g_object_new(G_TYPE_OBJECT, NULL);
    g_object_ref_sink(obj3);
    g_print("[toggle] 引用计数=%d\n", obj3->ref_count);

    /* 6. 属性冻结/解冻 */
    /* 用第19章的对象演示属性批量通知 */

    /* 7. object notify 信号 */
    GObject *obj4 = g_object_new(G_TYPE_OBJECT, NULL);
    gulong notify_id = g_signal_connect(obj4, "notify", G_CALLBACK(on_ch19_notify), NULL);
    (void)notify_id;

    /* 8. 对象接口查询 */
    guint n_ifaces = 0;
    GType *obj_ifaces = g_type_interfaces(G_TYPE_OBJECT, &n_ifaces);
    g_print("[interface] GObject 实现接口数=%u\n", n_ifaces);
    g_free(obj_ifaces);

    /* 9. weak ref 回调 */
    GObject *obj5 = g_object_new(G_TYPE_OBJECT, NULL);
    g_object_weak_ref(obj5, (GWeakNotify)g_print, "[weak_ref] 对象被销毁");
    g_object_unref(obj5);

    /* 10. 多个弱引用 */
    GObject *obj6 = g_object_new(G_TYPE_OBJECT, NULL);
    GObject *weak1 = NULL, *weak2 = NULL;
    g_object_add_weak_pointer(obj6, (gpointer *)&weak1);
    g_object_add_weak_pointer(obj6, (gpointer *)&weak2);
    g_print("[多弱引用] weak1=%p weak2=%p\n", (void *)weak1, (void *)weak2);
    g_object_unref(obj6);
    g_print("[多弱引用] 释放后 weak1=%p weak2=%p\n", (void *)weak1, (void *)weak2);

    g_object_unref(obj2);
    g_object_unref(obj3);
    g_object_unref(obj4);
}

/* 第 24 章：GVariant 类型系统 */
void chapter_24_gvariant(void)
{
    g_print("\n=== 第 24 章 GVariant 类型系统 ===\n");

    /* 1. 基本 variant */
    GVariant *v = g_variant_new("(si)", "GLib", 42);
    gchar *str = NULL;
    gint num = 0;
    g_variant_get(v, "(&si)", &str, &num);
    g_print("[基本] str=%s num=%d 类型=%s\n", str, num, g_variant_get_type_string(v));
    g_variant_unref(v);

    /* 2. 基本类型 variant */
    GVariant *vi = g_variant_new_int32(100);
    g_print("[int32] 值=%d 类型=%s\n", g_variant_get_int32(vi), g_variant_get_type_string(vi));
    g_variant_unref(vi);

    GVariant *vs = g_variant_new_string("Hello");
    g_print("[string] 值=%s 类型=%s\n", g_variant_get_string(vs, NULL), g_variant_get_type_string(vs));
    g_variant_unref(vs);

    GVariant *vb = g_variant_new_boolean(TRUE);
    g_print("[boolean] 值=%s 类型=%s\n", g_variant_get_boolean(vb) ? "TRUE" : "FALSE",
            g_variant_get_type_string(vb));
    g_variant_unref(vb);

    GVariant *vd = g_variant_new_double(3.14);
    g_print("[double] 值=%.2f 类型=%s\n", g_variant_get_double(vd), g_variant_get_type_string(vd));
    g_variant_unref(vd);

    /* 3. 数组 */
    GVariantBuilder builder;
    g_variant_builder_init(&builder, G_VARIANT_TYPE("ai"));
    g_variant_builder_add(&builder, "i", 1);
    g_variant_builder_add(&builder, "i", 2);
    g_variant_builder_add(&builder, "i", 3);
    GVariant *arr = g_variant_builder_end(&builder);
    g_print("[数组] 类型=%s 大小=%d\n", g_variant_get_type_string(arr), g_variant_n_children(arr));

    /* 遍历数组 */
    GVariantIter iter;
    g_variant_iter_init(&iter, arr);
    gint val;
    g_print("[数组遍历] ");
    while (g_variant_iter_loop(&iter, "i", &val)) {
        g_print("%d ", val);
    }
    g_print("\n");
    g_variant_unref(arr);

    /* 4. 字典 */
    GVariantBuilder dbuilder;
    g_variant_builder_init(&dbuilder, G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add(&dbuilder, "{sv}", "name", g_variant_new_string("GLib"));
    g_variant_builder_add(&dbuilder, "{sv}", "version", g_variant_new_double(2.88));
    GVariant *dict = g_variant_builder_end(&dbuilder);
    g_print("[字典] 类型=%s 子项数=%d\n", g_variant_get_type_string(dict), g_variant_n_children(dict));

    /* 查找字典 */
    GVariant *lookup = g_variant_lookup_value(dict, "name", NULL);
    if (lookup) {
        g_print("[字典查找] name=%s\n", g_variant_get_string(lookup, NULL));
        g_variant_unref(lookup);
    }
    g_variant_unref(dict);

    /* 5. 元组 */
    GVariant *tuple = g_variant_new("(sis)", "hello", 42, "world");
    gchar *s1, *s2;
    gint i1;
    g_variant_get(tuple, "(sis)", &s1, &i1, &s2);
    g_print("[元组] s1=%s i1=%d s2=%s\n", s1, i1, s2);
    g_free(s1);
    g_free(s2);
    g_variant_unref(tuple);

    /* 6. 字符串序列化 */
    GVariant *ser = g_variant_new("(si)", "GLib", 42);
    gchar *json = g_variant_print(ser, TRUE);
    g_print("[序列化] %s\n", json);
    g_free(json);
    g_variant_unref(ser);

    /* 7. 可能类型（Maybe） */
    GVariant *maybe = g_variant_new("ms", g_variant_new_string("value"));
    g_print("[maybe] 类型=%s\n", g_variant_get_type_string(maybe));
    g_variant_unref(maybe);

    GVariant *null_maybe = g_variant_new("ms", NULL);
    g_print("[maybe null] 类型=%s\n", g_variant_get_type_string(null_maybe));
    g_variant_unref(null_maybe);

    /* 8. GVariant 类型字符串判断 */
    g_print("[类型检查] is_container=%s\n",
            g_variant_is_container(g_variant_new("()")) ? "是" : "否");
    g_print("[类型检查] is_of_type=%s\n",
            g_variant_is_of_type(g_variant_new_int32(1), G_VARIANT_TYPE("i")) ? "是" : "否");
}

/* ============================================================
 * 第五篇 GIO 输入输出与网络篇
 * ============================================================ */

/* 第 25 章：GIO 基础与流体系 */
void chapter_25_gio_basics_and_streams(void)
{
    g_print("\n=== 第 25 章 GIO 基础与流体系 ===\n");

    /* 1. GMemoryInputStream 内存输入流 */
    const gchar *input = "Hello GIO Stream";
    GInputStream *istream = g_memory_input_stream_new_from_data(input, -1, NULL);
    gchar buf[64] = { 0 };
    gssize n = g_input_stream_read(istream, buf, sizeof(buf) - 1, NULL, NULL);
    g_print("[MemoryInputStream] 读取: %s (字节数: %d)\n", buf, (gint)n);
    g_object_unref(istream);

    /* 2. GMemoryOutputStream 内存输出流 */
    GOutputStream *ostream = g_memory_output_stream_new_resizable();
    const gchar *out = "GLib output stream";
    g_output_stream_write_all(ostream, out, strlen(out), NULL, NULL, NULL);
    gchar *data = (gchar *)g_memory_output_stream_get_data(G_MEMORY_OUTPUT_STREAM(ostream));
    g_print("[MemoryOutputStream] 内容: %s\n", data);
    g_object_unref(ostream);

    /* 3. GDataInputStream 数据输入流 */
    GInputStream *mem_in = g_memory_input_stream_new_from_data("line1\nline2\n", -1, NULL);
    GDataInputStream *data_in = g_data_input_stream_new(mem_in);
    gchar *line1 = g_data_input_stream_read_line_utf8(data_in, NULL, NULL, NULL);
    gchar *line2 = g_data_input_stream_read_line_utf8(data_in, NULL, NULL, NULL);
    g_print("[DataInputStream] line1=%s line2=%s\n", line1 ? line1 : "(null)", line2 ? line2 : "(null)");
    g_free(line1);
    g_free(line2);
    g_object_unref(data_in);
    g_object_unref(mem_in);

    /* 4. GDataOutputStream 数据输出流 */
    GOutputStream *mem_out = g_memory_output_stream_new_resizable();
    GDataOutputStream *data_out = g_data_output_stream_new(mem_out);
    g_data_output_stream_put_string(data_out, "Hello ", NULL, NULL);
    g_data_output_stream_put_int32(data_out, 42, NULL, NULL);
    g_data_output_stream_put_byte(data_out, '\n', NULL, NULL);
    g_print("[DataOutputStream] 大小=%" G_GSIZE_FORMAT "\n",
            g_memory_output_stream_get_size(G_MEMORY_OUTPUT_STREAM(mem_out)));
    g_object_unref(data_out);
    g_object_unref(mem_out);

    /* 5. 流的 close */
    GInputStream *close_stream = g_memory_input_stream_new_from_data("test", -1, NULL);
    g_input_stream_close(close_stream, NULL, NULL);
    g_print("[stream close] 已关闭: %s\n",
            g_input_stream_is_closed(close_stream) ? "是" : "否");
    g_object_unref(close_stream);

    /* 6. GBufferedInputStream 缓冲输入流 */
    GInputStream *base = g_memory_input_stream_new_from_data("buffered data", -1, NULL);
    GBufferedInputStream *buf_stream = G_BUFFERED_INPUT_STREAM(
        g_buffered_input_stream_new(base));
    g_buffered_input_stream_set_buffer_size(buf_stream, 1024);
    g_print("[BufferedInputStream] 缓冲区大小=%u\n",
            g_buffered_input_stream_get_buffer_size(buf_stream));
    g_object_unref(buf_stream);
    g_object_unref(base);
}

/* 第 26 章：文件系统操作 */
void chapter_26_filesystem_operations(void)
{
    g_print("\n=== 第 26 章 文件系统操作 ===\n");
    GError *error = NULL;

    /* 1. 创建 GFile */
    GFile *file = g_file_new_for_path("demo.txt");
    g_print("[GFile] 路径=%s\n", g_file_peek_path(file));

    /* 2. 写入文件 */
    if (g_file_replace_contents(file, "GLib GFile demo\n", strlen("GLib GFile demo\n"),
                                NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, &error)) {
        g_print("[写入] 文件写入成功\n");

        /* 3. 获取文件路径和 URI */
        gchar *path = g_file_get_path(file);
        gchar *uri = g_file_get_uri(file);
        gchar *basename = g_file_get_basename(file);
        gchar *dirname = g_file_get_parent(file) ? g_file_get_path(g_file_get_parent(file)) : g_strdup("(无)");
        g_print("[路径] path=%s\n", path);
        g_print("[路径] uri=%s\n", uri);
        g_print("[路径] basename=%s dirname=%s\n", basename, dirname);
        g_free(path);
        g_free(uri);
        g_free(basename);
        g_free(dirname);

        /* 4. 文件信息查询 */
        GFileInfo *info = g_file_query_info(file,
            G_FILE_ATTRIBUTE_STANDARD_SIZE "," G_FILE_ATTRIBUTE_STANDARD_TYPE "," G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE,
            G_FILE_QUERY_INFO_NONE, NULL, NULL);
        if (info) {
            goffset size = g_file_info_get_size(info);
            GFileType ftype = g_file_info_get_file_type(info);
            const gchar *ctype = g_file_info_get_content_type(info);
            g_print("[FileInfo] 大小=%" G_GOFFSET_FORMAT "\n", size);
            g_print("[FileInfo] 类型=%d (1=常规 2=目录)\n", ftype);
            g_print("[FileInfo] content_type=%s\n", ctype ? ctype : "(null)");
            g_object_unref(info);
        }

        /* 5. 读取文件 */
        gchar *contents = NULL;
        gsize len = 0;
        if (g_file_load_contents(file, NULL, &contents, &len, NULL, NULL)) {
            g_print("[读取] 内容=%s长度=%u\n", contents, (guint)len);
            g_free(contents);
        }

        /* 6. 检查文件存在 */
        gboolean exists = g_file_query_exists(file, NULL);
        g_print("[存在] %s\n", exists ? "是" : "否");

        /* 7. 复制文件 */
        GFile *copy = g_file_new_for_path("demo_copy.txt");
        if (g_file_copy(file, copy, G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, &error)) {
            g_print("[复制] demo.txt -> demo_copy.txt 成功\n");
        } else {
            g_print("[复制] 失败: %s\n", error->message);
            g_clear_error(&error);
        }

        /* 8. 删除复制的文件 */
        if (g_file_delete(copy, NULL, &error)) {
            g_print("[删除] demo_copy.txt 成功\n");
        } else {
            g_print("[删除] 失败: %s\n", error->message);
            g_clear_error(&error);
        }
        g_object_unref(copy);
    } else {
        g_print("[写入] 失败: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 9. 目录操作 */
    GFile *dir = g_file_new_for_path("test_dir");
    if (g_file_make_directory(dir, NULL, &error)) {
        g_print("[目录] test_dir 创建成功\n");
    } else {
        g_print("[目录] 创建失败（可能已存在）: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 10. 枚举目录 */
    GFileEnumerator *enumerator = g_file_enumerate_children(
        g_file_new_for_path("."),
        G_FILE_ATTRIBUTE_STANDARD_NAME,
        G_FILE_QUERY_INFO_NONE, NULL, NULL);
    if (enumerator) {
        g_print("[枚举] 当前目录文件:\n");
        guint count = 0;
        GFileInfo *fi;
        while ((fi = g_file_enumerator_next_file(enumerator, NULL, NULL)) && count < 5) {
            g_print("  %s\n", g_file_info_get_name(fi));
            g_object_unref(fi);
            count++;
        }
        g_object_unref(enumerator);
    }

    g_object_unref(file);
    g_object_unref(dir);
}

/* 第 27 章：异步 IO 编程模型 */
void read_async_callback(GObject *source, GAsyncResult *res, gpointer user_data)
{
    GFile *file = G_FILE(source);
    GError *error = NULL;
    gchar *contents = NULL;
    gsize len = 0;

    if (g_file_load_contents_finish(file, res, &contents, &len, NULL, &error)) {
        g_print("[异步读取] 内容: %s", contents);
        g_free(contents);
    } else {
        g_print("[异步读取] 失败: %s\n", error->message);
        g_clear_error(&error);
    }
    g_main_loop_quit((GMainLoop *)user_data);
}

gboolean async_timeout_callback(gpointer data)
{
    g_print("[异步超时] 1秒已过\n");
    return G_SOURCE_REMOVE;
}

void chapter_27_async_io(void)
{
    g_print("\n=== 第 27 章 异步 IO 编程模型 ===\n");

    /* 1. 异步读取文件 */
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    GCancellable *cancellable = g_cancellable_new();
    GFile *file = g_file_new_for_path("demo.txt");

    g_print("[异步] 开始异步读取 demo.txt...\n");
    g_file_load_contents_async(file, cancellable, read_async_callback, loop);

    /* 2. 同时添加超时源 */
    g_timeout_add_seconds(1, async_timeout_callback, NULL);

    /* 3. 运行主循环等待异步完成 */
    g_main_loop_run(loop);

    /* 4. GCancellable 说明 */
    g_print("[Cancellable] 是否已取消=%s\n",
            g_cancellable_is_cancelled(cancellable) ? "是" : "否");
    g_print("[Cancellable] 可在异步操作中调用 g_cancellable_cancel 取消\n");

    g_object_unref(cancellable);
    g_object_unref(file);
    g_main_loop_unref(loop);

    /* 5. 同步读取对比 */
    g_print("[同步] 对比同步读取...\n");
    GFile *file2 = g_file_new_for_path("demo.txt");
    gchar *contents = NULL;
    gsize len = 0;
    if (g_file_load_contents(file2, NULL, &contents, &len, NULL, NULL)) {
        g_print("[同步读取] 长度=%u\n", (guint)len);
        g_free(contents);
    }
    g_object_unref(file2);

    /* 6. 异步写入说明 */
    g_print("[异步写入] 使用 g_file_replace_async / g_file_replace_contents_async\n");

    /* 7. GTask 说明（自定义异步任务） */
    g_print("[GTask] 自定义异步任务通过 g_task_new / g_task_return_* 实现\n");
}

/* 第 28 章：网络编程基础 */
void chapter_28_network_basics(void)
{
    g_print("\n=== 第 28 章 网络编程基础 ===\n");

    /* 1. GInetAddress 回环地址 */
    GInetAddress *loopback = g_inet_address_new_loopback(G_SOCKET_FAMILY_IPV4);
    gchar *str = g_inet_address_to_string(loopback);
    g_print("[IPv4 回环] %s\n", str);
    g_free(str);
    g_object_unref(loopback);

    /* 2. IPv6 回环地址 */
    GInetAddress *loopback6 = g_inet_address_new_loopback(G_SOCKET_FAMILY_IPV6);
    gchar *str6 = g_inet_address_to_string(loopback6);
    g_print("[IPv6 回环] %s\n", str6);
    g_free(str6);
    g_object_unref(loopback6);

    /* 3. 从字符串创建地址 */
    GInetAddress *addr = g_inet_address_new_from_string("192.168.1.1");
    if (addr) {
        gchar *s = g_inet_address_to_string(addr);
        g_print("[字符串创建] %s\n", s);
        g_free(s);
        g_object_unref(addr);
    }

    /* 4. GSocketAddress 套接字地址 */
    GInetAddress *any = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
    GSocketAddress *saddr = g_inet_socket_address_new(any, 8080);
    g_print("[SocketAddress] 端口=%d\n",
            g_inet_socket_address_get_port(G_INET_SOCKET_ADDRESS(saddr)));
    g_object_unref(saddr);
    g_object_unref(any);

    /* 5. 地址族 */
    g_print("[地址族] G_SOCKET_FAMILY_IPV4=%d G_SOCKET_FAMILY_IPV6=%d\n",
            G_SOCKET_FAMILY_IPV4, G_SOCKET_FAMILY_IPV6);

    /* 6. Socket 类型 */
    g_print("[Socket类型] G_SOCKET_TYPE_STREAM=%d (TCP)\n", G_SOCKET_TYPE_STREAM);
    g_print("[Socket类型] G_SOCKET_TYPE_DATAGRAM=%d (UDP)\n", G_SOCKET_TYPE_DATAGRAM);

    /* 7. 协议 */
    g_print("[协议] G_SOCKET_PROTOCOL_TCP=%d\n", G_SOCKET_PROTOCOL_TCP);
    g_print("[协议] G_SOCKET_PROTOCOL_UDP=%d\n", G_SOCKET_PROTOCOL_UDP);

    /* 8. 创建 Socket */
    GError *error = NULL;
    GSocket *sock = g_socket_new(G_SOCKET_FAMILY_IPV4,
                                  G_SOCKET_TYPE_STREAM,
                                  G_SOCKET_PROTOCOL_TCP,
                                  &error);
    if (sock) {
        g_print("[Socket] 创建成功\n");
        g_socket_set_blocking(sock, FALSE);
        g_print("[Socket] 阻塞模式=%s\n", g_socket_get_blocking(sock) ? "阻塞" : "非阻塞");
        g_object_unref(sock);
    } else {
        g_print("[Socket] 创建失败: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 9. GResolver 域名解析 */
    GResolver *resolver = g_resolver_get_default();
    if (resolver) {
        GList *addrs = g_resolver_lookup_by_name(resolver, "localhost", NULL, NULL);
        if (addrs) {
            GInetAddress *first = G_INET_ADDRESS(addrs->data);
            gchar *resolved = g_inet_address_to_string(first);
            g_print("[DNS解析] localhost -> %s\n", resolved);
            g_free(resolved);
            g_resolver_free_addresses(addrs);
        }
        g_object_unref(resolver);
    }
}

/* 第 29 章：网络客户端与服务端 */
void chapter_29_network_client_server(void)
{
    g_print("\n=== 第 29 章 网络客户端与服务端 ===\n");

    /* 1. GSocketService 服务端 */
    GSocketService *service = g_socket_service_new();
    GError *error = NULL;

    /* 2. 添加监听端口（使用固定端口便于演示） */
    guint16 listen_port = 12345;
    if (g_socket_listener_add_inet_port(G_SOCKET_LISTENER(service), listen_port, NULL, &error)) {
        g_print("[服务端] 监听端口 %d 添加成功\n", listen_port);
    } else {
        g_print("[服务端] 监听端口添加失败: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 3. 说明监听端口 */
    g_print("[服务端] 配置监听端口=%d\n", listen_port);

    /* 4. 启动服务（不实际运行循环） */
    g_socket_service_start(service);
    g_print("[服务端] 服务已启动\n");

    /* 5. GSocketClient 客户端 */
    GSocketClient *client = g_socket_client_new();
    g_socket_client_set_timeout(client, 5);
    g_print("[客户端] 超时设置=%d秒\n", g_socket_client_get_timeout(client));

    /* 6. 客户端连接配置 */
    g_socket_client_set_family(client, G_SOCKET_FAMILY_IPV4);
    g_socket_client_set_protocol(client, G_SOCKET_PROTOCOL_TCP);
    g_socket_client_set_socket_type(client, G_SOCKET_TYPE_STREAM);
    g_print("[客户端] 已配置 TCP/IPv4\n");

    /* 7. 停止服务 */
    g_socket_service_stop(service);
    g_print("[服务端] 服务已停止\n");

    /* 8. GSocketConnection 说明 */
    g_print("[GSocketConnection] 表示已建立的连接\n");
    g_print("[GSocketConnection] 可通过 g_socket_connection_get_socket 获取底层 Socket\n");

    /* 9. GSocketListener 说明 */
    g_print("[GSocketListener] 可同时监听多个端口\n");
    g_print("[GSocketListener] g_socket_listener_accept_async 异步接受连接\n");

    /* 10. 连接信号说明 */
    g_print("[信号] GSocketService::incoming 新连接到来时触发\n");
    g_print("[信号] 回调返回 TRUE 可阻止默认处理\n");

    g_object_unref(service);
    g_object_unref(client);
}

/* 第 30 章：D-Bus IPC 基础 */
void chapter_30_dbus_basics(void)
{
    g_print("\n=== 第 30 章 D-Bus IPC 基础 ===\n");
    GError *error = NULL;

    /* 1. 连接会话总线 */
    GDBusConnection *conn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
    if (conn) {
        g_print("[会话总线] 连接成功\n");
        g_print("[会话总线] 唯一名: %s\n", g_dbus_connection_get_unique_name(conn));
        g_print("[会话总线] 是否关闭: %s\n",
                g_dbus_connection_is_closed(conn) ? "是" : "否");

        /* 2. 总线类型说明 */
        g_print("[总线类型] G_BUS_TYPE_SESSION=%d (会话)\n", G_BUS_TYPE_SESSION);
        g_print("[总线类型] G_BUS_TYPE_SYSTEM=%d (系统)\n", G_BUS_TYPE_SYSTEM);
        g_print("[总线类型] G_BUS_TYPE_STARTER=%d (启动者)\n", G_BUS_TYPE_STARTER);

        /* 3. 连接标志说明 */
        g_print("[标志] G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT\n");
        g_print("[标志] G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION\n");

        /* 4. 发送消息示例（ListNames） */
        GVariant *result = g_dbus_connection_call_sync(
            conn,
            "org.freedesktop.DBus",      /* 总线名 */
            "/org/freedesktop/DBus",     /* 对象路径 */
            "org.freedesktop.DBus",      /* 接口名 */
            "ListNames",                 /* 方法名 */
            NULL,                        /* 参数 */
            G_VARIANT_TYPE("(as)"),      /* 返回类型 */
            G_DBUS_CALL_FLAGS_NONE,
            -1,                          /* 超时 */
            NULL, &error);

        if (result) {
            GVariantIter iter;
            g_variant_get(result, "(as)", &iter);
            gchar *name;
            guint count = 0;
            while (g_variant_iter_loop(&iter, "s", &name)) {
                if (count < 3) {
                    g_print("[总线名] %s\n", name);
                }
                count++;
            }
            g_print("[总线名] 共 %d 个已注册名称（仅显示前3个）\n", count);
            g_variant_unref(result);
        } else {
            g_print("[D-Bus 调用] 失败: %s\n", error->message);
            g_clear_error(&error);
        }

        g_object_unref(conn);
    } else {
        g_print("[会话总线] 连接失败: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 5. 连接系统总线 */
    GDBusConnection *sys_conn = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    if (sys_conn) {
        g_print("[系统总线] 连接成功\n");
        g_print("[系统总线] 唯一名: %s\n", g_dbus_connection_get_unique_name(sys_conn));
        g_object_unref(sys_conn);
    } else {
        g_print("[系统总线] 连接失败: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 6. D-Bus 概念说明 */
    g_print("[D-Bus 概念]\n");
    g_print("  Bus Name: 如 org.freedesktop.DBus\n");
    g_print("  Object Path: 如 /org/freedesktop/DBus\n");
    g_print("  Interface: 如 org.freedesktop.DBus\n");
    g_print("  Method: 如 ListNames\n");
    g_print("  Signal: 事件通知机制\n");
}

/* 第 31 章：D-Bus 高级编程 */
void chapter_31_dbus_advanced(void)
{
    g_print("\n=== 第 31 章 D-Bus 高级编程 ===\n");
    g_print("建议使用 g_dbus_proxy_new_sync / g_dbus_proxy_call_sync。\n");
    g_print("需要目标服务已注册在 D-Bus 上。\n");

    /* 1. 获取会话总线连接 */
    GError *error = NULL;
    GDBusConnection *conn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
    if (conn) {
        /* 2. 创建 D-Bus 代理：代理封装了对远端对象的访问 */
        /* 参数：连接、标志、 introspection XML、总线名、对象路径、接口名 */
        GDBusProxy *proxy = g_dbus_proxy_new_sync(conn,
                                                  G_DBUS_PROXY_FLAGS_NONE,
                                                  NULL,
                                                  "org.freedesktop.DBus",
                                                  "/org/freedesktop/DBus",
                                                  "org.freedesktop.DBus",
                                                  NULL, &error);
        if (proxy) {
            g_print("[代理] 创建成功，目标=%s\n", g_dbus_proxy_get_name(proxy));

            /* 3. 通过代理调用方法（同步方式） */
            GVariant *result = g_dbus_proxy_call_sync(proxy,
                                                       "GetId",
                                                       NULL,
                                                       G_DBUS_CALL_FLAGS_NONE,
                                                       -1,
                                                       NULL,
                                                       &error);
            if (result) {
                /* GetId 返回一个字符串 */
                const gchar *id;
                g_variant_get(result, "(&s)", &id);
                g_print("[GetId] 总线 ID=%s\n", id);
                g_variant_unref(result);
            } else {
                g_print("[方法调用] 失败: %s\n", error->message);
                g_clear_error(&error);
            }

            /* 4. 获取接口信息 */
            GDBusInterfaceInfo *info = g_dbus_proxy_get_interface_info(proxy);
            if (info) {
                g_print("[接口信息] 名称=%s\n", info ? info->name : "(null)");
            }

            g_object_unref(proxy);
        } else {
            g_print("[代理] 创建失败: %s\n", error->message);
            g_clear_error(&error);
        }
        g_object_unref(conn);
    } else {
        g_print("[D-Bus] 连接失败: %s\n", error->message);
        g_clear_error(&error);
    }

    /* 5. D-Bus 高级概念说明 */
    g_print("[高级概念]\n");
    g_print("  - GDBusProxy: 代理模式，缓存属性值，可监听信号\n");
    g_print("  - GDBusInterfaceVTable: 虚表模式，直接处理方法调用\n");
    g_print("  - GDBusObjectManager: 管理多个对象\n");
    g_print("  - g_dbus_connection_register_object: 注册服务端对象\n");
    g_print("  - g_dbus_connection_emit_signal: 发送信号\n");
}

/* 第 32 章：应用与资源管理 */
void chapter_32_application_and_resources(void)
{
    g_print("\n=== 第 32 章 应用与资源管理 ===\n");

    /* 1. GApplication 应用入口 */
    /* GApplication 提供应用唯一性、激活、命令行处理等 */
    GApplication *app = g_application_new("com.example.glibtutorial", G_APPLICATION_DEFAULT_FLAGS);
    g_print("[GApplication] ID=%s\n", g_application_get_application_id(app));

    /* 2. 应用标志说明 */
    g_print("[标志] G_APPLICATION_DEFAULT_FLAGS=%d (默认)\n", G_APPLICATION_DEFAULT_FLAGS);
    g_print("[标志] G_APPLICATION_IS_SERVICE=%d (服务模式)\n", G_APPLICATION_IS_SERVICE);
    g_print("[标志] G_APPLICATION_HANDLES_COMMAND_LINE=%d (处理命令行)\n",
            G_APPLICATION_HANDLES_COMMAND_LINE);

    /* 3. 检查应用 ID */
    const gchar *app_id = g_application_get_application_id(app);
    g_print("[应用 ID] %s (反向域名格式)\n", app_id);

    /* 4. GResource 资源系统说明 */
    /* GResource 用于将文件打包到二进制中 */
    g_print("[GResource] 使用流程:\n");
    g_print("  1. 编写 .gresource.xml 资源描述文件\n");
    g_print("  2. 用 glib-compile-resources 编译为 .c 或二进制\n");
    g_print("  3. 代码中用 g_resource_load() 加载\n");
    g_print("  4. 用 g_resources_lookup_data() 访问资源\n");

    /* 5. 资源路径格式 */
    g_print("[资源路径] 格式: /com/example/app/icon.png\n");

    g_object_unref(app);
}

/* 第 33 章：应用配置管理 GSettings */
void chapter_33_gsettings(void)
{
    g_print("\n=== 第 33 章 应用配置管理 GSettings ===\n");
    g_print("GSettings 需要已安装的 schema；\n");
    g_print("示例：g_settings_new(\"org.gnome.desktop.interface\")。\n");

    /* 1. 获取默认 schema 源 */
    /* Schema 源是已安装的 .gschema.xml 文件的集合 */
    GSettingsSchemaSource *source = g_settings_schema_source_get_default();
    if (source) {
        g_print("[schema 源] 已找到默认源\n");

        /* 2. 查找特定 schema */
        GSettingsSchema *schema = g_settings_schema_source_lookup(source,
            "org.gnome.desktop.interface", TRUE);
        if (schema) {
            g_print("[schema] 找到: org.gnome.desktop.interface\n");

            /* 3. 列出 schema 的键 */
            gchar **keys = g_settings_schema_list_keys(schema);
            if (keys) {
                g_print("[键列表] ");
                for (guint i = 0; keys[i] && i < 5; i++) {
                    g_print("%s ", keys[i]);
                }
                g_print("...\n");
                g_strfreev(keys);
            }

            /* 4. 创建 GSettings 并读取值 */
            GSettings *settings = g_settings_new_full(schema, NULL, NULL);
            if (settings) {
                /* 读取字符串值 */
                gchar *theme = g_settings_get_string(settings, "gtk-theme");
                g_print("[读取] gtk-theme=%s\n", theme ? theme : "(null)");
                g_free(theme);

                g_object_unref(settings);
            }

            g_settings_schema_unref(schema);
        } else {
            g_print("[schema] 未找到（常见情况）\n");
        }
    } else {
        g_print("[schema 源] 没有默认源\n");
    }

    /* 5. GSettings 特性说明 */
    g_print("[特性]\n");
    g_print("  - 基于 key-value 的配置存储\n");
    g_print("  - 支持 change 信号监听键变化\n");
    g_print("  - 支持延迟应用（g_settings_delay）\n");
    g_print("  - 支持 GSettingsBind 绑定到 GObject 属性\n");
}

/* ============================================================
 * 第六篇 高级特性与工程实践篇
 * ============================================================ */

/* 第 34 章：跨平台适配与兼容性 */
void chapter_34_cross_platform_adaptation(void)
{
    g_print("\n=== 第 34 章 跨平台适配与兼容性 ===\n");

    /* 1. 操作系统信息 */
    const gchar *os_name = g_get_os_info(G_OS_INFO_KEY_NAME);
    const gchar *os_ver = g_get_os_info(G_OS_INFO_KEY_VERSION);
    g_print("[系统] %s %s\n", os_name ? os_name : "unknown", os_ver ? os_ver : "");

    /* 2. 路径分隔符 */
    /* Windows 用 '\'，Unix 用 '/' */
    g_print("[路径分隔符] '%c'\n", G_DIR_SEPARATOR);
    /* 环境变量 PATH 的分隔符：Windows 用 ';'，Unix 用 ':' */
    g_print("[搜索路径分隔符] '%c'\n", G_SEARCHPATH_SEPARATOR);

    /* 3. 标准目录 */
    g_print("[用户数据目录] %s\n", g_get_user_data_dir());
    g_print("[用户配置目录] %s\n", g_get_user_config_dir());
    g_print("[用户缓存目录] %s\n", g_get_user_cache_dir());
    g_print("[系统临时目录] %s\n", g_get_tmp_dir());

    /* 4. 路径构建（跨平台安全） */
    /* g_build_filename 自动使用正确的分隔符 */
    gchar *path = g_build_filename("usr", "local", "bin", "program", NULL);
    g_print("[构建路径] %s\n", path);
    g_free(path);

    /* 5. 环境变量跨平台处理 */
    const gchar *home = g_getenv("HOME");
    if (!home) home = g_getenv("USERPROFILE"); /* Windows */
    g_print("[HOME] %s\n", home ? home : "(null)");

    /* 6. 换行符处理 */
    g_print("[换行符] G_DIR_SEPARATOR 用于路径\n");
    g_print("[换行符] 文本换行 Unix:'\\n' Windows:'\\r\\n'\n");
}

/* 第 35 章：性能优化与调试技巧 */
void chapter_35_performance_and_debugging(void)
{
    GTimer *timer = g_timer_new();
    GHashTable *ht = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    g_print("\n=== 第 35 章 性能优化与调试技巧 ===\n");

    /* 1. 插入性能测试 */
    g_timer_start(timer);
    for (gint i = 0; i < 10000; i++) {
        gchar *key = g_strdup_printf("key%d", i);
        g_hash_table_insert(ht, key, GINT_TO_POINTER(i));
    }
    g_timer_stop(timer);
    g_print("[插入] 10000 项耗时: %f 秒\n", g_timer_elapsed(timer, NULL));

    /* 2. 查找性能测试 */
    g_timer_start(timer);
    for (gint i = 0; i < 10000; i++) {
        gchar *key = g_strdup_printf("key%d", i);
        g_hash_table_lookup(ht, key);
        g_free(key);
    }
    g_timer_stop(timer);
    g_print("[查找] 10000 项耗时: %f 秒\n", g_timer_elapsed(timer, NULL));

    /* 3. slice 分配器 vs malloc 性能对比 */
    g_timer_start(timer);
    for (gint i = 0; i < 10000; i++) {
        gpointer p = g_slice_alloc(sizeof(gint));
        g_slice_free1(sizeof(gint), p);
    }
    g_timer_stop(timer);
    g_print("[slice] 10000 次分配/释放: %f 秒\n", g_timer_elapsed(timer, NULL));

    g_timer_start(timer);
    for (gint i = 0; i < 10000; i++) {
        gpointer p = g_malloc(sizeof(gint));
        g_free(p);
    }
    g_timer_stop(timer);
    g_print("[malloc] 10000 次分配/释放: %f 秒\n", g_timer_elapsed(timer, NULL));

    /* 4. 调试技巧说明 */
    g_print("[调试技巧]\n");
    g_print("  - GTimer: 精确计时\n");
    g_print("  - g_get_monotonic_time: 单调时间戳\n");
    g_print("  - g_log_structured: 结构化日志带字段\n");
    g_print("  - g_debug: 调试日志（需设置 G_MESSAGES_DEBUG）\n");
    g_print("  - 环境变量 G_DEBUG=fatal-warnings 将警告转为致命\n");
    g_print("  - 环境变量 G_SLICE=always-malloc 用于 valgrind\n");

    g_hash_table_destroy(ht);
    g_timer_destroy(timer);
}

/* 第 36 章：自定义扩展与组件封装 */
void chapter_36_custom_extensions(void)
{
    g_print("\n=== 第 36 章 自定义扩展与组件封装 ===\n");

    /* 1. 自定义 Boxed 类型 */
    /* Boxed 类型用于包装不透明数据，提供复制和释放函数 */
    GType boxed_type = g_boxed_type_register_static("MyBoxedInt",
                                           (GBoxedCopyFunc)g_strdup,
                                           (GBoxedFreeFunc)g_free);
    g_print("[Boxed] 类型注册成功: %s (id=%lu)\n", g_type_name(boxed_type), boxed_type);

    /* 2. 自定义枚举类型 */
    /* 枚举类型用于注册可被 GObject 属性系统使用的枚举 */
    GType enum_type = g_enum_register_static("MyEnum",
        (GEnumValue[]) {
            { 0, "MY_ENUM_ZERO", "zero" },
            { 1, "MY_ENUM_ONE",  "one" },
            { 2, "MY_ENUM_TWO",  "two" },
            { 0, NULL, NULL }
        });
    g_print("[Enum] 类型注册成功: %s (id=%lu)\n", g_type_name(enum_type), enum_type);

    /* 3. 查询枚举值 */
    GEnumClass *enum_class = g_type_class_ref(enum_type);
    if (enum_class) {
        g_print("[Enum] 值数量=%u\n", enum_class->n_values);
        for (guint i = 0; i < enum_class->n_values; i++) {
            g_print("  %s = %d\n", enum_class->values[i].value_name,
                    enum_class->values[i].value);
        }
        g_type_class_unref(enum_class);
    }

    /* 4. 自定义标志类型 */
    GType flags_type = g_flags_register_static("MyFlags",
        (GFlagsValue[]) {
            { 1, "MY_FLAG_READ",  "read" },
            { 2, "MY_FLAG_WRITE", "write" },
            { 4, "MY_FLAG_EXEC",  "exec" },
            { 0, NULL, NULL }
        });
    g_print("[Flags] 类型注册成功: %s (id=%lu)\n", g_type_name(flags_type), flags_type);

    /* 5. 组件封装建议 */
    g_print("[封装建议]\n");
    g_print("  - 用 G_DECLARE_FINAL_TYPE 声明最终类型\n");
    g_print("  - 用 G_DECLARE_DERIVABLE_TYPE 声明可派生类型\n");
    g_print("  - 私有数据用 G_PRIVATE_FIELD 或 G_ADD_PRIVATE\n");
    g_print("  - 属性用 g_param_spec_* + g_object_class_install_property\n");
    g_print("  - 信号用 g_signal_new 注册\n");
}

/* 第 37 章：测试框架 GTest */
void test_case_addition(void)
{
    /* 基本断言宏 */
    g_assert_cmpint(1 + 1, ==, 2);          /* 整数比较 */
    g_assert_cmpint(10 > 5, ==, TRUE);       /* 布尔断言 */
}

void test_case_string(void)
{
    /* 字符串断言 */
    g_assert_cmpstr("GLib", ==, "GLib");     /* 相等 */
    g_assert_cmpstr("abc", !=, "xyz");       /* 不等 */
}

void test_case_float(void)
{
    /* 浮点数断言（注意精度问题） */
    g_assert_cmpfloat(0.1 + 0.2, !=, 0.3);   /* 浮点精度示例 */
    g_assert_cmpfloat(1.0 + 1.0, ==, 2.0);   /* 精确相等 */
}

void test_case_pointer(void)
{
    /* 指针断言 */
    g_assert_null(NULL);                     /* 断言为 NULL */
    g_assert_nonnull(g_strdup("x"));         /* 断言非 NULL */
    g_free(g_strdup("x"));                   /* 释放避免泄漏 */
}

void chapter_37_gtest_framework(void)
{
    g_print("\n=== 第 37 章 测试框架 GTest ===\n");

    /* 1. 初始化测试框架 */
    /* g_test_init 会解析 --verbose 等命令行参数 */
    g_test_init(&g_argc, &g_argv, NULL);

    /* 2. 设置测试行为 */
    g_test_set_nonfatal_assertions();  /* 断言失败不终止 */
    g_test_timer_start();              /* 启动计时器 */

    /* 3. 添加测试用例 */
    /* 路径格式: /模块/用例名 */
    g_test_add_func("/math/addition", test_case_addition);
    g_test_add_func("/string/compare", test_case_string);
    g_test_add_func("/float/precision", test_case_float);
    g_test_add_func("/pointer/null", test_case_pointer);

    /* 4. 运行测试 */
    gint ret = g_test_run();
    g_print("[结果] 退出码=%d (0=全部通过)\n", ret);

    /* 5. 测试时间 */
    g_print("[计时] 测试耗时: %.6f 秒\n", g_test_timer_elapsed());

    /* 6. 断言宏说明 */
    g_print("[断言宏]\n");
    g_print("  g_assert(expr)               断言为真\n");
    g_print("  g_assert_cmpint(a, op, b)    整数比较 (==, !=, <, >, <=, >=)\n");
    g_print("  g_assert_cmpstr(a, op, b)    字符串比较\n");
    g_print("  g_assert_cmpfloat(a, op, b)  浮点比较\n");
    g_print("  g_assert_null(ptr)           断言为 NULL\n");
    g_print("  g_assert_nonnull(ptr)        断言非 NULL\n");
    g_print("  g_assert_true(expr)          断言为 TRUE\n");
    g_print("  g_assert_false(expr)         断言为 FALSE\n");
}

/* 第 38 章：综合项目实战 */
void chapter_38_comprehensive_project(void)
{
    g_print("\n=== 第 38 章 综合项目实战 ===\n");
    g_print("综合运用 GLib 各模块构建一个简单的任务管理系统\n");

    /* === 模块 1: 配置管理（GKeyFile） === */
    g_print("\n[1] 配置管理\n");
    GKeyFile *kf = g_key_file_new();
    g_key_file_set_string(kf, "settings", "name", "TaskManager");
    g_key_file_set_integer(kf, "settings", "timeout", 30);
    g_key_file_set_double(kf, "settings", "ratio", 0.75);
    g_key_file_set_boolean(kf, "settings", "debug", TRUE);

    gchar *config_name = g_key_file_get_string(kf, "settings", "name", NULL);
    gint config_timeout = g_key_file_get_integer(kf, "settings", "timeout", NULL);
    g_print("  配置: name=%s timeout=%d\n", config_name, config_timeout);
    g_free(config_name);

    /* === 模块 2: 任务列表（GList + 动态分配） === */
    g_print("\n[2] 任务列表\n");
    GList *tasks = NULL;
    tasks = g_list_append(tasks, g_strdup("init"));
    tasks = g_list_append(tasks, g_strdup("run"));
    tasks = g_list_append(tasks, g_strdup("cleanup"));

    guint task_num = 0;
    for (GList *l = tasks; l; l = l->next) {
        g_print("  任务[%u]: %s\n", task_num++, (gchar *)l->data);
    }
    g_list_free_full(tasks, g_free);

    /* === 模块 3: 状态表（GHashTable） === */
    g_print("\n[3] 状态表\n");
    GHashTable *status = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(status, "init", "done");
    g_hash_table_insert(status, "run", "running");
    g_hash_table_insert(status, "cleanup", "pending");

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, status);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("  %s -> %s\n", (gchar *)key, (gchar *)value);
    }
    g_hash_table_destroy(status);

    /* === 模块 4: 日志记录（GDateTime + 日志） === */
    g_print("\n[4] 日志记录\n");
    GDateTime *now = g_date_time_new_now_local();
    gchar *timestamp = g_date_time_format(now, "%H:%M:%S");
    g_message("[综合项目] %s 任务系统启动", timestamp);
    g_print("  时间戳: %s\n", timestamp);
    g_free(timestamp);
    g_date_time_unref(now);

    /* === 模块 5: 文件 I/O（GFile） === */
    g_print("\n[5] 文件 I/O\n");
    GFile *file = g_file_new_for_path("demo.txt");
    gchar *contents = NULL;
    gsize len = 0;
    if (g_file_load_contents(file, NULL, &contents, &len, NULL, NULL)) {
        g_print("  文件大小: %u 字节\n", (guint)len);
        g_print("  文件内容: %s", contents);
        g_free(contents);
    } else {
        g_print("  文件读取失败\n");
    }
    g_object_unref(file);

    /* === 模块 6: 随机数据（GRand） === */
    g_print("\n[6] 随机数据\n");
    GRand *rng = g_rand_new_with_seed(42);
    g_print("  随机数: %d %d %d\n",
            g_rand_int_range(rng, 0, 100),
            g_rand_int_range(rng, 0, 100),
            g_rand_int_range(rng, 0, 100));
    g_rand_free(rng);

    /* === 模块 7: GVariant 数据序列化 === */
    g_print("\n[7] 数据序列化\n");
    GVariant *data = g_variant_new("(sia{sv})",
                                    "TaskManager",
                                    3,
                                    NULL);
    gchar *serialized = g_variant_print(data, TRUE);
    g_print("  序列化: %s\n", serialized);
    g_free(serialized);
    g_variant_unref(data);

    g_key_file_free(kf);
    g_print("\n[综合项目] 示例结束\n");
}

/* ============================================================
 * main：依次调用所有章节的教学方法
 * ============================================================ */
int main(int argc, char *argv[])
{
    g_argc = argc;
    g_argv = argv;

    chapter_01_glib_overview();
    chapter_02_basic_types_and_macros();
    chapter_03_memory_management();
    chapter_04_strings_and_text();
    chapter_05_linear_data_structures();
    chapter_06_associative_and_set_structures();
    chapter_07_date_time_and_timer();
    chapter_08_commandline_and_config();
    chapter_09_utility_functions();
    chapter_10_logging_and_error_handling();
    chapter_11_main_event_loop();
    chapter_12_thread_basics();
    chapter_13_thread_synchronization();
    chapter_14_concurrency_and_thread_pool();
    chapter_15_subprocess_management();
    chapter_16_modules_and_plugins();
    chapter_17_gtype_basics();
    chapter_18_gobject_basics();
    chapter_19_properties();
    chapter_20_signals();
    chapter_21_subclassing();
    chapter_22_ginterface();
    chapter_23_gobject_advanced();
    chapter_24_gvariant();
    chapter_25_gio_basics_and_streams();
    chapter_26_filesystem_operations();
    chapter_27_async_io();
    chapter_28_network_basics();
    chapter_29_network_client_server();
    chapter_30_dbus_basics();
    chapter_31_dbus_advanced();
    chapter_32_application_and_resources();
    chapter_33_gsettings();
    chapter_34_cross_platform_adaptation();
    chapter_35_performance_and_debugging();
    chapter_36_custom_extensions();
    chapter_37_gtest_framework();
    chapter_38_comprehensive_project();
    return 0;
}
