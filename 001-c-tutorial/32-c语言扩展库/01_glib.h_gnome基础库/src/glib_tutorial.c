/*
 * GLib / GObject / GIO 渐进式教学案例（十三章）
 * ============================================================================
 * 章节总览（由浅入深、由底层到高层、由理论到实战）
 * ============================================================================
 *
 * 【第一部分】GLib 基础 —— 现代 C 语言工程基石（第 1~4 章）
 *   第 1 章  环境搭建与初识 GLib
 *            · GLib 家族生态（GLib/GObject/GIO 依赖关系）
 *            · 跨平台基础类型 gint/guint/gboolean/gsize/gpointer
 *            · 断言与防御式编程 g_assert / g_return_if_fail
 *            · 常用工具宏 CLAMP/MAX/MIN/G_N_ELEMENTS、版本信息
 *
 *   第 2 章  核心数据类型与内存管理
 *            · g_malloc/g_malloc0/g_realloc/g_free 与原生 C 的区别
 *            · g_slice 内存切片（小对象高效分配）
 *            · ★ g_autoptr / g_autofree / g_steal_pointer 自动清理宏（现代必备）
 *            · GString 动态字符串、g_strdup_printf、字符串工具集
 *            · GError 错误处理：错误域 GQuark、g_set_error、释放规范
 *
 *   第 3 章  常用数据结构（容器）
 *            · 动态数组：GArray / GPtrArray / GByteArray
 *            · 哈希表 GHashTable：键值对、销毁通知、GHashTableIter
 *            · 链表：GSList（单向）/ GList（双向）
 *            · 双端队列 GQueue、平衡二叉树 GTree
 *
 *   第 4 章  事件驱动基石——主循环与并发
 *            · GMainContext 与 GMainLoop
 *            · 事件源 GSource：g_timeout_add、g_idle_add
 *            · 并发：GThread、GMutex、GCond
 *            · 线程与主循环交互
 *
 * 【第二部分】GObject 面向对象系统 —— C 语言的 OOP 工程（第 5~8 章）
 *   第 5 章  GObject 类型系统初探
 *            · GType 动态类型注册机制
 *            · 从零手写 GObject 类：实例结构体 + 类结构体
 *            · G_DEFINE_TYPE 宏解析、类型检查与安全转换宏
 *
 *   第 6 章  对象的生命周期与内存管理
 *            · g_object_new 实例化流程
 *            · 引用计数 g_object_ref / g_object_unref
 *            · 弱引用 g_object_weak_ref
 *            · ★ dispose vs finalize 的阶级区别（难点突破）
 *            · 结合 g_autoptr 自动销毁
 *
 *   第 7 章  封装、继承与多态
 *            · 封装：G_ADD_PRIVATE 私有数据宏
 *            · 继承：父子类链式 init/dispose/finalize
 *            · 多态：虚函数表覆写
 *            · ★ GInterface 接口系统（模拟多继承）
 *
 *   第 8 章  高级对象特性：属性与信号
 *            · GParamSpec 属性定义、get/set_property
 *            · g_object_get/set、notify::prop 通知
 *            · 信号系统 g_signal_new/connect/emit
 *            · 信号阻塞、停止发射、累积器
 *
 * 【第三部分】GIO 现代系统编程 —— 异步、流与设备抽象（第 9~12 章）
 *   第 9 章  GIO 概览与 GFile 抽象
 *            · GFile 面向对象文件抽象
 *            · 同步文件读写、GFileInfo 信息查询
 *            · GFileEnumerator 目录遍历、复制/删除
 *
 *   第 10 章 流式 I/O 模型
 *            · GInputStream / GOutputStream 基础
 *            · ★ GFilterInputStream 缓冲流（组合模式）
 *            · 流与 GObject 生命周期结合
 *
 *   第 11 章 异步编程模型
 *            · 异步三件套 _async/_finish/GCancellable
 *            · ★ GTask 现代异步任务统一封装
 *            · 取消机制 GCancellable
 *
 *   第 12 章 GIO 高级应用与系统集成
 *            · GApplication 标准化应用框架
 *            · GFileMonitor 文件监控
 *            · ★ GSettings 配置持久化
 *            · ★ GDBus 系统总线通信（概念演示）
 *
 * 【第四部分】综合实战（第 13 章）
 *   第 13 章 实战项目 —— 异步文件扫描分析器
 *            · 自定义 GObject 子类 FileAnalyzer
 *            · GFileEnumerator 异步遍历
 *            · GHashTable 统计 + GObject 信号推送进度
 *            · GCancellable 取消支持
 * ============================================================================
 *
 * 编译（Linux/macOS）：
 *   gcc -o glib_tutorial glib_tutorial.c `pkg-config --cflags --libs glib-2.0 gobject-2.0 gio-2.0`
 *
 * 编译（Windows MSYS2，PowerShell）：
 *   powershell -ExecutionPolicy Bypass -File build.ps1
 */

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <glib/gstdio.h>   /* g_mkdir / g_unlink / g_rmdir 跨平台封装 */
#include <string.h>

/* =====================================================================
 *                    GObject 类型定义区（第 5~8 章使用）
 *   说明：GObject 子类化的样板代码集中在文件顶部，便于各章节引用。
 * ===================================================================== */

/* ---------- 第 7 章 Greeter 接口：演示 GInterface ---------- */
#define TYPE_GREETER (greeter_get_type())

typedef struct _Greeter          Greeter;
typedef struct _GreeterInterface GreeterInterface;

struct _GreeterInterface
{
    GTypeInterface parent_iface;
    void (*greet)(Greeter *self);   /* 接口虚函数 */
};

#define GREETER(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_GREETER, Greeter))
#define GREETER_IS_GREETER(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_GREETER))
#define GREETER_GET_IFACE(obj)  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TYPE_GREETER, GreeterInterface))

GType greeter_get_type(void);
void  greeter_greet(Greeter *self);

G_DEFINE_INTERFACE(Greeter, greeter, G_TYPE_OBJECT)

static void greeter_default_init(GreeterInterface *iface) { (void)iface; }

void greeter_greet(Greeter *self)
{
    g_return_if_fail(GREETER_IS_GREETER(self));
    GREETER_GET_IFACE(self)->greet(self);
}

/* ---------- 第 5~8 章 Animal 抽象基类 ---------- */
#define TYPE_ANIMAL (animal_get_type())

typedef struct _Animal      Animal;
typedef struct _AnimalClass AnimalClass;

/* 实例结构：仅含父类实例 */
struct _Animal
{
    GObject parent;
};

/* 类结构：虚函数表 */
struct _AnimalClass
{
    GObjectClass parent_class;
    void (*speak)(Animal *self);   /* 虚函数，子类可覆写 */
};

#define ANIMAL(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_ANIMAL, Animal))
#define ANIMAL_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_ANIMAL, AnimalClass))
#define ANIMAL_IS_ANIMAL(obj)     (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_ANIMAL))
#define ANIMAL_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj), TYPE_ANIMAL, AnimalClass))

/* 私有数据（G_ADD_PRIVATE 机制） */
typedef struct _AnimalPrivate AnimalPrivate;
struct _AnimalPrivate
{
    gchar *name;
};

