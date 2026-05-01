#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define N 20

/**
 * 题目列表
 * 001.循环打印 a-g 方式一：不使用取余运算
 * 002.循环打印 a-g 方式二：使用取余运算
 * 003.求最大公约数 方式一：暴力穷举
 * 004.求最大公约数 方式二：辗转相除法
 * 005.求最大公约数 方式三：更相减损术(辗转相减法)
 * 006.求最小公倍数 方式一：暴力穷举
 * 007.求最小公倍数 方式二：利用最大公约数
 * 008.求最小公倍数 方式三：最小i值法
 * 009.输入三个整型数据，求最小值
 * 010.输入三个整型数据，求中间值
 * 011.输入三个整型数据，求最大值
 * 012.统计字符串中一共有多少个单词
 * 013.小球从100米落下,每次落地后跳回原来的高度一半，再落下，求它在第10次落下时共经过多少米?反弹高度是多少?
 * 014.有一对兔子，从出生后第三个月起每个月都生一对兔子，小兔子长到第三个月后又生一对兔子，假如兔子都不死，问每个月有多少对兔子?（递归求解）
 * 015.有一对兔子，从出生后第三个月起每个月都生一对兔子，小兔子长到第三个月后又生一对兔子，假如兔子都不死，问每个月有多少对兔子?（非递归求解）
 * 016.牛顿迭代法求平方根，要求两次求出的平方根的差的绝对值小于0.00001
 * 017.如果一个数等于它的因子之和，则这个数称为完数 6 = 1 + 2 + 3，找出1000以内的所有完数
 * 018.如果一个数等于它的因子之和，则这个数称为完数 6 = 1 + 2 + 3，找出1000以内的所有完数和该完数的因数（方式一：不使用结构体版）
 * 019.如果一个数等于它的因子之和，则这个数称为完数 6 = 1 + 2 + 3，找出1000以内的所有完数和该完数的因数（方式二：使用结构体版）
 * 020.打印九九乘法表
 * 021.找出用户输入的一串数字中的最大数，程序需要提示用户一个一个的输入，当用户输入0或负数时，程序显示已经输入的最大非负数
 * 022.随机生成1-100之间的数字请人猜，如果是猜对了结束游戏，如果猜错则继续猜并提示所猜的数是大于还是小于所指定的数，最终提示猜对所用次数
 * 023.多次输入年月日，输出最早的年月日（方式一）
 * 024.多次输入年月日，输出最早的年月日（方式二）
 * 025.打印杨辉三角
 */

/**
 * 001.循环打印 a-g 方式一：不使用取余运算
 */
void question_001_loop_print_a2g()
{
	char str[] = "abcdefg";
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		int k = i;
		for(int j = 0; j < len; j++)
		{
			printf("%c", str[k]);
			k = k + 1;
			if(k == len)
			{
				k = 0;
			}
		}
		printf("\n");
	}
}

/**
 * 002.循环打印 a-g 方式二：使用取余运算
 */
void question_002_loop_print_a2g()
{
	char str[] = "abcdefg";
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		int k = i;
		for(int j = 0; j < len; j++)
		{
			printf("%c", str[k]);
			k = k + 1;
			k =  k % len;
		}
		printf("\n");
	}
}

/**
 * 003.求最大公约数 方式一：暴力穷举
 * 		a.找出a和b中最小的数，把这个数赋值给c
 * 		b.第一个满足 a%c==0 && b%c==0 的数就是a和b的最大公约数
 */
void question_003_gcd()
{
	int a, b;
	scanf("%d %d", &a, &b);
	int c = a<b ? a : b;
	while(c>1)
	{
		if(a % c == 0 && b % c==0)
		{
			break;
		}
		c--;
	}
	printf("最大公约数 = %d", c);
}

/**
 * 004.求最大公约数 方式二：辗转相除法
 * 		公式：gcd(a,b) = gcd(b, a mod b);
 * 		     gcd(48,18) = gcd(18, 12);
 * 	    	 gcd(18,12) = gcd(12, 6);
 * 	         gcd(12,6)  = gcd(6, 0);
 */
void question_004_gcd()
{
	int a, b, mod;
	scanf("%d %d", &a, &b);
	while(mod != 0)
	{
		mod = a % b;
		a = b;
		b = mod;
	}
	printf("最大公约数 = %d",a);
}

/**
 * 005.求最大公约数 方式三：更相减损术(辗转相减法)
 * 		公式：gcd(a, b) = gcd(b, a - b);
 * 		注意：a<b时，要先交换a、b两个数的位置再进行相减
 */
