#include <stdio.h>

int main()
{
    int a = 10;
    int b = 20;
    int *pa = &a;
    int *pb = &b;

    /**
     * 开口向上: b的地址 > a的地址,a放在下面,b 放在上面 ;
     * 开头向下: b的地址 < a的地址,a放在上面,b 放在下面 ;
     */
    // 打印 变量 a , b 的地址
    printf("pa = %p , bp = %p\n", pa, pb);
    if(pa > pb)
    {
    	printf("栈的开口方向向下\n");
    }
    else
    {
    	printf("栈的开口方向向上\n");
    }
    return 0;
}
