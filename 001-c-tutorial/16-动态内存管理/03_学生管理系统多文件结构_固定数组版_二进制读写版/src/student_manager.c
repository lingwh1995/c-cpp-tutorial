#include "../inc/stdaef.h"
#include "../inc/student_manager.h"

void init_student_manager(StudentManager *p_student_manager)
{
	assert(p_student_manager != NULL);
	p_student_manager->current_count = 0;
	p_student_manager->max_capacity = MAX_STUDENT;
	memset(p_student_manager->student_list, 0, sizeof(Student) * p_student_manager->max_capacity);
}

void load_student_from_file(StudentManager *p_student_manager)
{
    assert(p_student_manager != NULL);
    // 二进制读文件
    FILE* fp = fopen("student.txt", "rb");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    fread(&p_student_manager->current_count, sizeof(int), 1, fp);
    fread(p_student_manager->student_list, sizeof(Student), p_student_manager->current_count, fp);
    fclose(fp);
    fp = NULL;
}

int get_student_size(const StudentManager  *p_student_manager)
{
	assert(p_student_manager != NULL);
	return p_student_manager->current_count;
}

bool is_full(const StudentManager  *p_student_manager)
{
	assert(p_student_manager != NULL);
	return get_student_size(p_student_manager) == p_student_manager->max_capacity;
}

bool is_empty(const StudentManager  *p_student_manager)
{
	assert(p_student_manager != NULL);
	return get_student_size(p_student_manager) == 0;
}

Student input_student()
{
	Student student = { 0 };
	printf("请输入学生编号: \n");
	scanf("%d", &student.id);
	printf("请输入学生姓名: \n");
	scanf("%s", student.name);
	printf("请输入学生性别(male/female): \n");
	scanf("%s", student.sex);
    while (strcmp(student.sex, "male") != 0 && strcmp(student.sex, "female") != 0)
    {
        printf("性别输入错误！请重新输入:\n");
        scanf("%s", student.sex);
    }
	printf("请输入学生年龄(1-50): \n");
	scanf("%d", &student.age);
    while (student.age < 0 || student.age > 50)
    {
        printf("年龄输入错误！请重新输入:\n");
        scanf("%d", &student.age);
    }
	printf("请输入学生分数: \n");
	for(int i = 0; i < SCORE_SIZE; i++)
	{
		printf("请输入科目 %d 的分数: \n", i+1);
		scanf("%f", &student.scores[i]);
		student.total_score += student.scores[i];
	}
	student.avg_score = student.total_score / SCORE_SIZE;
	return student;
}

bool add_student(StudentManager  *p_student_manager)
{
	assert(p_student_manager != NULL);
	if(is_full(p_student_manager))
	{
		return false;
	}
	const Student student = input_student();
	p_student_manager->student_list[p_student_manager->current_count] = student;
	p_student_manager->current_count += 1;
	return true;
}

