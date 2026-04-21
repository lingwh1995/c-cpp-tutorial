#include <stdio.h>

/**
 * typedef 关键字用法详解
 *
 * 1. 作用规则
 *    语法规则：在任意合法的变量定义语句前添加 typedef，即可将变量名转换为该变量对应类型的别名，简单说 可以把一切合法的变量定义变成类型声明。
 *    示例：double d;  →  typedef double d;
 *    原语句定义 double 变量 d，添加 typedef 后，d 成为 double 类型的别名。
 *
 * 2. 本质特性
 *    C 语言中用于为现有数据类型起别名的关键字，属于存储类关键字，与 auto、extern、static、register 等关键字不能在同一声明语句中同时使用。
 *
 * 3. 适用范围
 *    可对所有合法数据类型起别名，包括：基本数据类型、指针类型、数组类型、结构体、枚举、联合体等。
 *
 * 4. 与宏定义的区别
 *    不同于 #define 单纯的文本替换，typedef 是类型重命名，拥有类型作用域，会被编译器识别，属于类型别名定义。
 *
 * 5. 常用场景
 *    简化复杂类型写法，提升代码可读性，最常用于结构体、枚举、指针等复杂类型的别名定义。如自定义bool或者简化学生(结构体)类型变量的声明
 */


// 宏定义和typedef的对比
#define MINT int *
typedef int* PINT;


void typedef_test()
{
    // 正常定义
    unsigned char c;
    unsigned short s;
    unsigned int i;
    unsigned long long ll;
    int array[10];

    // 使用typedef起简化别名
    typedef unsigned char uint_8;
    typedef unsigned short uint_16;
    typedef unsigned int uint_32;
    typedef unsigned long long uint_64;
    typedef int Array[10];

    //使用数据类型的简化别名定义数据
    uint_8 tc;
    uint_16 ts;
    uint_32 ti;
    uint_64 tll;
    //在下面打端点,使用使用debug模式查看数据类型,控制台中可以明确查看到数据类型为数组
    Array nums = { 1,2,3,4 };
    printf("unsigned char: sizeof(c)= %d, sizeof(tc)= %d\n", sizeof(c), sizeof(tc));
    printf("unsigned short: sizeof(s)= %d, sizeof(ts)= %d\n", sizeof(s), sizeof(ts));
    printf("unsigned int: sizeof(i)= %d, sizeof(ti)= %d\n", sizeof(i), sizeof(ti));
    printf("unsigned long: sizeof(ll)= %d, sizeof(tll)= %d\n", sizeof(ll), sizeof(tll));
}


/**
 * typedef和结构体结合使用方式一:
 */
struct Student
{
    char id[32];
    char name[20];
    int age;
};
typedef struct Student Student;
typedef struct Student *PStudent;

/**
 * typedef和结构体结合使用方式二:
 */
typedef struct User
{
    char id[32];
    char name[20];
    int age;
} User, *PUser;


/**
 * 测试typedef和结构体结合使用
 */
void typedef_with_struct_test()
{
    /**
     * 测试 typedef和结构体结合使用方式一:
     */
	Student student;
	PStudent p_student = &student;

    /**
     * 测试 typedef和结构体结合使用方式二:
     */
    User user;
    PUser p_user = &user;
}

/**
 * 宏定义和typedef的对比
 */ 
void macrodefine_and_typedef()
{
    // 相当于 int *a; int b; 宏只是做字符串替换
    MINT a, b;
    printf("hello\n");
    // 相当于 int *i, int *j;
    PINT i, j;
    printf("world\n");
}

int main()
{
    //typedef_test();
    //typedef_with_struct_test();
    macrodefine_and_typedef();
    return 0;
}
