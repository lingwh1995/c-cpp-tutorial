#include <stdio.h>

#define ROWS 3
#define COLS 5

#if 0
int main()
{
	// 定义二维数组
	int arr[ROWS][COLS] = {
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 3, 0, 0 },
		{ 0, 0, 0, 0, 5 }
	};

	// 遍历二维数组
	printf("原始二维数组：\n");
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			printf("%d  ", arr[i][j]);
		}
		printf("\n");
	}

	// 定义稀疏二维数组， 特别注意：下面写法没有问题 1.二维数组定义时第一维可以省略 2.可以使用定义一维数组右值的方法定义二维数组右值
	int sparse_arr[][3] = { 0 };
	int sparse_arr_row_index = 0;
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			if(arr[i][j] != 0)
			{
				sparse_arr[sparse_arr_row_index][0] = i;
				sparse_arr[sparse_arr_row_index][1] = j;
				sparse_arr[sparse_arr_row_index][2] = arr[i][j];
				sparse_arr_row_index++;
			}
		}
	}

	// 打印稀疏二维数组
	printf("稀疏二维数组：\n");
	for(int i = 0; i < sparse_arr_row_index; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			printf("%d  ", sparse_arr[i][j]);
		}
		printf("\n");
	}

	// 通过稀疏二维数组还原原始二维数组
	int arr_from_sparse_arr[ROWS][COLS] = { 0 };

	// 还原二维数组
	for(int i = 0; i < sparse_arr_row_index; i++)
	{
		int row_index = sparse_arr[i][0];
		int col_index = sparse_arr[i][1];
		int value = sparse_arr[i][2];
		arr_from_sparse_arr[row_index][col_index] = value;
	}

	// 遍历还原后的二维数组
	printf("还原后的二维数组：\n");
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			printf("%d  ", arr_from_sparse_arr[i][j]);
		}
		printf("\n");
	}

	// 定义转置二维数组（行数变列数，列数变行数）
	int trans_arr[COLS][ROWS] = { 0 };
	for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			trans_arr[i][j] = arr_from_sparse_arr[j][i];
		}
	}

	// 遍历转置后的二维数组
	printf("转置后的二维数组：\n");
	for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			printf("%d  ", trans_arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
#endif
