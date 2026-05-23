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
 * 第1章：GLib 基础数据类型
 */
void chapter1_basic_types_test()
{
    g_print("--- 第1章：GLib 基础数据类型 ---\n\n");

    // 1.1 基本数据类型（官方文档：glib-Basic-Types.html）
    g_print("1.1 基本数据类型\n");
    g_print("gboolean: TRUE=%d, FALSE=%d\n", TRUE, FALSE);
    g_print("gchar: %zu bytes\n", sizeof(gchar));
    g_print("gint: %zu bytes, 范围: %d ~ %d\n", sizeof(gint), G_MININT, G_MAXINT);
    g_print("guint: %zu bytes, 最大值: %u\n", sizeof(guint), G_MAXUINT);
    g_print("glong: %zu bytes, 范围: %ld ~ %ld\n", sizeof(glong), G_MINLONG, G_MAXLONG);
    g_print("gulong: %zu bytes, 最大值: %lu\n", sizeof(gulong), G_MAXULONG);
    g_print("gint64: %zu bytes, 范围: %" G_GINT64_FORMAT " ~ %" G_GINT64_FORMAT "\n",
            sizeof(gint64), G_MININT64, G_MAXINT64);
    g_print("guint64: %zu bytes, 最大值: %" G_GUINT64_FORMAT "\n",
            sizeof(guint64), G_MAXUINT64);
    g_print("gsize: %zu bytes, 最大值: %zu\n", sizeof(gsize), G_MAXSIZE);
    g_print("gssize: %zu bytes, 范围: %zd ~ %zd\n\n", sizeof(gssize), G_MINSSIZE, G_MAXSSIZE);

    // 1.2 指针类型
    g_print("1.2 指针类型\n");
    gpointer ptr = GINT_TO_POINTER(42);
    g_print("GINT_TO_POINTER(42) = %p\n", ptr);
    g_print("GPOINTER_TO_INT(ptr) = %d\n\n", GPOINTER_TO_INT(ptr));

    // 1.3 宏定义
    g_print("1.3 常用宏\n");
    g_print("G_STRUCT_OFFSET(struct stat, st_size) = %zu\n", G_STRUCT_OFFSET(struct stat, st_size));

    gint sample_array[] = {1, 2, 3, 4, 5};
    g_print("G_N_ELEMENTS(sample_array) = %zu\n", G_N_ELEMENTS(sample_array));

    // G_LIKELY 和 G_UNLIKELY 是编译器优化提示，通常用于条件判断
    if (G_LIKELY(1))
    {
        g_print("G_LIKELY(1): 分支很可能执行\n");
    }
    if (G_UNLIKELY(0))
    {
        g_print("G_UNLIKELY(0): 分支不太可能执行\n");
    }
    g_print("\n");
}

/**
 * 第2章：内存管理
 */
void chapter2_memory_management_test()
{
    g_print("--- 第2章：内存管理 ---\n\n");

    // 2.1 基本内存分配（官方文档：glib-Memory-Allocation.html）
    g_print("2.1 基本内存分配\n");
    gpointer mem1 = g_malloc(100);
    g_print("g_malloc(100) = %p\n", mem1);
    g_free(mem1);  // 安全：g_free(NULL) 什么也不做

    gpointer mem2 = g_malloc0(100);  // 分配并清零
    g_print("g_malloc0(100) = %p, 第一个字节: %d\n", mem2, ((guchar*)mem2)[0]);
    g_free(mem2);

    gpointer mem3 = g_realloc(NULL, 100);  // 等价于 g_malloc(100)
    g_print("g_realloc(NULL, 100) = %p\n", mem3);
    gpointer mem4 = g_realloc(mem3, 200);  // 重新分配
    g_print("g_realloc(mem3, 200) = %p\n", mem4);
    g_free(mem4);

    // 2.2 对齐内存分配（GLib 2.72+）
    g_print("\n2.2 对齐内存分配\n");
    gpointer aligned_mem = g_aligned_alloc(1, 100, 16);  // 1块×100字节，16字节对齐
    g_print("g_aligned_alloc(1, 100, 16) = %p\n", aligned_mem);
    g_aligned_free(aligned_mem);  // 必须使用对应的释放函数

    // 2.3 临时内存分配（栈分配）
    g_print("\n2.3 临时内存分配\n");
    gchar* stack_mem = g_alloca(100);  // 从栈分配，自动释放
    g_print("g_alloca(100) = %p\n", stack_mem);

    // 2.4 内存切片分配器（高效小内存分配）
    g_print("\n2.4 内存切片分配器\n");
    gpointer slice = g_slice_alloc(64);
    g_print("g_slice_alloc(64) = %p\n", slice);
    g_slice_free1(64, slice);
}

