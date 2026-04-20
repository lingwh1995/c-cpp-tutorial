#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------------
/**
 * 嵌套结构体测试
 */
void nested_structure_test()
{
	struct date_s
	{
		int year;
		int month;
		int day;
	};

	/**
	 * 在结构体中使用另一个结构体作为成员变量
	 */
	struct student_s
	{
		char id[20];
		char name[20];
		char sex[8];
		int age;
		struct date_s birthday;
	};

	// 使用 . 访问
	struct student_s student = { "001", "张三", "男", 23, { 2026, 3, 20}};
	printf("id = %s\n", student.id);
	printf("name = %s\n", student.name);
	printf("sex = %s\n", student.sex);
	printf("age = %d\n", student.age);
	printf("birthday = %d年%d月%d日\n", student.birthday.year, student.birthday.month, student.birthday.day);
	printf("-----------------\n");

	// 使用 -> 访问
	struct student_s *p_student = &student;
	printf("id = %s\n", (*p_student).id);
	printf("name = %s\n", (*p_student).name);
	printf("sex = %s\n", p_student->sex);
	printf("age = %d\n", p_student->age);
	printf("birthday = %d年%d月%d日\n", p_student->birthday.year, p_student->birthday.month, p_student->birthday.day);
	printf("-------------------------------------\n");
}
// -----------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------
// 定义结构体类型和结构体指针类型
typedef struct
{
	char id[20];
	char name[20];
	char sex[8];
	int age;
} Student, *PStudent;

/**
 * 使用指针打印结构体
 */
void pointer_print_structure(const Student *student)
{
	if(student == NULL)
	{
		return;
	}
	/**
	 * -> 就是 (* ). 的简化写法
	 */
	printf("id = %s\n", (*student).id);
	printf("name = %s\n", (*student).name);
	printf("sex = %s\n", student->sex);
	printf("age = %d\n", student->age);
}

/**
 * 使用指针给结构体赋值
 */
void pointer_input_structure(Student *student)
{
	if(student == NULL)
	{
		return;
	}
	/**
	 * 特别注意
	 *
	 * 1. student->id 的意思是：用结构体指针，访问它指向的结构体里的 id 成员，所以 student->id = 指针指向的结构体
	 *    中的 id 成员
	 * 2. 之所以是student->name而不是&student->name，因为student->name 类型是 char[20]，在传参时，自动退化成指
	 *    针，所以直接写 student->name 就等于传了地址
	 * 3. ->(成员选择符)的优先级高于&(取地址符)，所以 &student->age 实际上相当于 &(student->age)
	 */
	printf("请输入student id:\n");
	scanf("%s", student->id);
	printf("请输入student name:\n");
	scanf("%s", student->name);
	printf("请输入student sex:\n");
	scanf("%s", student->sex);
	printf("请输入student age:\n");
	scanf("%d", &student->age);
}

void pointer_print_structure_test()
{
	Student student = { "002", "李四", "男", 20 };
	PStudent p_student = &student;
	// 只有数组才名才能在不去地址的情况下直接当成指针用，其他类型数据不行，要取地址才能用
	pointer_print_structure(p_student);
	printf("-------------------------------------\n");
}

/**
 * 给结构体赋值并打印赋值后的结构体
 */
void pointer_input_and_print_structure_test()
{
	Student student = { 0 };
	PStudent p_student = &student;
	pointer_input_structure(p_student);
	pointer_print_structure(p_student);
	printf("-------------------------------------\n");
}
// -----------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------
// 使用指针打印结构体数组 方式一
/*
void pointer_print_structure_arr(const Student *p_students, int len)
{
	if(p_students == NULL)
	{
		return;
	}
	for(int i = 0; i < len; i++)
	{
		printf("id = %s ", p_students[i].id);
		printf("name = %s ", p_students[i].name);
		printf("sex = %s ", p_students[i].sex);
		printf("age = %d\n", p_students[i].age);
	}
}
*/

// 使用指针打印结构体数组 方式二
void pointer_print_structure_arr(const Student *p_students, int len)
{
	if(p_students == NULL)
	{
		return;
	}
	for(int i = 0; i < len; i++)
	{
		printf("id = %s ", p_students->id);
		printf("name = %s ", p_students->name);
		printf("sex = %s ", p_students->sex);
		printf("age = %d\n", p_students->age);
		p_students++;
	}
}

/**
 * 使用指针打印结构体数组测试
 */
void pointer_print_structure_arr_test()
{
	// 定义结构体数组
	Student students[] = {
			{ "001", "张三", "男", 18 },
			{ "002", "李四", "女", 20 },
			{ "003", "王五", "男", 24 },
			{ "006", "赵六", "女", 28 },
	};
	int len = sizeof(students) / sizeof(students[0]);
	/**
	 * 特别注意：
	 * 	  PStudent p_students = &students; 错误写法  &students代表的是整个数组的地址
	 * 	  PStudent p_students = students;  正确写法  students 代表的是数组首元素地址
	 */
	PStudent p_students = students;
	pointer_print_structure_arr(p_students, len);
	printf("-------------------------------------\n");
}
// -----------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------
/**
 * 使用指针查找结构体测试
 */
int pointer_find_structure(const Student *p_students, int len, char *name)
{
	int position = -1;
	if(p_students == NULL || name == NULL)
	{
		return position;
	}
	for(int i = 0; i < len; i++)
	{
		if(strcmp(p_students[i].name, name) == 0)
		{
			printf("id = %s ", p_students[i].id);
			printf("name = %s ", p_students[i].name);
			printf("sex = %s ", p_students[i].sex);
			printf("age = %d\n", p_students[i].age);
			position = i;
		}
	}
	return position;
}

void pointer_find_structure_test()
{
	// 定义结构体数组
	Student students[] = {
			{ "001", "张三", "男", 18 },
			{ "002", "李四", "女", 20 },
			{ "003", "王五", "男", 24 },
			{ "006", "赵六", "女", 28 },
	};
	int len = sizeof(students) / sizeof(students[0]);
	/**
	 * 特别注意：
	 * 	  PStudent p_students = &students; 错误写法  &students代表的是整个数组的地址
	 * 	  PStudent p_students = students;  正确写法  students 代表的是数组首元素地址
	 */
	const PStudent p_students = students;
	char *name = "王五";
	int position = pointer_find_structure(p_students, len, name);
	printf("索引位置 = %d\n", position);
	printf("-------------------------------------\n");
}
// -----------------------------------------------------------------------------------

#if 0
int main()
{
	nested_structure_test();
	pointer_print_structure_test();
	//pointer_input_and_print_structure_test();
	pointer_print_structure_arr_test();
	pointer_find_structure_test();
	return 0;
}
#endif
