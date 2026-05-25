#include <stdio.h>

void swap_int(int *pa, int *pb)
{
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

void swap_double(double *pa, double *pb)
{
    double tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

/**
 * 注意事项
 *
 * 1. 使用宏方式实现交换两个数时，传递的参数不是地址，而是直接的值，因为替换后的代码在一个代码块中，而不是在另一个函数中，所以不用传递地址
 * 2. 使用异或运算不传递类型也能交换，不过仅适用于整数
 *    #define SWAP_XOR(a, b)  do { (a) ^= (b); (b) ^= (a); (a) ^= (b); } while(0)
 * 3. c中使用typeof或__typeof__关键字，可以实现自动推断数据类型，可以实现不传递类型也能交换
 *    #define SWAP_TYPEOF(a, b)  do { __typeof__(a) tmp = (a); (a) = (b); (b) = tmp; } while(0)
 *    #define SWAP_TYPEOF(a, b)  do { typeof(a) tmp = (a); (a) = (b); (b) = tmp; } while(0)
 * 4. c++中使用auto关键字可以实现自动类型推断
 *    #define SWAP_AUTO(a, b)  do { auto tmp = (a); (a) = (b); (b) = tmp; } while(0)
 *
 *
 * typeof发展历史
 *
 * 1. C89/C99/C11/C17 中 typeof 都是编译器扩展
 * 2. C23 标准化了 typeof，但 C23 刚刚发布（2023年），普及还需要时间
 *
 * 宏定义的安全写法
 *
 * 1. 使用括号保护，可以避免宏展开后代码中出现分号导致语法错误，有时宏参数为表达式，没有括号保护，展开后会直接报错
 * 2. 使用 do {...} while(0) 封装宏，提交宏定义规范性和安全性
 *    - 使用 do {...} while(0) 避免宏展开后在 if-else、while 等控制流语句中出现分号导致语法错误
 *    - 推荐在 do {...} while(0) 中多行代码可以使用断行符进行换行，这样代码阅读起来更清晰
 * 3. 简单的示例
 *    #define SWAP(a, b, type)  { type tmp = a; a = b; b = tmp; }                               // 不安全的写法
 *    #define SWAP(a, b, type)  do { type tmp = (a); (a) = (b); (b) = tmp; } while(0)           //安全的写法
 *
 *    #define SWAP_XOR(a, b)  { a ^= b; b ^= a; a ^= b; }                                       // 不安全的写法
 *    #define SWAP_XOR(a, b)  do { (a) ^= (b); (b) ^= (a); (a) ^= (b); } while(0)               //安全的写法
 *
 *    // 不安全的写法
 *    #ifdef _MSC_VER // _MSC_VER 是 MSVC 编译器预定义的宏
 *    #define SWAP_TYPEOF(a, b)  { __typeof__(a) tmp = a; a = b; b = tmp; } // Microsoft 编译器
 *    #else
 *    #define SWAP_TYPEOF(a, b)  { typeof(a) tmp = a; a = b; b = tmp; } // GCC/Clang 编译器
 *    #endif
 *
 *    // 安全的写法
 *    #ifdef _MSC_VER // _MSC_VER 是 MSVC 编译器预定义的宏
 *    #define SWAP_TYPEOF(a, b)  do { __typeof__(a) _tmp = (a); (a) = (b); (b) = _tmp; } while(0)    // Microsoft 编译器
 *    #else
 *    #define SWAP_TYPEOF(a, b)  do { typeof(a) _tmp = (a); (a) = (b); (b) = _tmp; } while(0)        // GCC/Clang 编译器
 *    #endif
 */

/**
 * 通用的交换函数（必须传递数据类型）
 */
// 常规版
#define SWAP_NORMAL(a, b, type)  do { type tmp = (a); (a) = (b); (b) = tmp; } while(0)
// 阅读友好版
#define SWAP_FRIENDLY(a, b, type)  do { \
    type tmp = (a); \
    (a) = (b); \
    (b) = tmp; \
} while(0)

/**
 * 不传递数据类型完成交换，但是只能用于整数
 */
// 常规版
#define SWAP_XOR_NORMAL(a, b)  do { (a) ^= (b); (b) ^= (a); (a) ^= (b); } while(0)
// 阅读友好版
#define SWAP_XOR_FRIENDLY(a, b)  do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while(0)

/**
 * 不传递数据类型完成交换，需要依赖编译器
 */
// 常规版
#ifdef _MSC_VER // _MSC_VER 是 MSVC 编译器预定义的宏
#define SWAP_TYPEOF_NORMAL(a, b)  do { __typeof__(a) _tmp = (a); (a) = (b); (b) = _tmp; } while(0)     // Microsoft 编译器
#else
#define SWAP_TYPEOF_NORMAL(a, b)  do { typeof(a) _tmp = (a); (a) = (b); (b) = _tmp; } while(0)         // GCC/Clang 编译器
#endif

// 阅读友好版
#ifdef _MSC_VER // _MSC_VER 是 MSVC 编译器预定义的宏
#define SWAP_TYPEOF_FRIENDLY(a, b)  do { \                                                              // Microsoft 编译器
    __typeof__(a) _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
} while(0)
#else
#define SWAP_TYPEOF_FRIENDLY(a, b)  do { \
    typeof(a) _tmp = (a); \
    (a) = (b); (b) = _tmp; \
} while(0)
#endif

#if 0
#endif
int main()
{
    int a = 10, b = 20;
    // 传统函数方式交换
    //swap_int(&a, &b);

    // 宏定义方式交换（需要传递数据类型）
    //SWAP_NORMAL(a, b , int);
    //SWAP_FRIENDLY(a, b , int);

    // 宏定义方式交换（不用传递数据类型）
    //SWAP_TYPEOF_NORMAL(a, b);
    SWAP_TYPEOF_FRIENDLY(a, b);
    printf("a = %d, b = %d\n", a, b);


    double x = 10.10, y = 20.20;
    // 传统函数方式交换
    //swap_double(&x, &y);

    // 宏定义方式交换（需要传递数据类型）
    //SWAP_NORMAL(x, y , double);
    //SWAP_FRIENDLY(x, y , double);

    // 宏定义方式交换（不用传递数据类型）
    //SWAP_TYPEOF_NORMAL(x, y);
    SWAP_TYPEOF_FRIENDLY(x, y);
    printf("x = %.2f, y = %.2f\n", x, y);
    return 0;
}