void question_005_gcd()
{
	int a, b, diff;
	scanf("%d %d", &a, &b);
	while(diff != 0)
	{
        if(a < b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
		diff = a - b;
		a = b;
		b = diff;
	}
	printf("最大公约数 = %d",a);
}

/**
 * 006.求最小公倍数 方式一：暴力穷举
 */
void question_006_lcm()
{
	int a, b, lcm;
	scanf("%d %d", &a, &b);
	lcm = a > b ? a : b;
	while(true)
	{
		if(lcm%a==0 && lcm%b==0)
		{
			break;
		}
		++lcm;
	}
	printf("最小公倍数 = %d", lcm);
}

/**
 * 007.求最小公倍数 方式二：利用最大公约数 int lcm = a*b / gcd(a,b)
 */

/**
 * 计算两个整数的最大公约数（Greatest Common Divisor）
 * 使用欧几里得算法（辗转相除法）实现
 *
 * @param a 第一个整数
 * @param b 第二个整数
 * @return 返回 a 和 b 的最大公约数
 */
int gcd(int a, int b)
{
	int mod;
	while(mod != 0)
	{
		mod = a % b;
		a = b;
		b = mod;
	}
	return a;
}
void question_007_lcm()
{
	int a, b, lcm;
	scanf("%d %d", &a, &b);
	lcm = a*b / gcd(a,b);
	printf("最小公倍数 = %d", lcm);
}

/**
 * 008.求最小公倍数 方式三：最小i值法
 */
void question_008_lcm()
{
	int a, b, lcm;
	scanf("%d %d", &a, &b);
	int i = 1;
	while(a*i % b != 0)
	{
		i++;
	}
	lcm = a * i;
	printf("最小公倍数 = %d", lcm);
}

/**
 * 009.输入三个整型数据，求最小值
 */ 
void question_009_get_min_value()
{
	printf("请输入三个整型数据，使用空格分隔:\n");
	int a, b, c, min;
	scanf("%d %d %d", &a, &b, &c);
	min = a < b ? a : b;
	min = min < c ? min : c;
	printf("min = %d\n", min);
}

/**
 * 010.输入三个整型数据，求中间值
 */ 
void question_010_get_mid_value()
{
	printf("请输入三个整型数据，使用空格分隔:\n");
	int a, b, c, min, mid, max;
	scanf("%d %d %d", &a, &b, &c);
	// 求出三个数里面最小值
	min = a < b ? a : b;
	min = min < c ? min : c;
	// 求出三个数里面最大值
	max = a > b ? a : b;
	max = max > c ? max : c;
	mid = a + b + c - min - max;
	printf("mid = %d\n", mid);
}

/**
 * 011.输入三个整型数据，求最大值
 */ 
void question_011_get_max_value()
{
	printf("请输入三个整型数据，使用空格分隔:\n");
	int a, b, c, max;
	scanf("%d %d %d", &a, &b, &c);
	max = a > b ? a : b;
	max = max > c ? max : c;
	printf("max = %d\n", max);
}

/**
 * 012.统计字符串中一共有多少个单词
 */ 
void question_012_count_word()
{
	char str[] = " one  two   three    four     five ";
    int j;
    int c = str[0] == ' ' ? 0 : 1;
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] != ' ')
        {
            if(j == 0)
            {
                c++;
            }
            j++;
        }
        else
        {
            j = 0;
        }
    }
    printf("单词个数 = %d\n", c);
}

/**
 * 013.小球从100米落下,每次落地后跳回原来的高度一半，再落下，求它在第10次落下时共经过多少米?反弹高度是多少?
 */
void question_013_ball_falls()
{
    //下落经过的总高度
    double sum_height = 100.00;
    //每一次的反弹高度
    double current_jump_height = sum_height / 2;
    for (int i = 2; i <= 10; i++)
    {
        sum_height = sum_height + current_jump_height * 2;
        current_jump_height = current_jump_height / 2;
    }
    printf("经过的总高度 sum_height = %f\n", sum_height);
    printf("第10次反弹高度 current_jump_height = %f\n", current_jump_height);
}

/**
 * 递归求解
 * 014.有一对兔子，从出生后第三个月起每个月都生一对兔子，小兔子长到第三个月后又生一对兔子，假如兔子都不死，问每个月有多少对兔子?
 * 月份     1       2       3       4       5       6       7       8
 * 对数     1       1       2       3       5       8       13      21
 */

/**
 * 计算第 m 个月的兔子总数（斐波那契数列）
 * 使用递归方式实现：每个月的兔子数等于前两个月兔子数之和
 *
 * @param m 月份数
 * @return 返回第 m 个月的兔子总数
 */
int rabbit_count(int m)
{
	if(m == 1 || m == 2)
	{
		return 1;
	}
	return rabbit_count(m-1) + rabbit_count(m-2);
}

void question_014_rabbit_count_recursion()
{
	int m = 8;
	int totalRabbit = rabbit_count(m);
	printf("第%d个月兔子总数 = %d\n", m, totalRabbit);
}

