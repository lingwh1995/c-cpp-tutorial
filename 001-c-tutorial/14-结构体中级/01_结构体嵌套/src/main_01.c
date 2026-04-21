#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------------
/**
 * 创建候选人结构体
 */
typedef struct
{
	char name[20];
	int votes;
} Candidate;

/**
 * 给候选人投票
 */
void vote_for_candidate(Candidate *candidates, int len)
{
	if(candidates == NULL || len == 0)
	{
		return;
	}
	char name[20];
	// 1. 最多读取19个字符 2. scanf中使用 name 而非 &name 因为字符数组的名称本身就代表它的地址，再取地址就成了指针的地址
	while(printf("请输入候选人姓名:\n"), scanf("%19s", name), name[0] != '#')
	{
		for(int i = 0; i < len; i++)
		{
			if(strcmp(name, candidates[i].name) == 0)
			{
				candidates[i].votes++;
				break;
			}
		}
	}
}

/**
 * 打印投票结果
 */
void printf_vote_result(Candidate *candidates, int len)
{
	printf("投票结果\n");
	if(candidates == NULL || len == 0)
	{
		return;
	}
	for(int i = 0; i < len; i++)
	{
		printf("姓名 %s -> %d\n", candidates[i].name, candidates[i].votes);
	}
}

/**
 * 投票程序
 */
void vote_test()
{
	Candidate candidates[3] = {
		{ "zs", 0 },
		{ "ls", 0 },
		{ "ww", 0 },
	};
	int len = sizeof(candidates) / sizeof(candidates[0]);
	// 给候选人投票
	vote_for_candidate(candidates, len);
	// 打印投票结果
	printf_vote_result(candidates, len);
}
// -----------------------------------------------------------------------------------

/**
 * 学生结构体
 */
typedef struct
{
	char id[20];
	char name[20];
	float scores;
} Student;

/**
 * 交换两个学生对象
 * @param student_1
 * @param student_2
 */
void swap(Student *student_1, Student *student_2)
{
	Student temp_student = *student_1;
	*student_1 = *student_2;
	*student_2 = temp_student;
}

/**
 * 使用选择排序按分数从高到低排序
 * @param student
 * @param len
 */
void select_sort_by_scores(Student *student, int len)
{
	if (student == NULL || len == 0)
	{
		return;
	}
	for (int i = 0; i < len; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < len; j++)
		{
			if(student[j].scores - student[minIndex].scores > 0)
			{
				minIndex = j;
			}
		}
		swap(&student[i], &student[minIndex]);
	}
}

/**
 * 打印安分数排序后的学生数组
 * @param students
 * @param len
 */
void print_sort_by_scores_result(Student *students, int len)
{
	if (students == NULL || len == 0)
	{
		return;
	}
	for (int i = 0; i < len; i++)
	{
		printf("id %s, name %s, scores %.1f\n", students[i].id, students[i].name, students[i].scores);
	}
}

/**
 * 根据分数排序
 */
void select_sort_by_scores_test()
{
	// 学生数组
	Student students[] = {
		{ "001", "zhangsan", 88.8},
		{ "002", "lisi", 85.5},
		{ "003", "wangwu", 92.3},
		{ "004", "zhaoliu", 39.5},
		{ "005", "sunqi", 56.3}
	};
	int len = sizeof(students) / sizeof(students[0]);
	select_sort_by_scores(students, len);
	print_sort_by_scores_result(students, len);
}

#if 0
int main()
{
	//vote_test();
	select_sort_by_scores_test();
	return 0;
}
#endif
