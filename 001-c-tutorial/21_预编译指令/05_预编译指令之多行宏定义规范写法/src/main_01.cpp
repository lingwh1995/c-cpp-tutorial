// C++中的auto交换宏（利用auto类型推导）
#define SWAP_AUTO(a, b)  { auto tmp = (a); (a) = (b); (b) = tmp; }

// 使用示例
#include <iostream>
using namespace std;

#if 0
int main()
{
    // 整数交换
    int a = 10, b = 20;
    SWAP_AUTO(a, b);
    cout << "a = " << a << ", b = " << b << endl;  // a = 20, b = 10

    // 浮点数交换
    double x = 10.5, y = 20.8;
    SWAP_AUTO(x, y);
    cout << "x = " << x << ", y = " << y << endl;  // x = 20.8, y = 10.5

    return 0;
}
#endif