#include<stdio.h>
#include<stdbool.h>
#include<string.h>

/**
 * 基于函数指针实现对不同数据类型的数组进行冒泡排序
 */


// 结构体 + typedef简化结构体定义 方式一
/*
// 定义一个结构体
struct Student
{
	int id,
	char[] name,
	int age
};

// 使用typedef简化结构体定义
typedef struct Student Student;
*/


// （匿名）结构体 + typedef简化结构体定义
typedef struct
{
	int id;
	char name[20];
	int age;
} Student;


/**
 * 打印整型数组
 */ 
void print_int_arr_4(const void *pv)
{
	printf("%d\t", *(int *)pv);
}

/**
 * 打印float类型数组
 */ 
void print_float_arr_4(const void *pv)
{
	printf("%.2f\t", *(float *)pv);
}

/**
 * 打印double类型数组
 */ 
void print_double_arr_4(const void *pv)
{
	printf("%.2f\t", *(double *)pv);
}

/**
 * 打印字符数组
 */ 
void print_char_arr_4(const void *pv)
{
	printf("%c\t", *(char *)pv);
}

/**
 * 打印字符串数组
 * 特别注意： 这里的vp是一个二级指针
 */ 
void print_str_arr_4(const void *pv)
{
    char **s = (char **)pv;  // 正确的类型转换
    printf("%s\t", *s);     // 打印字符串内容
}


/**
 * 打印结构体数组
 */ 
void print_struct_arr_4(const void *pv)
{
	const Student *p_student = (const Student *)pv;
	printf("%d，%s，%d\t", p_student -> id, p_student -> name, p_student -> age);
}

/**
 * 打印数组（泛型方法）
 */
void print_arr_4(const void *pv, const int size, int element_size, void (*print)(const void *), char *element_type_name, int print_type)
{
	printf("%s类型数组冒泡排序%s => ", element_type_name, print_type == 0 ? "前" : "后");
	if(NULL == pv || NULL == print || size < 1 || element_size < 1)
	{
		return;
	}
	const char *pc = (const char *)pv;
	for(int i = 0; i < size; i++)
	{
		(*print)(pc);
		pc += element_size;
	}
	printf("\n");
}

// 交换函数
void swap(void *pa, void *pb, int size)
{
    char temp[size];
    memcpy(temp, pa, size);
    memcpy(pa, pb, size);
    memcpy(pb, temp, size);
}

/**
 * 比较两个int类型数据的大小
 */
bool compare_int(const void *pa, const void *pb)
{
	const int *pia = (const int *)pa;
	const int *pib = (const int *)pb;
	if(*pia > *pib)
	{
		return true;
	}
	return false;
}

/**
 * 比较两个float类型数据的大小
 */
bool compare_float(const void *pa, const void *pb)
{
	const float *pfa = (const float *)pa;
	const float *pfb = (const float *)pb;
	if(*pfa > *pfb)
	{
		return true;
	}
	return false;
}

/**
 * 比较两个double类型数据的大小
 */
bool compare_double(const void *pa, const void *pb)
{
	const double *pda = (const double *)pa;
	const double *pdb = (const double *)pb;
	if(*pda > *pdb)
	{
		return true;
	}
	return false;
}

/**
 * 比较两个char类型数据的大小
 */
bool compare_char(const void *pa, const void *pb)
{
	const char *pca = (const char *)pa;
	const char *pcb = (const char *)pb;
	if(*pca > *pcb)
	{
		return true;
	}
	return false;
}

/**
 * 比较两个字符串类型数据的大小
 */
bool compare_str(const void *pa, const void *pb)
{
	const char **psa = (const char **)pa;
	const char **psb = (const char **)pb;
	if(strcmp(*psa, *psb) > 0)
	{
		return true;
	}
	return false;
}

/**
 * 比较两个结构体类型数据的大小（按id）
 */
bool compare_struct_by_id(const void *pa, const void *pb)
{
	const Student *p_stu_a = (const Student *)pa;
	const Student *p_stu_b = (const Student *)pb;
	if(p_stu_a->id > p_stu_b->id)
	{
		return true;
	}
	return false;
}

