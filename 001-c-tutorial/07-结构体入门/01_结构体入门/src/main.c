#include <stdio.h>
#include <string.h>

/*
 * 结构体专题
 *
 * 1. 结构体是属性的集合
 * 2. 结构体定义时最后必须加分号，否则会报错
 * 3. 定义在main()之外的结构体称为全局结构体，定义在main()里面的结构体称为局部结构体
 * 4. typedef 定义的 结构体类型 首字母大写为 C 语言标准命名规范，用于与变量命名区分，直观标识该名称为自定义类型而非一个变量
 * 5. 定义结构体、 结构体类型 变量、 结构体指针类型 变量有以下几种方式
 * 	  - 方式一：先定义结构体，再定义 结构体类型 变量(或 结构体指针类型 变量)
 *		// 定义结构体(这个 student_s 是结构体标签，不是别名)
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量
 *		struct Student student;
 *		// 定义  结构体指针类型 变量
 *		struct Student *p_student;
 *
 *    - 方式二：定义结构体的同时定义 结构体类型 变量(或 结构体指针类型 变量)
 *		// 带标签名的结构体(不推荐省略标签名)
 *		struct Student
 *		{
 *			int id;
 *	 		char name[20];
 *			int age;
 *		} student, *p_student;
 *
 *    - 方式三：使用typedef关键字定义结构体，定义 结构体类型 变量(或 结构体指针类型 变量)时可以使用简化的方式声明
 *      // 只定义 结构体类型 别名，不定义 结构体指针类型 别名	 (typedef + 匿名结构体)	=> 不推荐
 * 		typedef struct
 * 		{
 *   		int id;
 *   		char name[20];
 *   		int age;
 * 		} Student;
 *
 *		// 定义 结构体类型 变量
 * 		Student student;
 * 		// 定义 结构体指针类型 变量(必须手动加 *)
 * 		Student *p_student;
 *      --------------------------------------------------------------------------------
 *
 *      // 同时定义 结构体类型 别名和 结构体指针类型 别名 (typedef + 匿名结构体)  		=> 更推荐
 *	    typedef struct
 *	    {
 *    		int id;
 *   		char name[20];
 *   		int age;
 *	    } Student, *PStudent;	// 一般不推荐使用 typedef 直接定义指针，现代C语言开发已经淘汰这种风格
 *
 *      // 定义 结构体类型 变量
 * 	    Student student;
 * 	    // 定义 结构体指针类型 变量(不用写 *，直接用别名)
 *	    PStudent p_student;
 *      --------------------------------------------------------------------------------
 *
 *		// 同时定义 结构体类型 别名和 结构体指针类型 别名 (typedef + 带标签结构体)  	=> 不推荐，只有结构体自引用(如：链表)才加标签
 *		typedef struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		} Student, *PStudent;	// 一般不推荐使用 typedef 直接定义指针，现代C语言开发已经淘汰这种风格
 *
 *		// 定义 结构体类型 变量
 *		Student student;
 *		// 定义 结构体指针类型 变量
 *		PStudent p_student;
 *		--------------------------------------------------------------------------------
 *
 *    - 方式四：定义匿名结构体(适用于临时使用结构体的情况)
 *		// 定义匿名 结构体类型 变量(或 结构体指针类型 变量)
 *		struct
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		} student, *p_student;
 *
 * 5. 给 结构体类型 变量赋值有以下几种方式
 *    - 方式一：直接赋值(使用.运算符赋值)
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量并赋值
 *		struct Student student = { 1, "张三", 18 };
 *
 *    - 方式二：先定义 结构体类型 变量，后赋值(使用.运算符赋值)
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量
 *		struct Student student;
 *		// 给 结构体类型 变量赋值
 *		student.id = 1;
 *		// 给字符串类型成员变量赋值
 *		strcpy(student.name, "张三");
 *		student.age = 18;
 *
 *    - 方式三：C99指定初始化器(可乱序赋值)
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量并使用C99指定初始化器赋值
 *		struct Student student = {.id=1, .age=18, .name="张三"};
 *
 *    - 方式四：使用指针解引用赋值(指针需要进行初始化且初始化时不能指向NULL)
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		struct Student student = {};
 *
 *		// 定义 结构体指针类型 变量
 *		struct Student *p_student = &student;
 *		// 使用指针解引用赋值
 *		(*p_student).id = 1;
 *		// 给字符串类型成员变量赋值
 *		strcpy((*p_student).name, "张三");
 *		(*p_student).age = 23;
 *
 *    - 方式五：使用指针配合箭头函数(成员选择符)赋值
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		struct Student student = {};
 *
 *		// 定义 结构体指针类型 变量
 *		struct Student *p_student = &student;
 *		// 使用指针配合箭头函数(成员选择符)赋值
 *		p_student->id = 1;
 *		// 给字符串类型成员变量赋值
 *		strcpy(p_student->name, "张三");
 *		p_student->age = 23;
 *
 * 6. 访问 结构体类型 变量有以下几种方式
 *    - 方式一：使用.运算符访问
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量并赋值
 *		struct Student student = { 1,"张三", 18 };
 *		printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);
 *
 *    - 方式二：使用指针解引用访问
 * 		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量并赋值
 *		struct Student student = { 1,"张三", 18 };
 *		struct Student *p_student = &student;
 *		printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", (*p_student).id, (*p_student).name, (*p_student).age);
 *
 *    - 方式三：使用指针配合箭头函数(成员选择符)访问
 *		// 定义结构体
 *		struct Student
 *		{
 *			int id;
 *			char name[20];
 *			int age;
 *		};
 *
 *		// 定义 结构体类型 变量并赋值
 *		struct Student student = { 1,"张三", 18 };
 *		struct Student *p_student = &student;
 *		printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", p_student->id, p_student->name, p_student->age);
 *
 * 7. 结构体名和结构体类型名，typedef的作用就是给类型起别名，定义该类型变量时可以简单的写几个字母
 *    结构体名		Student
 *    结构体类型名	struct Student
 */

