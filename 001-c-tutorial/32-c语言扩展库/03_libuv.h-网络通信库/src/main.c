/**
 * libuv 渐进式学习代码
 * 涵盖 libuv 所有核心知识点
 *
 * 编译: gcc -o libuv-tutorial.exe main.c -luv -lws2_32 -liphlpapi
 * 运行: ./libuv-tutorial          (运行全部章节)
 *       ./libuv-tutorial 5        (只运行第5章)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <uv.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#include <sys/resource.h>
#endif

// 第一部分：事件循环与基础句柄
void chapter1_event_loop_test(void);
void chapter2_handle_request_test(void);
void chapter3_timer_test(void);
void chapter4_idle_prepare_check_test(void);

// 第二部分：I/O 操作
void chapter5_file_system_test(void);
void chapter6_tcp_test(void);
void chapter7_udp_test(void);

// 第三部分：进程间通信与系统
void chapter8_pipe_test(void);
void chapter9_tty_test(void);
void chapter10_signal_test(void);
void chapter11_process_test(void);

// 第四部分：高级特性
void chapter12_async_test(void);
void chapter13_thread_pool_test(void);
void chapter14_dns_test(void);
void chapter15_utilities_test(void);

/*
 * 第1章：事件循环 (Event Loop)
 * 参考：libuv documentation - The I/O loop
 */
void chapter1_event_loop_test(void)
{
    printf("\n=== 第1章：事件循环示例 ===\n");

    /* -- 默认事件循环 -- */
    printf("-- 默认事件循环 --\n");
    uv_loop_t *default_loop = uv_default_loop();
    printf("默认事件循环地址: %p\n", (void *)default_loop);
    printf("事件循环是否存活: %s\n", uv_loop_alive(default_loop) ? "是" : "否");

    /* -- 自定义事件循环 -- */
    printf("\n-- 自定义事件循环 --\n");
    uv_loop_t custom_loop;
    int r = uv_loop_init(&custom_loop);
    printf("uv_loop_init 返回值: %d (%s)\n", r, r == 0 ? "成功" : uv_strerror(r));
    printf("自定义循环是否存活: %s\n", uv_loop_alive(&custom_loop) ? "是" : "否");

    /* -- 事件循环配置 -- */
    printf("\n-- 事件循环配置 --\n");
    uv_loop_configure(&custom_loop, UV_LOOP_BLOCK_SIGNAL, SIGINT);
    printf("已配置 UV_LOOP_BLOCK_SIGNAL=SIGINT\n");

    /* -- 事件循环模式 -- */
    printf("\n-- 事件循环运行模式 --\n");
    printf("UV_RUN_DEFAULT: 运行直到没有活跃句柄和请求\n");
    printf("UV_RUN_ONCE:    运行一个循环迭代，若无活跃句柄则阻塞\n");
    printf("UV_RUN_NOWAIT:  运行一个循环迭代，不阻塞\n");

    /* -- 事件循环信息 -- */
    printf("\n-- 事件循环信息 --\n");
    printf("后端文件描述符: %d\n", uv_backend_fd(&custom_loop));
    printf("后端超时时间: %d ms\n", uv_backend_timeout(&custom_loop));

    /* -- 使用定时器演示事件循环运行 -- */
    printf("\n-- 运行事件循环 (带定时器) --\n");
    uv_timer_t timer;
    uv_timer_init(&custom_loop, &timer);
    uv_timer_start(&timer,
                   (uv_timer_cb)NULL,  /* 简单演示，不需要回调 */
                   0, 0);  /* 0ms 后触发，不重复 */

    /* 使用 UV_RUN_NOWAIT 非阻塞运行一次 */
    uv_run(&custom_loop, UV_RUN_NOWAIT);
    printf("UV_RUN_NOWAIT 执行完毕\n");

    /* 清理 */
    uv_timer_stop(&timer);
    uv_close((uv_handle_t *)&timer, NULL);
    uv_run(&custom_loop, UV_RUN_DEFAULT);  /* 让关闭回调完成 */
    r = uv_loop_close(&custom_loop);
    printf("uv_loop_close 返回值: %d (%s)\n", r, r == 0 ? "成功" : uv_strerror(r));

    /* -- 循环资源统计 -- */
    printf("\n-- 资源统计 --\n");
    printf("活跃句柄数: %lu\n", (unsigned long)uv_loop_alive(default_loop));
    printf("libuv 版本: %s\n", uv_version_string());
}

/*
 * 第2章：句柄与请求 (Handles and Requests)
 * 参考：libuv documentation - Handles and Requests
 */

// 通用缓冲区分配回调
static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    (void)handle;
    buf->base = (char *)malloc(suggested_size);
    buf->len = buf->base ? suggested_size : 0;
}

// 句柄类型名称映射
static const char *handle_type_name(uv_handle_type type)
{
    switch (type) {
    case UV_ASYNC:      return "UV_ASYNC";
    case UV_CHECK:      return "UV_CHECK";
    case UV_FS_EVENT:   return "UV_FS_EVENT";
    case UV_FS_POLL:    return "UV_FS_POLL";
    case UV_HANDLE:     return "UV_HANDLE";
    case UV_IDLE:       return "UV_IDLE";
    case UV_NAMED_PIPE: return "UV_NAMED_PIPE";
    case UV_POLL:       return "UV_POLL";
    case UV_PREPARE:    return "UV_PREPARE";
    case UV_PROCESS:    return "UV_PROCESS";
    case UV_SIGNAL:     return "UV_SIGNAL";
    case UV_TCP:        return "UV_TCP";
    case UV_TIMER:      return "UV_TIMER";
    case UV_TTY:        return "UV_TTY";
    case UV_UDP:        return "UV_UDP";
    default:            return "UNKNOWN";
    }
}

static void walk_callback(uv_handle_t *handle, void *arg)
{
    int *count = (int *)arg;
    (*count)++;
    printf("  句柄 #%d: 类型=%s, flags=0x%x, 正在关闭=%s\n",
            *count,
            handle_type_name(handle->type),
            handle->flags,
            uv_is_closing(handle) ? "是" : "否");
}

static void close_cb(uv_handle_t *handle)
{
    printf("  句柄关闭回调触发, 类型=%s\n", handle_type_name(handle->type));
}