/**
 * 第3章：字符串处理
 */
void chapter3_glib_string_handling_test()
{
    g_print("\n--- 第3章：字符串处理 ---\n\n");

    // 3.1 字符串操作（官方文档：glib-Strings.html）
    g_print("3.1 基本字符串操作\n");
    const gchar* str1 = "Hello";
    const gchar* str2 = "World";

    gchar* concat = g_strconcat(str1, ", ", str2, "!", NULL);
    g_print("g_strconcat: %s\n", concat);
    g_free(concat);

    gchar* dup = g_strdup(str1);
    g_print("g_strdup: %s\n", dup);
    g_free(dup);

    gchar* substr = g_strndup(str1, 3);
    g_print("g_strndup(3): %s\n", substr);
    g_free(substr);

    gchar* upper = g_ascii_strup(str1, -1);
    g_print("g_ascii_strup: %s\n", upper);
    g_free(upper);

    gchar* lower = g_ascii_strdown(str1, -1);
    g_print("g_ascii_strdown: %s\n", lower);
    g_free(lower);

    // 3.2 安全字符串比较
    g_print("\n3.2 安全字符串比较\n");
    g_print("g_strcmp0(\"apple\", \"banana\"): %d\n", g_strcmp0("apple", "banana"));
    g_print("g_strcmp0(NULL, \"\"): %d (NULL视为空字符串)\n", g_strcmp0(NULL, ""));
    g_print("g_ascii_strcasecmp(\"Apple\", \"apple\"): %d\n", g_ascii_strcasecmp("Apple", "apple"));

    // 3.3 UTF-8 字符串处理（官方文档：glib-Unicode-Manipulation.html）
    g_print("\n3.3 UTF-8 字符串处理\n");
    const gchar* utf8_str = "你好，世界！";
    g_print("UTF-8字符串: %s\n", utf8_str);
    g_print("字节长度(strlen): %zu\n", strlen(utf8_str));
    g_print("字符长度(g_utf8_strlen): %ld\n", g_utf8_strlen(utf8_str, -1));
    g_print("是否有效UTF-8: %s\n", g_utf8_validate(utf8_str, -1, NULL) ? "是" : "否");

    // 3.4 GString 动态字符串（官方文档：glib-Strings.html#GString）
    g_print("\n3.4 GString 动态字符串\n");
    GString* gstr = g_string_new("Hello");
    g_string_append(gstr, ", ");
    g_string_append(gstr, "GLib!");
    g_print("GString内容: %s\n", gstr->str);
    g_print("GString长度: %zu\n", gstr->len);
    g_print("GString分配大小: %zu\n", gstr->allocated_len);

    g_string_prepend(gstr, "Wow! ");
    g_print("prepend后: %s\n", gstr->str);

    g_string_insert(gstr, 5, " amazing");
    g_print("insert后: %s\n", gstr->str);

    g_string_printf(gstr, "格式化: %d, %s", 42, "test");
    g_print("printf后: %s\n", gstr->str);

    g_string_free(gstr, TRUE);  // TRUE表示同时释放字符串数据
}

/**
 * 第4章：数据结构
 */