/**
 * 定义结构体、 结构体类型 变量(或 结构体指针类型 变量)
 *    方式一：先定义结构体，再定义 结构体类型 变量(或 结构体指针类型 变量)	 => 不推荐
 */ 
void define_struct_1()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量
	struct Student student;
	// 定义 结构体指针类型 变量
	struct Student *p_student;

	student.id = 1;
	// 给字符串类型成员变量赋值
	strcpy(student.name, "张一");
	student.age = 15;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);

	p_student = &student;
	p_student->id = 2;
	// 给字符串类型成员变量赋值
	strcpy(p_student->name, "李一");
	p_student->age = 20;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", p_student->id, p_student->name, p_student->age);
	printf("-------------------------------------\n");
}

/**
 * 定义结构体、 结构体类型 变量(或 结构体指针类型 变量)
 *    方式二：定义结构体的同时定义 结构体类型 变量(或 结构体指针类型 变量)  => 不推荐
 */ 
void define_struct_2()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	} student, *p_student;

	student.id = 1;
	// 给字符串类型成员变量赋值
	strcpy(student.name, "张二");
	student.age = 16;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);

	p_student = &student;
	p_student->id = 2;
	// 给字符串类型成员变量赋值
	strcpy(p_student->name, "李二");
	p_student->age = 21;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", p_student->id, p_student->name, p_student->age);
	printf("-------------------------------------\n");
}

/**
 * 定义结构体、 结构体类型 变量(或 结构体指针类型 变量)
 * 	  方式三：使用typedef关键字给 结构体类型 和 结构体指针类型 起别名，定义变量时可以使用简化的方式声明  => 推荐v3.0版写法
 */ 
