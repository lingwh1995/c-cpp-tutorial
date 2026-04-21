#include <stdio.h>

/**
 * 指针知识进阶
 */

/*
 * 指针中 * 的含义
 */
void pointer_senior_test_1()
{
	/**
	 * 常见的指针变量
	 *
	 * p可以指向int类型的数据，也可以指向类似 int arr[n] 数组元素的地址
	 * int *p;
	 * 二级指针，指向 int * 类型的数据
	 * int **p;
	 * p是数组，数组的元素是 int指针
	 * int *p[n];
	 * p为指向数组的指针，指向大小为n个整数的数组
	 * int (*p)[n];
	 */

    int a = 10, b =20;
    int *p = &a;
    *p = 100;
    printf("a = %d, %p => *p %d\n", a, p, *p);

    //*&a = a; 	*&a和a代表同样的值，同样的含义
    	// a 就等价于 *&a, *意思是对此地址解引用
    printf("*&a = %d, a = %d\n", *&a, a);
    //*&p = p; 	*&p和p代表同样的值，同样的含义
    printf("*&p = %p, p = %p\n", *&p, p);
    // &*p = p; 等式不成立，原因是 指针是一个常量，不能给常量赋值
    printf("&*p = %p, p = %p\n", &*p, p);

    int *s = NULL;
    s = &*p; // 等价于 s = &a;
}

void pointer_senior_test_2()
{
    int a = 10, b = 20;
    int *pa = &a;
    int *pb = &b;
    printf("pa = %p, pb = %p\n", pa, pb);
    if (pa > pb)
    {
    	printf("a的地址比b的地址高\n");
    }
    else
    {
    	printf("a的地址比b的地址低\n");
    }

    if (*pa > *pb)
    {
    	printf("a的值比b的值大\n");
    }
    else
    {
    	printf("a的值比b的值小\n");
    }
}

void fun(int *p)
{
    int b = 200;
    *p = 100;
    p = &b;
    printf("b = %d, %p => *p %d\n", b, p, *p);
}

/**
 * 调用方法修改指针指向的值
 */
void pointer_senior_test_3()
{
    int a = 1;
    int *p = &a;
    fun(p);
    printf("a = %d, %p => *p %d\n", a, p, *p);
}

/**
 * 野指针
 *
 * 防止出现野指针的两种方法:
 *  1.定义指针时就对指针进行初始化(定义指针变量时一定要初始化)，使用合法的地址值进行初始化或者赋值为NULL
 *  2.定义指针时赋值为NULL，使用前先判断是否为NULL
 *
 * 特别说明：
 *  1.野指针不允许出现，一定不能出现野指针，很危险
 *  2.野指针一般可以通过参数校验，即使通过了参数校验，依然是一个不合法的参数，所以不允许出现野指针
 *  3.指针类型变量如果没有初始值，定义为空指针即可
 */
void pointer_senior_test_4()
{
    int a; //随机值
    int *p; //野指针:非常危险，要杜绝野指针的使用

    //定义指针时赋值为NULL(NULL: c语言中的空地址,实际上是0地址)
    int *pa = NULL;
    printf("pa = %p\n", pa);
    //使用指针前先进行判空处理
    if (pa != NULL)
    {
        a = *pa;
    }
    printf("a = %d\n", a);
}


/**
 * 空指针
 * 变量初始化值+指针的正确定义
 *  定义指针变量时不管是局部的、全局的、静态的、非静态的都要进行初始化,不要把安全性寄托在编译器上
 *
 */
int g;
static int sg;

// 定义一个全局空指针
int *gp = NULL;
// 定义一个静态类型的全局空指针
static int *sgp = NULL;
void pointer_senior_test_5()
{
    int i;
    static int si = 0;

    // 定义一个局部空指针
    int *pi = NULL;
    // 定义一个静态类型的局部空指针
    static int *spi = NULL;

    printf("全局变量g = %d\n", g);
    printf("全局静态变量sg = %d\n", sg);
    printf("局部变量i = %d\n", i);
    printf("局部静态变量si = %d\n", si);

    printf("全局指针变量gp = %p\n", gp);
    printf("全局静态指针变量sgp = %p\n", sgp);
    printf("局部指针变量pi = %p\n", pi);
    printf("局部静态指针变量spi = %p\n", spi);
}


/**
 * 失效指针(空悬指针):本意是返回一个指针类型的数据，结果返回一个空悬指针，不推荐这个写法，因为栈帧回收之后变量a就被回收了
 * 返回指针类型数据，栈帧回收后，这个返回值存放在一个临时变量中
 */