void chapter4_data_structures_test()
{
    g_print("\n--- 第4章：数据结构 ---\n\n");

    // 4.1 单链表 GList（官方文档：glib-Doubly-Linked-Lists.html）
    g_print("4.1 单链表 GList\n");
    GList* list = NULL;
    list = g_list_append(list, "apple");
    list = g_list_append(list, "banana");
    list = g_list_append(list, "cherry");

    g_print("链表长度: %u\n", g_list_length(list));
    g_print("第一个元素: %s\n", (gchar*)g_list_first(list)->data);
    g_print("最后一个元素: %s\n", (gchar*)g_list_last(list)->data);
    g_print("索引1的元素: %s\n", (gchar*)g_list_nth_data(list, 1));

    // 遍历链表
    g_print("遍历链表: ");
    for (GList* l = list; l != NULL; l = l->next)
    {
        g_print("%s ", (gchar*)l->data);
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

    g_list_free(list);  // 只释放链表节点，不释放数据

    // 4.2 指针数组 GPtrArray（官方文档：glib-Pointer-Arrays.html）
    g_print("\n4.2 指针数组 GPtrArray\n");
    GPtrArray* ptr_array = g_ptr_array_new();
    g_ptr_array_add(ptr_array, g_strdup("first"));
    g_ptr_array_add(ptr_array, g_strdup("second"));
    g_ptr_array_add(ptr_array, g_strdup("third"));

    g_print("数组长度: %u\n", ptr_array->len);
    g_print("索引1的元素: %s\n", (gchar*)g_ptr_array_index(ptr_array, 1));

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

    // 4.3 哈希表 GHashTable（官方文档：glib-Hash-Tables.html）
    g_print("\n4.3 哈希表 GHashTable\n");
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(hash, "apple", "red");
    g_hash_table_insert(hash, "banana", "yellow");
    g_hash_table_insert(hash, "cherry", "red");

    g_print("哈希表大小: %u\n", g_hash_table_size(hash));
    g_print("apple的颜色: %s\n", (gchar*)g_hash_table_lookup(hash, "apple"));
    g_print("grape是否存在: %s\n", g_hash_table_contains(hash, "grape") ? "是" : "否");

    // 遍历哈希表
    g_print("遍历哈希表: ");
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, hash);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_print("%s=%s ", (gchar*)key, (gchar*)value);
    }
    g_print("\n");

    g_hash_table_destroy(hash);  // 释放哈希表

    // 4.4 队列 GQueue（官方文档：glib-Double-Ended-Queues.html）
    g_print("\n4.4 队列 GQueue\n");
    GQueue* queue = g_queue_new();
    g_queue_push_tail(queue, "first");
    g_queue_push_tail(queue, "second");
    g_queue_push_tail(queue, "third");

    g_print("队列长度: %u\n", g_queue_get_length(queue));
    g_print("队头元素: %s\n", (gchar*)g_queue_peek_head(queue));
    g_print("出队: %s\n", (gchar*)g_queue_pop_head(queue));
    g_print("出队后长度: %u\n", g_queue_get_length(queue));

    g_queue_free(queue);
}

/**
 * 第5章：GObject 类型系统基础
 */
// 定义一个简单的 GObject 派生类
#define MY_TYPE_OBJECT (my_object_get_type())
#define MY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_OBJECT, MyObject))
#define MY_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_OBJECT))

typedef struct _MyObject MyObject;
typedef struct _MyObjectClass MyObjectClass;

struct _MyObject {
    GObject parent_instance;
    gint value;
};

struct _MyObjectClass {
    GObjectClass parent_class;
};

GType my_object_get_type(void);

static void my_object_class_init(MyObjectClass* klass)
{
    // 类初始化代码
}

static void my_object_init(MyObject* self)
{
    self->value = 0;
}

G_DEFINE_TYPE(MyObject, my_object, G_TYPE_OBJECT)

// 公共方法
void my_object_set_value(MyObject* self, gint value)
{
    g_return_if_fail(MY_IS_OBJECT(self));
    self->value = value;
}

gint my_object_get_value(MyObject* self)
{
    g_return_val_if_fail(MY_IS_OBJECT(self), 0);
    return self->value;
}

void chapter5_gobject_basics_test()
{
    g_print("\n--- 第5章：GObject 类型系统基础 ---\n\n");

    // 5.1 GObject 基本概念（官方文档：gobject-Type-Information.html）
    g_print("5.1 GObject 基本概念\n");
    g_print("G_TYPE_OBJECT: %s\n", g_type_name(G_TYPE_OBJECT));
    g_print("MY_TYPE_OBJECT: %s\n", g_type_name(MY_TYPE_OBJECT));
    g_print("类型是否有效: %s\n", g_type_is_a(MY_TYPE_OBJECT, G_TYPE_OBJECT) ? "是" : "否");

    // 5.2 创建和销毁对象（官方文档：gobject-The-Base-Object-Type.html）
    g_print("\n5.2 创建和销毁对象\n");
    MyObject* obj = g_object_new(MY_TYPE_OBJECT, NULL);
    g_print("创建对象: %p\n", obj);

    my_object_set_value(obj, 42);
    g_print("对象值: %d\n", my_object_get_value(obj));

    g_object_unref(obj);  // 释放对象
    g_print("对象已释放\n");

    // 5.3 引用计数
    g_print("\n5.3 引用计数\n");
    MyObject* obj2 = g_object_new(MY_TYPE_OBJECT, NULL);
    g_print("初始引用计数: %d\n", (int)obj2->parent_instance.ref_count);

    g_object_ref(obj2);
    g_print("ref后引用计数: %d\n", (int)obj2->parent_instance.ref_count);

    g_object_unref(obj2);
    g_print("unref后引用计数: %d\n", (int)obj2->parent_instance.ref_count);

    g_object_unref(obj2);  // 引用计数变为0，对象被销毁
}