void define_struct_3()
{
	/*
	// v1.0 => 只定义 结构体类型 别名，不定义 结构体指针类型 别名	 (typedef + 匿名结构体)	=> 不推荐
	typedef struct
	{
	 	int id;
	 	char name[20];
	 	int age;
	} Student;

	// 定义 结构体类型 变量
	Student student;
	// 定义 结构体指针类型 变量(必须手动加 *)
	Student *p_student;
	*/

	// v2.0 => 同时定义 结构体类型 别名和 结构体指针类型 别名 (typedef + 带标签结构体)  	 => 不推荐，只有结构体自引用(如：链表)才加标签
	/*
	typedef struct Node
	{
		int data;
		p_node next;
	} Node, *PNode;		// 一般不推荐使用 typedef 直接定义指针，现代C语言开发已经淘汰这种风格
	*/
	/*
	typedef struct Student
	{
	 	int id;
	 	char name[20];
	 	int age;
	} Student, *PStudent;	// 一般不推荐使用 typedef 直接定义指针，现代C语言开发已经淘汰这种风格

	// 定义 结构体类型 变量
	Student student;
	// 定义 结构体指针类型 变量
	PStudent p_student;
	*/

	// v3.0 => 同时定义 结构体类型 别名和 结构体指针类型 别名 (typedef + 匿名结构体)  		=> 最推荐
	typedef struct
	{
		int id;
	 	char name[20];
	 	int age;
	} Student, *PStudent;	// 一般不推荐使用 typedef 直接定义指针，现代C语言开发已经淘汰这种风格

	// 定义 结构体类型 变量
	Student student;
	// 定义 结构体指针类型 变量(不用写 *，直接用别名)
	PStudent p_student;

	student.id = 1;
	// 给字符串类型成员变量赋值
	strcpy(student.name, "张三");
	student.age = 18;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);

	p_student = &student;
	p_student->id = 2;
	// 给字符串类型成员变量赋值
	strcpy(p_student->name, "李三");
	p_student->age = 23;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", p_student->id, p_student->name, p_student->age);
	printf("-------------------------------------\n");
}

/**
 * 定义结构体、 结构体类型 变量(或 结构体指针类型 变量)
 *    方式四：定义匿名 结构体类型 变量(或 结构体指针类型 变量)(适用于临时使用结构体的情况)  => 不推荐
 */ 
void define_struct_4()
{
	// 定义匿名 结构体类型 变量(或 结构体指针类型 变量)
	struct
	{
		int id;
		char name[20];
		int age;
	} student, *p_student;

	student.id = 1;
	// 给字符串类型成员变量赋值
	strcpy(student.name, "张四");
	student.age = 20;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);

	p_student = &student;
	p_student->id = 2;
	// 给字符串类型成员变量赋值
	strcpy(p_student->name, "李四");
	p_student->age = 25;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", p_student->id, p_student->name, p_student->age);
	printf("-------------------------------------\n");
}


/**
 * 给 结构体类型 变量赋值方式一：直接赋值(使用.运算符赋值)
 */ 
void assignment_struct_1()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量并赋值
	struct Student student = { 1, "张三", 18 };
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);
	printf("-------------------------------------\n");
}


/**
 * 给 结构体类型 变量赋值方式二：先定义 结构体类型 变量，后赋值(使用.运算符赋值)
 */ 
void assignment_struct_2()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量
	struct Student student;
	// 给 结构体类型 变量赋值
	student.id = 1;
	// 给字符串类型成员变量赋值
	strcpy(student.name, "张三");
	student.age = 18;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);
	printf("-------------------------------------\n");
}


/**
 * 给 结构体类型 变量赋值方式三：C99指定初始化器(可乱序赋值)
 */ 
void assignment_struct_3()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量并使用C99指定初始化器赋值
	struct Student student = { .id=1, .age=18, .name="张三" };
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);
	printf("-------------------------------------\n");
}


/**
 * 给 结构体类型 变量赋值方式四：使用指针解引用赋值(指针需要进行初始化且初始化时不能指向NULL)
 */ 
void assignment_struct_4()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	struct Student student = {};

	// 定义 结构体指针类型 变量
	struct Student *p_student = &student;
	// 使用指针解引用赋值
	(*p_student).id = 1;
	// 给字符串类型成员变量赋值
	strcpy((*p_student).name, "张三");
	(*p_student).age = 23;

	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", (*p_student).id, (*p_student).name, (*p_student).age);
	printf("-------------------------------------\n");
}


