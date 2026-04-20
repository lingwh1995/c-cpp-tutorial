#include <stdio.h>
#include <time.h>

int main()
{
	// 获取当前时间
	time_t current_time;
	time(&current_time);
	printf("Current time: %s", ctime(&current_time));

	// 格式化时间
	struct tm *time_info_t;
	char buffer[80];
	time_info_t = localtime(&current_time);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info_t);
	printf("Formatted time: %s\n", buffer);

	// 计算时间差
	time_t start_time, end_time;
	double time_diff;
	time(&start_time);
	// 模拟耗时操作
	for (int i = 0; i < 100000000; i++);
	time(&end_time);
	time_diff = difftime(end_time, start_time);
	printf("Time difference: %.2f seconds\n", time_diff);
	return 0;
}
