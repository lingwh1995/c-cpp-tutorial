#include <stdbool.h>

/**
 * 使用查表法优化获取每月天数 + 使用查表法优化获取本年第一天到本月的前一月的最后一天总天数
 */


//引入枚举提高程序健壮性，好处是可以在getDays()方法之外做输入数据有误的处理逻辑，而不是直接在getDays()方法中做输入数据有误的处理逻辑
//这是一种很有用的编程思维，也可以使用宏定义来实现类似于枚举的作用，可以实现更好的分离代码逻辑和异常处理逻辑
enum
{
    YEAR_ERROR = -1,
	MONTH_ERROR = -2,
    DAY_ERROR = -3
};

/**
 * 判断当前年份是否是闰年(闰年全年366天，2月29天，平年全年365天，2月28天)
 * @param year 当前年份
 */
bool is_leap_year_(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
  * 返回每个月有多少天
  *     一维数组最佳应用场景: 查表法获取指定索引元素
  * 直接使用数组来获取每个月的天数,比使用switch-case要快很多
  * @param year
  * @param month
  */
int get_days_by_year_and_month_(int year, int month)
{
    // 被static修饰的变量会存放在数据区(.data)，从索引1开始存放一月数据而不是从索引0开始存放一月数据体现了灵活编程思想
    static const int days[] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // 短路与的细节用法，只有月份是2月的时候才需要判断是否是闰年
    if (month == 2 && is_leap_year_(year))
    {
        month = 0;
    }
    return days[month];
}

/**
 * 输入年份、月份和日期，获取从第一天到这个日期总共有多少天
 * @param year
 * @param month
 * @param day
 * @return
 */
int get_days_(int year, int month, int day)
{
	// 返回-1代表输入的年份不合理
	if(year < 1)
	{
		return YEAR_ERROR;
	}
    // 返回-1代表输入的月份不合理
    if (month < 1 || month > 12)
    {
        return MONTH_ERROR;
    }
    // 返回-2代表输入的天数不合理
    if (day < 1 || day > get_days_by_year_and_month_(year,month))
    {
        return DAY_ERROR;
    }
    int total_days = 0;
    // 被static修饰的变量会存放在数据区(.data)，从索引1开始存放一月数据而不是从索引0开始存放一月数据体现了灵活编程思想
    static const int days[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
    // 短路与的细节用法，只有月份是2月的时候才需要判断是否是闰年
    return total_days = (month > 2 && is_leap_year_(year) ? 1 : 0) +  days[month-1] + day;
}

#if 0
int main()
{
    // 获取从第一天到这个日期总共有多少天
	// 测试闰年
    int days = get_days_(2000, 3, 1);
    // 测试非闰年
    //int days = get_days_(2001, 3, 1);
    switch (days)
    {
    case -1:
        printf("输入的年份有误!\n");
        break;
    case -2:
        printf("输入的月份有误!\n");
        break;
    case -3:
        printf("输入的日期有误!\n");
        break;
    default:
        printf("总天数: %d\n", days);
        break;
    }
}
#endif