/**
 * 给 结构体类型 变量赋值方式五：使用指针配合箭头函数(成员选择符)赋值
 */ 
void assignment_struct_5()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	struct Student student = {};

	// 定义 结构体指针类型 变量
	struct Student *p_student = &student;
	// 使用指针配合箭头函数(成员选择符)赋值
	p_student->id = 1;
	// 给字符串类型成员变量赋值
	strcpy(p_student->name, "张三");
	p_student->age = 23;

	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", (*p_student).id, (*p_student).name, (*p_student).age);
	printf("-------------------------------------\n");
}

/**
 * 访问 结构体类型 变量方式一：使用.运算符访问
 */ 
void visit_struct_1()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量并赋值
	struct Student student = { 1, "张三", 18 };
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", student.id, student.name, student.age);
	printf("-------------------------------------\n");
}


/**
 * 访问 结构体类型 变量方式二：使用指针解引用访问
 */ 
void visit_struct_2()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量并赋值
	struct Student student = { 1, "张三", 18 };
	struct Student *p_student = &student;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", (*p_student).id, (*p_student).name, (*p_student).age);
	printf("-------------------------------------\n");
}


/**
 * 访问 结构体类型 变量方式三：使用指针配合箭头函数(成员选择符)访问
 */ 
void visit_struct_3()
{
	// 定义结构体
	struct Student
	{
		int id;
		char name[20];
		int age;
	};

	// 定义 结构体类型 变量并赋值
	struct Student student = { 1, "张三", 18 };
	struct Student *p_student = &student;
	printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", p_student->id, p_student->name, p_student->age);
	printf("-------------------------------------\n");
}


/**
 * 结构体数组
 */ 
void struct_array()
{
	struct Student
	{
		char id;
		char name[20];
		int age;
	};
	struct Student student1 = { 1, "张三", 18 };
	struct Student student2 = { 2, "李四", 23 };
	struct Student student3 = { 3, "王五", 25 };

	// 定义一个结构体数组
	struct Student students[] = { student1, student2, student3 };
	int len = sizeof(students) / sizeof(students[0]);
	for(int i = 0; i < len; i++)
	{
		printf("学号 = %d, 姓名 = %s, 年龄 = %d\n", students[i].id, students[i].name, students[i].age);
	}
	printf("-------------------------------------\n");
}

/**
 * 结构体成员初始值
 */
void struct_member_init_val()
{
	/**
	 * 结构体名		student_s
	 * 结构体类型 名	struct student_s
	 * 特别注意		最后的分号必须写，否则会报错
	 */
	struct Student
	{
		char id[20];	// 20字节
		char name[20];	// 20字节
		char sex[10];	// 10字节
		int age;		// 4字节
	};

	struct Student s1 = { "001", "张三", "男", 20 };
	printf("s1 => id = %s, name = %s, sex = %s, age = %d\n", s1.id, s1.name, s1.sex, s1.age);

	// 如果不赋初始值，打印时会打印出随机值
	struct Student s2;
	printf("s2 => id = %s, name = %s, sex = %s, age = %d\n", s2.id, s2.name, s2.sex, s2.age);
	// 把s1的值赋给s2
	s2 = s1;
	printf("s2 => id = %s, name = %s, sex = %s, age = %d\n", s2.id, s2.name, s2.sex, s2.age);
	printf("-------------------------------------\n");
}

int main()
{
	// 定义结构体、 结构体类型 变量、 结构体指针类型 变量有以下几种方式
	define_struct_1();
	define_struct_2();
	define_struct_3();
	define_struct_4();

	// 给 结构体类型 变量赋值有以下几种方式
	assignment_struct_1();
	assignment_struct_2();
	assignment_struct_3();
	assignment_struct_4();
	assignment_struct_5();

	// 访问 结构体类型 变量有以下几种方式
	visit_struct_1();
	visit_struct_2();
	visit_struct_3();

	// 结构体类型 数组
	struct_array();

    // 结构体成员初始值
	struct_member_init_val();
	return 0;
}
