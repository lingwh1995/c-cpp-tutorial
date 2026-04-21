#include <stdio.h>

/**
 * goto最有价值应用场景(最佳应用场景):
 *  从最内层循环跳转到最外层循环,即一次性跳转到多层循环最外层
 */

 /**
  * goto测试
  *      
  */
void goto_test()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (k == 5)
                {
                    printf("k = %d\n", k);
                    goto jump;
                }
            }
        }
    }
jump:
    printf("I am jump!");
}

int main()
{
    goto_test();
    return 0;
}