enum
{
    ANIMAL_PROP_0,
    ANIMAL_PROP_NAME,
    N_ANIMAL_PROPS
};

enum
{
    ANIMAL_SIGNAL_FED,
    N_ANIMAL_SIGNALS
};

static GParamSpec *animal_props[N_ANIMAL_PROPS];
static guint       animal_signals[N_ANIMAL_SIGNALS];

GType animal_get_type(void);
void  animal_speak(Animal *self);

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(Animal, animal, G_TYPE_OBJECT)

/* 私有数据访问宏 */
#define ANIMAL_GET_PRIVATE(obj) \
    ((AnimalPrivate *)animal_get_instance_private(ANIMAL(obj)))

static void animal_set_property(GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(object);
    switch (prop_id) {
    case ANIMAL_PROP_NAME:
        g_free(priv->name);
        priv->name = g_value_dup_string(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    }
}

static void animal_get_property(GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(object);
    switch (prop_id) {
    case ANIMAL_PROP_NAME:
        g_value_set_string(value, priv->name);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    }
}

/* dispose：释放对其他 GObject 的引用（可被多次调用） */
static void animal_dispose(GObject *object)
{
    g_print("  [Animal.dispose] 释放引用（可多次调用）\n");
    G_OBJECT_CLASS(animal_parent_class)->dispose(object);
}

/* finalize：释放私有数据中持有的资源（仅调用一次） */
static void animal_finalize(GObject *object)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(object);
    g_print("  [Animal.finalize] 释放 name 私有数据\n");
    g_clear_pointer(&priv->name, g_free);
    G_OBJECT_CLASS(animal_parent_class)->finalize(object);
}

/* 默认 speak 实现 */
static void animal_speak_default(Animal *self)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(self);
    g_print("  [Animal] %s: ...\n", priv->name ? priv->name : "(unnamed)");
}

static void animal_class_init(AnimalClass *klass)
{
    GObjectClass *oc = G_OBJECT_CLASS(klass);

    oc->set_property = animal_set_property;
    oc->get_property = animal_get_property;
    oc->dispose      = animal_dispose;     /* 第 6 章：dispose */
    oc->finalize     = animal_finalize;    /* 第 6 章：finalize */
    klass->speak     = animal_speak_default;

    animal_props[ANIMAL_PROP_NAME] =
        g_param_spec_string("name", "Name", "Animal name",
                            NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    g_object_class_install_properties(oc, N_ANIMAL_PROPS, animal_props);

    animal_signals[ANIMAL_SIGNAL_FED] =
        g_signal_new("fed", G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST, 0, NULL, NULL, NULL, G_TYPE_NONE, 0);
}

static void animal_init(Animal *self) { (void)self; }

void animal_speak(Animal *self)
{
    g_return_if_fail(ANIMAL_IS_ANIMAL(self));
    ANIMAL_GET_CLASS(self)->speak(self);
}

/* ---------- 第 7 章 Dog 子类（继承 Animal，覆写 speak） ---------- */
#define TYPE_DOG (dog_get_type())

typedef struct _Dog Dog;
typedef struct _DogClass DogClass;

struct _Dog      { Animal parent; };
struct _DogClass { AnimalClass parent_class; };

#define DOG(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_DOG, Dog))
#define DOG_IS_DOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_DOG))

GType dog_get_type(void);
G_DEFINE_TYPE(Dog, dog, TYPE_ANIMAL)

/* 覆写父类虚函数：多态 */
static void dog_speak(Animal *self)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(self);
    g_print("  [Dog] %s: Woof!\n", priv->name ? priv->name : "(unnamed)");
}

static void dog_class_init(DogClass *klass)
{
    ANIMAL_CLASS(klass)->speak = dog_speak;
}

static void dog_init(Dog *self) { (void)self; }

Dog *dog_new(const gchar *name)
{
    return DOG(g_object_new(TYPE_DOG, "name", name, NULL));
}

/* ---------- 第 7 章 Cat 子类（继承 Animal + 实现 Greeter 接口） ---------- */
#define TYPE_CAT (cat_get_type())

typedef struct _Cat Cat;
typedef struct _CatClass CatClass;

struct _Cat      { Animal parent; };
struct _CatClass { AnimalClass parent_class; };

#define CAT(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_CAT, Cat))
#define CAT_IS_CAT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_CAT))

GType cat_get_type(void);

/* 前向声明接口初始化函数 */
static void cat_interface_init(GreeterInterface *iface);

G_DEFINE_TYPE_WITH_CODE(Cat, cat, TYPE_ANIMAL,
                        G_IMPLEMENT_INTERFACE(TYPE_GREETER, cat_interface_init))

static void cat_speak(Animal *self)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(self);
    g_print("  [Cat] %s: Meow!\n", priv->name ? priv->name : "(unnamed)");
}

static void cat_greet(Greeter *self)
{
    AnimalPrivate *priv = ANIMAL_GET_PRIVATE(self);
    g_print("  [Cat] %s 弓背打招呼\n", priv->name ? priv->name : "(unnamed)");
}

static void cat_interface_init(GreeterInterface *iface)
{
    iface->greet = cat_greet;
}

static void cat_class_init(CatClass *klass)
{
    ANIMAL_CLASS(klass)->speak = cat_speak;
}

static void cat_init(Cat *self) { (void)self; }

Cat *cat_new(const gchar *name)
{
    return CAT(g_object_new(TYPE_CAT, "name", name, NULL));
}

/* =====================================================================
 * 第 13 章实战：FileAnalyzer —— 自定义 GObject 子类
 *   功能：异步扫描目录，用 GHashTable 按扩展名统计文件数，
 *         通过信号推送进度，支持 GCancellable 取消。
 * ===================================================================== */
#define TYPE_FILE_ANALYZER (file_analyzer_get_type())

typedef struct _FileAnalyzer      FileAnalyzer;
typedef struct _FileAnalyzerClass FileAnalyzerClass;

struct _FileAnalyzer      { GObject parent; };
struct _FileAnalyzerClass { GObjectClass parent_class; };

#define FILE_ANALYZER(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_FILE_ANALYZER, FileAnalyzer))
#define FILE_ANALYZER_IS(obj)     (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_FILE_ANALYZER))

typedef struct _FileAnalyzerPrivate FileAnalyzerPrivate;
struct _FileAnalyzerPrivate
{
    GHashTable *stats;   /* 扩展名 -> 文件数 */
    gint        total;   /* 总文件数 */
};

enum
{
    FILE_ANALYZER_SIGNAL_PROGRESS,
    FILE_ANALYZER_SIGNAL_DONE,
    N_FILE_ANALYZER_SIGNALS
};

static guint file_analyzer_signals[N_FILE_ANALYZER_SIGNALS];

GType file_analyzer_get_type(void);

G_DEFINE_TYPE_WITH_PRIVATE(FileAnalyzer, file_analyzer, G_TYPE_OBJECT)

/* 注册 g_autoptr(FileAnalyzer) 自动调用 g_object_unref */
G_DEFINE_AUTOPTR_CLEANUP_FUNC(FileAnalyzer, g_object_unref)