/**/
int *get_pointer_1()
{
	int a = 100;
    //相当于把主函数中的 变量a 复制一份放在get_pointer_1()这个函数中执行
    int *p = &a;
    //返回的p是当前栈帧中的 变量a 的地址
    printf("变量a的地址 = %p\n", &a);
    return p;
}

//解决失效指针(空悬指针)
/*
int *get_pointer_1()
{
    //使用static修饰，修改变量a的声明周期，本质是因为静态变量不在栈区，不会在栈帧被回收时同时回收
    static int a = 100;
    //相当于把主函数中的 变量a 复制一份放在get_pointer_1()这个函数中执行
    int *p = &a;
    //返回的p是当前栈帧中的 变量a 的地址
    printf("变量a的地址 = %p\n", &a);
    return p;
}*/

void pointer_senior_test_6()
{
    //指针的判断正确定义
    int i = 5;
    int *p = NULL;
    printf("变量i的地址 = %p\n", &i);
    printf("对变量i解引用 = %d\n", *&i);
    p = get_pointer_1();
    //指针的判空处理
    if (p != NULL)
    {
    	// 初次解引用还是可以获取到正确的值的，第二次解引用就无法获取到正确的值了
    	printf("对变量a在栈帧中地址的副本解引用 = %d\n", *p);
        printf("变量a在栈帧中地址的副本 = %p\n", p);
        //为什么返回的值不是100,因为这个指针失效了: 当get_pointer_1()执行结束后，get_pointer_1()中的变量已经释放了，所以解引用的时候这个指针已经失效了
        //MinGW编译器不会失效，可以成功解引用,但是vs编译器会失效
        printf("对变量a在栈帧中地址的副本解引用 = %d\n", *p);
    }
}

int *get_pointer_2(int *p)
{
    if (p != NULL)
    {
        *p = 100;
    }
    return p;
}

void pointer_senior_test_7()
{
    int a = 10;
    int *p = &a;
    int *s = NULL;
    s = get_pointer_2(p);
    printf("a = %d\n", a);
    printf("*s = %d\n", *s);
}

struct student_s {
    char id[32];
    int age;
    char name[50];
};

/**
 * 查看各种类型指针的大小
 */
void pointer_senior_test_8()
{
    int *pi = NULL;
    char *pc = NULL;
    double *pd = NULL;
    int **ps = NULL;
    struct student_s *p_student;
    printf("pi = %d\n", sizeof(pi));
    printf("pc = %d\n", sizeof(pc));
    printf("pd = %d\n", sizeof(pd));
    printf("sp = %d\n", sizeof(ps));
    printf("p_student = %d\n", sizeof(p_student));
}


/**
 * 指针经典练习题：指针和自增运算符的结合
 */
void pointer_senior_test_9()
{
    int arr[5] = { 12, 23, 34, 45, 56 };
    int *p = arr;
    int x = 0;//12
    int y = 0;//23
    x = *p++; // p++先用后加，相当于 x = *p; p++; 特别注意，不等同于：x = *p; (*p)++;
    y = *p;
    printf("x = %d, y = %d\n", x, y);
    x = ++*p;//24
    y = *p;//24 因为上一步操作之后,数组中第二个元素的值发生了变化,这里取的就是第二个值
    printf("x = %d, y = %d\n", x, y);
    x = *++p;//34
    y = *p;//34
    printf("x = %d, y = %d\n", x, y);
}

/*
 * *&p = &*p，编译器会自动处理成 *&p = &*p = p
 */
void pointer_senior_test_10()
{
    int a = 10;
    int *p = &a;
    printf("*&a = %d\n", *&a); // 10
    printf("p = %p\n", p);
    printf("*&p = %p\n", *&p); // *&p = p
    printf("&*p = %p\n", &*p); // &*p = p
    //变量一旦定义,就会在内存中分配地址，C语言不允许把一个地址赋值给另一个地址，这是非法的行为，实际上这里的&a是一个地址常量，常量的值是不允许被改变的，改变地址常量的值是一个非法的行为
}

#if 0
int main()
{
	//pointer_senior_test_1();
	pointer_senior_test_2();
	//pointer_senior_test_3();
	//pointer_senior_test_4();
	//pointer_senior_test_5();
	//pointer_senior_test_6();
	//pointer_senior_test_7();
	//pointer_senior_test_8();
	//pointer_senior_test_9();
	//pointer_senior_test_10();
    return 0;
}
#endif

