#include <stdio.h>
#include <windows.h>

/**
 * windows库函数（用于操作和管理windows操作系统的各个方面，是c语言中调用windows操作系统api的主要入口）
 * 	1.提供windows api支持
 * 	2.定义windows平台特有的数据类型
 * 	3.包含windows消息和事件处理机制
 * 	4.支持图形用户界面(GUI)开发
 * 	5.提供多线程支持
 * 	6.包含对文件、输入输出和系统服务的操作
 */

/**
 * Sleep()函数测试，参数单位为毫秒
 * 	注意：在sublime中运行此测试方法，eclipse控制台中无法正确的展示此方法运行效果
 */
void sleep_test()
{
	for(int i = 0; i < 5; i++)
	{
		printf("%s\n", "i am stdlib.h");
		Sleep(1000);
	}
}

int main()
{
	sleep_test();
	return 0;
}
