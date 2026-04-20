#include <stdio.h>
#include <stdbool.h>

/**
 * 2025年版
 */
void print_calendar_monday_to_sunday(int year);
void print_calendar_sunday_to_saturday(int year);


#if 0
int main()
{
    int year = 2025;
    //print_calendar_monday_to_sunday(year);
    print_calendar_sunday_to_saturday(year);
    return 0;
}
#endif

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
 * 判断当前年当前月第一天是周几，已知1900年1月1日是周一
 * @param year 当前年份
 * @param month 当前月份
 */ 
int get_first_day_of_current_month_of_week(int year, int month)
{
    int y, days = 0, m;
    // 计算1900到当前年一共经过了多少天
    for(y=1900; y<year; y++)
    {
        if(is_leap_year(y))
        {
            days += 366;
        }
        else
        {
            days += 365;
        }
    }
    // 计算当前年1月1日到当前年指定月的上一个月的最后一天一共经过了多少天
    for(m=1; m<month; m++)
    {
        days += get_current_month_days(year, m);
    }
    // 计算当前年当前月的上一个月的最后一天是周几
    return days % 7;
}

/**
 * 打印日历 周一到周日版
 * @param year 当前年份
 */ 
void print_calendar_monday_to_sunday(int year)
{
    printf("  年份：%d年\n", year);
    printf("  --------------------------\n\n");
    int m, dow, d;
    for(m=1; m<=12; m++)
    {
        // 1.计算当前年份每个月有多少天
        int days = get_current_month_days(year, m);
        printf("  月份：%2d月，本月天数：%d\n", m, days);
        printf("  --------------------------\n");
        printf("%4d%4d%4d%4d%4d%4d%4d\n", 1, 2, 3, 4, 5, 6, 7);
        printf("  --------------------------\n");
        const char blank[] = { "    " };
        // 2.计算当前月第一天是星期几
        int day_of_week = get_first_day_of_current_month_of_week(year,m) + 1;
        for(dow=1; dow<day_of_week; dow++)
        {
            printf("%s", blank);
        }
        for(d=1; d<=days; d++)
        {
            printf("%4d", d);
            if(day_of_week%7 == 0)
            {
              printf("\n");
            }
            day_of_week++;
        }
        // 格式化日历换行
        if((day_of_week-1)%7 == 0)
        {
            printf("\n");
        }
        else
        {
            printf("\n\n");
        }
    }
}

/**
 * 打印日历 周日到周六版
 * @param year 当前年份
 */
void print_calendar_sunday_to_saturday(int year)
{
    printf("  年份：%d年\n", year);
    printf("  --------------------------\n\n");
    int m, dow, d;
    for(m=1; m<=12; m++)
    {
        // 1.计算当前年份每个月有多少天
        int days = get_current_month_days(year, m);
        printf("  月份：%2d月，本月天数：%d\n", m, days);
        printf("  --------------------------\n");
        printf("%4d%4d%4d%4d%4d%4d%4d\n", 7, 1, 2, 3, 4, 5, 6);
        printf("  --------------------------\n");
        const char blank[] = { "    " };
        // 2.计算当前月第一天是星期几
        int day_of_week = get_first_day_of_current_month_of_week(year,m) + 1;
        for(dow=1; dow<=day_of_week; dow++)
        {
            if(day_of_week == 7)
            {
                break;
            }
            printf("%s", blank);
        }
        for(d=1; d<=days; d++)
        {
        	day_of_week++;
            printf("%4d", d);
            if(day_of_week%7 == 0)
            {
              printf("\n");
            }
        }
        // 格式化日历换行
        if((day_of_week-1)%7 == 0)
        {
            printf("\n");
        }
        else
        {
            printf("\n\n");
        }
    }
}
