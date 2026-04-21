#include <stdio.h>
#include <string.h>

#define STUDENTS 3
#define SUBJECTS 4

#define ROWS 3
#define COLS 4

/**
 * 从尾到头在一个字符串中查找给定子串的第一个匹配之处
 */ 
char *my_strstr(const char *str, const char *substr)
{
    if(NULL == str || NULL == substr)
    {
        return NULL;
    }
	int m = strlen(str);
	int n = strlen(substr);
	for(int i = 0; i < m - n + 1; i++)
	{
		int k = i;
		int j = 0;
		while(str[k] == substr[j] && j < n)
		{
			k++;
			j++;
		}
		if(j == n)
		{
			return (char *)str + i;
		}
	}
	return NULL;
}

void my_strstr_test()
{
	const char *str = "abccabcabbc";
	const char *substr = "abc";
	char *result = my_strstr(str,substr);
	printf("result = %s\n", result);
}

void strncpy_test()
{
   char src[40];
   char dest[12];
   memset(dest, '\0', sizeof(dest));
   strcpy(src, "Hello, world!");
   strncpy(dest, src, 5);
   printf("最终的目标字符串： %s\n", dest);
}

/**
 * 打印学生分数
 */
void print_student_scores_test()
{
	char names[STUDENTS][10] = { "张三", "李四", "王五" };
	float scores[STUDENTS][SUBJECTS] = {
		{ 77.1, 77.2, 77.3, 77.4 },
		{ 88.1, 88.2, 88.3, 88.4 },
		{ 99.1, 99.2, 99.3, 99.4 }
	};
	printf("姓名\t语文\t数学\t英语\t物理\t平均分\n");
	for(int i = 0; i < STUDENTS; i++)
	{
		int sumScores = 0;
		printf("%s\t", names[i]);
		for(int j = 0; j < SUBJECTS; j++)
		{
			sumScores = scores[i][j];
			printf("%.2f\t", scores[i][j]);
		}
		printf("%d\n", sumScores / SUBJECTS);
	}
}

/**
 * 矩阵相加测试
 */
void matrix_add_test()
{
	int matrix_1[ROWS][COLS] = {
			{ 1, 1, 1, 1 },
			{ 2, 2, 2, 2 },
			{ 3, 3, 3, 3 }
	};
	int matrix_2[ROWS][COLS] = {
			{ 3, 3, 3, 3 },
			{ 2, 2, 2, 2 },
			{ 1, 1, 1, 1 }
	};
	int matrix_3[ROWS][COLS] = {};

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			matrix_3[i][j] = matrix_1[i][j] + matrix_2[i][j];
		}
	}

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			printf("%d\t", matrix_3[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	//my_strstr_test();
	//strncpy_test();
	//print_student_scores_test();
	matrix_add_test();
	return 0;
}
