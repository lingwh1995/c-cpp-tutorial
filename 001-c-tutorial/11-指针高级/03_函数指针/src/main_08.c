#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// 结构体 + typedef简化结构体定义 方式一
/*
// 定义一个结构体
struct person_s
{
	int id,
	char[] name,
	int age
};

// 使用typedef简化结构体定义
typedef struct person_s person;
*/

// （匿名）结构体 + typedef简化结构体定义
typedef struct
{
	int id;
	char name[20];
	int age;
} Person;


/**
 * 比较两个int类型数据的大小
 * @param pa
 * @param pb
 * @return
 */
int comp_int(const void *pa, const void *pb)
{
	const int *pia = (const int *)pa;
	const int *pib = (const int *)pb;
	if(*pia > *pib)
	{
		return 1;
	}
	else if(*pia < *pib)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**
 * 比较两个double类型数据的大小
 * @param pa
 * @param pb
 * @return
 */
int comp_double(const void *pa, const void *pb)
{
	const double *pda = (const double *)pa;
	const double *pdb = (const double *)pb;
	if(*pda > *pdb)
	{
		return 1;
	}
	else if(*pda < *pdb)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**
 * 比较两个char类型数据的大小
 * @param pa
 * @param pb
 * @return
 */
int comp_char(const void *pa, const void *pb)
{
	const char *pca = (const char *)pa;
	const char *pcb = (const char *)pb;
	if(*pca > *pcb)
	{
		return 1;
	}
	else if(*pca < *pcb)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**
 * 比较两个字符串的大小
 * @param pa
 * @param pb
 * @return
 */
int comp_str(const void *pa, const void *pb)
{
	const char **psa = (const char **)pa;
	const char **psb = (const char **)pb;
	return strcmp(*psa, *psb);
}

/**
 * 比较两个结构体类型数据的大小（按id）
 */
int compare_struct(const void *pa, const void *pb)
{
	const Person *p_person_a = (const Person*)pa;
	const Person *p_person_b = (const Person*)pb;
	if(p_person_a->id > p_person_b->id)
	{
		return 1;
	}
	else if(p_person_a->id < p_person_b->id)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**
 * 打印整形数组
 */
void print_int_arr_5(int *arr, int len)
{
	for(int i = 0; i < len; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

/**
 * 打印double类型数组
 */
void print_double_arr_5(double *arr, int len)
{
	for(int i = 0; i < len; i++)
	{
		printf("%.2f\t", arr[i]);
	}
	printf("\n");
}


/**
 * 打印char类型数组
 */
void print_char_arr_5(char *arr, int len)
{
	for(int i = 0; i < len; i++)
	{
		printf("%c\t", arr[i]);
	}
	printf("\n");
}

/*
 * 打印字符串类型数组
 */
void print_str_arr_5(const char *arr[], int len)
{
	for(int i = 0; i < len; i++)
	{
		printf("%s\t", arr[i]);
	}
	printf("\n");
}


/**
 * 打印结构体数组
 */
void print_struct_arr_5(const void *pv, int len)
{
    const Person *p_person = (const Person*)pv;
    for(int i = 0; i < len; i++)
    {
        printf("%d，%s，%d\t", p_person[i].id, p_person[i].name, p_person[i].age);
    }
    printf("\n");
}

#if 0
int main()
{
	// 对整型数组进行快速排序
	int ar[] = { 34, 56, 89, 12, 90, 100, 45, 23 };
	int in = sizeof(ar) / sizeof(ar[0]);
	qsort(ar, in, sizeof(int), comp_int);
	print_int_arr_5(ar, in);

	// 对double型数组进行快速排序
	double dr[] = { 2.6, 2.8, 3.7, 4.6, 7.2 };
	int dn = sizeof(dr) / sizeof(dr[0]);
	qsort(dr, dn, sizeof(double), comp_double);
	print_double_arr_5(dr, dn);

	// 对char型数组进行快速排序
	char cr[] = { 'b', 'e', 'c', 'a', 'd' };
	int cn = sizeof(cr) / sizeof(cr[0]);
	qsort(cr, cn, sizeof(char), comp_char);
	print_char_arr_5(cr, cn);

	// 对字符串数组进行排序
	const char *str[] = { "bcd", "acd", "abc", "efg", "def"};
	int sn = 5;
	qsort(str, sn, sizeof(char *), comp_str);
	print_str_arr_5(str, sn);

	// 对结构体数组进行排序

	//定义结构体数组
	Person persons[] = {
		{ 1, "zhangsan", 18 },
		{ 3, "lisi", 20 },
		{ 2, "wangwu", 22 }
	};
	int personn = sizeof(persons) / sizeof(persons[0]);
	qsort(persons, personn, sizeof(persons[0]), compare_struct);
	print_struct_arr_5(persons, personn);
	return 0;
}
#endif