void chapter2_handle_request_test(void)
{
    printf("\n=== 第2章：句柄与请求示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // 句柄生命周期
    printf("-- 句柄生命周期 --\n");
    printf("句柄生命周期: init -> start -> (活跃) -> stop -> close -> (关闭回调)\n");

    // 创建多种句柄
    printf("\n-- 创建多种句柄 --\n");
    uv_timer_t timer1, timer2;
    uv_idle_t idle1;

    uv_timer_init(loop, &timer1);
    uv_timer_init(loop, &timer2);
    uv_idle_init(loop, &idle1);

    printf("timer1 类型: %s\n", handle_type_name(((uv_handle_t *)&timer1)->type));
    printf("idle1 类型: %s\n", handle_type_name(((uv_handle_t *)&idle1)->type));

    // 句柄状态查询
    printf("\n-- 句柄状态查询 --\n");
    printf("timer1 是否活跃: %s\n", uv_is_active((uv_handle_t *)&timer1) ? "是" : "否");
    printf("timer1 是否正在关闭: %s\n", uv_is_closing((uv_handle_t *)&timer1) ? "是" : "否");

    // 启动句柄
    uv_timer_start(&timer1, NULL, 10000, 0);  /* 10秒后(不会真正等到) */
    printf("timer1 启动后是否活跃: %s\n", uv_is_active((uv_handle_t *)&timer1) ? "是" : "否");

    // 句柄引用计数
    printf("\n-- 句柄引用 (ref/unref) --\n");
    printf("timer1 是否被引用: %s\n", uv_has_ref((uv_handle_t *)&timer1) ? "是" : "否");
    uv_unref((uv_handle_t *)&timer1);
    printf("uv_unref 后是否被引用: %s\n", uv_has_ref((uv_handle_t *)&timer1) ? "是" : "否");
    uv_ref((uv_handle_t *)&timer1);
    printf("uv_ref 后是否被引用: %s\n", uv_has_ref((uv_handle_t *)&timer1) ? "是" : "否");

    // 遍历句柄
    printf("\n-- 遍历事件循环中的句柄 --\n");
    int handle_count = 0;
    uv_walk(loop, walk_callback, &handle_count);
    printf("总句柄数: %d\n", handle_count);

    // 句柄大小
    printf("\n-- 句柄大小 --\n");
    printf("uv_handle_t 大小: %zu 字节\n", sizeof(uv_handle_t));
    printf("uv_timer_t 大小: %zu 字节\n", sizeof(uv_timer_t));
    printf("uv_tcp_t 大小: %zu 字节\n", sizeof(uv_tcp_t));
    printf("uv_udp_t 大小: %zu 字节\n", sizeof(uv_udp_t));

    // 关闭句柄
    printf("\n-- 关闭句柄 --\n");
    uv_timer_stop(&timer1);
    uv_close((uv_handle_t *)&timer1, close_cb);
    uv_close((uv_handle_t *)&timer2, close_cb);
    uv_close((uv_handle_t *)&idle1, close_cb);

    // 运行一次让关闭回调执行
    uv_run(loop, UV_RUN_NOWAIT);
    printf("句柄关闭完毕\n");
}

/*
 * 第3章：定时器 (Timers)
 * 参考：libuv documentation - Timers
 */

static void on_timer_once(uv_timer_t *handle)
{
    printf("  [一次性定时器] 触发!\n");
}

static void on_timer_repeat(uv_timer_t *handle)
{
    int *count = (int *)handle->data;
    (*count)++;
    printf("  [重复定时器] 第 %d 次触发\n", *count);

    if (*count >= 3) {
        printf("  [重复定时器] 已达3次，停止\n");
        uv_timer_stop(handle);
    }
}

static void on_timer_again(uv_timer_t *handle)
{
    int *count = (int *)handle->data;
    (*count)++;
    printf("  [timer_again] 第 %d 次触发\n", *count);

    if (*count >= 2) {
        // uv_timer_again 重新设置重复间隔
        printf("  [timer_again] 调用 uv_timer_again 重新启动\n");
        uv_timer_again(handle);
        if (*count >= 4) {
            uv_timer_stop(handle);
        }
    }
}

void chapter3_timer_test(void)
{
    printf("\n=== 第3章：定时器示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // 一次性定时器
    printf("-- 一次性定时器 --\n");
    uv_timer_t once_timer;
    uv_timer_init(loop, &once_timer);
    uv_timer_start(&once_timer, on_timer_once, 50, 0);  /* 50ms后触发，不重复 */
    printf("定时器到期时间: %llu ms\n", (unsigned long long)uv_timer_get_due_in(&once_timer));

    // 重复定时器
    printf("\n-- 重复定时器 --\n");
    static int repeat_count = 0;
    uv_timer_t repeat_timer;
    uv_timer_init(loop, &repeat_timer);
    repeat_timer.data = &repeat_count;
    uv_timer_start(&repeat_timer, on_timer_repeat, 30, 30);  /* 30ms后首次，每30ms重复 */
    printf("重复间隔: %llu ms\n", (unsigned long long)uv_timer_get_repeat(&repeat_timer));

    // timer_again
    printf("\n-- uv_timer_again --\n");
    static int again_count = 0;
    uv_timer_t again_timer;
    uv_timer_init(loop, &again_timer);
    again_timer.data = &again_count;
    // 先用 timer_start 设置初始超时，repeat=0
    uv_timer_start(&again_timer, on_timer_again, 20, 20);

    // 定时器停止与重新启动
    printf("\n-- 定时器停止与重新启动 --\n");
    uv_timer_t restart_timer;
    uv_timer_init(loop, &restart_timer);
    uv_timer_start(&restart_timer, on_timer_once, 1000, 0);
    uv_timer_stop(&restart_timer);
    printf("定时器已停止\n");
    // 重新启动
    uv_timer_start(&restart_timer, on_timer_once, 10, 0);
    printf("定时器已重新启动 (10ms)\n");

    // set_repeat
    printf("\n-- uv_timer_set_repeat --\n");
    uv_timer_set_repeat(&repeat_timer, 100);
    printf("修改后重复间隔: %llu ms\n", (unsigned long long)uv_timer_get_repeat(&repeat_timer));

    // 运行事件循环让定时器执行
    uv_run(loop, UV_RUN_DEFAULT);

    // 清理
    uv_close((uv_handle_t *)&restart_timer, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/*
 * 第4章：空闲、准备、检查句柄 (Idle, Prepare, Check)
 * 参考：libuv documentation - Idle, Prepare, Check
 */

static int idle_count = 0;

static void on_idle(uv_idle_t *handle)
{
    idle_count++;
    if (idle_count <= 3) {
        printf("  [idle] 第 %d 次空闲回调\n", idle_count);
    }
    if (idle_count >= 3) {
        uv_idle_stop(handle);
    }
}

static void on_prepare(uv_prepare_t *handle)
{
    printf("  [prepare] I/O 轮询前回调\n");
}

static void on_check(uv_check_t *handle)
{
    printf("  [check] I/O 轮询后回调\n");
    // 只运行一次
    uv_check_stop(handle);
    uv_prepare_stop((uv_prepare_t *)handle->data);
}

void chapter4_idle_prepare_check_test(void)
{
    printf("\n=== 第4章：空闲、准备、检查句柄示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // 事件循环阶段说明
    printf("-- 事件循环阶段 --\n");
    printf("1. uv_update_time -> 2. uv_prepare -> 3. I/O 轮询 -> 4. uv_check -> 5. uv_idle\n");

    // uv_idle_t
    printf("\n-- uv_idle_t 空闲句柄 --\n");
    printf("空闲回调在每次事件循环迭代中都会被调用（如果没有 I/O 时）\n");
    uv_idle_t idle;
    uv_idle_init(loop, &idle);
    uv_idle_start(&idle, on_idle);

    // uv_prepare_t
    printf("\n-- uv_prepare_t 准备句柄 --\n");
    uv_prepare_t prepare;
    uv_prepare_init(loop, &prepare);
    uv_prepare_start(&prepare, on_prepare);

    // uv_check_t
    printf("\n-- uv_check_t 检查句柄 --\n");
    uv_check_t check;
    uv_check_init(loop, &check);
    check.data = &prepare;  /* 让 check 回调可以停止 prepare */
    uv_check_start(&check, on_check);

    // 运行事件循环
    uv_run(loop, UV_RUN_DEFAULT);

    // 清理
    uv_close((uv_handle_t *)&idle, NULL);
    uv_close((uv_handle_t *)&prepare, NULL);
    uv_close((uv_handle_t *)&check, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/*
 * 第5章：文件系统操作 (File System Operations)
 * 参考：libuv documentation - File system operations
 */

static void fs_test_cb(uv_fs_t *req)
{
    printf("  [fs回调] 请求类型: %s, 结果: %ld\n",
            uv_fs_type_name(req->fs_type), (long)req->result);
}

void chapter5_file_system_test(void)
{
    printf("\n=== 第5章：文件系统操作示例 ===\n");

    uv_loop_t *loop = uv_default_loop();
    const char *test_file = "uv_test_file.txt";
    const char *test_dir = "uv_test_dir";
    const char *renamed_file = "uv_test_renamed.txt";
    const char *symlink_file = "uv_test_symlink.txt";
    uv_fs_t req;
    int r;

    // 同步文件操作
    printf("-- 同步文件操作 --\n");

    // uv_fs_open: 打开/创建文件
    r = uv_fs_open(loop, &req, test_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, NULL);
    uv_fs_req_cleanup(&req);
    int fd = r;
    printf("uv_fs_open: fd=%d\n", fd);

    // uv_fs_write: 写入数据
    uv_buf_t write_buf = uv_buf_init("Hello libuv!\n", 13);
    r = uv_fs_write(loop, &req, fd, &write_buf, 1, 0, NULL);
    printf("uv_fs_write: 写入 %d 字节\n", r);
    uv_fs_req_cleanup(&req);

    // uv_fs_close: 关闭文件
    uv_fs_close(loop, &req, fd, NULL);
    printf("uv_fs_close: 完成\n");
    uv_fs_req_cleanup(&req);

    // 异步文件操作
    printf("\n-- 异步文件操作 --\n");

    // uv_fs_stat: 获取文件信息
    r = uv_fs_stat(loop, &req, test_file, NULL);
    if (r == 0) {
        printf("uv_fs_stat: 文件大小=%llu 字节\n",
                (unsigned long long)req.statbuf.st_size);
        printf("uv_fs_stat: 文件模式=0x%x\n", (unsigned)req.statbuf.st_mode);
    }
    uv_fs_req_cleanup(&req);

    // uv_fs_rename: 重命名
    r = uv_fs_rename(loop, &req, test_file, renamed_file, NULL);
    printf("uv_fs_rename: %s\n", r == 0 ? "成功" : uv_strerror(r));
    uv_fs_req_cleanup(&req);

    // uv_fs_copyfile: 复制文件
    r = uv_fs_copyfile(loop, &req, renamed_file, test_file, 0, NULL);
    printf("uv_fs_copyfile: %s\n", r == 0 ? "成功" : uv_strerror(r));
    uv_fs_req_cleanup(&req);

    // uv_fs_symlink: 创建符号链接
    r = uv_fs_symlink(loop, &req, test_file, symlink_file, 0, NULL);
    printf("uv_fs_symlink: %s\n", r == 0 ? "成功" : uv_strerror(r));
    uv_fs_req_cleanup(&req);

    // uv_fs_readlink: 读取符号链接
    r = uv_fs_readlink(loop, &req, symlink_file, NULL);
    if (r == 0) {
        printf("uv_fs_readlink: 目标=%s\n", (char *)req.ptr);
    }
    uv_fs_req_cleanup(&req);

    // uv_fs_realpath: 获取真实路径
    r = uv_fs_realpath(loop, &req, symlink_file, NULL);
    if (r == 0) {
        printf("uv_fs_realpath: %s\n", (char *)req.ptr);
    }
    uv_fs_req_cleanup(&req);

    // 读取文件
    printf("\n-- 读取文件 --\n");
    r = uv_fs_stat(loop, &req, test_file, NULL);
    size_t file_size = (r == 0) ? (size_t)req.statbuf.st_size : 0;
    uv_fs_req_cleanup(&req);

    if (file_size > 0) {
        char *buf = (char *)malloc(file_size + 1);
        uv_buf_t read_buf = uv_buf_init(buf, file_size);
        r = uv_fs_open(loop, &req, test_file, O_RDONLY, 0, NULL);
        fd = r;
        uv_fs_req_cleanup(&req);

        r = uv_fs_read(loop, &req, fd, &read_buf, 1, 0, NULL);
        if (r > 0) {
            buf[r] = '\0';
            printf("uv_fs_read: 内容=\"%s\"\n", buf);
        }
        uv_fs_req_cleanup(&req);
        uv_fs_close(loop, &req, fd, NULL);
        uv_fs_req_cleanup(&req);
        free(buf);
    }

    // 目录操作
    printf("\n-- 目录操作 --\n");

    // uv_fs_mkdir: 创建目录
    r = uv_fs_mkdir(loop, &req, test_dir, 0755, NULL);
    printf("uv_fs_mkdir: %s\n", r == 0 ? "成功" : uv_strerror(r));
    uv_fs_req_cleanup(&req);

    // uv_fs_scandir: 扫描目录
    r = uv_fs_scandir(loop, &req, ".", 0, NULL);
    if (r >= 0) {
        printf("uv_fs_scandir: 找到 %d 个条目\n", r);
        uv_dirent_t dent;
        int shown = 0;
        while (uv_fs_scandir_next(&req, &dent) == 0 && shown < 5) {
            printf("  - %s (类型=%d)\n", dent.name, dent.type);
            shown++;
        }
        if (r > 5) printf("  ... (省略 %d 个)\n", r - 5);
    }
    uv_fs_req_cleanup(&req);

    // uv_fs_rmdir: 删除目录
    uv_fs_rmdir(loop, &req, test_dir, NULL);
    printf("uv_fs_rmdir: 完成\n");
    uv_fs_req_cleanup(&req);

    // 其他文件操作
    printf("\n-- 其他文件操作 --\n");

    // uv_fs_chmod
    uv_fs_chmod(loop, &req, test_file, S_IRUSR | S_IWUSR, NULL);
    printf("uv_fs_chmod: 完成\n");
    uv_fs_req_cleanup(&req);

    // uv_fs_utime: 修改访问/修改时间
    uv_fs_utime(loop, &req, test_file, 1000000.0, 1000000.0, NULL);
    printf("uv_fs_utime: 完成\n");
    uv_fs_req_cleanup(&req);

    // uv_fs_ftruncate: 截断文件
    r = uv_fs_open(loop, &req, test_file, O_RDWR, 0, NULL);
    fd = r;
    uv_fs_req_cleanup(&req);
    uv_fs_ftruncate(loop, &req, fd, 5, NULL);
    printf("uv_fs_ftruncate: 截断到5字节\n");
    uv_fs_req_cleanup(&req);
    uv_fs_close(loop, &req, fd, NULL);
    uv_fs_req_cleanup(&req);

    // 异步回调示例
    printf("\n-- 异步回调示例 --\n");
    uv_fs_t async_req;
    uv_fs_stat(loop, &async_req, test_file, fs_test_cb);

    // 文件发送 (sendfile)
    printf("\n-- uv_fs_sendfile --\n");
    const char *dest_file = "uv_test_copy.txt";
    r = uv_fs_open(loop, &req, test_file, O_RDONLY, 0, NULL);
    int src_fd = r;
    uv_fs_req_cleanup(&req);
    r = uv_fs_open(loop, &req, dest_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, NULL);
    int dst_fd = r;
    uv_fs_req_cleanup(&req);
    if (src_fd >= 0 && dst_fd >= 0) {
        uv_fs_sendfile(loop, &req, dst_fd, src_fd, 0, 5, NULL);
        printf("uv_fs_sendfile: %s\n", req.result >= 0 ? "成功" : uv_strerror(req.result));
        uv_fs_req_cleanup(&req);
    }
    uv_fs_close(loop, &req, src_fd, NULL);
    uv_fs_req_cleanup(&req);
    uv_fs_close(loop, &req, dst_fd, NULL);
    uv_fs_req_cleanup(&req);

    // 运行异步回调
    uv_run(loop, UV_RUN_DEFAULT);

    // 清理测试文件
    uv_fs_unlink(loop, &req, test_file, NULL);
    uv_fs_req_cleanup(&req);
    uv_fs_unlink(loop, &req, renamed_file, NULL);
    uv_fs_req_cleanup(&req);
    uv_fs_unlink(loop, &req, symlink_file, NULL);
    uv_fs_req_cleanup(&req);
    uv_fs_unlink(loop, &req, dest_file, NULL);
    uv_fs_req_cleanup(&req);
}

/*
 * 第6章：TCP 网络 (TCP Networking)
 * 参考：libuv documentation - TCP
 */

static uv_tcp_t tcp_server;
static uv_tcp_t tcp_client;

static void on_tcp_close(uv_handle_t *handle)
{
    printf("  [TCP] 连接关闭\n");
}

static void on_tcp_write(uv_write_t *req, int status)
{
    if (status < 0) {
        printf("  [TCP写入] 错误: %s\n", uv_strerror(status));
    } else {
        printf("  [TCP写入] 成功\n");
    }
    free(req);
}

static void on_tcp_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0) {
        buf->base[nread] = '\0';
        printf("  [TCP读取] 收到 %zd 字节: %s", nread, buf->base);
    } else if (nread < 0) {
        if (nread != UV_EOF) {
            printf("  [TCP读取] 错误: %s\n", uv_strerror((int)nread));
        }
        uv_close((uv_handle_t *)stream, on_tcp_close);
    }
    if (buf->base) free(buf->base);
}

static void on_tcp_connection(uv_stream_t *server, int status)
{
    if (status < 0) {
        printf("  [TCP连接] 错误: %s\n", uv_strerror(status));
        return;
    }

    printf("  [TCP连接] 新客户端连接!\n");
    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        uv_read_start((uv_stream_t *)client,
                      alloc_buffer,  /* 简化：用 malloc 分配缓冲区 */
                      on_tcp_read);

        // 发送欢迎消息
        uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
        uv_buf_t buf = uv_buf_init("Welcome to libuv TCP server!\n", 29);
        uv_write(write_req, (uv_stream_t *)client, &buf, 1, on_tcp_write);
    } else {
        uv_close((uv_handle_t *)client, (uv_close_cb)free);
    }
}

static void on_tcp_connect(uv_connect_t *req, int status)
{
    if (status < 0) {
        printf("  [TCP客户端连接] 错误: %s\n", uv_strerror(status));
        free(req);
        return;
    }

    printf("  [TCP客户端] 已连接到服务器!\n");

    /* 发送数据 */
    uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
    uv_buf_t buf = uv_buf_init("Hello from client!\n", 19);
    uv_write(write_req, req->handle, &buf, 1, on_tcp_write);

    // 开始读取响应
    uv_read_start(req->handle,
                  alloc_buffer,
                  on_tcp_read);

    // 短暂延迟后关闭
    free(req);
}

static void on_tcp_write2(uv_write_t *req, int status)
{
    (void)status;
    free(req);
}

void chapter6_tcp_test(void)
{
    printf("\n=== 第6章：TCP 网络示例 ===\n");

    uv_loop_t *loop = uv_default_loop();
    int r;

    // TCP 服务器
    printf("-- TCP 服务器 --\n");
    uv_tcp_init(loop, &tcp_server);

    struct sockaddr_in addr;
    // 端口0让系统自动分配
    uv_ip4_addr("127.0.0.1", 0, &addr);

    uv_tcp_bind(&tcp_server, (const struct sockaddr *)&addr, 0);

    r = uv_listen((uv_stream_t *)&tcp_server, 128, on_tcp_connection);
    if (r < 0) {
        printf("TCP 监听失败: %s\n", uv_strerror(r));
        return;
    }

    // 获取实际分配的端口
    int namelen = sizeof(addr);
    uv_tcp_getsockname(&tcp_server, (struct sockaddr *)&addr, &namelen);
    printf("TCP 服务器监听端口: %d\n", ntohs(addr.sin_port));

    // TCP 客户端
    printf("\n-- TCP 客户端 --\n");
    uv_tcp_init(loop, &tcp_client);

    uv_connect_t *connect_req = (uv_connect_t *)malloc(sizeof(uv_connect_t));
    uv_tcp_connect(connect_req, &tcp_client,
                   (const struct sockaddr *)&addr,
                   on_tcp_connect);

    // 运行事件循环让连接完成
    uv_run(loop, UV_RUN_DEFAULT);

    // TCP 选项
    printf("\n-- TCP 选项 --\n");
    uv_tcp_t demo_tcp;
    uv_tcp_init(loop, &demo_tcp);

    // uv_tcp_nodelay: 禁用 Nagle 算法
    uv_tcp_nodelay(&demo_tcp, 1);
    printf("TCP_NODELAY: 已启用\n");

    // uv_tcp_keepalive: 启用 TCP keepalive
    uv_tcp_keepalive(&demo_tcp, 1, 60);
    printf("TCP_KEEPALIVE: 已启用, 延迟=60秒\n");

    // uv_tcp_simultaneous_accepts: Windows 专用
    uv_tcp_simultaneous_accepts(&demo_tcp, 1);
    printf("simultaneous_accepts: 已启用\n");

    // 清理
    uv_close((uv_handle_t *)&tcp_server, NULL);
    uv_close((uv_handle_t *)&tcp_client, NULL);
    uv_close((uv_handle_t *)&demo_tcp, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/*
 * 第7章：UDP 网络 (UDP Networking)
 * 参考：libuv documentation - UDP
 */

static uv_udp_t udp_server;
static uv_udp_t udp_client;

static void on_udp_recv(uv_udp_t *handle, ssize_t nread,
                        const uv_buf_t *buf,
                        const struct sockaddr *addr,
                        unsigned flags)
{
    if (nread > 0) {
        char sender[17] = {0};
        uv_ip4_name((const struct sockaddr_in *)addr, sender, 16);
        buf->base[nread] = '\0';
        printf("  [UDP接收] 从 %s 收到 %zd 字节: %s", sender, nread, buf->base);
    } else if (nread < 0 && nread != UV_EOF) {
        printf("  [UDP接收] 错误: %s\n", uv_strerror((int)nread));
    }
    if (buf->base) free(buf->base);
}

static void on_udp_send(uv_udp_send_t *req, int status)
{
    if (status < 0) {
        printf("  [UDP发送] 错误: %s\n", uv_strerror(status));
    } else {
        printf("  [UDP发送] 成功\n");
    }
    free(req);
}

void chapter7_udp_test(void)
{
    printf("\n=== 第7章：UDP 网络示例 ===\n");

    uv_loop_t *loop = uv_default_loop();
    int r;

    // UDP 服务器
    printf("-- UDP 服务器 --\n");
    uv_udp_init(loop, &udp_server);

    struct sockaddr_in recv_addr;
    uv_ip4_addr("0.0.0.0", 0, &recv_addr);
    uv_udp_bind(&udp_server, (const struct sockaddr *)&recv_addr, UV_UDP_REUSEADDR);

    // 获取绑定端口
    int addr_len = sizeof(recv_addr);
    uv_udp_getsockname(&udp_server, (struct sockaddr *)&recv_addr, &addr_len);
    printf("UDP 服务器绑定端口: %d\n", ntohs(recv_addr.sin_port));

    // 开始接收
    uv_udp_recv_start(&udp_server,
                      alloc_buffer,
                      on_udp_recv);
    printf("UDP 服务器开始接收...\n");

    // UDP 客户端
    printf("\n-- UDP 客户端 --\n");
    uv_udp_init(loop, &udp_client);

    // 发送数据
    uv_udp_send_t *send_req = (uv_udp_send_t *)malloc(sizeof(uv_udp_send_t));
    uv_buf_t buf = uv_buf_init("Hello UDP!\n", 11);

    struct sockaddr_in dest_addr;
    uv_ip4_addr("127.0.0.1", ntohs(recv_addr.sin_port), &dest_addr);

    uv_udp_send(send_req, &udp_client, &buf, 1,
                (const struct sockaddr *)&dest_addr,
                on_udp_send);

    // 运行事件循环
    uv_run(loop, UV_RUN_DEFAULT);

    // UDP 选项
    printf("\n-- UDP 选项 --\n");
    uv_udp_t demo_udp;
    uv_udp_init(loop, &demo_udp);

    // uv_udp_set_broadcast: 启用广播
    uv_udp_set_broadcast(&demo_udp, 1);
    printf("UDP broadcast: 已启用\n");

    // uv_udp_set_ttl: 设置 TTL
    uv_udp_set_ttl(&demo_udp, 64);
    printf("UDP TTL: 64\n");

    // uv_udp_set_multicast_ttl: 设置多播 TTL
    uv_udp_set_multicast_ttl(&demo_udp, 1);
    printf("UDP multicast TTL: 1\n");

    // uv_udp_set_multicast_loop: 启用多播回环
    uv_udp_set_multicast_loop(&demo_udp, 1);
    printf("UDP multicast loop: 已启用\n");

    // 清理
    uv_udp_recv_stop(&udp_server);
    uv_close((uv_handle_t *)&udp_server, NULL);
    uv_close((uv_handle_t *)&udp_client, NULL);
    uv_close((uv_handle_t *)&demo_udp, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/*
 * 第8章：管道 (Pipe)
 * 参考：libuv documentation - Pipe
 */

static uv_pipe_t pipe_server;
static uv_pipe_t pipe_client;

static void on_pipe_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0) {
        buf->base[nread] = '\0';
        printf("  [Pipe读取] 收到: %s", buf->base);
    } else if (nread < 0) {
        if (nread != UV_EOF) {
            printf("  [Pipe读取] 错误: %s\n", uv_strerror((int)nread));
        }
        uv_close((uv_handle_t *)stream, NULL);
    }
    if (buf->base) free(buf->base);
}

static void on_pipe_write(uv_write_t *req, int status)
{
    (void)status;
    free(req);
}

static void on_pipe_connection(uv_stream_t *server, int status)
{
    if (status < 0) {
        printf("  [Pipe连接] 错误: %s\n", uv_strerror(status));
        return;
    }

    printf("  [Pipe连接] 客户端已连接!\n");
    uv_pipe_t *client = (uv_pipe_t *)malloc(sizeof(uv_pipe_t));
    uv_pipe_init(server->loop, client, 0);

    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        uv_read_start((uv_stream_t *)client,
                      alloc_buffer,
                      on_pipe_read);

        uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
        uv_buf_t buf = uv_buf_init("Hello from pipe server!\n", 26);
        uv_write(write_req, (uv_stream_t *)client, &buf, 1, on_pipe_write);
    } else {
        uv_close((uv_handle_t *)client, (uv_close_cb)free);
    }
}

static void on_pipe_connect(uv_connect_t *req, int status)
{
    if (status < 0) {
        printf("  [Pipe客户端连接] 错误: %s\n", uv_strerror(status));
        free(req);
        return;
    }

    printf("  [Pipe客户端] 已连接!\n");
    uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
    uv_buf_t buf = uv_buf_init("Hello from pipe client!\n", 24);
    uv_write(write_req, req->handle, &buf, 1, on_pipe_write);

    uv_read_start(req->handle,
                  alloc_buffer,
                  on_pipe_read);
    free(req);
}

void chapter8_pipe_test(void)
{
    printf("\n=== 第8章：管道示例 ===\n");

    uv_loop_t *loop = uv_default_loop();
    int r;

    // 命名管道服务器
    printf("-- 命名管道服务器 --\n");
    uv_pipe_init(loop, &pipe_server, 0);

#ifdef _WIN32
    const char *pipe_name = "\\\\.\\pipe\\uv_test_pipe";
#else
    const char *pipe_name = "/tmp/uv_test_pipe";
#endif

    r = uv_pipe_bind(&pipe_server, pipe_name);
    if (r < 0) {
        printf("Pipe bind 失败: %s\n", uv_strerror(r));
        return;
    }
    printf("Pipe 绑定: %s\n", pipe_name);

    r = uv_listen((uv_stream_t *)&pipe_server, 128, on_pipe_connection);
    if (r < 0) {
        printf("Pipe listen 失败: %s\n", uv_strerror(r));
        return;
    }
    printf("Pipe 服务器开始监听\n");

    // 命名管道客户端
    printf("\n-- 命名管道客户端 --\n");
    uv_pipe_init(loop, &pipe_client, 0);

    uv_connect_t *connect_req = (uv_connect_t *)malloc(sizeof(uv_connect_t));
    uv_pipe_connect(connect_req, &pipe_client, pipe_name, on_pipe_connect);

    // 运行事件循环
    uv_run(loop, UV_RUN_DEFAULT);

    // 管道工具函数
    printf("\n-- 管道工具函数 --\n");

    // uv_pipe_pending_count: 获取待处理的句柄数
    printf("uv_pipe_pending_count: %lu\n", (unsigned long)uv_pipe_pending_count(&pipe_server));

    // uv_pipe_chmod: 修改管道权限 (仅 Unix)
#ifndef _WIN32
    uv_pipe_chmod(&pipe_server, UV_READABLE | UV_WRITABLE);
    printf("uv_pipe_chmod: 已设置读写权限\n");
#endif

    // 清理
    uv_close((uv_handle_t *)&pipe_server, NULL);
    uv_close((uv_handle_t *)&pipe_client, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/*
 * 第9章：TTY (Terminal I/O)
 * 参考：libuv documentation - TTY
 */

void chapter9_tty_test(void)
{
    printf("\n=== 第9章：TTY 示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // TTY 初始化
    printf("-- TTY 初始化 --\n");
    uv_tty_t tty_out;
    int r = uv_tty_init(loop, &tty_out, 1, 0);  /* fd=1 (stdout), readable=0 */
    if (r < 0) {
        printf("TTY 初始化失败: %s\n", uv_strerror(r));
        printf("(在非终端环境下 TTY 可能不可用)\n");
        return;
    }
    printf("TTY 初始化成功\n");

    // TTY 模式设置
    printf("\n-- TTY 模式 --\n");
    printf("UV_TTY_MODE_NORMAL: 正常模式\n");
    printf("UV_TTY_MODE_RAW: 原始模式 (无缓冲, 无回显)\n");
    printf("UV_TTY_MODE_IO: I/O 模式\n");

    // uv_tty_set_mode: 设置 TTY 模式
    r = uv_tty_set_mode(&tty_out, UV_TTY_MODE_NORMAL);
    printf("uv_tty_set_mode(NORMAL): %s\n", r == 0 ? "成功" : uv_strerror(r));

    // TTY 写入
    printf("\n-- TTY 写入 --\n");
    uv_write_t write_req;
    uv_buf_t buf = uv_buf_init("  TTY 输出测试\n", 15);
    uv_write(&write_req, (uv_stream_t *)&tty_out, &buf, 1, NULL);

    // TTY 窗口大小
    printf("\n-- TTY 窗口大小 --\n");
    int width, height;
    uv_tty_get_winsize(&tty_out, &width, &height);
    printf("终端窗口大小: %d x %d\n", width, height);

    // TTY 重置模式
    uv_tty_reset_mode();
    printf("TTY 模式已重置\n");

    // uv_guess_handle: 猜测句柄类型
    printf("\n-- uv_guess_handle --\n");
    uv_handle_type type = uv_guess_handle(0);  /* stdin */
    printf("fd=0 (stdin) 的句柄类型: %s\n", handle_type_name(type));
    type = uv_guess_handle(1);  /* stdout */
    printf("fd=1 (stdout) 的句柄类型: %s\n", handle_type_name(type));

    // 清理
    uv_close((uv_handle_t *)&tty_out, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/*
 * 第10章：信号处理 (Signals)
 * 参考：libuv documentation - Signals
 */

static uv_signal_t signal_handle;
static int signal_received = 0;

static void on_signal(uv_signal_t *handle, int signum)
{
    signal_received = 1;
    printf("  [信号] 收到信号: %d (%s)\n", signum,
            signum == SIGINT ? "SIGINT" :
            signum == SIGTERM ? "SIGTERM" : "OTHER");
    uv_signal_stop(handle);
}

void chapter10_signal_test(void)
{
    printf("\n=== 第10章：信号处理示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // 信号句柄初始化
    printf("-- 信号句柄 --\n");
    uv_signal_init(loop, &signal_handle);

    // uv_signal_start: 监听信号
    uv_signal_start(&signal_handle, on_signal, SIGINT);
    printf("已注册 SIGINT 信号处理\n");

    // uv_signal_start_oneshot: 只触发一次
    uv_signal_t oneshot_handle;
    uv_signal_init(loop, &oneshot_handle);
    uv_signal_start_oneshot(&oneshot_handle, on_signal, SIGTERM);
    printf("已注册 SIGTERM 一次性信号处理\n");

    // 发送信号给自己
    printf("\n-- 发送测试信号 --\n");
#ifdef _WIN32
    printf("Windows 下信号支持有限，模拟信号触发\n");
    // 在 Windows 下直接调用回调模拟
    on_signal(&signal_handle, SIGINT);
#else
    /* Unix 下可以发送信号 */
    uv_kill(uv_os_getpid(), SIGINT);
#endif

    // 运行事件循环处理信号
    uv_run(loop, UV_RUN_DEFAULT);

    // uv_kill 和 uv_process_kill
    printf("\n-- 进程信号函数 --\n");
    printf("uv_kill(pid, signum): 向指定进程发送信号\n");
    printf("uv_process_kill(process, signum): 向子进程发送信号\n");

    // 清理
    uv_close((uv_handle_t *)&signal_handle, NULL);
    uv_close((uv_handle_t *)&oneshot_handle, NULL);
    uv_run(loop, UV_RUN_NOWAIT);
}

/* ============================================================
 * 第11章：进程管理 (Process)
 * 参考：libuv documentation - Process
 * ============================================================ */

static uv_process_t child_process;
static uv_process_options_t process_options;
static int process_exit_status = -1;

static void on_process_exit(uv_process_t *process, int64_t exit_status, int term_signal)
{
    process_exit_status = (int)exit_status;
    printf("  [进程退出] exit_status=%lld, term_signal=%d\n",
            (long long)exit_status, term_signal);
    uv_close((uv_handle_t *)process, NULL);
}

static void on_process_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0) {
        buf->base[nread] = '\0';
        printf("  [进程输出] %s", buf->base);
    } else if (nread < 0) {
        if (nread != UV_EOF) {
            printf("  [进程读取] 错误: %s\n", uv_strerror((int)nread));
        }
        uv_close((uv_handle_t *)stream, NULL);
    }
    if (buf->base) free(buf->base);
}

void chapter11_process_test(void)
{
    printf("\n=== 第11章：进程管理示例 ===\n");

    uv_loop_t *loop = uv_default_loop();
    int r;

    // 基本进程创建
    printf("-- 基本进程创建 --\n");

    // 设置子进程标准输出管道
    uv_pipe_t child_stdout_pipe;
    uv_pipe_init(loop, &child_stdout_pipe, 0);

    uv_stdio_container_t child_stdio[3];
    // stdin: 忽略
    child_stdio[0].flags = UV_IGNORE;
    // stdout: 管道
    child_stdio[1].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
    child_stdio[1].data.stream = (uv_stream_t *)&child_stdout_pipe;
    // stderr: 继承
    child_stdio[2].flags = UV_INHERIT_FD;
    child_stdio[2].data.fd = 2;

    // 进程选项
    memset(&process_options, 0, sizeof(process_options));
    process_options.exit_cb = on_process_exit;
#ifdef _WIN32
    process_options.file = "cmd.exe";
    char *args[] = {"cmd.exe", "/C", "echo", "Hello from child process!", NULL};
#else
    process_options.file = "echo";
    char *args[] = {"echo", "Hello from child process!", NULL};
#endif
    process_options.args = args;
    process_options.stdio = child_stdio;
    process_options.stdio_count = 3;

    // uv_spawn: 创建子进程
    r = uv_spawn(loop, &child_process, &process_options);
    if (r < 0) {
        printf("uv_spawn 失败: %s\n", uv_strerror(r));
    } else {
        printf("子进程已创建, pid=%d\n", child_process.pid);

        // 读取子进程输出
        uv_read_start((uv_stream_t *)&child_stdout_pipe,
                      alloc_buffer,
                      on_process_read);
    }

    // 运行事件循环等待子进程完成
    uv_run(loop, UV_RUN_DEFAULT);

    // 进程选项详解
    printf("\n-- 进程选项 --\n");
    printf("UV_PROCESS_DETACHED: 分离进程\n");
    printf("UV_PROCESS_SETUID: 设置用户ID (Unix)\n");
    printf("UV_PROCESS_SETGID: 设置组ID (Unix)\n");
    printf("UV_PROCESS_WINDOWS_HIDE: 隐藏窗口 (Windows)\n");
    printf("UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS: 原样传递参数 (Windows)\n");

    // 环境变量
    printf("\n-- 环境变量 --\n");
    char *env_args[] = {"PATH=/usr/bin", NULL};
    process_options.env = env_args;
    process_options.flags = UV_PROCESS_DETACHED;
    printf("可设置 process_options.env 传递环境变量\n");
    printf("可设置 process_options.cwd 改变工作目录\n");

    // uv_process_kill
    printf("\n-- 进程信号 --\n");
    printf("uv_process_kill(process, signum): 向子进程发送信号\n");
    printf("uv_kill(pid, signum): 向任意进程发送信号\n");

    // uv_os_getpid / uv_os_getppid
    printf("\n-- 进程ID --\n");
    printf("当前进程 PID: %d\n", (int)uv_os_getpid());
    printf("父进程 PID: %d\n", (int)uv_os_getppid());
}

/*
 * 第12章：异步通知 (Async)
 * 参考：libuv documentation - Async
 */

static uv_async_t async_handle;
static uv_thread_t async_thread;
static int async_count = 0;

static void on_async(uv_async_t *handle)
{
    async_count++;
    printf("  [async] 收到异步通知 #%d\n", async_count);

    if (async_count >= 3) {
        // 发送最后一次通知后关闭
        uv_async_send(handle);
        uv_close((uv_handle_t *)handle, NULL);
    }
}

static void async_thread_func(void *arg)
{
    int i;
    for (i = 0; i < 3; i++) {
        printf("  [线程] 发送异步通知 #%d\n", i + 1);
        uv_async_send((uv_async_t *)arg);
        uv_sleep(50);
    }
}

void chapter12_async_test(void)
{
    printf("\n=== 第12章：异步通知示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // uv_async_t
    printf("-- uv_async_t 异步通知 --\n");
    printf("uv_async 允许从其他线程安全地唤醒事件循环\n");

    uv_async_init(loop, &async_handle, on_async);

    // 创建线程发送异步通知
    uv_thread_create(&async_thread, async_thread_func, &async_handle);

    // 运行事件循环
    uv_run(loop, UV_RUN_DEFAULT);

    // 等待线程完成
    uv_thread_join(&async_thread);

    printf("异步通知测试完成\n");
}

/*
 * 第13章：线程池 (Thread Pool)
 * 参考：libuv documentation - Thread pool work queue
 */

static uv_work_t work_reqs[3];

static void on_work(uv_work_t *req)
{
    int *data = (int *)req->data;
    printf("  [线程池] 执行工作 #%d, 线程ID=%lu\n",
            *data, (unsigned long)uv_thread_self());
    uv_sleep(100);  /* 模拟耗时操作 */
    *data *= 10;  /* 修改数据 */
}

static void on_work_done(uv_work_t *req, int status)
{
    int *data = (int *)req->data;
    printf("  [线程池完成] 工作 #%d 结果=%d, status=%d\n",
            *data / 10, *data, status);
}

void chapter13_thread_pool_test(void)
{
    printf("\n=== 第13章：线程池示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    /* -- uv_queue_work -- */
    printf("-- uv_queue_work 线程池工作队列 --\n");
    printf("libuv 内置线程池默认4个线程 (UV_THREADPOOL_SIZE 可配置)\n");

    static int work_data[3] = {1, 2, 3};
    int i;
    for (i = 0; i < 3; i++) {
        work_reqs[i].data = &work_data[i];
        uv_queue_work(loop, &work_reqs[i], on_work, on_work_done);
        printf("  已提交工作 #%d\n", i + 1);
    }

    // 运行事件循环等待所有工作完成
    uv_run(loop, UV_RUN_DEFAULT);

    // 线程相关函数
    printf("\n-- 线程工具 --\n");
    printf("uv_thread_create: 创建线程\n");
    printf("uv_thread_join: 等待线程结束\n");
    printf("uv_thread_self: 获取当前线程ID\n");

    // 互斥锁
    printf("\n-- 互斥锁 --\n");
    uv_mutex_t mutex;
    uv_mutex_init(&mutex);
    uv_mutex_lock(&mutex);
    printf("uv_mutex_lock: 已加锁\n");
    uv_mutex_unlock(&mutex);
    printf("uv_mutex_unlock: 已解锁\n");
    uv_mutex_destroy(&mutex);

    // 读写锁
    printf("\n-- 读写锁 --\n");
    uv_rwlock_t rwlock;
    uv_rwlock_init(&rwlock);
    uv_rwlock_rdlock(&rwlock);
    printf("uv_rwlock_rdlock: 已加读锁\n");
    uv_rwlock_rdunlock(&rwlock);
    uv_rwlock_wrlock(&rwlock);
    printf("uv_rwlock_wrlock: 已加写锁\n");
    uv_rwlock_wrunlock(&rwlock);
    uv_rwlock_destroy(&rwlock);

    // 信号量
    printf("\n-- 信号量 --\n");
    uv_sem_t sem;
    uv_sem_init(&sem, 0);
    uv_sem_post(&sem);
    printf("uv_sem_post: 已发送信号量\n");
    uv_sem_wait(&sem);
    printf("uv_sem_wait: 已等待信号量\n");
    uv_sem_destroy(&sem);

    // 条件变量
    printf("\n-- 条件变量 --\n");
    uv_cond_t cond;
    uv_cond_init(&cond);
    printf("uv_cond_init: 条件变量已初始化\n");
    uv_cond_destroy(&cond);

    // 屏障
    printf("\n-- 屏障 --\n");
    uv_barrier_t barrier;
    uv_barrier_init(&barrier, 1);
    printf("uv_barrier_init: 屏障已初始化 (count=1)\n");
    uv_barrier_wait(&barrier);
    printf("uv_barrier_wait: 屏障已通过\n");
    uv_barrier_destroy(&barrier);

    // 线程局部存储
    printf("\n-- 线程局部存储 --\n");
    uv_key_t tls_key;
    uv_key_create(&tls_key);
    uv_key_set(&tls_key, (void *)42);
    printf("uv_key_get: %lu\n", (unsigned long)(size_t)uv_key_get(&tls_key));
    uv_key_delete(&tls_key);

    /* -- once -- */
    printf("\n-- uv_once --\n");
    printf("uv_once: 确保函数只执行一次 (类似 pthread_once)\n");
}

/*
 * 第14章：DNS 解析 (DNS)
 * 参考：libuv documentation - DNS
 */

static void on_getaddrinfo(uv_getaddrinfo_t *req, int status, struct addrinfo *res)
{
    if (status < 0) {
        printf("  [DNS] getaddrinfo 失败: %s\n", uv_strerror(status));
    } else {
        printf("  [DNS] getaddrinfo 成功!\n");
        char ip[17] = {0};
        struct addrinfo *addr = res;
        int count = 0;
        while (addr && count < 3) {
            uv_ip4_name((struct sockaddr_in *)addr->ai_addr, ip, 16);
            printf("  [DNS] 地址 #%d: %s\n", count + 1, ip);
            addr = addr->ai_next;
            count++;
        }
    }
    uv_freeaddrinfo(res);
}

static void on_getnameinfo(uv_getnameinfo_t *req, int status, const char *hostname, const char *service)
{
    if (status < 0) {
        printf("  [DNS] getnameinfo 失败: %s\n", uv_strerror(status));
    } else {
        printf("  [DNS] getnameinfo: hostname=%s, service=%s\n", hostname, service);
    }
}

void chapter14_dns_test(void)
{
    printf("\n=== 第14章：DNS 解析示例 ===\n");

    uv_loop_t *loop = uv_default_loop();

    // uv_getaddrinfo: 异步 DNS 解析
    printf("-- uv_getaddrinfo 异步解析 --\n");
    uv_getaddrinfo_t addr_req;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int r = uv_getaddrinfo(loop, &addr_req, on_getaddrinfo,
                           "localhost", NULL, &hints);
    if (r < 0) {
        printf("uv_getaddrinfo 启动失败: %s\n", uv_strerror(r));
    }

    // uv_getnameinfo: 反向 DNS 解析
    printf("\n-- uv_getnameinfo 反向解析 --\n");
    uv_getnameinfo_t name_req;
    struct sockaddr_in addr;
    uv_ip4_addr("127.0.0.1", 80, &addr);

    r = uv_getnameinfo(loop, &name_req, on_getnameinfo,
                       (struct sockaddr *)&addr, 0);
    if (r < 0) {
        printf("uv_getnameinfo 启动失败: %s\n", uv_strerror(r));
    }

    // 运行事件循环
    uv_run(loop, UV_RUN_DEFAULT);
}

/*
 * 第15章：工具函数 (Utilities)
 * 参考：libuv documentation - Miscellaneous utilities
 */

void chapter15_utilities_test(void)
{
    printf("\n=== 第15章：工具函数示例 ===\n");

    // 时间函数
    printf("-- 时间函数 --\n");
    uint64_t now = uv_hrtime();
    printf("uv_hrtime: %llu 纳秒\n", (unsigned long long)now);

    uv_update_time(uv_default_loop());
    uint64_t loop_time = uv_now(uv_default_loop());
    printf("uv_now: %llu 毫秒\n", (unsigned long long)loop_time);

    printf("uv_sleep(100): 休眠100毫秒...\n");
    uv_sleep(100);
    printf("uv_sleep 完成\n");

    /* -- IP 地址转换 -- */
    printf("\n-- IP 地址转换 --\n");
    struct sockaddr_in addr4;
    uv_ip4_addr("192.168.1.1", 8080, &addr4);
    char ip_str[17] = {0};
    uv_ip4_name(&addr4, ip_str, 16);
    printf("uv_ip4_addr -> uv_ip4_name: %s:%d\n", ip_str, ntohs(addr4.sin_port));

    struct sockaddr_in6 addr6;
    uv_ip6_addr("::1", 8080, &addr6);
    char ip6_str[46] = {0};
    uv_ip6_name(&addr6, ip6_str, 45);
    printf("uv_ip6_addr -> uv_ip6_name: %s:%d\n", ip6_str, ntohs(addr6.sin6_port));

    /* -- 系统信息 -- */
    printf("\n-- 系统信息 --\n");
    printf("CPU 数量: %d\n", uv_available_parallelism());

    double loadavg[3];
    uv_loadavg(loadavg);
    printf("系统负载: %.2f, %.2f, %.2f\n", loadavg[0], loadavg[1], loadavg[2]);

    uint64_t total_mem = uv_get_total_memory();
    uint64_t free_mem = uv_get_free_memory();
    printf("总内存: %llu MB\n", (unsigned long long)(total_mem / (1024 * 1024)));
    printf("可用内存: %llu MB\n", (unsigned long long)(free_mem / (1024 * 1024)));

    uint64_t constrained_mem = uv_get_constrained_memory();
    printf("受限内存: %llu MB\n", (unsigned long long)(constrained_mem / (1024 * 1024)));

    /* -- 资源限制 -- */
    printf("\n-- 资源限制 --\n");
    uv_rlimit_t rlimit;
    if (uv_getrlimit(RLIMIT_NOFILE, &rlimit) == 0) {
        printf("RLIMIT_NOFILE: soft=%llu, hard=%llu\n",
                (unsigned long long)rlimit.rlim_cur,
                (unsigned long long)rlimit.rlim_max);
    }

    // 环境变量
    printf("\n-- 环境变量 --\n");
    char env_val[256];
    size_t env_len = sizeof(env_val);
    int r = uv_os_getenv("PATH", env_val, &env_len);
    if (r == 0) {
        printf("PATH (前50字符): %.50s...\n", env_val);
    }

    r = uv_os_setenv("UV_TEST_VAR", "hello");
    printf("uv_os_setenv: %s\n", r == 0 ? "成功" : uv_strerror(r));

    env_len = sizeof(env_val);
    r = uv_os_getenv("UV_TEST_VAR", env_val, &env_len);
    if (r == 0) {
        printf("UV_TEST_VAR = %s\n", env_val);
    }

    uv_os_unsetenv("UV_TEST_VAR");
    printf("uv_os_unsetenv: 已删除 UV_TEST_VAR\n");

    // 主机名
    printf("\n-- 主机名 --\n");
    char hostname[256];
    size_t hostname_len = sizeof(hostname);
    if (uv_os_gethostname(hostname, &hostname_len) == 0) {
        printf("主机名: %s\n", hostname);
    }

    // 用户信息
    printf("\n-- 用户信息 --\n");
    uv_passwd_t passwd;
    if (uv_os_get_passwd(&passwd) == 0) {
        printf("用户名: %s\n", passwd.username);
        printf("UID: %lu\n", (unsigned long)passwd.uid);
        printf("GID: %lu\n", (unsigned long)passwd.gid);
        printf("Shell: %s\n", passwd.shell ? passwd.shell : "(null)");
        printf("Home: %s\n", passwd.homedir ? passwd.homedir : "(null)");
        uv_os_free_passwd(&passwd);
    }

    // 系统统计
    printf("\n-- 系统统计 --\n");
    uv_cpu_info_t *cpu_infos;
    int cpu_count;
    if (uv_cpu_info(&cpu_infos, &cpu_count) == 0) {
        printf("CPU 数量: %d\n", cpu_count);
        if (cpu_count > 0) {
            printf("CPU #0: %s, 模型=%s, 速度=%d MHz\n",
                    cpu_infos[0].name, cpu_infos[0].model, cpu_infos[0].speed);
        }
        uv_free_cpu_info(cpu_infos, cpu_count);
    }

    uv_interface_address_t *interfaces;
    int iface_count;
    if (uv_interface_addresses(&interfaces, &iface_count) == 0) {
        printf("网络接口数量: %d\n", iface_count);
        int shown = 0;
        for (int i = 0; i < iface_count && shown < 3; i++) {
            char addr_buf[46] = {0};
            if (interfaces[i].address.address4.sin_family == AF_INET) {
                uv_ip4_name(&interfaces[i].address.address4, addr_buf, 45);
            } else {
                uv_ip6_name(&interfaces[i].address.address6, addr_buf, 45);
            }
            printf("  接口: %s, IP: %s, 内部: %s\n",
                    interfaces[i].name, addr_buf,
                    interfaces[i].is_internal ? "是" : "否");
            shown++;
        }
        uv_free_interface_addresses(interfaces, iface_count);
    }

    // 版本信息
    printf("\n-- 版本信息 --\n");
    printf("libuv 版本: %s (0x%06x)\n", uv_version_string(), uv_version());

    // 错误处理
    printf("\n-- 错误处理 --\n");
    printf("uv_strerror(UV_ECONNREFUSED): %s\n", uv_strerror(UV_ECONNREFUSED));
    printf("uv_err_name(UV_ECONNREFUSED): %s\n", uv_err_name(UV_ECONNREFUSED));

    // 句柄大小查询
    printf("\n-- 句柄大小查询 --\n");
    printf("uv_handle_size(UV_TCP): %zu\n", uv_handle_size(UV_TCP));
    printf("uv_handle_size(UV_UDP): %zu\n", uv_handle_size(UV_UDP));
    printf("uv_handle_size(UV_TIMER): %zu\n", uv_handle_size(UV_TIMER));
    printf("uv_req_size(UV_FS): %zu\n", uv_req_size(UV_FS));
    printf("uv_req_size(UV_CONNECT): %zu\n", uv_req_size(UV_CONNECT));

    // fs_event: 文件系统事件监视
    printf("\n-- uv_fs_event_t 文件监视 --\n");
    printf("uv_fs_event: 监视文件或目录的变化\n");
    printf("事件类型: UV_RENAME, UV_CHANGE\n");

    // uv_fs_poll: 文件轮询
    printf("\n-- uv_fs_poll_t 文件轮询 --\n");
    printf("uv_fs_poll: 定期检查文件状态变化\n");
}

typedef void (*ChapterFunc)(void);

typedef struct {
    const char *number;
    const char *title;
    ChapterFunc func;
} ChapterEntry;

#if 0
#endif
int main(int argc, char **argv)
{
    // 第一部分：事件循环与基础句柄
    chapter1_event_loop_test();
    // chapter2_handle_request_test();
    // chapter3_timer_test();
    // chapter4_idle_prepare_check_test();

    // 第二部分：I/O 操作
    // chapter5_file_system_test();
    // chapter6_tcp_test();
    // chapter7_udp_test();

    // 第三部分：进程间通信与系统
    // chapter8_pipe_test();
    // chapter9_tty_test();
    // chapter10_signal_test();
    // chapter11_process_test();

    // 第四部分：高级特性
    // chapter12_async_test();
    // chapter13_thread_pool_test();
    // chapter14_dns_test();
    // chapter15_utilities_test();
    return 0;
}