/**
 * 第6章：GObject 属性
 */
// 定义带属性的 GObject 类
#define MY_TYPE_PROPERTY_OBJECT (my_property_object_get_type())
#define MY_PROPERTY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_PROPERTY_OBJECT, MyPropertyObject))
#define MY_IS_PROPERTY_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_PROPERTY_OBJECT))

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

static void my_property_object_set_property(GObject* object, guint property_id,
                                           const GValue* value, GParamSpec* pspec)
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

static void my_property_object_get_property(GObject* object, guint property_id,
                                           GValue* value, GParamSpec* pspec)
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

    // 6.1 属性基本操作（官方文档：gobject-GObject-Properties.html）
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
 * 第7章：GObject 信号
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

void chapter7_gobject_signals_test()
{
    g_print("\n--- 第7章：GObject 信号 ---\n\n");

    // 7.1 信号基本操作（官方文档：gobject-Signals.html）
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
 * 第8章：GObject 高级特性
 */
void chapter8_gobject_advanced_test()
{
    g_print("\n--- 第8章：GObject 高级特性 ---\n\n");

    // 8.1 接口（官方文档：gobject-Interfaces.html）
    g_print("8.1 接口\n");
    g_print("G_TYPE_INTERFACE: %s\n", g_type_name(G_TYPE_INTERFACE));
    g_print("G_TYPE_INITIALLY_UNOWNED: %s\n", g_type_name(G_TYPE_INITIALLY_UNOWNED));

    // 8.2 弱引用
    g_print("\n8.2 弱引用\n");
    GObject* obj = g_object_new(G_TYPE_OBJECT, NULL);
    gpointer weak_data = GINT_TO_POINTER(123);

    g_object_weak_ref(obj, (GWeakNotify)g_print, "对象被销毁了！\n");
    g_object_unref(obj);  // 触发弱引用回调
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

    // 9.1 GFile 基本操作（官方文档：gio-GFile.html）
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

    // 10.1 主循环基础（官方文档：gio-The-Main-Event-Loop.html）
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

    // 11.1 网络地址解析（官方文档：gio-GSocketAddress.html）
    g_print("11.1 网络地址解析\n");

    GError* error = NULL;
    GResolver* resolver = g_resolver_get_default();

    g_print("解析 www.example.com...\n");
    GList* addresses = g_resolver_lookup_by_name(resolver, "www.example.com", NULL, &error);

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

    // 12.1 异步操作（官方文档：gio-Asynchronous-IO.html）
    g_print("12.1 异步操作\n");
    g_print("GIO 支持异步文件操作、网络操作等\n");
    g_print("异步操作通过 GAsyncResult 和回调函数实现\n");

    // 12.2 数据流（官方文档：gio-IO-Streams.html）
    g_print("\n12.2 数据流\n");
    g_print("GInputStream 和 GOutputStream 是所有 I/O 流的基类\n");
    g_print("支持文件流、网络流、内存流等\n");
}

#if 0
#endif
int main()
{
    g_print("----------------------------------------------\n");
    g_print("GLib 渐进式教学示例代码\n");
    g_print("严格遵循 GLib 2.80+ 官方文档\n");
    g_print("----------------------------------------------\n\n");

    // 第1-4章：GLib 核心
    chapter1_basic_types_test();
    chapter2_memory_management_test();
    chapter3_glib_string_handling_test();
    chapter4_data_structures_test();

    // 第5-8章：GObject 系统
    chapter5_gobject_basics_test();
    chapter6_gobject_properties_test();
    chapter6_gobject_properties_test();
    chapter7_gobject_signals_test();
    chapter8_gobject_advanced_test();

    // 第9-12章：GIO 库
    chapter9_gio_file_operations_test();
    chapter10_gio_main_loop_test();
    chapter11_gio_networking_test();
    chapter12_gio_advanced_test();


    g_print("\n---------------------------------------------=\n");
    g_print("所有示例运行完成！\n");
    g_print("---------------------------------------------=\n");
    return 0;
}