#define FILE_ANALYZER_GET_PRIVATE(obj) \
    ((FileAnalyzerPrivate *)file_analyzer_get_instance_private(FILE_ANALYZER(obj)))

/* 进度回调签名：progress(percent) */
typedef void (*FileAnalyzerProgressFunc)(FileAnalyzer *self, gint percent, gpointer user_data);

static void file_analyzer_finalize(GObject *object)
{
    FileAnalyzerPrivate *priv = FILE_ANALYZER_GET_PRIVATE(object);
    g_clear_pointer(&priv->stats, g_hash_table_unref);
    G_OBJECT_CLASS(file_analyzer_parent_class)->finalize(object);
}

static void file_analyzer_class_init(FileAnalyzerClass *klass)
{
    GObjectClass *oc = G_OBJECT_CLASS(klass);
    oc->finalize = file_analyzer_finalize;

    /* 信号 1：progress(gint percent) */
    file_analyzer_signals[FILE_ANALYZER_SIGNAL_PROGRESS] =
        g_signal_new("progress", G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST, 0, NULL, NULL, NULL,
                     G_TYPE_NONE, 1, G_TYPE_INT);

    /* 信号 2：done(gint total) */
    file_analyzer_signals[FILE_ANALYZER_SIGNAL_DONE] =
        g_signal_new("done", G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST, 0, NULL, NULL, NULL,
                     G_TYPE_NONE, 1, G_TYPE_INT);
}

static void file_analyzer_init(FileAnalyzer *self)
{
    FileAnalyzerPrivate *priv = FILE_ANALYZER_GET_PRIVATE(self);
    /* key 是扩展名（g_strdup 复制），value 是 gint（用 GINT_TO_POINTER 存） */
    priv->stats = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    priv->total = 0;
}

FileAnalyzer *file_analyzer_new(void)
{
    return FILE_ANALYZER(g_object_new(TYPE_FILE_ANALYZER, NULL));
}

/* 同步扫描目录：遍历、统计、发射进度信号 */
static void file_analyzer_scan_sync(FileAnalyzer *self,
                                    const gchar  *path,
                                    GCancellable *cancellable)
{
    FileAnalyzerPrivate *priv = FILE_ANALYZER_GET_PRIVATE(self);
    GError *err = NULL;

    g_autoptr(GFile) dir = g_file_new_for_path(path);
    g_autoptr(GFileEnumerator) enu = g_file_enumerate_children(
        dir, "standard::name,standard::type",
        G_FILE_QUERY_INFO_NONE, NULL, &err);

    if (enu == NULL) {
        g_print("  [FileAnalyzer] 无法枚举 %s: %s\n", path, err->message);
        return;
    }

    GFileInfo *info = NULL;
    while ((info = g_file_enumerator_next_file(enu, cancellable, NULL)) != NULL) {
        g_autoptr(GFileInfo) auto_info = info;

        /* 只统计常规文件 */
        if (g_file_info_get_file_type(info) != G_FILE_TYPE_REGULAR) {
            continue;
        }

        const gchar *name = g_file_info_get_name(info);
        const gchar *dot = strrchr(name, '.');
        const gchar *ext = (dot != NULL && dot != name) ? dot + 1 : "(无扩展名)";

        /* 哈希表统计 */
        gint count = GPOINTER_TO_INT(g_hash_table_lookup(priv->stats, ext));
        g_hash_table_insert(priv->stats, g_strdup(ext), GINT_TO_POINTER(count + 1));
        priv->total++;

        /* 每扫一个文件发一次进度信号 */
        g_signal_emit(self, file_analyzer_signals[FILE_ANALYZER_SIGNAL_PROGRESS],
                      0, priv->total);
    }

    g_signal_emit(self, file_analyzer_signals[FILE_ANALYZER_SIGNAL_DONE],
                  0, priv->total);
}

/* 打印统计结果 */
static void file_analyzer_print_stats(FileAnalyzer *self)
{
    FileAnalyzerPrivate *priv = FILE_ANALYZER_GET_PRIVATE(self);
    GHashTableIter iter;
    gpointer k, v;
    g_hash_table_iter_init(&iter, priv->stats);
    g_print("  [FileAnalyzer] 统计结果（按扩展名）:\n");
    while (g_hash_table_iter_next(&iter, &k, &v)) {
        g_print("    %-12s : %d 个\n", (gchar *)k, GPOINTER_TO_INT(v));
    }
    g_print("  [FileAnalyzer] 总计 %d 个文件\n", priv->total);
}

/* ---------- 第 13 章信号回调 ---------- */
static void chapter13_on_progress(FileAnalyzer *self, gint percent, gpointer user_data)
{
    (void)self; (void)user_data;
    g_print("  [信号 progress] 已扫描 %d 个文件\n", percent);
}

static void chapter13_on_done(FileAnalyzer *self, gint total, gpointer user_data)
{
    (void)self; (void)user_data;
    g_print("  [信号 done] 扫描完成，共 %d 个文件\n", total);
}

/* =====================================================================
 * 第一部分：GLib 基础（第 1~4 章）
 * ===================================================================== */

/* =====================================================================
 * 第 1 章：环境搭建与初识 GLib
 *   知识点：跨平台基础类型、断言与防御式编程、工具宏、版本信息
 * ===================================================================== */