void show_student(const StudentManager *p_student_manager)
{
    assert(p_student_manager != NULL);
    if (is_empty(p_student_manager))
    {
        printf("No student data found!\n");
        return;
    }

    // 定义统一的列宽，方便一处修改全表生效
    const int W_ID = 12;
    const int W_NAME = 12;
    const int W_OTHER = 12;
    const int W_SCORE = 12;

    printf("\n");
    // 使用 %-*s 动态传入宽度，确保表头和数据完美垂直对齐
    printf("%-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s\n",
           W_ID, "ID", W_NAME, "Name", W_OTHER, "Sex", W_OTHER, "Age",
           W_SCORE, "Chinese", W_SCORE, "Math", W_SCORE, "English",
           W_SCORE, "Total", W_SCORE, "Average");

    printf("---------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < p_student_manager->current_count; i++)
    {
        const Student *p_student = &p_student_manager->student_list[i];

        // 打印基础信息
        printf("%-*d ", W_ID, p_student->id);

        // 姓名列：如果姓名是英文，%-*s 完美对齐；如果是中文，依然会有微小偏移（因为中文字符宽度问题）
        printf("%-*s ", W_NAME, p_student->name);

        printf("%-*s ", W_OTHER, p_student->sex);
        printf("%-*d ", W_OTHER, p_student->age);

        // 打印各科分数
        for (int j = 0; j < SCORE_SIZE; j++)
        {
            printf("%-*.2f ", W_SCORE, p_student->scores[j]);
        }

        // 打印总分和平均分
        printf("%-*.2f ", W_SCORE, p_student->total_score);
        printf("%-*.2f\n", W_SCORE, p_student->avg_score); // 注意这里加了 \n 换行
    }
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

void show_student_by_pos(const StudentManager *p_student_manager, int pos)
{
    assert(p_student_manager != NULL);
    if (is_empty(p_student_manager))
    {
        printf("No student data found!\n");
        return;
    }

    // 定义统一的列宽，方便一处修改全表生效
    const int W_ID = 12;
    const int W_NAME = 12;
    const int W_OTHER = 12;
    const int W_SCORE = 12;

    printf("\n");
    // 1. 打印英文表头
    // 使用 %-*s 动态传入宽度，确保表头和数据完美垂直对齐
    printf("%-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s\n",
           W_ID, "ID", W_NAME, "Name", W_OTHER, "Sex", W_OTHER, "Age",
           W_SCORE, "Chinese", W_SCORE, "Math", W_SCORE, "English",
           W_SCORE, "Total", W_SCORE, "Average");

    // 2. 打印分割线（长度约 110 个字符）
    printf("---------------------------------------------------------------------------------------------------------------\n");

    // 3. 循环打印学生信息
    for (int i = 0; i < p_student_manager->current_count; i++)
    {
        if(pos == i)
        {
            const Student *p_student = &p_student_manager->student_list[i];

            // 打印基础信息
            printf("%-*d ", W_ID, p_student->id);

            // 姓名列：如果姓名是英文，%-*s 完美对齐；如果是中文，依然会有微小偏移（因为中文字符宽度问题）
            printf("%-*s ", W_NAME, p_student->name);

            printf("%-*s ", W_OTHER, p_student->sex);
            printf("%-*d ", W_OTHER, p_student->age);

            // 打印各科分数
            for (int j = 0; j < SCORE_SIZE; j++)
            {
                printf("%-*.2f ", W_SCORE, p_student->scores[j]);
            }

            // 打印总分和平均分
            printf("%-*.2f ", W_SCORE, p_student->total_score);
            printf("%-*.2f\n", W_SCORE, p_student->avg_score); // 注意这里加了 \n 换行
        }
    }
    printf("\n");
}

void write_student_to_file(const StudentManager *p_student_manager)
{
    assert(p_student_manager != NULL);
    // 二进制写文件
    FILE* fp = fopen("student.txt", "wb");
    if (fp == NULL)
    {
        printf("open file error\n");
        return;
    }
    // 把数组中的元素个数写进去
    fwrite(&p_student_manager->current_count, sizeof(int), 1, fp);
    // 把数组写入
    fwrite(p_student_manager->student_list, sizeof(Student), p_student_manager->current_count, fp);
    fclose(fp);
    fp = NULL;
}

int find_by_id(const StudentManager *p_student_manager, int id)
{
	assert(p_student_manager != NULL);
	int pos = -1;
	for (int i = 0; i < p_student_manager->current_count; i++)
	{
		if (p_student_manager->student_list[i].id == id)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

int find_by_name(const StudentManager *p_student_manager, char *name)
{
	assert(p_student_manager != NULL);
	int pos = -1;
	for (int i = 0; i < p_student_manager->current_count; i++)
	{
		if (strcmp(p_student_manager->student_list[i].name, name) == 0)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

void find_student(const StudentManager *p_student_manager)
{
	assert(p_student_manager != NULL);
	int id;
	char name[10];
	int select = 0;
	int pos = -1;
	do
	{
		printf("**********\n");
		printf("1. 按学号查询\n");
		printf("2. 按姓名查询\n");
		printf("0. 退出查询\n");
		printf("请选择功能: \n");
		printf("**********\n");
		scanf("%d", &select);
		switch (select)
		{
			case 0:
				printf("退出查询\n");
				break;
			case 1:
                printf("请输入学号:\n");
				scanf("%d", &id);
				if ((pos = find_by_id(p_student_manager, id)) != -1)
				{
                    show_student_by_pos(p_student_manager, pos);
				}
				else
				{
					printf("无该学生信息！");
				}
				break;
			case 2:
                printf("请输入姓名:\n");
				scanf("%s", name);
				if ((pos = find_by_name(p_student_manager, name)) != -1)
				{
					show_student_by_pos(p_student_manager, pos);
				}
				else
				{
					printf("无该学生信息！");
				}
				break;
            default:
                break;
		}
	} while (select != 0);
}

void delete_student_by_pos(StudentManager *p_student_manager, int pos)
{
    assert(p_student_manager != NULL);
    for (int i = pos; i < p_student_manager->current_count - 1; i++)
    {
        p_student_manager->student_list[i] = p_student_manager->student_list[i + 1];
    }
    p_student_manager->current_count--;
    printf("删除成功！\n");
    show_student(p_student_manager);
}

void delete_student(StudentManager *p_student_manager)
{
    assert(p_student_manager != NULL);
    int id;
    char name[10];
    int select = 0;
    int pos = -1;
    do
    {
        printf("**********\n");
        printf("1. 按学号删除\n");
        printf("2. 按姓名删除\n");
        printf("0. 退出删除\n");
        printf("请选择功能: \n");
        printf("**********\n");
        scanf("%d", &select);
        switch (select)
        {
            case 0:
                printf("退出查询\n");
                break;
            case 1:
                printf("请输入学号:\n");
                scanf("%d", &id);
                if ((pos = find_by_id(p_student_manager, id)) != -1)
                {
                    delete_student_by_pos(p_student_manager, pos);
                }
                else
                {
                    printf("无该学生信息！");
                }
                break;
            case 2:
                printf("请输入姓名:\n");
                scanf("%s", name);
                if ((pos = find_by_name(p_student_manager, name)) != -1)
                {
                    delete_student_by_pos(p_student_manager, pos);
                }
                else
                {
                    printf("无该学生信息！");
                }
                break;
            default:
                break;
        }
    } while (select != 0);
}

void modify_student(StudentManager *p_student_manager) // 去掉const
{
    assert(p_student_manager != NULL);
    char is_continue = 'n';
    do
    {
        printf("请输入要修改学生编号:\n");
        int id;
        scanf("%d", &id);
        int pos = find_by_id(p_student_manager, id);

        if(pos != -1)
        {
            // 指针，直接改原数据
            Student *p_student = &p_student_manager->student_list[pos];
            int select = 0;

            printf("**********\n");
            printf("1.修改姓名 2.修改性别 3.修改年龄 4.修改所有成绩 5.修改单科成绩 0.退出\n");
            scanf("%d", &select);

            switch(select)
            {
                case 1:
                    printf("输入姓名:\n");
                    scanf("%s", p_student->name);
                    break;
                case 2:
                    printf("输入性别(male/female):\n");
                    scanf("%s", p_student->sex);
                    while (strcmp(p_student->sex, "male") != 0 && strcmp(p_student->sex, "female") != 0)
                    {
                        printf("性别输入错误！请重新输入:\n");
                        scanf("%s", p_student->sex);
                    }
                    break;
                case 3:
                    printf("输入年龄:\n");
                    scanf("%d", &p_student->age);
                    while (p_student->age < 0 || p_student->age > 50)
                    {
                        printf("年龄输入错误！请重新输入:\n");
                        scanf("%d", &p_student->age);
                    }
                    break;
                case 4:
                    p_student->total_score = 0; // 清零！
                    for(int i=0;i<SCORE_SIZE;i++)
                    {
                        printf("科目%d分数:\n",i+1);
                        scanf("%f",&p_student->scores[i]);
                        p_student->total_score += p_student->scores[i];
                    }
                    p_student->avg_score = p_student->total_score / SCORE_SIZE;
                    break;
                case 5:
                    {
                        is_continue = 'n';
                        do {
                            // 显示科目菜单
                            printf("1.修改语文成绩 2.修改数学成绩 3.修改英语成绩 0.退出\n");
                            int select_sub;
                            scanf("%d", &select_sub);

                            if(select_sub <1 || select_sub>3)
                            {
                                printf("科目输入错误！\n");
                            }
                            else
                            {
                                float input_score;
                                printf("请输入新成绩：");
                                scanf("%f", &input_score);

                                // 计算总分
                                p_student->total_score -= p_student->scores[select_sub-1];
                                p_student->scores[select_sub-1] = input_score;
                                p_student->total_score += input_score;
                                p_student->avg_score = p_student->total_score / SCORE_SIZE;
                                printf("修改成功！\n");
                            }

                            // 清空缓冲区（必须加）
                            while(getchar()!='\n');

                            // 输入 Y/y 继续修改单科
                            printf("是否继续修改单科成绩？(Y/N)：");
                            scanf("%c", &is_continue);

                        } while(is_continue == 'Y' || is_continue == 'y'); // Y/y 才继续

                        printf("退出单科修改~\n");
                        break;
                    }
                default:
                    break;
            }
            show_student_by_pos(p_student_manager, pos);
            // 清空缓冲区，解决无法输入Y/N
            while(getchar()!='\n');
            printf("是否继续修改?(Y/N):\n");
            scanf("%c",&is_continue);
        }
        else
        {
            printf("无该学生信息！\n");
            is_continue = 'n';
        }
    } while(is_continue == 'Y' || is_continue == 'y');
}

void show_student_manager_info(const StudentManager *p_student_manager)
{
	if(p_student_manager == NULL)
	{
		return;
	}
	printf("当前学生数量 %d,数组容量大小 %d\n", p_student_manager->current_count, p_student_manager->max_capacity);
}

void start_student_manager()
{
	// 解决eclipse无法使用scanf()从控制台接收参数的问题
	setbuf(stdout, NULL);

	StudentManager student_manager;
	init_student_manager(&student_manager);
	load_student_from_file(&student_manager);
	int select = 0;
	do
	{
		printf("**********\n");
		printf("1. 增加学生\n");
		printf("2. 展示学生\n");
		printf("3. 查询学生\n");
		printf("4. 删除学生\n");
		printf("5. 修改学生\n");
		printf("6. 系统信息\n");
		printf("0. 退出系统\n");
		printf("请选择功能: \n");
		printf("**********\n");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			printf("退出管理系统\n");
			break;
		case 1:
			add_student(&student_manager);
			break;
		case 2:
			show_student(&student_manager);
			break;
		case 3:
			find_student(&student_manager);
			break;
		case 4:
			delete_student(&student_manager);
			break;
		case 5:
			modify_student(&student_manager);
			break;
		case 6:
			show_student_manager_info(&student_manager);
			break;
		default:
			printf("不支持该选项！");
			break;
		}
	} while (select != 0);
	write_student_to_file(&student_manager);
}
