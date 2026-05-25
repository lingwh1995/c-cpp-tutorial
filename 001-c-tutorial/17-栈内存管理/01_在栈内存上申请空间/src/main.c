#include <stdio.h>

#ifdef _WIN32
// Windows 平台：使用 _alloca
#include <malloc.h>
#define stack_alloc(size)  _alloca(size)
#else
// Linux / macOS / Unix 平台：使用 alloca
#include <alloca.h>
#define stack_alloc(size)  alloca(size)
#endif

/**
 * 栈内存空间分配核心优势
 *
 * 1. 支持运行时动态确定大小，比固定长度数组更灵活
 * 2. 函数退出自动释放内存，无需手动 free，杜绝泄漏
 * 3. 仅移动栈指针，分配速度远快于堆内存（malloc/g_malloc）
 *
 * 栈内存空间分配应用场景
 *
 * 1. 短时小容量动态缓冲区
 *    函数内临时存数据，大小运行时才确定，用完自动销毁，不用 malloc/free。例：解析字符串、临时拼接文本、局部数据中转。
 *    char *tmp_buf = stack_alloc(buf_len);
 * 2. 高频轻量分配降开销
 *    频繁创建销毁小内存，栈分配无堆内存碎片、无锁开销，性能远优于堆分配。适合循环内临时数组、算法临时缓存。
 * 3. 规避堆内存泄漏风险
 *    函数结束内存自动回收，忘记释放也不会内存泄漏，简化代码逻辑。
 * 4. 替代固定数组，灵活适配尺寸
 *    数组长度由输入参数决定，不用预设超大固定长度节省栈空间。
 * 5. 协议 / 报文临时解析
 *    网络包、文件报文解析，按报文实际长度开辟临时栈缓冲区，处理完自动回收。
 */
int main() {
    // 动态在栈上分配内存（跨平台）
    int* arr = stack_alloc(10 * sizeof(int));

    arr[0] = 100;
    printf("%d\n", arr[0]);

    return 0;
}