static void chapter1_basics_test(void)
{
    g_print("===== 第 1 章：初识 GLib =====\n");

    /* 1.1 跨平台基础类型 —— 保证不同平台上位宽一致 */
    gint     i = 42;
    guint    u = 100u;
    gboolean b = TRUE;
    gsize    s = sizeof(i);
    gpointer p = NULL;

    g_print("gint=%d, guint=%u, gboolean=%s, gsize=%" G_GSIZE_FORMAT "\n",
            i, u, b ? "TRUE" : "FALSE", s);
    g_print("gpointer is NULL: %s\n", p == NULL ? "yes" : "no");

    /* 1.2 GLib 版本 */
    g_print("GLib 版本: %d.%d.%d\n",
            GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

    /* 1.3 断言：g_assert 失败则终止；g_return_if_fail 用于参数检查 */
    g_assert(i > 0);

    /* 1.4 常用工具宏 */
    g_print("CLAMP(15, 0, 10) = %d\n", CLAMP(15, 0, 10));
    g_print("MAX(3, 7) = %d, MIN(3, 7) = %d\n", MAX(3, 7), MIN(3, 7));

    gint arr[] = {1, 2, 3, 4, 5};
    g_print("G_N_ELEMENTS(arr) = %" G_GSIZE_FORMAT "\n", G_N_ELEMENTS(arr));

    g_print("\n");
}

/* =====================================================================
 * 第 2 章：核心数据类型与内存管理
 *   知识点：g_malloc 系列、g_slice、★g_autoptr/g_autofree、GString、GError
 * ===================================================================== */

/* 一个会返回 GError 的辅助函数，演示错误处理 */
static gboolean chapter2_parse_int(const gchar *str, gint *out, GError **error)
{
    g_return_val_if_fail(error == NULL || *error == NULL, FALSE);
    if (str == NULL || *str == '\0') {
        g_set_error(error, g_quark_from_static_string("ch2-error"),
                    1, "空字符串无法解析");
        return FALSE;
    }
    gchar *end = NULL;
    gint v = (gint)g_ascii_strtoull(str, &end, 10);
    if (end == str) {
        g_set_error(error, g_quark_from_static_string("ch2-error"),
                    2, "'%s' 不是合法数字", str);
        return FALSE;
    }
    *out = v;
    return TRUE;
}

static void chapter2_memory_test(void)
{
    g_print("===== 第 2 章：内存管理与字符串 =====\n");

    /* 2.1 g_malloc / g_realloc / g_free（失败时直接终止，无需检查 NULL） */
    gchar *buf = g_malloc(16);
    g_strlcpy(buf, "g_malloc", 16);
    buf = g_realloc(buf, 64);
    g_strlcat(buf, " + realloc", 64);
    g_print("内存: %s\n", buf);
    g_free(buf);

    /* 2.2 g_slice —— 固定大小小块内存的高效分配器 */
    gchar *slice = g_slice_alloc(32);
    g_strlcpy(slice, "from g_slice", 32);
    g_print("Slice: %s\n", slice);
    g_slice_free1(32, slice);

    /* 2.3 ★ g_autoptr / g_autofree：现代 GLib 自动清理宏
       变量离开作用域时自动调用对应的释放函数，杜绝内存泄漏 */
    {
        g_autofree gchar *auto_str = g_strdup("自动释放的字符串");
        g_autoptr(GString) auto_gs = g_string_new("自动释放的 GString");
        g_string_append(auto_gs, " (附加上内容)");
        g_print("g_autofree: %s\n", auto_str);
        g_print("g_autoptr: %s\n", auto_gs->str);
        /* 离开作用域时：auto_str 调用 g_free，auto_gs 调用 g_string_free */
    }

    /* 2.4 g_steal_pointer：转移所有权，原指针置 NULL 避免悬垂 */
    {
        g_autofree gchar *owner = g_strdup("所有权转移");
        gchar *receiver = g_steal_pointer(&owner);  /* owner 变为 NULL */
        g_print("steal 后 owner=%p, receiver='%s'\n", (gpointer)owner, receiver);
        g_free(receiver);
    }

    /* 2.5 GString 动态字符串 */
    {
        g_autoptr(GString) gs = g_string_new("Hello");
        g_string_append(gs, ", ");
        g_string_append_printf(gs, "PI=%.2f, Year=%d", 3.14, 2026);
        g_string_prepend_c(gs, '>');
        g_print("GString: %s (len=%" G_GSIZE_FORMAT ")\n", gs->str, gs->len);
    }

    /* 2.6 g_strdup_printf —— 格式化复制字符串 */
    {
        g_autofree gchar *formatted = g_strdup_printf("格式化: %d-%s", 2026, "GLib");
        g_print("g_strdup_printf: %s\n", formatted);
    }

    /* 2.7 字符串工具集：切分、连接、路径规范化 */
    {
        g_auto(GStrv) parts = g_strsplit("a,b,,c", ",", -1);
        g_print("切分 'a,b,,c':");
        for (gint k = 0; parts[k] != NULL; k++) g_print(" [%s]", parts[k]);
        g_print("\n");

        g_autofree gchar *joined = g_strjoinv("|", parts);
        g_print("用 | 连接: %s\n", joined);

        g_autofree gchar *canonical = g_canonicalize_filename("./a/b/../c.txt", NULL);
        g_print("路径规范化: %s\n", canonical);
    }

    /* 2.8 GError 错误处理 */
    {
        GError *err = NULL;
        gint    value = 0;

        if (chapter2_parse_int("2026", &value, &err)) {
            g_print("解析成功: %d\n", value);
        } else {
            g_printerr("解析失败: %s\n", err->message);
            g_error_free(err);
            err = NULL;
        }

        if (!chapter2_parse_int("abc", &value, &err)) {
            g_print("捕获错误: %s\n", err->message);
            g_error_free(err);
            err = NULL;
        }
    }

    g_print("\n");
}

/* =====================================================================
 * 第 3 章：常用数据结构（容器）
 *   知识点：GArray/GPtrArray/GByteArray、GHashTable、GSList/GList、GQueue、GTree
 * ===================================================================== */

/* GTree 遍历回调 */
static gboolean chapter3_tree_traverse(gpointer key, gpointer value, gpointer data)
{
    (void)data;
    g_print(" %d=%s", GPOINTER_TO_INT(key), (gchar *)value);
    return FALSE;
}

static gint chapter3_int_compare(gconstpointer a, gconstpointer b)
{
    return GPOINTER_TO_INT(a) - GPOINTER_TO_INT(b);
}

static void chapter3_containers_test(void)
{
    g_print("===== 第 3 章：常用数据结构 =====\n");

    /* 3.1 GArray 动态数组（基本类型） */
    {
        g_autoptr(GArray) arr = g_array_new(FALSE, FALSE, sizeof(gint));
        for (gint v = 1; v <= 3; v++) g_array_append_val(arr, v);
        g_print("GArray:");
        for (guint k = 0; k < arr->len; k++) g_print(" %d", g_array_index(arr, gint, k));
        g_print("\n");
        /* g_autoptr 会自动调用 g_array_unref */
    }

    /* 3.2 GPtrArray 指针数组（带 free_func 自动释放元素） */
    {
        g_autoptr(GPtrArray) parr = g_ptr_array_new_with_free_func(g_free);
        g_ptr_array_add(parr, g_strdup("alpha"));
        g_ptr_array_add(parr, g_strdup("beta"));
        g_print("GPtrArray:");
        for (guint k = 0; k < parr->len; k++) g_print(" %s", (gchar *)g_ptr_array_index(parr, k));
        g_print("\n");
    }

    /* 3.3 GByteArray 字节数组 */
    {
        g_autoptr(GByteArray) ba = g_byte_array_new();
        g_byte_array_append(ba, (const guint8 *)"bytes", 5);
        g_print("GByteArray: len=%u\n", ba->len);
    }

    /* 3.4 GHashTable 哈希表（带 key/value 销毁函数） */
    {
        g_autoptr(GHashTable) ht = g_hash_table_new_full(g_str_hash, g_str_equal,
                                                          g_free, g_free);
        g_hash_table_insert(ht, g_strdup("lang"),    g_strdup("C"));
        g_hash_table_insert(ht, g_strdup("lib"),     g_strdup("GLib"));
        g_hash_table_insert(ht, g_strdup("license"), g_strdup("LGPL"));
        g_print("GHashTable size=%u, 'lib'='%s'\n",
                g_hash_table_size(ht),
                (gchar *)g_hash_table_lookup(ht, "lib"));

        /* 用 GHashTableIter 遍历 */
        GHashTableIter iter;
        gpointer k, v;
        g_hash_table_iter_init(&iter, ht);
        g_print("  遍历:");
        while (g_hash_table_iter_next(&iter, &k, &v)) {
            g_print(" %s=%s", (gchar *)k, (gchar *)v);
        }
        g_print("\n");
    }

    /* 3.5 GList 双向链表 */
    {
        GList *list = NULL;
        list = g_list_append(list, "b");
        list = g_list_prepend(list, "a");
        list = g_list_append(list, "c");
        g_print("GList:");
        for (GList *n = list; n; n = n->next) g_print(" %s", (gchar *)n->data);
        g_print("\n");
        g_list_free(list);
    }

    /* 3.6 GSList 单向链表 */
    {
        GSList *slist = NULL;
        slist = g_slist_append(slist, "x");
        slist = g_slist_append(slist, "y");
        g_print("GSList:");
        for (GSList *n = slist; n; n = n->next) g_print(" %s", (gchar *)n->data);
        g_print("\n");
        g_slist_free(slist);
    }

    /* 3.7 GQueue 双端队列 */
    {
        g_autoptr(GQueue) q = g_queue_new();
        g_queue_push_tail(q, "head");
        g_queue_push_head(q, "front");
        g_print("GQueue pop_head: %s\n", (gchar *)g_queue_pop_head(q));
        /* g_queue_free 已被 g_queue_unref 替代，g_autoptr 自动调用 unref */
    }

    /* 3.8 GTree 平衡二叉树（有序映射） */
    {
        g_autoptr(GTree) tree = g_tree_new(chapter3_int_compare);
        g_tree_insert(tree, GINT_TO_POINTER(3), "three");
        g_tree_insert(tree, GINT_TO_POINTER(1), "one");
        g_tree_insert(tree, GINT_TO_POINTER(2), "two");
        g_print("GTree (升序):");
        g_tree_foreach(tree, chapter3_tree_traverse, NULL);
        g_print("\n");
    }

    g_print("\n");
}

/* =====================================================================
 * 第 4 章：事件驱动基石——主循环与并发
 *   知识点：GMainLoop、g_timeout_add、g_idle_add、GThread、GMutex、GCond
 * ===================================================================== */

typedef struct
{
    GMutex  mutex;
    GCond   cond;
    gint    value;
    gboolean done;
} Chapter4Shared;

static gpointer chapter4_thread_func(gpointer data)
{
    Chapter4Shared *sh = (Chapter4Shared *)data;
    g_usleep(50 * 1000);  /* 模拟耗时工作 */
    g_mutex_lock(&sh->mutex);
    sh->value = 42;
    sh->done  = TRUE;
    g_cond_signal(&sh->cond);   /* 通知等待的主线程 */
    g_mutex_unlock(&sh->mutex);
    return NULL;
}

static gboolean chapter4_on_timeout(gpointer user_data)
{
    static gint count = 0;
    count++;
    g_print("  [timeout] tick #%d\n", count);
    if (count >= 2) {
        g_main_loop_quit((GMainLoop *)user_data);
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

static gboolean chapter4_on_idle(gpointer user_data)
{
    (void)user_data;
    g_print("  [idle] 空闲回调执行一次\n");
    return G_SOURCE_REMOVE;
}

static void chapter4_mainloop_thread_test(void)
{
    g_print("===== 第 4 章：事件循环与并发 =====\n");

    /* 4.1 GThread + GMutex + GCond：线程同步 */
    Chapter4Shared sh = {0};
    g_mutex_init(&sh.mutex);
    g_cond_init(&sh.cond);

    GThread *th = g_thread_new("worker", chapter4_thread_func, &sh);
    g_print("  [main] 等待子线程结果...\n");
    g_mutex_lock(&sh.mutex);
    while (!sh.done) {
        g_cond_wait(&sh.cond, &sh.mutex);
    }
    g_print("  [main] 子线程返回 value=%d\n", sh.value);
    g_mutex_unlock(&sh.mutex);
    g_thread_join(th);
    g_mutex_clear(&sh.mutex);
    g_cond_clear(&sh.cond);

    /* 4.2 GMainLoop + timeout + idle */
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_idle_add(chapter4_on_idle, NULL);
    g_timeout_add(80, chapter4_on_timeout, loop);
    g_print("  [main] 进入事件循环...\n");
    g_main_loop_run(loop);
    g_print("  [main] 事件循环退出\n");
    g_main_loop_unref(loop);

    g_print("\n");
}

/* =====================================================================
 * 第二部分：GObject 面向对象系统（第 5~8 章）
 * ===================================================================== */

/* =====================================================================
 * 第 5 章：GObject 类型系统初探
 *   知识点：GType、类型注册、类型检查、安全转换宏、G_DEFINE_TYPE
 * ===================================================================== */
static void chapter5_gtype_test(void)
{
    g_print("===== 第 5 章：GType 类型系统 =====\n");

    /* 5.1 类型 ID 与名称互查 */
    GType t_str = G_TYPE_STRING;
    g_print("G_TYPE_STRING = %lu, name='%s'\n",
            (gulong)t_str, g_type_name(t_str));

    /* 5.2 类型层次查询 */
    g_print("G_TYPE_OBJECT 是否基本类型: %s\n",
            G_TYPE_IS_FUNDAMENTAL(G_TYPE_OBJECT) ? "yes" : "no");
    g_print("G_TYPE_INT 是否基本类型: %s\n",
            G_TYPE_IS_FUNDAMENTAL(G_TYPE_INT) ? "yes" : "no");

    /* 5.3 类型检查与安全转换宏（前文已定义 TYPE_DOG 等） */
    g_print("TYPE_DOG 名称: %s\n", g_type_name(TYPE_DOG));
    g_print("TYPE_DOG 的父类型: %s\n", g_type_name(g_type_parent(TYPE_DOG)));

    /* 5.4 检查继承关系：g_type_is_a */
    g_print("Dog 是否派生自 Animal: %s\n",
            g_type_is_a(TYPE_DOG, TYPE_ANIMAL) ? "yes" : "no");
    g_print("Dog 是否派生自 GObject: %s\n",
            g_type_is_a(TYPE_DOG, G_TYPE_OBJECT) ? "yes" : "no");

    /* 5.5 类结构与实例结构分离：通过 class pointer 访问虚函数表 */
    g_autoptr(Dog) d = dog_new("Rex");
    AnimalClass *cls = ANIMAL_GET_CLASS(d);
    g_print("Dog 实例的 speak 虚函数是否被覆写: %s\n",
            cls->speak != animal_speak_default ? "yes" : "no");

    g_print("\n");
}

/* =====================================================================
 * 第 6 章：对象的生命周期与内存管理
 *   知识点：g_object_new、引用计数、weak_ref、★dispose vs finalize、g_autoptr
 * ===================================================================== */

static void chapter6_on_weak_notify(gpointer data, GObject *where_the_object_was)
{
    (void)data; (void)where_the_object_was;
    g_print("  [weak_ref] 对象即将销毁\n");
}

static void chapter6_lifecycle_test(void)
{
    g_print("===== 第 6 章：对象生命周期与引用计数 =====\n");

    /* 6.1 实例化：g_object_new 创建对象，初始引用计数 = 1 */
    Dog *d = dog_new("Buddy");
    g_print("  创建 Dog，初始 ref_count = 1\n");

    /* 6.2 引用计数 */
    g_object_ref(d);   /* ref_count -> 2 */
    g_print("  g_object_ref 后 ref_count = 2\n");
    g_object_unref(d); /* ref_count -> 1 */
    g_object_unref(d); /* ref_count -> 0，触发 dispose + finalize */
    g_print("  两次 unref 后对象已销毁（注意上面的 dispose/finalize 日志）\n");

    /* 6.3 弱引用：不增加引用计数，对象销毁前回调 */
    Dog *d2 = dog_new("Weak");
    g_object_weak_ref(G_OBJECT(d2), chapter6_on_weak_notify, NULL);
    g_print("  设置 weak_ref 后销毁对象:\n");
    g_object_unref(d2);

    /* 6.4 ★ g_autoptr 自动管理 GObject 生命周期
       变量离开作用域时自动调用 g_object_unref */
    {
        g_autoptr(Dog) auto_dog = dog_new("Auto");
        g_print("  g_autoptr 管理的对象: %s\n",
                ANIMAL_GET_PRIVATE(auto_dog)->name);
        /* 离开作用域自动 unref，无需手动释放 */
    }
    g_print("  g_autoptr 已自动释放\n");

    /* 6.5 dispose vs finalize 对比（见前文 animal_dispose/finalize 实现）
       - dispose：释放对其他 GObject 的强引用，可被多次调用
       - finalize：释放私有数据持有的资源，仅调用一次
       两者都通过 parent_class 链式调用父类实现 */

    g_print("\n");
}

/* =====================================================================
 * 第 7 章：封装、继承与多态
 *   知识点：G_ADD_PRIVATE 私有数据、继承链、虚函数覆写、★GInterface 接口
 * ===================================================================== */
static void chapter7_oop_test(void)
{
    g_print("===== 第 7 章：封装、继承与多态 =====\n");

    /* 7.1 多态：同一个父类指针调用 speak，行为由子类决定 */
    g_autoptr(Dog) dog = dog_new("Rex");
    g_autoptr(Cat) cat = cat_new("Kitty");
    Animal *animals[] = { ANIMAL(dog), ANIMAL(cat) };

    g_print("  多态调用 speak():\n");
    for (gsize k = 0; k < G_N_ELEMENTS(animals); k++) {
        animal_speak(animals[k]);
    }

    /* 7.2 封装：私有数据通过属性访问，子类无法直接读取 */
    gchar *name = NULL;
    g_object_get(G_OBJECT(dog), "name", &name, NULL);
    g_print("  通过属性读取 Dog 私有数据 name=%s\n", name);
    g_free(name);

    /* 7.3 ★ GInterface 接口：Cat 实现 Greeter 接口（模拟多继承） */
    g_print("  Cat 是否实现 Greeter 接口: %s\n",
            GREETER_IS_GREETER(cat) ? "yes" : "no");
    if (GREETER_IS_GREETER(cat)) {
        greeter_greet(GREETER(cat));
    }

    /* 7.4 继承链：Dog/Cat 都继承自 Animal，Animal 继承自 GObject */
    g_print("  继承链: Dog -> Animal -> GObject\n");
    g_print("  Cat 实现接口: Greeter\n");

    g_print("\n");
}

/* =====================================================================
 * 第 8 章：高级对象特性：属性与信号
 *   知识点：GParamSpec、get/set_property、notify、g_signal_new/connect/emit、信号阻塞
 * ===================================================================== */

static void chapter8_on_fed(GObject *obj, gpointer user_data)
{
    (void)obj;
    g_print("  [信号回调] %s - 动物被喂食了！\n", (gchar *)user_data);
}

static void chapter8_on_notify(GObject *obj, GParamSpec *pspec, gpointer user_data)
{
    (void)obj; (void)user_data;
    g_autofree gchar *val = NULL;
    g_object_get(obj, pspec->name, &val, NULL);
    g_print("  [notify] 属性 '%s' 变为 '%s'\n", pspec->name, val);
}

static void chapter8_signal_property_test(void)
{
    g_print("===== 第 8 章：属性与信号 =====\n");

    g_autoptr(Dog) dog = dog_new("Max");

    /* 8.1 信号：连接、发射 */
    gulong sid = g_signal_connect(G_OBJECT(dog), "fed",
                                  G_CALLBACK(chapter8_on_fed), (gpointer)"Max");
    g_print("  发射信号 fed (id=%lu):\n", sid);
    g_signal_emit_by_name(G_OBJECT(dog), "fed");

    /* 8.2 信号阻塞与解除阻塞 */
    g_signal_handler_block(G_OBJECT(dog), sid);
    g_print("  阻塞后再次发射（无回调）:\n");
    g_signal_emit_by_name(G_OBJECT(dog), "fed");
    g_signal_handler_unblock(G_OBJECT(dog), sid);

    /* 8.3 属性：set / get / notify 通知信号 */
    g_signal_connect(G_OBJECT(dog), "notify::name",
                     G_CALLBACK(chapter8_on_notify), NULL);
    g_print("  修改属性 name:\n");
    g_object_set(G_OBJECT(dog), "name", "MaxII", NULL);

    /* 8.4 属性批量设置 */
    g_print("  批量属性操作:\n");
    g_object_set(G_OBJECT(dog), "name", "FinalName", NULL);
    g_autofree gchar *final_name = NULL;
    g_object_get(G_OBJECT(dog), "name", &final_name, NULL);
    g_print("  最终 name = %s\n", final_name);

    g_print("\n");
}

/* =====================================================================
 * 第三部分：GIO 现代系统编程（第 9~12 章）
 * ===================================================================== */

/* =====================================================================
 * 第 9 章：GIO 概览与 GFile 抽象
 *   知识点：GFile、同步文件读写、GFileInfo、GFileEnumerator、复制/删除
 * ===================================================================== */
static void chapter9_gfile_test(void)
{
    g_print("===== 第 9 章：GFile 文件抽象 =====\n");

    GError *err = NULL;

    /* 9.1 GFile 创建与同步写入（replace_contents 一次性写入） */
    g_autoptr(GFile) file = g_file_new_for_path("gio_demo.txt");
    const gchar *text = "GIO demo line 1\nGIO demo line 2\n";
    if (!g_file_replace_contents(file, text, strlen(text),
                                 NULL, FALSE, G_FILE_CREATE_NONE,
                                 NULL, NULL, &err)) {
        g_print("  写入失败: %s\n", err->message);
        g_error_free(err);
        return;
    }
    g_print("  已写入 gio_demo.txt\n");

    /* 9.2 同步读取全部内容 */
    g_autofree gchar *content = NULL;
    gsize length = 0;
    if (g_file_load_contents(file, NULL, &content, &length, NULL, &err)) {
        g_print("  读取到 %lu 字节:\n%s", (gulong)length, content);
    } else {
        g_print("  读取失败: %s\n", err->message);
        g_error_free(err);
        err = NULL;
    }

    /* 9.3 文件信息查询 GFileInfo */
    g_autoptr(GFileInfo) info = g_file_query_info(file,
        "standard::name,standard::size", G_FILE_QUERY_INFO_NONE, NULL, &err);
    if (info != NULL) {
        g_print("  文件信息: name=%s, size=%" G_GINT64_FORMAT "\n",
                g_file_info_get_name(info), g_file_info_get_size(info));
    }

    /* 9.4 目录遍历 GFileEnumerator */
    g_autoptr(GFile) dir = g_file_new_for_path(".");
    g_autoptr(GFileEnumerator) enu = g_file_enumerate_children(dir,
        "standard::name", G_FILE_QUERY_INFO_NONE, NULL, &err);
    if (enu != NULL) {
        g_print("  当前目录前 3 个文件:\n");
        gint n = 0;
        GFileInfo *child = NULL;
        while (n < 3 && (child = g_file_enumerator_next_file(enu, NULL, NULL)) != NULL) {
            g_print("    - %s\n", g_file_info_get_name(child));
            g_object_unref(child);
            n++;
        }
    }

    /* 9.5 复制与删除 */
    g_autoptr(GFile) copy = g_file_new_for_path("gio_demo_copy.txt");
    if (g_file_copy(file, copy, G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, &err)) {
        g_print("  已复制为 gio_demo_copy.txt 并删除\n");
        g_file_delete(copy, NULL, NULL);
    } else {
        g_error_free(err);
        err = NULL;
    }

    g_file_delete(file, NULL, NULL);
    g_print("\n");
}

/* =====================================================================
 * 第 10 章：流式 I/O 模型
 *   知识点：GInputStream/GOutputStream、★GFilterInputStream 缓冲流
 * ===================================================================== */
static void chapter10_stream_test(void)
{
    g_print("===== 第 10 章：流式 I/O 模型 =====\n");

    GError *err = NULL;

    /* 10.1 准备测试文件 */
    g_autoptr(GFile) file = g_file_new_for_path("gio_stream_demo.txt");
    g_file_replace_contents(file, "Stream IO demo content\n",
                            strlen("Stream IO demo content\n"),
                            NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, &err);

    /* 10.2 GFileInputStream —— 基础输入流 */
    GFileInputStream *fin = g_file_read(file, NULL, &err);
    if (fin == NULL) {
        g_print("  打开输入流失败: %s\n", err->message);
        g_error_free(err);
        return;
    }

    /* 10.3 ★ GBufferedInputStream —— 缓冲过滤流
       包装基础流，提供缓冲读取，减少系统调用次数 */
    GInputStream *buffered = g_buffered_input_stream_new(G_INPUT_STREAM(fin));
    g_print("  是否为 GFilterInputStream: %s\n",
            G_IS_FILTER_INPUT_STREAM(buffered) ? "yes" : "no");

    gchar rbuf[128] = {0};
    gsize bytes_read = 0;
    if (g_input_stream_read_all(buffered, rbuf, sizeof(rbuf) - 1,
                                &bytes_read, NULL, &err)) {
        g_print("  缓冲流读取到 %lu 字节:\n  %s", (gulong)bytes_read, rbuf);
    }

    /* 10.4 流与 GObject 生命周期结合：g_autoptr 自动关闭
       GInputStream 实现了 GInitable，g_object_unref 时会自动 close */
    g_input_stream_close(buffered, NULL, NULL);
    g_object_unref(buffered);
    g_object_unref(fin);

    /* 10.5 GFileOutputStream —— 输出流 */
    GFileOutputStream *fout = g_file_replace(file, NULL, FALSE,
                                             G_FILE_CREATE_NONE, NULL, &err);
    if (fout != NULL) {
        const gchar *new_text = "Overwritten via stream\n";
        gsize bytes_written = 0;
        g_output_stream_write_all(G_OUTPUT_STREAM(fout), new_text,
                                  strlen(new_text), &bytes_written, NULL, &err);
        g_print("  输出流写入 %lu 字节\n", (gulong)bytes_written);
        g_output_stream_close(G_OUTPUT_STREAM(fout), NULL, NULL);
        g_object_unref(fout);
    }

    g_file_delete(file, NULL, NULL);
    g_print("\n");
}

/* =====================================================================
 * 第 11 章：异步编程模型
 *   知识点：异步三件套 _async/_finish/GCancellable、★GTask
 * ===================================================================== */

static void chapter11_on_load_async(GObject      *source,
                                    GAsyncResult *res,
                                    gpointer      user_data)
{
    GFile     *file  = G_FILE(source);
    GMainLoop *loop  = (GMainLoop *)user_data;
    GError    *err   = NULL;
    gchar     *content = NULL;
    gsize      length  = 0;

    if (g_file_load_contents_finish(file, res, &content, &length, NULL, &err)) {
        g_print("  异步读取成功，共 %lu 字节\n", (gulong)length);
        g_free(content);
    } else {
        g_print("  异步读取失败: %s\n", err->message);
        g_error_free(err);
    }
    g_main_loop_quit(loop);
}

static void chapter11_async_test(void)
{
    g_print("===== 第 11 章：异步编程模型 =====\n");

    GError *err = NULL;

    /* 11.1 准备测试文件 */
    g_autoptr(GFile) file = g_file_new_for_path("gio_async_demo.txt");
    g_file_replace_contents(file, "Async IO demo content\n",
                            strlen("Async IO demo content\n"),
                            NULL, FALSE, G_FILE_CREATE_NONE,
                            NULL, NULL, &err);

    /* 11.2 GCancellable 取消机制 */
    g_autoptr(GCancellable) cancellable = g_cancellable_new();
    g_print("  GCancellable 是否已取消: %s\n",
            g_cancellable_is_cancelled(cancellable) ? "yes" : "no");

    /* 11.3 异步读取：_async + 回调 + GMainLoop
       异步三件套：g_file_load_contents_async → 回调 → g_file_load_contents_finish */
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_file_load_contents_async(file, cancellable,
                               chapter11_on_load_async, loop);
    g_print("  已发起异步读取请求，进入事件循环等待...\n");
    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    /* 11.4 取消演示：cancel 后同步读取会得到 G_IO_ERROR_CANCELLED */
    GCancellable *cancel2 = g_cancellable_new();
    g_cancellable_cancel(cancel2);
    gchar *content = NULL;
    gsize  length  = 0;
    if (!g_file_load_contents(file, cancel2, &content, &length, NULL, &err)) {
        g_print("  取消后读取得到错误: %s\n",
                err->code == G_IO_ERROR_CANCELLED ? "G_IO_ERROR_CANCELLED" : err->message);
        g_error_free(err);
        err = NULL;
    } else {
        g_free(content);
    }
    g_object_unref(cancel2);

    /* 11.5 ★ GTask —— 现代 GIO 异步任务的统一封装
       用 g_task_new 创建任务，g_task_return_* 返回结果，g_task_propagate_* 取结果 */
    {
        g_autoptr(GTask) task = g_task_new(NULL, NULL, NULL, NULL);
        g_task_return_int(task, 2026);   /* 在任务中返回结果 */
        gint result = g_task_propagate_int(task, NULL);  /* 取出结果 */
        g_print("  GTask 返回值: %d\n", result);
    }

    g_file_delete(file, NULL, NULL);
    g_print("\n");
}

/* =====================================================================
 * 第 12 章：GIO 高级应用与系统集成
 *   知识点：GApplication、GFileMonitor、★GSettings、★GDBus 概念
 * ===================================================================== */

static void chapter12_on_file_changed(GFileMonitor      *monitor,
                                      GFile             *file,
                                      GFile             *other,
                                      GFileMonitorEvent  event,
                                      gpointer           user_data)
{
    (void)monitor; (void)other; (void)user_data;
    if (event == G_FILE_MONITOR_EVENT_CHANGED ||
        event == G_FILE_MONITOR_EVENT_CHANGES_DONE_HINT) {
        g_print("  [GFileMonitor] 捕获事件 %d on: %s\n",
                event, g_file_get_basename(file));
    }
}

static void chapter12_on_app_activate(GApplication *app, gpointer user_data)
{
    (void)user_data;
    g_print("  [GApplication] activate 信号触发\n");
    g_application_hold(app);
    g_application_release(app);
}

static void chapter12_advanced_test(void)
{
    g_print("===== 第 12 章：GIO 高级应用 =====\n");

    /* 12.1 GApplication —— 标准化应用框架（这里仅创建不 run，避免阻塞） */
    {
        g_autoptr(GApplication) app = g_application_new("org.example.GlibTutorial",
                                                         G_APPLICATION_NON_UNIQUE);
        g_signal_connect(app, "activate", G_CALLBACK(chapter12_on_app_activate), NULL);
        g_print("  GApplication 已创建（未调用 run 以避免阻塞教学流程）\n");
    }

    /* 12.2 GFileMonitor —— 实时监听文件变化
       Windows 上 GFileMonitor 的事件派发依赖 main loop，为避免阻塞教学流程，
       这里只演示 monitor 的创建与信号连接，不实际 run main loop 等待事件 */
    {
        GError *err = NULL;
        g_autoptr(GFile) file = g_file_new_for_path("gio_monitor_demo.txt");
        g_file_replace_contents(file, "v1\n", 3, NULL, FALSE,
                                G_FILE_CREATE_NONE, NULL, NULL, &err);

        g_autoptr(GFileMonitor) monitor = g_file_monitor_file(file,
            G_FILE_MONITOR_NONE, NULL, &err);
        if (monitor != NULL) {
            g_signal_connect(monitor, "changed",
                             G_CALLBACK(chapter12_on_file_changed), NULL);
            g_print("  [GFileMonitor] 已创建并连接 'changed' 信号\n");
            g_print("    在真实应用中，需配合 GMainLoop 监听文件变化事件\n");
        } else {
            g_print("  创建 monitor 失败: %s\n", err->message);
            g_error_free(err);
        }
        g_file_delete(file, NULL, NULL);
    }

    /* 12.3 ★ GSettings —— 应用配置持久化
       注：完整使用需要安装 schema，这里仅展示 API 概念 */
    {
        g_print("  [GSettings] 概念演示：\n");
        g_print("    - 通过 g_settings_new(\"org.example.app\") 创建\n");
        g_print("    - g_settings_get_string / set_string 读写配置\n");
        g_print("    - g_settings_bind 绑定到 GObject 属性\n");
        g_print("    - 配置自动持久化到 ~/.config/dconf/\n");
    }

    /* 12.4 ★ GDBus —— 系统总线通信（概念演示）
       GIO 提供 GDBus 进行进程间通信：
       - g_bus_get_sync 获取系统/会话总线
       - g_dbus_proxy_new_sync 创建代理对象
       - g_dbus_proxy_call_sync 同步调用远程方法 */
    {
        g_print("  [GDBus] 概念演示：\n");
        g_print("    - g_bus_get_sync(G_BUS_TYPE_SESSION, ...) 获取会话总线\n");
        g_print("    - g_dbus_proxy_new_sync 创建代理\n");
        g_print("    - g_dbus_proxy_call_sync 调用远程方法\n");
    }

    g_print("\n");
}

/* =====================================================================
 * 第四部分：综合实战（第 13 章）
 * ===================================================================== */

/* =====================================================================
 * 第 13 章：实战项目 —— 异步文件扫描分析器
 *   整合：GObject 子类化 + GIO 文件操作 + GHashTable 统计 + 信号通知
 * ===================================================================== */
static void chapter13_practice_test(void)
{
    g_print("===== 第 13 章：实战 —— 文件扫描分析器 =====\n");

    /* 13.1 创建 FileAnalyzer 实例（g_autoptr 自动管理） */
    g_autoptr(FileAnalyzer) analyzer = file_analyzer_new();

    /* 13.2 连接信号：进度 + 完成 */
    g_signal_connect(analyzer, "progress",
                     G_CALLBACK(chapter13_on_progress), NULL);
    g_signal_connect(analyzer, "done",
                     G_CALLBACK(chapter13_on_done), NULL);

    /* 13.3 准备测试目录：创建几个不同扩展名的文件 */
    g_print("  准备测试目录 analyzer_demo/...\n");
    g_mkdir("analyzer_demo", 0755);
    const gchar *files[] = {
        "analyzer_demo/a.txt", "analyzer_demo/b.txt", "analyzer_demo/c.c",
        "analyzer_demo/d.c", "analyzer_demo/e.h", "analyzer_demo/f.md",
        "analyzer_demo/README"  /* 无扩展名 */
    };
    for (gsize i = 0; i < G_N_ELEMENTS(files); i++) {
        g_file_set_contents(files[i], "x", 1, NULL);
    }

    /* 13.4 扫描目录（同步版，信号会推送进度） */
    g_print("  开始扫描 analyzer_demo/...\n");
    g_autoptr(GCancellable) cancellable = g_cancellable_new();
    file_analyzer_scan_sync(analyzer, "analyzer_demo", cancellable);

    /* 13.5 打印统计结果 */
    file_analyzer_print_stats(analyzer);

    /* 13.6 清理测试文件 */
    for (gsize i = 0; i < G_N_ELEMENTS(files); i++) {
        g_unlink(files[i]);
    }
    g_rmdir("analyzer_demo");
    g_print("  测试目录已清理\n");

    g_print("\n");
}

/* =====================================================================
 * 主函数：依次调用第 1 章到第 13 章
 * ===================================================================== */
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    /* GObject 类型系统初始化（显式调用更清晰） */
    g_type_ensure(G_TYPE_OBJECT);

    g_print("================================================================\n");
    g_print("  GLib / GObject / GIO 渐进式教学案例 —— 共十三章\n");
    g_print("================================================================\n");
    g_print("  第一部分  GLib 基础        （第 1~4 章）\n");
    g_print("  第二部分  GObject 对象系统  （第 5~8 章）\n");
    g_print("  第三部分  GIO 现代系统编程  （第 9~12 章）\n");
    g_print("  第四部分  综合实战          （第 13 章）\n");
    g_print("================================================================\n\n");

    chapter1_basics_test();
    chapter2_memory_test();
    chapter3_containers_test();
    chapter4_mainloop_thread_test();

    chapter5_gtype_test();
    chapter6_lifecycle_test();
    chapter7_oop_test();
    chapter8_signal_property_test();

    chapter9_gfile_test();
    chapter10_stream_test();
    chapter11_async_test();
    chapter12_advanced_test();

    chapter13_practice_test();

    g_print("全部十三章演示完毕。\n");
    return 0;
}
