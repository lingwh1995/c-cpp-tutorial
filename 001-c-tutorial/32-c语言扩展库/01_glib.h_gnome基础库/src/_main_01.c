//
// /* ============================================================
//  * 第2章：内存管理示例
//  * 演示 g_malloc()、g_free()、g_new()、g_try_malloc() 等函数
//  * 参考：GLib Reference Manual - Memory Allocation
//  * ============================================================ */
// void chapter2_memory_management_test(void)
// {
//     g_print("\n=== 第2章：内存管理示例 ===\n");
//
//     /* g_malloc() / g_free() - 基本内存分配与释放
//      * g_malloc 在分配失败时直接终止程序（不同于 malloc 返回 NULL） */
//     gint *int_ptr = (gint *)g_malloc(sizeof(gint));
//     *int_ptr = 100;
//     g_print("g_malloc: *int_ptr = %d\n", *int_ptr);
//     g_free(int_ptr);
//
//     /* g_malloc0() - 分配并初始化为零 */
//     gint *zero_ptr = (gint *)g_malloc0(sizeof(gint) * 5);
//     g_print("g_malloc0: 初始化为零的数组 = [%d, %d, %d, %d, %d]\n",
//             zero_ptr[0], zero_ptr[1], zero_ptr[2], zero_ptr[3], zero_ptr[4]);
//     g_free(zero_ptr);
//
//     /* g_new() - 类型安全的内存分配宏
//      * 等价于 (type *)g_malloc(n * sizeof(type)) */
//     gint *arr = g_new(gint, 3);
//     arr[0] = 10;
//     arr[1] = 20;
//     arr[2] = 30;
//     g_print("g_new: arr = [%d, %d, %d]\n", arr[0], arr[1], arr[2]);
//     g_free(arr);
//
//     /* g_new0() - 类型安全的零初始化分配 */
//     gint *zero_arr = g_new0(gint, 3);
//     g_print("g_new0: zero_arr = [%d, %d, %d]\n",
//             zero_arr[0], zero_arr[1], zero_arr[2]);
//     g_free(zero_arr);
//
//     /* g_try_malloc() - 分配失败时返回 NULL（不终止程序） */
//     gpointer try_ptr = g_try_malloc(1024);
//     if (try_ptr != NULL) {
//         g_print("g_try_malloc: 成功分配 1024 字节\n");
//         g_free(try_ptr);
//     } else {
//         g_print("g_try_malloc: 分配失败\n");
//     }
//
//     /* g_try_malloc0() - 尝试分配并清零 */
//     gpointer try0_ptr = g_try_malloc0(512);
//     if (try0_ptr != NULL) {
//         g_print("g_try_malloc0: 成功分配并清零 512 字节\n");
//         g_free(try0_ptr);
//     }
//
//     /* g_realloc() - 重新分配内存 */
//     gint *realloc_ptr = g_new(gint, 2);
//     realloc_ptr[0] = 1;
//     realloc_ptr[1] = 2;
//     realloc_ptr = (gint *)g_realloc(realloc_ptr, sizeof(gint) * 4);
//     realloc_ptr[2] = 3;
//     realloc_ptr[3] = 4;
//     g_print("g_realloc: 扩展后 = [%d, %d, %d, %d]\n",
//             realloc_ptr[0], realloc_ptr[1], realloc_ptr[2], realloc_ptr[3]);
//     g_free(realloc_ptr);
//
//     /* g_steal_pointer() - 转移指针所有权并置空原指针 */
//     gchar *original = g_strdup("hello");
//     gchar *stolen = g_steal_pointer(&original);
//     g_print("g_steal_pointer: stolen = %s, original = %s\n",
//             stolen, original ? original : "(null)");
//     g_free(stolen);
//
//     /* g_clear_pointer() - 清除指针并释放资源 */
//     gint *clear_ptr = g_new(gint, 1);
//     *clear_ptr = 99;
//     g_clear_pointer(&clear_ptr, g_free);
//     g_print("g_clear_pointer: clear_ptr = %s\n",
//             clear_ptr ? "非NULL" : "NULL");
// }
//
// /* ============================================================
//  * 第3章：字符串处理示例
//  * 展示 g_strdup()、g_strconcat()、g_strcmp0()、g_string_append() 等
//  * 参考：GLib Reference Manual - String Utility Functions
//  * ============================================================ */
// void chapter3_string_handling_test(void)
// {
//     g_print("\n=== 第3章：字符串处理示例 ===\n");
//
//     /* g_strdup() - 复制字符串 */
//     const gchar *src = "GLib Tutorial";
//     gchar *dup = g_strdup(src);
//     g_print("g_strdup: dup = %s\n", dup);
//     g_free(dup);
//
//     /* g_strndup() - 复制字符串的前 n 个字符 */
//     const gchar *long_str = "Hello, GLib World!";
//     gchar *ndup = g_strndup(long_str, 5);
//     g_print("g_strndup: ndup = %s\n", ndup);
//     g_free(ndup);
//
//     /* g_strconcat() - 连接多个字符串，以 NULL 结尾 */
//     gchar *concat = g_strconcat("Hello", ", ", "GLib", "!", NULL);
//     g_print("g_strconcat: concat = %s\n", concat);
//     g_free(concat);
//
//     /* g_strdup_printf() - 格式化字符串并分配内存 */
//     gchar *formatted = g_strdup_printf("值: %d, 名称: %s", 42, "test");
//     g_print("g_strdup_printf: formatted = %s\n", formatted);
//     g_free(formatted);
//
//     /* g_strcmp0() - 安全的字符串比较（处理 NULL 指针） */
//     const gchar *s1 = "apple";
//     const gchar *s2 = "banana";
//     gint cmp_result = g_strcmp0(s1, s2);
//     g_print("g_strcmp0(\"%s\", \"%s\") = %d (%s)\n",
//             s1, s2, cmp_result, cmp_result < 0 ? "s1 < s2" : cmp_result > 0 ? "s1 > s2" : "相等");
//     /* NULL 安全比较 */
//     gint null_cmp = g_strcmp0(NULL, "hello");
//     g_print("g_strcmp0(NULL, \"hello\") = %d (NULL 被视为空字符串)\n", null_cmp);
//
//     /* g_str_equal() / g_str_hash() - 用于 GHashTable 的字符串比较/哈希 */
//     const gchar *ha = "key";
//     const gchar *hb = "key";
//     g_print("g_str_equal: %s\n", g_str_equal(ha, hb) ? "相等" : "不等");
//     g_print("g_str_hash: %u\n", (guint)g_str_hash(ha));
//
//     /* g_strsplit() / g_strfreev() - 字符串分割与释放 */
//     gchar **parts = g_strsplit("one:two:three", ":", -1);
//     g_print("g_strsplit: ");
//     for (gint i = 0; parts[i] != NULL; i++) {
//         g_print("[%s] ", parts[i]);
//     }
//     g_print("\n");
//     g_strfreev(parts);
//
//     /* g_strjoinv() - 用分隔符连接字符串数组 */
//     const gchar *tokens[] = {"red", "green", "blue", NULL};
//     gchar *joined = g_strjoinv(", ", (gchar **)tokens);
//     g_print("g_strjoinv: joined = %s\n", joined);
//     g_free(joined);
//
//     /* g_strstrip() - 去除首尾空白字符（原地修改） */
//     gchar *strip_str = g_strdup("  hello world  ");
//     g_strstrip(strip_str);
//     g_print("g_strstrip: \"%s\"\n", strip_str);
//     g_free(strip_str);
//
//     /* g_str_has_prefix() / g_str_has_suffix() - 前缀/后缀检查 */
//     const gchar *path = "/usr/local/bin/app";
//     g_print("g_str_has_prefix(\"/usr\"): %s\n",
//             g_str_has_prefix(path, "/usr") ? "是" : "否");
//     g_print("g_str_has_suffix(\"app\"): %s\n",
//             g_str_has_suffix(path, "app") ? "是" : "否");
//
//     /* GString - 动态字符串 */
//     GString *gstr = g_string_new("Hello");
//     g_string_append(gstr, ", GLib");
//     g_string_prepend(gstr, ">> ");
//     g_string_append_printf(gstr, " (长度: %u)", gstr->len);
//     g_print("GString: %s\n", gstr->str);
//     g_string_free(gstr, TRUE);
// }
//
// /* ============================================================
//  * 第4章：数据结构示例
//  * 演示 GList、GSList、GHashTable、GArray 的创建、操作及销毁
//  * 参考：GLib Reference Manual - Doubly-Linked Lists / Hash Tables / Arrays
//  * ============================================================ */
// void chapter4_data_structures_test(void)
// {
//     g_print("\n=== 第4章：数据结构示例 ===\n");
//
//     /* --- GSList: 单向链表 --- */
//     g_print("\n-- GSList 单向链表 --\n");
//     GSList *slist = NULL;
//     slist = g_slist_append(slist, "first");
//     slist = g_slist_append(slist, "second");
//     slist = g_slist_prepend(slist, "zero");
//     g_print("GSList 长度: %u\n", g_slist_length(slist));
//     g_print("GSList 内容: ");
//     for (GSList *iter = slist; iter != NULL; iter = iter->next) {
//         g_print("[%s] ", (gchar *)iter->data);
//     }
//     g_print("\n");
//     g_print("GSList 第2个元素: %s\n", (gchar *)g_slist_nth_data(slist, 1));
//     slist = g_slist_remove(slist, "second");
//     g_print("删除 \"second\" 后长度: %u\n", g_slist_length(slist));
//     g_slist_free(slist);
//
//     /* --- GList: 双向链表 --- */
//     g_print("\n-- GList 双向链表 --\n");
//     GList *list = NULL;
//     list = g_list_append(list, "alpha");
//     list = g_list_append(list, "beta");
//     list = g_list_prepend(list, "omega");
//     g_print("GList 长度: %u\n", g_list_length(list));
//     g_print("GList 正向遍历: ");
//     for (GList *iter = list; iter != NULL; iter = iter->next) {
//         g_print("[%s] ", (gchar *)iter->data);
//     }
//     g_print("\n");
//     /* 反向遍历需先定位到末尾 */
//     GList *last = g_list_last(list);
//     g_print("GList 反向遍历: ");
//     for (GList *iter = last; iter != NULL; iter = iter->prev) {
//         g_print("[%s] ", (gchar *)iter->data);
//     }
//     g_print("\n");
//     /* 排序 */
//     list = g_list_sort(list, (GCompareFunc)g_strcmp0);
//     g_print("GList 排序后: ");
//     for (GList *iter = list; iter != NULL; iter = iter->next) {
//         g_print("[%s] ", (gchar *)iter->data);
//     }
//     g_print("\n");
//     g_list_free(list);
//
//     /* --- GHashTable: 哈希表 --- */
//     g_print("\n-- GHashTable 哈希表 --\n");
//     GHashTable *ht = g_hash_table_new(g_str_hash, g_str_equal);
//     g_hash_table_insert(ht, g_strdup("name"), g_strdup("GLib"));
//     g_hash_table_insert(ht, g_strdup("version"), g_strdup("2.78"));
//     g_hash_table_insert(ht, g_strdup("type"), g_strdup("library"));
//     g_print("GHashTable 大小: %u\n", g_hash_table_size(ht));
//     g_print("查找 \"name\": %s\n", (gchar *)g_hash_table_lookup(ht, "name"));
//     g_print("包含 \"version\": %s\n",
//             g_hash_table_contains(ht, "version") ? "是" : "否");
//     /* 替换值 */
//     g_hash_table_replace(ht, g_strdup("version"), g_strdup("2.80"));
//     g_print("替换后 \"version\": %s\n", (gchar *)g_hash_table_lookup(ht, "version"));
//     /* 遍历 */
//     g_print("GHashTable 遍历: ");
//     GHashTableIter ht_iter;
//     gpointer ht_key, ht_value;
//     g_hash_table_iter_init(&ht_iter, ht);
//     while (g_hash_table_iter_next(&ht_iter, &ht_key, &ht_value)) {
//         g_print("[%s=%s] ", (gchar *)ht_key, (gchar *)ht_value);
//     }
//     g_print("\n");
//     /* 删除键 */
//     g_hash_table_remove(ht, "type");
//     g_print("删除 \"type\" 后大小: %u\n", g_hash_table_size(ht));
//     /* 使用 g_hash_table_new_full 自动释放键值内存 */
//     g_hash_table_destroy(ht);
//
//     /* --- GArray: 动态数组 --- */
//     g_print("\n-- GArray 动态数组 --\n");
//     GArray *arr = g_array_new(FALSE, FALSE, sizeof(gint));
//     gint val;
//     val = 10; g_array_append_val(arr, val);
//     val = 20; g_array_append_val(arr, val);
//     val = 30; g_array_append_val(arr, val);
//     g_print("GArray 长度: %u\n", arr->len);
//     g_print("GArray 内容: ");
//     for (guint i = 0; i < arr->len; i++) {
//         g_print("%d ", g_array_index(arr, gint, i));
//     }
//     g_print("\n");
//     /* 在指定位置插入 */
//     val = 15; g_array_insert_val(arr, 1, val);
//     g_print("插入后: ");
//     for (guint i = 0; i < arr->len; i++) {
//         g_print("%d ", g_array_index(arr, gint, i));
//     }
//     g_print("\n");
//     /* 移除元素 */
//     g_array_remove_index(arr, 2);
//     g_print("删除索引2后: ");
//     for (guint i = 0; i < arr->len; i++) {
//         g_print("%d ", g_array_index(arr, gint, i));
//     }
//     g_print("\n");
//     g_array_free(arr, TRUE);
// }
//
// /* ============================================================
//  * 第5章：类型系统示例
//  * 展示 GType 注册、类型检查和类型转换机制
//  * 参考：GObject Reference Manual - GType
//  * ============================================================ */
//
// /* 使用 G_DEFINE_TYPE 注册一个自定义类型 */
// #define MY_TYPE_BASIC (my_basic_get_type())
// G_DECLARE_FINAL_TYPE(MyBasic, my_basic, MY, BASIC, GObject)
//
// struct _MyBasic
// {
//     GObject parent_instance;
//     gint value;
// };
//
// G_DEFINE_TYPE(MyBasic, my_basic, G_TYPE_OBJECT)
//
// static void my_basic_class_init(MyBasicClass *klass)
// {
//     g_print("  MyBasic: 类初始化 (class_init)\n");
// }
//
// static void my_basic_init(MyBasic *self)
// {
//     self->value = 0;
//     g_print("  MyBasic: 实例初始化 (instance_init), value = %d\n", self->value);
// }
//
// void chapter5_type_system_test(void)
// {
//     g_print("\n=== 第5章：类型系统示例 ===\n");
//
//     /* 基本类型查询 */
//     g_print("G_TYPE_INT 的名称: %s\n", g_type_name(G_TYPE_INT));
//     g_print("G_TYPE_STRING 的名称: %s\n", g_type_name(G_TYPE_STRING));
//     g_print("G_TYPE_OBJECT 的名称: %s\n", g_type_name(G_TYPE_OBJECT));
//
//     /* 通过名称查找类型 */
//     GType t = g_type_from_name("gint");
//     g_print("g_type_from_name(\"gint\") = %lu\n", (gulong)t);
//     g_print("是否等于 G_TYPE_INT: %s\n", t == G_TYPE_INT ? "是" : "否");
//
//     /* 类型层级关系 */
//     g_print("G_TYPE_OBJECT 的父类型: %s\n",
//             g_type_name(g_type_parent(G_TYPE_OBJECT)));
//     g_print("G_TYPE_OBJECT 是否是 G_TYPE_FUNDAMENTAL: %s\n",
//             g_type_fundamental(G_TYPE_OBJECT) == G_TYPE_OBJECT ? "是" : "否");
//
//     /* 类型检查 */
//     g_print("G_TYPE_OBJECT 是接口吗: %s\n",
//             G_TYPE_IS_INTERFACE(G_TYPE_OBJECT) ? "是" : "否");
//     g_print("G_TYPE_OBJECT 是实例化类型吗: %s\n",
//             G_TYPE_IS_INSTANTIATABLE(G_TYPE_OBJECT) ? "是" : "否");
//     g_print("G_TYPE_OBJECT 是可派生的吗: %s\n",
//             G_TYPE_IS_DERIVABLE(G_TYPE_OBJECT) ? "是" : "否");
//
//     /* 自定义类型注册与检查 */
//     g_print("\n-- 自定义类型 MyBasic --\n");
//     GType my_type = MY_TYPE_BASIC;
//     g_print("MyBasic 类型名称: %s\n", g_type_name(my_type));
//     g_print("MyBasic 的父类型: %s\n", g_type_name(g_type_parent(my_type)));
//
//     /* 类型转换检查 */
//     g_print("MyBasic 是否派生自 GObject: %s\n",
//             g_type_is_a(my_type, G_TYPE_OBJECT) ? "是" : "否");
//
//     /* G_TYPE_CHECK_INSTANCE / G_TYPE_CHECK_CLASS */
//     MyBasic *obj = g_object_new(MY_TYPE_BASIC, NULL);
//     g_print("obj 是否是 GObject: %s\n",
//             G_IS_OBJECT(obj) ? "是" : "否");
//     g_print("obj 是否是 MyBasic: %s\n",
//             MY_IS_BASIC(obj) ? "是" : "否");
//
//     /* 类型转换 */
//     GObject *gobj = G_OBJECT(obj);
//     g_print("G_OBJECT(obj) 转换成功, 类型: %s\n",
//             G_OBJECT_TYPE_NAME(gobj));
//
//     /* G_TYPE_INSTANCE_GET_CLASS */
//     MyBasicClass *klass = G_TYPE_INSTANCE_GET_CLASS(obj, MY_TYPE_BASIC, MyBasicClass);
//     g_print("获取类结构体: %s\n", klass ? "成功" : "失败");
//
//     g_object_unref(obj);
//
//     /* 打印类型继承链 */
//     g_print("\n-- MyBasic 继承链 --\n");
//     GType current = my_type;
//     while (current != 0) {
//         g_print("  %s\n", g_type_name(current));
//         current = g_type_parent(current);
//     }
// }
//
// /* ============================================================
//  * 第6章：对象基础示例
//  * 演示 GObject 创建、初始化和销毁过程
//  * 参考：GObject Reference Manual - GObject
//  * ============================================================ */
//
// /* 定义带属性的 GObject 子类 */
// #define MY_TYPE_PERSON (my_person_get_type())
// G_DECLARE_FINAL_TYPE(MyPerson, my_person, MY, PERSON, GObject)
//
// struct _MyPerson
// {
//     GObject parent_instance;
//     gchar *name;
//     gint age;
// };
//
// enum
// {
//     PROP_PERSON_0,
//     PROP_PERSON_NAME,
//     PROP_PERSON_AGE,
//     N_PROP_PERSON
// };
//
// static GParamSpec *person_props[N_PROP_PERSON] = {NULL, };
//
// G_DEFINE_TYPE(MyPerson, my_person, G_TYPE_OBJECT)
//
// static void my_person_set_property(GObject *object, guint prop_id,
//                                    const GValue *value, GParamSpec *pspec)
// {
//     MyPerson *self = MY_PERSON(object);
//     switch (prop_id) {
//     case PROP_PERSON_NAME:
//         g_free(self->name);
//         self->name = g_value_dup_string(value);
//         break;
//     case PROP_PERSON_AGE:
//         self->age = g_value_get_int(value);
//         break;
//     default:
//         G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
//     }
// }
//
// static void my_person_get_property(GObject *object, guint prop_id,
//                                    GValue *value, GParamSpec *pspec)
// {
//     MyPerson *self = MY_PERSON(object);
//     switch (prop_id) {
//     case PROP_PERSON_NAME:
//         g_value_set_string(value, self->name);
//         break;
//     case PROP_PERSON_AGE:
//         g_value_set_int(value, self->age);
//         break;
//     default:
//         G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
//     }
// }
//
// static void my_person_dispose(GObject *object)
// {
//     MyPerson *self = MY_PERSON(object);
//     g_print("  MyPerson dispose: name = %s\n", self->name ? self->name : "(null)");
//     G_OBJECT_CLASS(my_person_parent_class)->dispose(object);
// }
//
// static void my_person_finalize(GObject *object)
// {
//     MyPerson *self = MY_PERSON(object);
//     g_free(self->name);
//     g_print("  MyPerson finalize: 对象已销毁\n");
//     G_OBJECT_CLASS(my_person_parent_class)->finalize(object);
// }
//
// static void my_person_class_init(MyPersonClass *klass)
// {
//     GObjectClass *gobj_class = G_OBJECT_CLASS(klass);
//     gobj_class->set_property = my_person_set_property;
//     gobj_class->get_property = my_person_get_property;
//     gobj_class->dispose = my_person_dispose;
//     gobj_class->finalize = my_person_finalize;
//
//     person_props[PROP_PERSON_NAME] =
//         g_param_spec_string("name", "Name", "Person's name", "",
//                             G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
//     person_props[PROP_PERSON_AGE] =
//         g_param_spec_int("age", "Age", "Person's age", 0, 200, 0,
//                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
//
//     g_object_class_install_properties(gobj_class, N_PROP_PERSON, person_props);
// }
//
// static void my_person_init(MyPerson *self)
// {
//     self->name = NULL;
//     self->age = 0;
//     g_print("  MyPerson 实例初始化\n");
// }
//
// void chapter6_object_basic_test(void)
// {
//     g_print("\n=== 第6章：对象基础示例 ===\n");
//
//     /* 使用 g_object_new 创建对象 */
//     g_print("-- 创建对象 --\n");
//     MyPerson *person = g_object_new(MY_TYPE_PERSON, NULL);
//     g_print("对象创建完成\n");
//
//     /* 使用构造属性创建对象 */
//     g_print("\n-- 使用构造属性创建 --\n");
//     MyPerson *person2 = g_object_new(MY_TYPE_PERSON,
//                                      "name", "Alice",
//                                      "age", 30,
//                                      NULL);
//     gchar *name = NULL;
//     gint age = 0;
//     g_object_get(person2, "name", &name, "age", &age, NULL);
//     g_print("person2: name = %s, age = %d\n", name, age);
//     g_free(name);
//
//     /* 设置属性 */
//     g_print("\n-- 设置属性 --\n");
//     g_object_set(person, "name", "Bob", "age", 25, NULL);
//     g_object_get(person, "name", &name, "age", &age, NULL);
//     g_print("person: name = %s, age = %d\n", name, age);
//     g_free(name);
//
//     /* 使用 g_object_set_property / g_object_get_property */
//     g_print("\n-- 使用 GValue 设置/获取属性 --\n");
//     GValue val = G_VALUE_INIT;
//     g_value_init(&val, G_TYPE_STRING);
//     g_value_set_string(&val, "Charlie");
//     g_object_set_property(G_OBJECT(person), "name", &val);
//     g_value_unset(&val);
//
//     g_value_init(&val, G_TYPE_STRING);
//     g_object_get_property(G_OBJECT(person), "name", &val);
//     g_print("通过 GValue 获取 name = %s\n", g_value_get_string(&val));
//     g_value_unset(&val);
//
//     /* 查询属性 */
//     g_print("\n-- 查询对象属性 --\n");
//     guint n_props = 0;
//     GParamSpec **props = g_object_class_list_properties(
//         G_OBJECT_GET_CLASS(person), &n_props);
//     g_print("MyPerson 有 %u 个属性:\n", n_props);
//     for (guint i = 0; i < n_props; i++) {
//         g_print("  - %s (%s)\n", props[i]->name, g_type_name(props[i]->value_type));
//     }
//     g_free(props);
//
//     /* 销毁对象 */
//     g_print("\n-- 销毁对象 --\n");
//     g_object_unref(person);
//     g_object_unref(person2);
// }
//
// /* ============================================================
//  * 第7章：对象生命周期示例
//  * 展示引用计数、对象所有权管理
//  * 参考：GObject Reference Manual - Object Lifecycle
//  * ============================================================ */
// void chapter7_object_lifecycle_test(void)
// {
//     g_print("\n=== 第7章：对象生命周期示例 ===\n");
//
//     /* 基本引用计数 */
//     g_print("-- 引用计数基础 --\n");
//     MyPerson *obj = g_object_new(MY_TYPE_PERSON, "name", "RefTest", NULL);
//     g_print("对象已创建 (初始引用计数为1)\n");
//
//     /* g_object_ref() 增加引用计数 */
//     MyPerson *ref1 = g_object_ref(obj);
//     g_print("g_object_ref 后引用计数增加 (现为2)\n");
//     g_print("ref1 == obj: %s\n", ref1 == obj ? "是" : "否");
//
//     /* 再次引用 */
//     MyPerson *ref2 = g_object_ref(obj);
//     g_print("再次 g_object_ref 后引用计数增加 (现为3)\n");
//
//     /* g_object_unref() 减少引用计数 */
//     g_object_unref(ref1);
//     g_print("unref ref1 后引用计数减少 (现为2)\n");
//
//     g_object_unref(ref2);
//     g_print("unref ref2 后引用计数减少 (现为1)\n");
//
//     /* 最后一次 unref 将触发销毁 */
//     g_print("即将执行最后一次 unref...\n");
//     g_object_unref(obj);
//     g_print("对象已销毁\n");
//
//     /* g_object_ref_sink() - 浮动引用（主要用于初始未归属的对象） */
//     g_print("\n-- 浮动引用 (g_object_ref_sink) --\n");
//     MyPerson *floating = g_object_new(MY_TYPE_PERSON, "name", "Floating", NULL);
//     /* GObject 默认不是浮动的，但 ref_sink 在非浮动对象上等同于 ref */
//     MyPerson *sunk = g_object_ref_sink(floating);
//     g_print("g_object_ref_sink: sunk == floating: %s\n", sunk == floating ? "是" : "否");
//     g_object_unref(sunk);
//     g_object_unref(floating);
//
//     /* g_clear_object() - 安全地释放引用并置空指针 */
//     g_print("\n-- g_clear_object --\n");
//     MyPerson *clear_obj = g_object_new(MY_TYPE_PERSON, "name", "ClearTest", NULL);
//     g_print("clear_obj 销毁前: %p\n", (void *)clear_obj);
//     g_clear_object(&clear_obj);
//     g_print("clear_obj 销毁后: %p\n", (void *)clear_obj);
//
//     /* g_object_weak_ref() - 弱引用（不增加引用计数，对象销毁时通知） */
//     g_print("\n-- 弱引用 (g_object_weak_ref) --\n");
//     MyPerson *weak_obj = g_object_new(MY_TYPE_PERSON, "name", "WeakTest", NULL);
//
//     /* 弱引用回调 */
//     g_object_weak_ref(G_OBJECT(weak_obj),
//                       (GWeakNotify)g_print,
//                       "  弱引用通知: 对象即将被销毁!\n");
//     g_print("弱引用已添加 (不增加引用计数)\n");
//     g_object_unref(weak_obj);
//     /* 对象已销毁，弱引用回调已触发 */
//
//     /* g_object_add_toggle_ref - 切换引用（引用计数在1和2之间切换时通知） */
//     g_print("\n-- 所有权管理示例 --\n");
//     MyPerson *owner_obj = g_object_new(MY_TYPE_PERSON, "name", "OwnerTest", NULL);
//     g_print("创建对象，调用者拥有所有权\n");
//     /* 模拟所有权转移：函数返回对象，调用者获得所有权 */
//     /* 调用者负责最终 g_object_unref */
//     g_object_unref(owner_obj);
// }
//
// /* ============================================================
//  * 第8章：信号与槽示例
//  * 演示 GObject 信号定义、连接、发射和处理机制
//  * 参考：GObject Reference Manual - Signals
//  * ============================================================ */
//
// /* 定义带信号的对象 */
// #define MY_TYPE_SIGNAL_OBJ (my_signal_obj_get_type())
// G_DECLARE_FINAL_TYPE(MySignalObj, my_signal_obj, MY, SIGNAL_OBJ, GObject)
//
// struct _MySignalObj
// {
//     GObject parent_instance;
//     gint counter;
// };
//
// enum
// {
//     SIG_COUNTER_CHANGED,
//     SIG_THRESHOLD_REACHED,
//     N_SIGNALS
// };
//
// static guint my_signal_obj_signals[N_SIGNALS] = {0, };
//
// G_DEFINE_TYPE(MySignalObj, my_signal_obj, G_TYPE_OBJECT)
//
// static void my_signal_obj_class_init(MySignalObjClass *klass)
// {
//     /* 定义 "counter-changed" 信号
//      * 参数: gint (新值)
//      * 返回: void */
//     my_signal_obj_signals[SIG_COUNTER_CHANGED] =
//         g_signal_new("counter-changed",
//                      G_TYPE_FROM_CLASS(klass),
//                      G_SIGNAL_RUN_LAST,
//                      0,  /* class closure offset */
//                      NULL, NULL,  /* accumulator, accumulator data */
//                      g_cclosure_marshal_VOID__INT,
//                      G_TYPE_NONE,
//                      1, G_TYPE_INT);
//
//     /* 定义 "threshold-reached" 信号
//      * 参数: gint (阈值)
//      * 返回: gboolean (是否由处理者处理） */
//     my_signal_obj_signals[SIG_THRESHOLD_REACHED] =
//         g_signal_new("threshold-reached",
//                      G_TYPE_FROM_CLASS(klass),
//                      G_SIGNAL_RUN_LAST,
//                      0,
//                      NULL, NULL,
//                      NULL,  /* c_marshaller: NULL 使用通用 marshaller */
//                      G_TYPE_BOOLEAN,
//                      1, G_TYPE_INT);
// }
//
// static void my_signal_obj_init(MySignalObj *self)
// {
//     self->counter = 0;
// }
//
// /* 信号处理函数 */
// static void on_counter_changed(MySignalObj *obj, gint new_val, gpointer user_data)
// {
//     g_print("  [信号处理] counter-changed: 新值 = %d, 用户数据 = %s\n",
//             new_val, (gchar *)user_data);
// }
//
// static gboolean on_threshold_reached(MySignalObj *obj, gint threshold, gpointer user_data)
// {
//     g_print("  [信号处理] threshold-reached: 阈值 = %d, 已处理\n", threshold);
//     return TRUE;  /* 表示信号已被处理 */
// }
//
// void chapter8_signal_slot_test(void)
// {
//     g_print("\n=== 第8章：信号与槽示例 ===\n");
//
//     /* 创建对象 */
//     MySignalObj *sig_obj = g_object_new(MY_TYPE_SIGNAL_OBJ, NULL);
//
//     /* 连接信号处理函数 */
//     g_print("-- 连接信号 --\n");
//     gulong handler_id1 = g_signal_connect(sig_obj, "counter-changed",
//                                           G_CALLBACK(on_counter_changed),
//                                           (gpointer)"观察者1");
//     gulong handler_id2 = g_signal_connect(sig_obj, "counter-changed",
//                                           G_CALLBACK(on_counter_changed),
//                                           (gpointer)"观察者2");
//     gulong handler_id3 = g_signal_connect(sig_obj, "threshold-reached",
//                                           G_CALLBACK(on_threshold_reached),
//                                           NULL);
//     g_print("已连接 3 个信号处理函数, handler_id: %lu, %lu, %lu\n",
//             handler_id1, handler_id2, handler_id3);
//
//     /* 发射信号 */
//     g_print("\n-- 发射 counter-changed 信号 --\n");
//     sig_obj->counter = 5;
//     g_signal_emit(sig_obj, my_signal_obj_signals[SIG_COUNTER_CHANGED], 0, 5);
//
//     sig_obj->counter = 10;
//     g_signal_emit(sig_obj, my_signal_obj_signals[SIG_COUNTER_CHANGED], 0, 10);
//
//     /* 发射带返回值的信号 */
//     g_print("\n-- 发射 threshold-reached 信号 --\n");
//     gboolean handled = FALSE;
//     g_signal_emit(sig_obj, my_signal_obj_signals[SIG_THRESHOLD_REACHED], 0,
//                   10, &handled);
//     g_print("threshold-reached 信号处理结果: %s\n", handled ? "已处理" : "未处理");
//
//     /* 阻断信号处理函数 */
//     g_print("\n-- 阻断信号处理 --\n");
//     g_signal_handler_block(sig_obj, handler_id1);
//     g_print("已阻断 handler_id1\n");
//     sig_obj->counter = 15;
//     g_signal_emit(sig_obj, my_signal_obj_signals[SIG_COUNTER_CHANGED], 0, 15);
//
//     /* 解除阻断 */
//     g_signal_handler_unblock(sig_obj, handler_id1);
//     g_print("已解除阻断 handler_id1\n");
//     sig_obj->counter = 20;
//     g_signal_emit(sig_obj, my_signal_obj_signals[SIG_COUNTER_CHANGED], 0, 20);
//
//     /* 断开信号处理函数 */
//     g_print("\n-- 断开信号处理 --\n");
//     g_signal_handler_disconnect(sig_obj, handler_id2);
//     g_print("已断开 handler_id2\n");
//     sig_obj->counter = 25;
//     g_signal_emit(sig_obj, my_signal_obj_signals[SIG_COUNTER_CHANGED], 0, 25);
//
//     /* 查询信号处理函数 */
//     g_print("\n-- 查询信号连接 --\n");
//     gulong found_id = g_signal_handler_find(
//         sig_obj, G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA,
//         0, 0, NULL, on_counter_changed, (gpointer)"观察者1");
//     g_print("on_counter_changed (观察者1) handler_id: %lu (%s)\n",
//             found_id, found_id != 0 ? "已连接" : "未找到");
//
//     /* 使用 g_signal_emit_by_name 按名称发射 */
//     g_print("\n-- 按名称发射信号 --\n");
//     g_signal_emit_by_name(sig_obj, "counter-changed", 30);
//
//     /* 清理 */
//     g_signal_handler_disconnect(sig_obj, handler_id1);
//     g_signal_handler_disconnect(sig_obj, handler_id3);
//     g_object_unref(sig_obj);
// }
//
// /* ============================================================
//  * 第9章：文件操作示例
//  * 展示 GFile、GFileInfo 等进行文件读写、属性操作
//  * 参考：GIO Reference Manual - GFile / GFileInfo
//  * ============================================================ */
// void chapter9_file_operations_test(void)
// {
//     g_print("\n=== 第9章：文件操作示例 ===\n");
//
//     GError *error = NULL;
//
//     /* GFile 创建 - 使用 g_file_new_for_path */
//     g_print("-- 创建 GFile --\n");
//     const gchar *test_path = "glib_tutorial_test.txt";
//     GFile *file = g_file_new_for_path(test_path);
//     g_print("GFile 路径: %s\n", g_file_get_path(file));
//     g_print("GFile basename: %s\n", g_file_get_basename(file));
//
//     /* GFile 创建 - 使用 g_file_new_for_uri */
//     GFile *uri_file = g_file_new_for_uri("file:///tmp/test.txt");
//     g_print("GFile URI 路径: %s\n", g_file_get_path(uri_file));
//     g_object_unref(uri_file);
//
//     /* 写入文件 - 使用 GFileOutputStream */
//     g_print("\n-- 写入文件 --\n");
//     GFileOutputStream *out_stream = g_file_replace(
//         file, NULL, FALSE, G_FILE_CREATE_NONE, NULL, &error);
//     if (error != NULL) {
//         g_print("写入文件失败: %s\n", error->message);
//         g_error_free(error);
//         error = NULL;
//     } else {
//         const gchar *content = "Hello, GIO Tutorial!\n这是GLib教学示例文件。\n";
//         gsize bytes_written = 0;
//         g_output_stream_write_all(G_OUTPUT_STREAM(out_stream),
//                                   content, strlen(content),
//                                   &bytes_written, NULL, &error);
//         if (error != NULL) {
//             g_print("写入数据失败: %s\n", error->message);
//             g_error_free(error);
//             error = NULL;
//         } else {
//             g_print("成功写入 %lu 字节\n", (gulong)bytes_written);
//         }
//         g_output_stream_close(G_OUTPUT_STREAM(out_stream), NULL, NULL);
//         g_object_unref(out_stream);
//     }
//
//     /* 读取文件 - 使用 GFileInputStream */
//     g_print("\n-- 读取文件 --\n");
//     GFileInputStream *in_stream = g_file_read(file, NULL, &error);
//     if (error != NULL) {
//         g_print("读取文件失败: %s\n", error->message);
//         g_error_free(error);
//         error = NULL;
//     } else {
//         gchar buffer[256] = {0};
//         gsize bytes_read = 0;
//         g_input_stream_read_all(G_INPUT_STREAM(in_stream),
//                                 buffer, sizeof(buffer) - 1,
//                                 &bytes_read, NULL, &error);
//         if (error != NULL) {
//             g_print("读取数据失败: %s\n", error->message);
//             g_error_free(error);
//             error = NULL;
//         } else {
//             g_print("成功读取 %lu 字节:\n%s\n", (gulong)bytes_read, buffer);
//         }
//         g_input_stream_close(G_INPUT_STREAM(in_stream), NULL, NULL);
//         g_object_unref(in_stream);
//     }
//
//     /* 查询文件信息 - GFileInfo */
//     g_print("\n-- 查询文件属性 --\n");
//     GFileInfo *info = g_file_query_info(file,
//                                         G_FILE_ATTRIBUTE_STANDARD_SIZE ","
//                                         G_FILE_ATTRIBUTE_STANDARD_TYPE ","
//                                         G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE,
//                                         G_FILE_QUERY_INFO_NONE,
//                                         NULL, &error);
//     if (error != NULL) {
//         g_print("查询文件信息失败: %s\n", error->message);
//         g_error_free(error);
//         error = NULL;
//     } else {
//         goffset file_size = g_file_info_get_size(info);
//         GFileType file_type = g_file_info_get_file_type(info);
//         const gchar *content_type = g_file_info_get_content_type(info);
//         const gchar *type_name = "未知";
//         switch (file_type) {
//         case G_FILE_TYPE_REGULAR:    type_name = "常规文件"; break;
//         case G_FILE_TYPE_DIRECTORY:  type_name = "目录"; break;
//         case G_FILE_TYPE_SYMBOLIC_LINK: type_name = "符号链接"; break;
//         default: break;
//         }
//         g_print("文件大小: %" G_GOFFSET_FORMAT " 字节\n", file_size);
//         g_print("文件类型: %s\n", type_name);
//         g_print("MIME类型: %s\n", content_type ? content_type : "(未知)");
//         g_object_unref(info);
//     }
//
//     /* 文件存在性检查 */
//     g_print("\n-- 文件存在性检查 --\n");
//     gboolean exists = g_file_query_exists(file, NULL);
//     g_print("文件 %s: %s\n", test_path, exists ? "存在" : "不存在");
//
//     /* 删除测试文件 */
//     g_print("\n-- 删除测试文件 --\n");
//     gboolean deleted = g_file_delete(file, NULL, &error);
//     if (error != NULL) {
//         g_print("删除文件失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_print("文件已删除: %s\n", deleted ? "成功" : "失败");
//     }
//
//     g_object_unref(file);
// }
//
// /* ============================================================
//  * 第10章：异步I/O示例
//  * 演示 GIO 异步操作模式和回调机制
//  * 参考：GIO Reference Manual - Asynchronous I/O
//  * ============================================================ */
//
// /* 异步读取完成回调 */
// static void chapter10_async_read_callback(GObject *source_object, GAsyncResult *res,
//                                           gpointer user_data)
// {
//     GError *error = NULL;
//     GFileInputStream *stream = G_FILE_INPUT_STREAM(source_object);
//     gsize bytes_read = 0;
//
//     /* 通过 g_input_stream_read_all_finish 获取异步读取结果 */
//     gboolean success = g_input_stream_read_all_finish(
//         G_INPUT_STREAM(stream), res, &bytes_read, &error);
//
//     if (!success) {
//         g_print("  [异步回调] 读取失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_print("  [异步回调] 异步读取完成, %lu 字节\n", (gulong)bytes_read);
//     }
//
//     /* 通知主循环退出 */
//     GMainLoop *loop = (GMainLoop *)user_data;
//     g_main_loop_quit(loop);
// }
//
// /* 异步写入完成回调 */
// static void chapter10_async_write_callback(GObject *source_object, GAsyncResult *res,
//                                            gpointer user_data)
// {
//     GError *error = NULL;
//     GOutputStream *stream = G_OUTPUT_STREAM(source_object);
//     gsize bytes_written = 0;
//
//     gboolean success = g_output_stream_write_all_finish(
//         stream, res, &bytes_written, &error);
//
//     if (!success) {
//         g_print("  [异步回调] 写入失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_print("  [异步回调] 异步写入完成, %lu 字节\n", (gulong)bytes_written);
//     }
//
//     g_output_stream_close(stream, NULL, NULL);
// }
//
// void chapter10_async_io_test(void)
// {
//     g_print("\n=== 第10章：异步I/O示例 ===\n");
//
//     GError *error = NULL;
//     const gchar *async_test_path = "glib_async_test.txt";
//
//     /* 创建主循环（异步操作需要主循环驱动） */
//     GMainLoop *loop = g_main_loop_new(NULL, FALSE);
//
//     /* 同步写入测试文件（为异步读取准备数据） */
//     GFile *file = g_file_new_for_path(async_test_path);
//     GFileOutputStream *out = g_file_replace(file, NULL, FALSE,
//                                             G_FILE_CREATE_NONE, NULL, &error);
//     if (error != NULL) {
//         g_print("创建文件失败: %s\n", error->message);
//         g_error_free(error);
//         g_object_unref(file);
//         g_main_loop_unref(loop);
//         return;
//     }
//
//     const gchar *content = "这是异步I/O测试文件的内容。";
//     gsize bytes_written = 0;
//     g_output_stream_write_all(G_OUTPUT_STREAM(out), content, strlen(content),
//                               &bytes_written, NULL, NULL);
//     g_output_stream_close(G_OUTPUT_STREAM(out), NULL, NULL);
//     g_object_unref(out);
//     g_print("已写入测试文件: %lu 字节\n", (gulong)bytes_written);
//
//     /* 异步写入 */
//     g_print("\n-- 异步写入 --\n");
//     GFileOutputStream *async_out = g_file_replace(file, NULL, FALSE,
//                                                    G_FILE_CREATE_NONE, NULL, &error);
//     if (error != NULL) {
//         g_print("打开文件失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         const gchar *new_content = "异步写入的新内容。";
//         g_output_stream_write_all_async(G_OUTPUT_STREAM(async_out),
//                                         new_content, strlen(new_content),
//                                         G_PRIORITY_DEFAULT, NULL,
//                                         chapter10_async_write_callback, NULL);
//         /* 等待写入完成 */
//         while (g_main_context_iteration(NULL, FALSE))
//             ;
//         g_object_unref(async_out);
//     }
//
//     /* 异步读取 */
//     g_print("\n-- 异步读取 --\n");
//     GFileInputStream *in = g_file_read(file, NULL, &error);
//     if (error != NULL) {
//         g_print("打开文件失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_input_stream_read_all_async(G_INPUT_STREAM(in),
//                                       g_new0(gchar, 256), 255,
//                                       G_PRIORITY_DEFAULT, NULL,
//                                       chapter10_async_read_callback, loop);
//         /* 运行主循环等待异步操作完成 */
//         g_print("  等待异步读取完成...\n");
//         g_main_loop_run(loop);
//         g_object_unref(in);
//     }
//
//     /* 清理 */
//     g_file_delete(file, NULL, NULL);
//     g_object_unref(file);
//     g_main_loop_unref(loop);
// }
//
// /* ============================================================
//  * 第11章：网络编程示例
//  * 展示 GIO 网络通信功能（GSocket、GSocketClient、GSocketService）
//  * 参考：GIO Reference Manual - Networking
//  * ============================================================ */
//
// /* TCP 回显服务器的连接处理回调 */
// static gboolean on_incoming_connection(GSocketService *service,
//                                        GSocketConnection *connection,
//                                        GObject *source_object,
//                                        gpointer user_data)
// {
//     GError *error = NULL;
//     GInputStream *in = g_io_stream_get_input_stream(G_IO_STREAM(connection));
//     GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(connection));
//
//     gchar buffer[256] = {0};
//     gsize bytes_read = 0;
//
//     /* 读取客户端数据 */
//     gboolean success = g_input_stream_read_all(in, buffer, sizeof(buffer) - 1,
//                                                &bytes_read, NULL, &error);
//     if (!success && error != NULL) {
//         g_print("  [服务器] 读取失败: %s\n", error->message);
//         g_error_free(error);
//         return TRUE;
//     }
//
//     g_print("  [服务器] 收到 %lu 字节: %s\n", (gulong)bytes_read, buffer);
//
//     /* 回显数据给客户端 */
//     gsize bytes_written = 0;
//     g_output_stream_write_all(out, buffer, bytes_read,
//                               &bytes_written, NULL, &error);
//     if (error != NULL) {
//         g_print("  [服务器] 回显失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_print("  [服务器] 已回显 %lu 字节\n", (gulong)bytes_written);
//     }
//
//     return TRUE;
// }
//
// void chapter11_network_programming_test(void)
// {
//     g_print("\n=== 第11章：网络编程示例 ===\n");
//
//     GError *error = NULL;
//
//     /* --- GSocketService: TCP 服务器 --- */
//     g_print("-- GSocketService TCP 服务器 --\n");
//     GSocketService *service = g_socket_service_new();
//
//     /* g_socket_listener_add_any_inet_port: 自动分配端口并返回端口号 */
//     guint16 port = g_socket_listener_add_any_inet_port(
//         G_SOCKET_LISTENER(service), NULL, &error);
//     if (error != NULL) {
//         g_print("添加监听端口失败: %s\n", error->message);
//         g_error_free(error);
//         g_object_unref(service);
//         return;
//     }
//     g_print("服务器监听端口: %u\n", port);
//
//     /* 连接 incoming 信号 */
//     g_signal_connect(service, "incoming",
//                      G_CALLBACK(on_incoming_connection), NULL);
//
//     /* 启动服务 */
//     g_socket_service_start(service);
//     g_print("TCP 服务器已启动\n");
//
//     /* --- GSocketClient: TCP 客户端 --- */
//     g_print("\n-- GSocketClient TCP 客户端 --\n");
//     GSocketClient *client = g_socket_client_new();
//
//     /* 连接到服务器 */
//     GSocketConnection *conn = g_socket_client_connect_to_host(
//         client, "127.0.0.1", port, NULL, &error);
//     if (error != NULL) {
//         g_print("连接服务器失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_print("已连接到服务器 127.0.0.1:%u\n", port);
//
//         /* 发送数据 */
//         GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(conn));
//         const gchar *msg = "Hello from GIO!";
//         gsize bytes_written = 0;
//         g_output_stream_write_all(out, msg, strlen(msg),
//                                   &bytes_written, NULL, &error);
//         if (error != NULL) {
//             g_print("发送数据失败: %s\n", error->message);
//             g_error_free(error);
//             error = NULL;
//         } else {
//             g_print("已发送 %lu 字节: %s\n", (gulong)bytes_written, msg);
//         }
//
//         /* 关闭写入端（通知服务器数据发送完毕） */
//         g_output_stream_close(out, NULL, NULL);
//
//         /* 读取回显 */
//         GInputStream *in = g_io_stream_get_input_stream(G_IO_STREAM(conn));
//         gchar buffer[256] = {0};
//         gsize bytes_read = 0;
//         g_input_stream_read_all(in, buffer, sizeof(buffer) - 1,
//                                 &bytes_read, NULL, &error);
//         if (error != NULL) {
//             g_print("读取回显失败: %s\n", error->message);
//             g_error_free(error);
//         } else {
//             g_print("收到回显 %lu 字节: %s\n", (gulong)bytes_read, buffer);
//         }
//
//         g_io_stream_close(G_IO_STREAM(conn), NULL, NULL);
//         g_object_unref(conn);
//     }
//
//     /* --- GSocket: 底层 Socket 操作 --- */
//     g_print("\n-- GSocket 底层操作 --\n");
//     GSocket *sock = g_socket_new(G_SOCKET_FAMILY_IPV4,
//                                  G_SOCKET_TYPE_DATAGRAM,
//                                  G_SOCKET_PROTOCOL_UDP, &error);
//     if (error != NULL) {
//         g_print("创建 UDP Socket 失败: %s\n", error->message);
//         g_error_free(error);
//     } else {
//         g_print("UDP Socket 创建成功\n");
//         g_print("Socket 类型: %s\n",
//                 g_socket_get_socket_type(sock) == G_SOCKET_TYPE_DATAGRAM
//                     ? "DATAGRAM" : "STREAM");
//         g_print("协议族: %s\n",
//                 g_socket_get_family(sock) == G_SOCKET_FAMILY_IPV4
//                     ? "IPv4" : "IPv6");
//         g_print("是否阻塞: %s\n",
//                 g_socket_get_blocking(sock) ? "是" : "否");
//         g_object_unref(sock);
//     }
//
//     /* --- GInetAddress: 网络地址操作 --- */
//     g_print("\n-- GInetAddress 网络地址 --\n");
//     GInetAddress *localhost = g_inet_address_new_from_string("127.0.0.1");
//     if (localhost != NULL) {
//         gchar *addr_str = g_inet_address_to_string(localhost);
//         g_print("localhost 地址: %s\n", addr_str);
//         g_print("是否为回环地址: %s\n",
//                 g_inet_address_get_is_loopback(localhost) ? "是" : "否");
//         g_print("是否为组播地址: %s\n",
//                 g_inet_address_get_is_multicast(localhost) ? "是" : "否");
//         g_free(addr_str);
//         g_object_unref(localhost);
//     }
//
//     /* 清理 */
//     g_socket_service_stop(service);
//     g_object_unref(service);
//     g_object_unref(client);
// }
//
// /* ============================================================
//  * 第12章：主循环示例
//  * 演示 GMainLoop 创建、运行和控制
//  * 参考：GLib Reference Manual - The Main Event Loop
//  * ============================================================ */
//
// /* 超时回调：每隔一段时间触发 */
// static gboolean chapter12_timeout_callback(gpointer user_data)
// {
//     gint *counter = (gint *)user_data;
//     (*counter)++;
//     g_print("  [超时回调] 第 %d 次触发\n", *counter);
//
//     if (*counter >= 3) {
//         g_print("  [超时回调] 达到3次，返回 G_SOURCE_REMOVE 停止\n");
//         return G_SOURCE_REMOVE;  /* 停止该定时源 */
//     }
//     return G_SOURCE_CONTINUE;  /* 继续触发 */
// }
//
// /* 空闲回调：当主循环无其他事件时触发 */
// static gboolean chapter12_idle_callback(gpointer user_data)
// {
//     g_print("  [空闲回调] 主循环空闲时触发\n");
//     return G_SOURCE_REMOVE;  /* 只触发一次 */
// }
//
// /* 一次性超时回调：用于退出主循环 */
// static gboolean chapter12_quit_loop_callback(gpointer user_data)
// {
//     GMainLoop *loop = (GMainLoop *)user_data;
//     g_print("  [退出回调] 准备退出主循环\n");
//     g_main_loop_quit(loop);
//     return G_SOURCE_REMOVE;
// }
//
// /* IO 监视回调 */
// static gboolean chapter12_io_watch_callback(GIOChannel *source,
//                                             GIOCondition condition,
//                                             gpointer user_data)
// {
//     if (condition & G_IO_IN) {
//         gchar buffer[128] = {0};
//         gsize bytes_read = 0;
//         GError *error = NULL;
//         GIOStatus status = g_io_channel_read_chars(source, buffer,
//                                                     sizeof(buffer) - 1,
//                                                     &bytes_read, &error);
//         if (status == G_IO_STATUS_NORMAL) {
//             g_print("  [IO监视] 读取 %lu 字节: %s\n", (gulong)bytes_read, buffer);
//         } else if (status == G_IO_STATUS_EOF) {
//             g_print("  [IO监视] 到达文件末尾\n");
//             return G_SOURCE_REMOVE;
//         }
//         if (error != NULL) {
//             g_print("  [IO监视] 读取错误: %s\n", error->message);
//             g_error_free(error);
//         }
//     }
//     return G_SOURCE_CONTINUE;
// }
//
// void chapter12_main_loop_test(void)
// {
//     g_print("\n=== 第12章：主循环示例 ===\n");
//
//     /* --- GMainLoop 基本使用 --- */
//     g_print("-- GMainLoop 基本使用 --\n");
//     GMainLoop *loop = g_main_loop_new(NULL, FALSE);
//     g_print("GMainLoop 已创建\n");
//
//     /* --- GSource: 超时源 --- */
//     g_print("\n-- 超时源 (g_timeout_add) --\n");
//     gint timeout_counter = 0;
//     guint timeout_id = g_timeout_add(100, chapter12_timeout_callback, &timeout_counter);
//     g_print("已添加超时源, source_id = %u (每100ms触发)\n", timeout_id);
//
//     /* --- GSource: 空闲源 --- */
//     g_print("\n-- 空闲源 (g_idle_add) --\n");
//     guint idle_id = g_idle_add(chapter12_idle_callback, NULL);
//     g_print("已添加空闲源, source_id = %u\n", idle_id);
//
//     /* --- 设置退出定时器 --- */
//     g_print("\n-- 退出定时器 --\n");
//     guint quit_id = g_timeout_add(1000, chapter12_quit_loop_callback, loop);
//     g_print("已添加1秒后退出主循环的定时器, source_id = %u\n", quit_id);
//
//     /* --- GMainContext --- */
//     g_print("\n-- GMainContext --\n");
//     GMainContext *ctx = g_main_loop_get_context(loop);
//     g_print("主循环上下文: %s\n", ctx ? "已获取" : "NULL");
//     g_print("主循环是否正在运行: %s\n",
//             g_main_loop_is_running(loop) ? "是" : "否");
//
//     /* --- GIOChannel 文件监视 --- */
//     g_print("\n-- GIOChannel 文件监视 --\n");
//     const gchar *watch_file_path = "glib_watch_test.txt";
//     /* 创建测试文件 */
//     GIOChannel *channel = g_io_channel_new_file(watch_file_path, "r", NULL);
//     if (channel != NULL) {
//         guint watch_id = g_io_add_watch(channel,
//                                         G_IO_IN | G_IO_HUP,
//                                         chapter12_io_watch_callback,
//                                         NULL);
//         g_print("已添加 IO 监视, watch_id = %u\n", watch_id);
//         g_source_remove(watch_id);
//         g_io_channel_unref(channel);
//     } else {
//         g_print("无法创建 IO Channel (文件不存在)\n");
//     }
//
//     /* --- 运行主循环 --- */
//     g_print("\n-- 运行主循环 --\n");
//     g_print("主循环开始运行...\n");
//     g_main_loop_run(loop);
//     g_print("主循环已退出\n");
//
//     /* --- 手动迭代 --- */
//     g_print("\n-- 手动迭代 (g_main_context_iteration) --\n");
//     gint iter_counter = 0;
//     g_timeout_add(50, chapter12_timeout_callback, &iter_counter);
//     /* 手动迭代几次 */
//     for (gint i = 0; i < 10; i++) {
//         g_main_context_iteration(NULL, FALSE);
//         g_usleep(50000);  /* 50ms */
//     }
//     g_print("手动迭代完成\n");
//
//     /* --- GSource 操作 --- */
//     g_print("\n-- GSource 操作 --\n");
//     GSource *source = g_timeout_source_new(200);
//     gint src_counter = 0;
//     g_source_set_callback(source, (GSourceFunc)chapter12_timeout_callback,
//                           &src_counter, NULL);
//     guint src_id = g_source_attach(source, NULL);
//     g_print("已创建并附加 GSource, id = %u\n", src_id);
//
//     /* 移除源 */
//     g_source_remove(src_id);
//     g_print("已移除 GSource\n");
//
//     g_source_unref(source);
//
//     /* 清理 */
//     g_main_loop_unref(loop);
//
//     /* 删除测试文件 */
//     {
//         GFile *wf = g_file_new_for_path(watch_file_path);
//         g_file_delete(wf, NULL, NULL);
//         g_object_unref(wf);
//     }
// }
//
// /* ============================================================
//  * 主入口
//  * ============================================================ */
//
// typedef void (*TestFunc)(void);
//
// typedef struct
// {
//     const gchar *name;
//     const gchar *description;
//     TestFunc func;
// } ChapterEntry;
//
// static ChapterEntry chapters[] = {
//     {"1",  "数据类型",           chapter1_data_types_test},
//     {"2",  "内存管理",           chapter2_memory_management_test},
//     {"3",  "字符串处理",         chapter3_string_handling_test},
//     {"4",  "数据结构",           chapter4_data_structures_test},
//     {"5",  "类型系统",           chapter5_type_system_test},
//     {"6",  "对象基础",           chapter6_object_basic_test},
//     {"7",  "对象生命周期",       chapter7_object_lifecycle_test},
//     {"8",  "信号与槽",           chapter8_signal_slot_test},
//     {"9",  "文件操作",           chapter9_file_operations_test},
//     {"10", "异步I/O",            chapter10_async_io_test},
//     {"11", "网络编程",           chapter11_network_programming_test},
//     {"12", "主循环",             chapter12_main_loop_test},
// };
//
// static void print_usage(const gchar *prog)
// {
//     g_print("用法: %s [章节号]\n", prog);
//     g_print("  不带参数: 运行全部章节\n");
//     g_print("  章节号:   运行指定章节 (1-12)\n\n");
//     g_print("可用章节:\n");
//     for (guint i = 0; i < G_N_ELEMENTS(chapters); i++) {
//         g_print("  %2s. %s\n", chapters[i].name, chapters[i].description);
//     }
// }
//
// #if 0
// #endif
// int main(int argc, char *argv[])
// {
//     g_print("========================================\n");
//     g_print("  GLib 渐进式教学示例\n");
//     g_print("========================================\n");
//
//     if (argc > 1) {
//         const gchar *arg = argv[1];
//
//         if (g_strcmp0(arg, "-h") == 0 || g_strcmp0(arg, "--help") == 0) {
//             print_usage(argv[0]);
//             return 0;
//         }
//
//         /* 查找并运行指定章节 */
//         gboolean found = FALSE;
//         for (guint i = 0; i < G_N_ELEMENTS(chapters); i++) {
//             if (g_strcmp0(arg, chapters[i].name) == 0) {
//                 chapters[i].func();
//                 found = TRUE;
//                 break;
//             }
//         }
//
//         if (!found) {
//             g_print("错误: 未知章节号 \"%s\"\n\n", arg);
//             print_usage(argv[0]);
//             return 1;
//         }
//     } else {
//         /* 运行全部章节 */
//         for (guint i = 0; i < G_N_ELEMENTS(chapters); i++) {
//             chapters[i].func();
//         }
//     }
//
//     g_print("\n========================================\n");
//     g_print("  所有示例运行完毕\n");
//     g_print("========================================\n");
//
//     return 0;
// }