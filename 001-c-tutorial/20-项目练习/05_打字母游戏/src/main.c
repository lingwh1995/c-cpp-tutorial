#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#if 0
/**
 * 打字母游戏第一版
 * 		随机产生一个字母从屏幕上方向下落，玩家输入字母，如果和显示的字母相同，就消去字母，游戏会再随机产生一个字母，继续游戏，如果字母落出屏幕，玩家失败，游戏结束。
 *
 * 注意事项
 *		在sublime中运行此测试程序，eclipse控制台中无法正确的展示此程序运行效果
 */

#define ROWSIZE 20 	   // 行数
#define COLSIZE 70 	   // 列数
#define LETSIZE 1  	   // 下落的字母数
#define GRDI_CHAR '.'  // 棋盘填充字符
#define SPEED 2000     // 下落速度

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
void show_grid(grid_array_t ga, struct letter_s *pl, int n)
{
	if(NULL == pl)
	{
		return;
	}
	system("cls");
	init_grid(ga);
	for(int i = 0; i < n; i++)
	{
		ga[pl[i].row][pl[i].col] = pl[i].ch;
	}
	for(int i = 0; i < ROWSIZE; i++)
	{
		printf("%s \n", ga[i]);
	}
}

/**
 * 产生随机字符
 */
void rand_letter(struct Letter* pl, int n)
{
	if(NULL == pl)
	{
		return;
	}
	srand(time(NULL));
	for(int i = 0; i < n; i++)
	{
		pl[i].ch = rand() % 26 + 'a';
		pl[i].row = 0;
		pl[i].col = rand() % COLSIZE;
	}
}

int main()
{
	grid_array_t ga;
	char ch;
	struct letter_s letter[LETSIZE] = { 0 };

	rand_letter(letter, LETSIZE);

	while(1)
	{
		show_grid(ga, letter, LETSIZE);
		// _kbhit() 判断键盘是否有输入，有输入，返回真
		if(_kbhit())
		{
			//ch = getchar(); // 需要等待输入 \n ，才能获取到输入缓冲区中的内容
			ch = _getch(); // 无需等待输入 \n ，直接就可以获取到输入缓冲区中的内容
			if(ch == letter[0].ch)
			{
				letter[0].ch = rand() % 26 + 'a';
				letter[0].row = -1;
				letter[0].col = rand() % COLSIZE;
			}
		}
		if(letter[0].row >= ROWSIZE)
		{
			printf("游戏结束\n");
		}
		letter[0].row++;
		Sleep(SPEED);
	}
	return 0;
}
#endif
