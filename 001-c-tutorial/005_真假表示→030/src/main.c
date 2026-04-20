#include <stdio.h>
#include <stdbool.h>


/**
 * 判断真假
 *
 * 1. C语言中0代表假，非0代表真，如1就代表真
 * 2. C语言中 '\0' 的ASCII码是 0，所以 '\0' 代表假
 */
void judge_true_or_false(int i)
{
	if(i)
	{
		printf("i = %d 代表 真\n",i);
	}
	else
	{
		printf("i = %d 代表 假\n",i);
	}
}


/**
 * C99中提供的Bool类型
 */ 
void c99_bool()
{
	bool b = true;
	printf("true = %d 代表 真\n",b);
	b = false;
	printf("false = %d 代表 假\n",b);
}

int main()
{
	int i = 0;
	judge_true_or_false(i);
	i = 1;
	judge_true_or_false(i);
	i = -1;
	judge_true_or_false(i);
    i = '\0';
    judge_true_or_false(i);
	c99_bool();
}
