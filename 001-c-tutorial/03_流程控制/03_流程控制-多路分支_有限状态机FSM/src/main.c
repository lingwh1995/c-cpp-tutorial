#include <stdio.h>
#include <ctype.h>

/**
 * 章节内容:
 *      多分支switch-case实现有限状态机，又称有限状态自动机，简称状态机(Finite state machine)
 *      需求:
 *          统计 字符串 {" hello    c   lang  nice   "} 中单词的个数
 *
 */


// 使用宏定义定义状态码	- 不推荐
/*
#define BEGIN 0
#define IN_WORD 1
#define OUT_WORD 2
#define END 3
*/

// 使用枚举定义状态码 - 推荐
enum state
{
    BEGIN,
    IN_WORD,
    OUT_WORD,
    END
};

int main()
{
	char str[] = " one  two   three    four     five ";
    // 用来记录单词的数量
    int word_count = 0;
    int state = BEGIN;
    for(int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        switch(state)
        {
            case BEGIN:
                if(isalpha(c))
                {
                    state = IN_WORD;  
                }
                else
                {
                    state = OUT_WORD;  
                }
                break;
            case IN_WORD:
                if(!isalpha(c))
                {
                    word_count++;
                    state = OUT_WORD; 
                }
                break;  
            case OUT_WORD:
                if(isalpha(c))
                {
                  state = IN_WORD;
                }
                break;            
        }
    }
    if(state == IN_WORD)
    {
        word_count++;
    }
    state = END;
    printf("单词个数：%d\n", word_count);
    printf("状态机状态：%d\n", state);
    return 0;
}
