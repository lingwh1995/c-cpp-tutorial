#include <stdio.h>
#include <glib.h>

/**
 * GLib - GNOME 基础库
 *
 * 1. 官网
 *    https://developer.gnome.org/glib/
 * 2. 功能
 *    数据结构、实用函数、事件循环、线程等
 * 3. 普通方式安装
 *    - windows(打开 MSYS2 UCRT64 的终端，执行以下命令)
 *       pacman -Syu                             # 更新系统
 *       pacman -S mingw-w64-ucrt-x86_64-glib2   # 安装glib2
 *       pacman -Qs glib2                        # 检查是否安装成功
 *    - linux
 *       sudo apt-get update
 *       sudo apt-get install libglib2.0-dev
 */
// 打印链表数据的辅助函数
void print_list_item(gpointer data, gpointer user_data) {
    g_print(" -> %s", (char*)data);
}

int main() {
    // ==========================================
    // 1. 测试 GLib 基本类型与打印
    // ==========================================
    g_print("=== 1. GLib Base Types Test ===\n");
    gint my_int = 42;
    gchar* my_str = "Hello UCRT64 & GLib!";
    g_print("Integer: %d, String: %s\n\n", my_int, my_str);

    // ==========================================
    // 2. 测试 动态数组 (GArray)
    // ==========================================
    g_print("=== 2. GArray Test ===\n");
    // 创建一个存储 int 类型的动态数组，清零并设置边界安全检查
    GArray *array = g_array_new(FALSE, FALSE, sizeof(gint));

    // 牢记：g_array_append_val 必须传入变量（左值）
    gint val1 = 10, val2 = 20, val3 = 30;
    g_array_append_val(array, val1);
    g_array_append_val(array, val2);
    g_array_append_val(array, val3);

    g_print("GArray length: %d\n", array->len);
    for (guint i = 0; i < array->len; i++) {
        // 使用 g_array_index 宏安全读取数据
        g_print("  Index %d: %d\n", i, g_array_index(array, gint, i));
    }

    // 释放数组内存
    g_array_free(array, TRUE);
    g_print("\n");

    // ==========================================
    // 3. 测试 双向链表 (GList)
    // ==========================================
    g_print("=== 3. GList Test ===\n");
    GList *list = NULL;

    // 往链表中追加字符串数据
    list = g_list_append(list, "Apple");
    list = g_list_append(list, "Banana");
    list = g_list_append(list, "Cherry");

    g_print("GList current items:");
    // 遍历链表
    g_list_foreach(list, print_list_item, NULL);
    g_print("\n");

    // 查找测试
    GList *found = g_list_find_custom(list, "Banana", (GCompareFunc)g_strcmp0);
    if (found) {
        g_print("  Find custom success: %s exists in list.\n", (char*)found->data);
    }

    // 释放整个链表
    g_list_free(list);
    g_print("==================================\n");

    return 0;
}
