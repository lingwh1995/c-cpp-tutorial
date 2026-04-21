# include <stdio.h>

/**
 * 枚举类型：
 *    1. 枚举类型是受到限制的有符号整型数据类型(unsigned int)
 *    2. 枚举元素(枚举常量)必须是有符号整型数据
 *    3. 枚举类型定义的变量，取值范围必须是枚举集合中的枚举元素的值
 *    4. 不指定枚举元素值时，默认从0开始，往后逐个+1
 *    5. 枚举类型定义的数据都是常量
 *
 * 枚举用法：
 * 	  用来替换多个有关联的宏定义，之前需要定义多个宏，现在把这几个宏放到一个枚举中
 */

// 使用宏定义定义
#define OK 0
#define NETWORK_ERROR 1
#define PTR_ERROR 2

// 使用枚举替代宏定义
enum Status
{
	STATUS_OK,
	STATUS_NETWORK_ERROR,
	STATUS_PTR_ERROR,
};

int main()
{
    /**
     * 枚举常量(枚举也是一种常量)
     *  注意:枚举常量的值只能是整形数据
     */
    enum Sex
    {
        SEX_MALE,   // 男性
		SEX_FEMALE, // 女性
		SEX_SECRET  // 保密
    };
    printf("MALE = %d\n", SEX_MALE);
    printf("FEMALE = %d\n", SEX_FEMALE);
    printf("SECRET = %d\n", SEX_SECRET);
    printf("-------------------------------------\n");

    enum Week
    {
        WEEK_MON = 1,
		WEEK_TUE = 2,
		WEEK_WED = 3
    };
    enum Week wk;
    wk = WEEK_MON;
    printf("wk = %d\n", wk);
    wk = WEEK_TUE;
    printf("wk = %d\n", wk);
    printf("-------------------------------------\n");

    enum Animal
    {
        ANIMAL_DOG = 5,
		ANIMAL_CAT,
		ANIMAL_SHEEP
    };
    printf("DOG = %d\n", ANIMAL_DOG);
    printf("CAT = %d\n", ANIMAL_CAT);
    printf("SHEEP = %d\n", ANIMAL_SHEEP);
    printf("-------------------------------------\n");
    return 0;
}
