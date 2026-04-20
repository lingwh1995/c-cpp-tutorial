# include <stdio.h>
# include <ctype.h>

/**
 *  ctype.h常用方法
 *  isalnum()		检查字符是否是字母或数字
 *  isalpha()		检查字符是否是字母
 *  islower()       检查字符是否是小写字母
 *  isupper()       检查字符是否是大写字母
 *  isdigit()       检查字符是否是数字
 *  isxdigit()      检查字符是否是十六进制字符
 *  iscntrl()       检查字符是否是控制字符
 *  isgraph()       检查字符是否是图形字符
 *  isspace()       检查字符是否是空白字符
 *  isblank()       检查字符是否是空格字符
 *  isprint()       检查字符是否是可打印字符
 *  ispunct()       检查字符是否是标点字符
 *  tolower()       将字符转换成小写
 *  toupper()       将字符转换成大写
 */

 /**
  * 自己实现判断逻辑
  */
void judge_character_type_test_1()
{
    printf("请输入一个字符:\n");
    char c = getchar();
    if (c < 32)
    {
        printf("this is a control char\n");
    }
    else if (c > '0' && c < '9')
    {
        printf("this is a number\n");
    }
    else if (c > 'a' && c < 'z')
    {
        printf("this is a lower case\n");
    }
    else if (c > 'A' && c < 'Z')
    {
        printf("this is a upper case\n");
    }
    else
    {
        printf("other char\n");
    }
}

/**
 * 调用ctype.h实现判断逻辑
 */
void judge_character_type_test_2()
{
    printf("请输入一个字符:\n");
    char c = getchar();
    if (iscntrl(c))
    {
        printf("this is a control char\n");
    }
    else if (isdigit(c))
    {
        printf("this is a number\n");
    }
    else if (islower(c))
    {
        printf("this is a lower case\n");
    }
    else if (isupper(c))
    {
        printf("this is a upper case\n");
    }
    else
    {
        printf("other char\n");
    }
}
int main()
{
    //judge_character_type_test_1();
    judge_character_type_test_2();
    return 0;
}
