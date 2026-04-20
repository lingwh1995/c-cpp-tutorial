#include "stdaef.h"
#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#define SCORE_SIZE 3	 // 科目数量
#define MAX_STUDENT 1   // 最大学生数
#define SCALING_RATIO 2  // 缩放倍数

typedef struct
{
	int id;
	char name[10];
    // 特别注意：要多开辟一个空间存放字符串结尾符 '\0'
	char sex[7];
	int age;
	float scores[SCORE_SIZE];
	float total_score;
	float avg_score;
} Student, *PStudent;

typedef struct
{
	// 前学生数量
	int current_count;
	// 容量
	int max_capacity;
	Student *student_list;
} StudentManager, *PStudentManager;

void init_student_manager(StudentManager *p_student_manager);
void destory_student_manager(StudentManager *p_student_manager);
bool scaling_student_list(StudentManager *p_student_manager);
void load_student_from_file(StudentManager *p_student_manager);
int get_student_size(const StudentManager  *p_student_manager);
bool is_full(const StudentManager  *p_student_manager);
bool is_empty(const StudentManager  *p_student_manager);
Student input_student();
bool add_student(StudentManager  *p_student_manager);
void show_student(const StudentManager *p_student_manager);
void show_student_by_pos(const StudentManager *p_student_manager, int pos);
void write_student_to_file(const StudentManager *p_student_manager);
int find_by_id(const StudentManager *p_student_manager, int id);
int find_by_name(const StudentManager *p_student_manager, char *name);
void find_student(const StudentManager *p_student_manager);
void delete_student_by_pos(StudentManager *p_student_manager, int pos);
void delete_student(StudentManager *p_student_manager);
void modify_student(StudentManager *p_student_manager);
void start_student_manager();
void show_student_manager_info(const StudentManager *p_student_manager);

#endif
