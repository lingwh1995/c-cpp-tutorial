# include <stdio.h>
# include <stdbool.h>

/**
 * 2022年版
 */
void print_calendar(int year);

#if 0
#endif
int main()
{
    //输入年份
    int year = 2025;
    print_calendar(year);
}

/**
 * 判断是否为闰年
 * @param year
 * @return
 */
bool is_leap_year_(int year)
{
    bool leap = false;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        leap = true;
    }
    return leap;
}


/**
 * 判断某个月有多少天,闰年 2月29天,平年2月28天
 * @return
 */
int get_days(int year, int month)
{
    int days = 0;
    switch (month)
    {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days = 31;
			break;
		case 2:
			days = is_leap_year_(year) ? 29 : 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
		default:
			break;
    }
    return days;
}


/**
 * 蔡勒公式: 根据年月日求具体的某一天是星期几
 * @param year 年
 * @param month 月
 * @param day 日
 * @return
 */
int get_day_of_week(int year, int month, int day)
{
    int c, y, week;
    //判断month是否为1或2　
    if (month == 1 || month == 2)
    {
        year--;
        month += 12;
    }

    c = year / 100;
    y = year - c * 100;
    week = (c / 4) - 2 * c + (y + y / 4) + (13 * (month + 1) / 5) + day - 1;

    while (week < 0)
    {
        week += 7;
    }
    week %= 7;
    return week;
}


/**
 * 打印某一个月的日历
 * @param day 这个月总共有多少天
 * @param wk  这个月的第1天是星期几
 */
void print_calendar(int year)
{
    //当前年份
    for (int i = 1; i <= 12; i++)
    {
        //根据年份和月份获取该月有多少天
        int days = get_days(year, i);
        //求当前月第一天是星期几
        int day_of_week = get_day_of_week(year, i, 1);
        int k = 0;
        printf("  年份:%d     月份:%d\n", year, i);
        printf("  ---------------------------\n");
        printf("   7   1   2   3   4   5   6\n");
        printf("  ---------------------------\n");
        char str[] = { "    " };
        for (int j = 0; j < day_of_week; j++)
        {
            printf("%s", str);
            k = k + 1;
        }
        for (int l = 1; l <= days; l++)
        {
            printf("%4d", l);
            k = k + 1;
            if (k % 7 == 0)
            {
                printf("\n");
            }
        }
        printf("\n\n");
    }
}