/**
 * 非递归求解
 * 015.有一对兔子，从出生后第三个月起每个月都生一对兔子，小兔子长到第三个月后又生一对兔子，假如兔子都不死，问每个月有多少对兔子?
 * 月份     1       2       3       4       5       6       7       8
 * 对数     1       1       2       3       5       8       13      21
 */
void question_015_rabbit_count_no_recursion()
{
    //c代表后续月份兔子个数
    int a = 1, b = 1, c = 1, m = 10;
    for (int i = 3; i <= m; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }
    printf("第%d个月的兔子对数 = %d\n", m, c);
}

/**
 * 016.牛顿迭代法求平方根，要求两次求出的平方根的差的绝对值小于0.00001
 */
void question_016_newton_raphson_method_sqrt()
{
	double d;
    printf("请输入一个浮点类型数据：\n");
    scanf("%lf", &d);
    printf("d = %lf\n", d);
	double x0 = d / 2;
	double x1 = (x0 + d/x0) / 2;
	while(fabs(x0-x1) > 0.00001)
	{
		x0 = x1;
		x1 = (x0 + d/x0) / 2;
	}
	printf("%f的平方根是 = %f\n", d, x1);
}

/**
 * 017.如果一个数等于它的因子之和，则这个数称为完数 6 = 1 + 2 + 3，找出1000以内的所有完数
 */
void question_017_perfect_number()
{
    int n = 1000;
    for (int i = 2; i <= n; i++)
    {
        int sum = 1;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                sum = sum + j;
            }
        }
        if (sum == i)
        {
            printf("%d\n", i);
        }
    }
}

/**
 * 018.如果一个数等于它的因子之和，则这个数称为完数 6 = 1 + 2 + 3，找出1000以内的所有完数和该完数的因数（方式一）
 */
void question_018_perfect_number_factor()
{
    int n = 1000;
    for (int i = 2; i <= n; i++)
    {
        int sum = 1;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                sum = sum + j;
            }
        }
        if (sum == i)
        {
            printf("%d => ", i);
            for (int x = 1; x <= i/2; x++)
            {
                if (i % x == 0)
                {
                    printf("%d ", x);
                }
            }
            printf("\n");
        }
    }
}

/**
 * 019.如果一个数等于它的因子之和，则这个数称为完数 6 = 1 + 2 + 3，找出1000以内的所有完数和该完数的因数（方式二）
 */
void question_019_perfect_number_factor()
{
    int n = 1000;
    for (int i = 2; i <= n; i++)
    {
        int sum = 1;
        int factor[30] = { 1 };
        int index = 1;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                sum = sum + j;
                factor[index++] = j;
            }
        }
        if (sum == i)
        {
            printf("%d => ", i);
            for (int x = 0; x < index; x++)
            {
            	printf("%d ", factor[x]);
            }
            printf("\n");
        }
    }
}

/**
 * 020.打印九九乘法表
 */
void question_020_multiplication_table()
{
	for(int i = 1; i <= 9; i++)
	{
		for(int j = 1; j <= i; j++)
		{
			printf("%d * %d =%3d\t", j, i, i*j);
		}
		printf("\n");
	}
}

/**
 * 021.找出用户输入的一串数字中的最大数，程序需要提示用户一个一个的输入，当用户输入0或负数时，程序显示已经输入的最大非负数
 */
void question_021_get_max_input_value()
{
    int input, max=0;
    while(input>0)
    {
        printf("请输入一个数字：\n");
        scanf("%d", &input);
        max = input > max ? input : max;
    }
    printf("max = %d\n", max);

}

/**
 * 022.随机生成1-100之间的数字请人猜，如果是猜对了结束游戏，如果猜错则继续猜并提示所猜的数是大于还是小于所指定的数，最终提示猜对所用次数
 */ 
void question_022_guess_number()
{
    srand((unsigned)time(NULL));
    int r = rand() % 10;
    printf("r = %d\n", r);
    printf("请输入:\n");
    int i = 0;
    int times = 0;
    while (1)
    {
        times++;
        scanf("%d", &i);
        if (i > r)
        {
            printf("你猜大了,当前输入值:%d\n", i);
        }
        else if (i < r)
        {
            printf("你猜小了,当前输入值:%d\n", i);
        }
        else
        {
            printf("你猜正确了,当前输入值:%d\n", i);
            break;
        }
    }
    printf("共猜了%d次才猜正确\n", times);
}

/**
 * 判断当前年份是否是闰年(闰年全年366天，2月29天，平年全年365天，2月28天)
 * @param year 当前年份
 */ 
