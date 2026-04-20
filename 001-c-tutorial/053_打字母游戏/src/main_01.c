#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#if 0
/**
 * 打字母游戏第二版
 * 		随机产生十个字母从屏幕上方向下落，玩家输入字母，如果和显示的字母相同，就消去字母，游戏会再随机产生一个字母（小写字母/小写字母和大写字母），使屏幕中的字母个数保持十个，继续游戏，如果有一个字母落出屏幕，玩家失败，游戏结束。
 *
 * 注意事项
 *		在sublime中运行此测试程序，eclipse控制台中无法正确的展示此程序运行效果
 */

#define ROWSIZE 20 	   // 行数
#define COLSIZE 70 	   // 列数
#define LETSIZE 10     // 下落的字母数
#define GRDI_CHAR '.'  // 棋盘填充字符
#define SPEED 2000 	   // 下落速度

/**
 * 定义字母结构体
 */
struct letter_s
{
	char ch;
	int row;
	int col;
};

typedef char grid_array_t[ROWSIZE][COLSIZE+1];

/**
 * 初始化网格
 */
void init_grid(grid_array_t ga)
{
	for(int i = 0; i < ROWSIZE; i++)
	{
		memset(ga[i], GRDI_CHAR, sizeof(char) * COLSIZE);
		ga[i][COLSIZE] = '\0';
	}
}

/**
 * 打印网格
 */
void show_grid(grid_array_t ga, struct letter_s *pla, int n)
{
	if(NULL == pla)
	{
		return;
	}
	system("cls");
	init_grid(ga);
	for(int i = 0; i < n; i++)
	{
		ga[pla[i].row][pla[i].col] = pla[i].ch;
	}
	for(int i = 0; i < ROWSIZE; i++)
	{
		printf("%s \n", ga[i]);
	}
}

/**
 * 产生随机字符
 */
void rand_letter(struct letter_s *pl)
{
	if(NULL == pl)
	{
		return;
	}
	if(rand() % 2 == 0)
	{
		pl->ch = rand() % 26 + 'a';
	}
	else
	{
		pl->ch = rand() % 26 + 'A';
	}
	pl->row = 0;

    // 特别注意： 可能会出现 col 值重复的情况
	pl->col = rand() % COLSIZE;
}

/**
 * 产生随机字符
 */
void rand_letters(struct letter_s *pla, int n)
{
	if(NULL == pla)
	{
		return;
	}
	int col_table[COLSIZE] = { 0 };
	srand(time(NULL));
	int i = 0;
	while(i < n)
	{
        // 随机生成小写字母
        //letter[i].ch = rand() % 26 + 'a';

        // 随机生成小写或大写字母
		rand_letter(&pla[i]);
		// 查表法去重
		if(col_table[pla[i].col] == 0)
		{
			col_table[pla[i].col] = 1;
			i++;
		}
	}
}

int main()
{
	grid_array_t ga;
	char ch;
	struct letter_s letter_arr[LETSIZE] = { 0 };

	rand_letters(letter_arr, LETSIZE);

	while(1)
	{
		show_grid(ga, letter_arr, LETSIZE);
		// _kbhit() 判断键盘是否有输入，有输入，返回真
		if(_kbhit())
		{
			//ch = getchar(); // 需要等待输入 \n，才能获取到输入缓冲区中的内容
			ch = _getch(); // 无需等待输入 \n，直接就可以获取到输入缓冲区中的内容
			printf("当前输入的字符： %c\n", ch);
			for(int i = 0; i < LETSIZE; i++)
			{
				if(ch == letter_arr[i].ch)
				{
				    // 随机生成小写字母
					//letter[i].ch = rand() % 26 + 'a';
					// 随机生成小写或大写字母
					rand_letter(&letter_arr[i]);
					letter_arr[i].row = -1;
					break;
				}
			}
		}
		for(int i = 0; i < LETSIZE; i++)
		{
			letter_arr[i].row++;
			if(letter_arr[i].row >= ROWSIZE)
			{
				printf("游戏结束\n");
				return 0;
			}
		}
		Sleep(SPEED);
	}
	return 0;
}
#endif