/**
 * 比较两个结构体类型数据的大小（按姓名）
 */
bool compare_struct_by_name(const void *pa, const void *pb)
{
	const Student *p_stu_a = (const Student *)pa;
	const Student *p_stu_b = (const Student *)pb;
	if(strcmp(p_stu_a->name, p_stu_b->name) > 0)
	{
		return true;
	}
	return false;
}

/**
 * 泛型冒泡排序
 */
void bubble_sort_3(const void *pv, int len, int element_size, bool (*compare)(const void *, const void *))
{
	char *pc = (char *)pv;
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i -1; j++)
		{
            void *current = pc + j * element_size;
            void *next = pc + (j + 1) * element_size;
            if((*compare)(current, next))
            {
                swap(current, next, element_size);
            }
		}
	}
}

#if 0
int main()
{
	// 定义整型数组
	int ir[] = {64, 34, 25, 12, 22, 90, 11};
	int in = sizeof(ir) / sizeof(ir[0]);
	// 冒泡排序前
	print_arr_4(ir, in, sizeof(int), print_int_arr_4, "int", 0);
	// 冒泡排序
	bubble_sort_3(ir, in, sizeof(int), compare_int);
	// 冒泡排序后
	print_arr_4(ir, in, sizeof(int), print_int_arr_4, "int", 1);

	// 定义float类型数组
	float fr[] = { 3.14f, 2.71f, 1.41f, 1.73f, 0.57f };
	int fn = sizeof(fr) / sizeof(fr[0]);
	// 冒泡排序前
	print_arr_4(fr, fn, sizeof(float), print_float_arr_4, "float", 0);
	// 冒泡排序
	bubble_sort_3(fr, fn, sizeof(float), compare_float);
	// 冒泡排序后
	print_arr_4(fr, fn, sizeof(float), print_float_arr_4, "float", 1);


	// 定义double类型数组
	double dr[] = { 5.24, 2.18, 3.43, 7.76, 0.58 };
	int dn = sizeof(dr) / sizeof(dr[0]);
	// 冒泡排序前
	print_arr_4(dr, dn, sizeof(double), print_double_arr_4, "double", 0);
	// 冒泡排序
	bubble_sort_3(dr, dn, sizeof(double), compare_double);
	// 冒泡排序后
	print_arr_4(dr, dn, sizeof(double), print_double_arr_4, "double", 1);


	//定义字符数组
	char cr[] = { 'k', 'a', 'i', 'b', 'd' };
	int cn = sizeof(cr) / sizeof(cr[0]);
	// 冒泡排序前
	print_arr_4(cr, cn, sizeof(char), print_char_arr_4, "char", 0);
	// 冒泡排序
	bubble_sort_3(cr, cn, sizeof(char), compare_char);
	// 冒泡排序后
	print_arr_4(cr, cn, sizeof(char), print_char_arr_4, "char", 1);


	//定义字符串数组（这里实际上是定义了一个二维数组）
	char *str[] = { "ban\0ana", "apple", "cherry", "orange", "pear" };
	int sn = sizeof(str) / sizeof(str[0]);
	// 冒泡排序前
	print_arr_4(str, sn, sizeof(str[0]), print_str_arr_4, "字符串", 0);
	// 冒泡排序
	bubble_sort_3(str, sn, sizeof(str[0]), compare_str);
	// 冒泡排序后
	print_arr_4(str, sn, sizeof(str[0]), print_str_arr_4, "字符串", 1);


	//定义结构体数组
	Student students[] = {
		{ 1, "zhangsan", 18 },
		{ 3, "lisi", 20 },
		{ 2, "wangwu", 22 }
	};
	int structn = sizeof(students) / sizeof(students[0]);
	// 冒泡排序前
	print_arr_4(students, structn, sizeof(students[0]), print_struct_arr_4, "结构体", 0);
	//bubble_sort_3(students, structn, sizeof(students[0]), compare_struct_by_id);
	bubble_sort_3(students, structn, sizeof(students[0]), compare_struct_by_name);
	// 冒泡排序后
	print_arr_4(students, structn, sizeof(students[0]), print_struct_arr_4, "结构体", 1);
	return 0;
}
#endif