bool is_leap_year(int year)
{
    return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

/**
 * 获取当前月份有多少天
 * @param year 当前年份
 * @param month 当前月份
 */ 
int get_current_month_days(int year, int month)
{
    int days = 31;
    switch(month)
    {
        case 2:
            days = is_leap_year(year) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
    }
    return days;
}

/**
 * 023.多次输入年月日，输出最早的年月日（方式一：不使用结构体版）
 */
void question_023_get_earliest_Input_date()
{
	int year = 1, month = 1, day = 1;
	int myear = INT_MAX, mmonth = 12, mday = 31;
	while(true)
	{
		bool flag = false;
		printf("输入年月日，格式yyyy/mm/dd：\n");
		scanf("%d/%d/%d", &year, &month, &day);
		// 判断输入的年月日是否合法
		if(year <=0 || month <=0 || day <=0)
		{
			break;
		}
		// 判断输入的月是否合法
		if(month < 1 || month > 12)
		{
			break;
		}
		// 判断输入的日是否合法
		if(day < 1 || day > get_current_month_days(year,month))
		{
			break;
		}
		if(year < myear)
		{
			flag = true;
		}
		else if(year == myear || month < mmonth)
		{
			flag = true;
		}
		else if(year == myear || month == mmonth || day < mday)
		{
			flag = true;
		}
		if(flag)
		{
			myear = year;
			mmonth = month;
			mday = day;
		}
	}
	printf("最早的是日期是：%d/%d/%d\n", myear, mmonth, mday);
}

/**
 * 024.多次输入年月日，输出最早的年月日（方式二：使用结构体版）
 */
void question_024_get_earliest_input_date()
{
	typedef struct
	{
		int year;
		int month;
		int day;
	} Date;
	Date input_val = { 1,1,1 };
	Date min = { INT_MAX,12,31 };
	while(true)
	{
		bool flag = false;
		printf("输入年月日，格式yyyy/mm/dd：\n");
		scanf("%d/%d/%d", &input_val.year, &input_val.month, &input_val.day);
		// 判断输入的年月日是否合法
		if(input_val.year <=0 || input_val.month <=0 || input_val.day <=0)
		{
			break;
		}
		// 判断输入的月是否合法
		if(input_val.month < 1 || input_val.month > 12)
		{
			break;
		}
		// 判断输入的日是否合法
		if(input_val.day < 1 || input_val.day > get_current_month_days(input_val.year,input_val.month))
		{
			break;
		}
		if(input_val.year < min.year)
		{
			flag = true;
		}
		else if(input_val.year == min.year || input_val.month < min.month)
		{
			flag = true;
		}
		else if(input_val.year == min.year || input_val.month == min.month || input_val.day < min.day)
		{
			flag = true;
		}
		if(flag)
		{
			min.year = input_val.year;
			min.month = input_val.month;
			min.day = input_val.day;
		}
	}
	printf("最早的是日期是：%d/%d/%d\n", min.year, min.month, min.day);
}



/**
 * 025.打印杨辉三角
 *
 * 1
 * 1	1
 * 1	2	1
 * 1	3	3	1
 * 1	4	6	4	1
 */
void question_025_pascals_triangle()
{
	int arr[N] = { 0 };
	for(int i = 0; i < N; i++)
	{
		printf("第 %2d 行:", i);
		for(int j = i; j >= 0; j--)
		{
			if(j == 0 || j == i)
			{
				arr[j] = 1;
				printf("%10d", arr[j]);
			}
			else
			{
				arr[j] = arr[j] + arr[j - 1];
				printf("%10d", arr[j]);
			}
		}
		printf("\n");
	}
}


int main()
{
	// 解决eclipse无法使用scanf()从控制台接收参数的问题
	//setbuf(stdout, NULL);

	// 测试执行效率，使用以下方法
	/*
	  long start, end;
	  start = time(NULL);
	  end = time(NULL);
	  printf("花费时间 = %ld s\n", (end - start));
	 */

	question_001_loop_print_a2g();
	//question_002_loop_print_a2g();
	//question_003_gcd();
	//question_004_gcd();
	//question_005_gcd();
	//question_006_lcm();
	//question_007_lcm();
	//question_008_lcm();
	//question_009_get_min_value();
	//question_010_get_mid_value();
	//question_011_get_max_value();
	//question_012_count_word();
	//question_013_ball_falls();
	//question_014_rabbit_count_recursion();
	//question_015_rabbit_count_no_recursion();
	//question_016_newton_raphson_method_sqrt();
	//question_017_perfect_number();
	//question_018_perfect_number_factor();
	//question_019_perfect_number_factor();
	//question_020_multiplication_table();
	//question_021_get_max_input_value();
    //question_022_guess_number();
    //question_023_get_earliest_Input_date();
	//question_024_get_earliest_input_date();
	//question_025_pascals_triangle();
	return 0;
}
