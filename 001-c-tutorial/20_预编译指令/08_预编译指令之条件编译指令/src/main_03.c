#include <stdio.h>

/**
 * 在条件编译指令中使用位运算
 */
// Linux 大类掩码：高4位为0000
#define LINUX          0x00
#define REDHAT         0x01    // Linux - RedHat
#define UBUNTU         0x02    // Linux - Ubuntu
#define OPENSUSE       0x03    // Linux - OpenSUSE

// Windows 大类掩码：高4位为1000
#define WINDOWS        0x80
#define WINXP          (WINDOWS + 0x01)
#define WIN7           (WINDOWS + 0x02)
#define WIN10          (WINDOWS + 0x03)
#define WIN11          (WINDOWS + 0x04)

// 示例：可改为 REDHAT / UBUNTU / OPENSUSE / WINXP / WIN7 / WIN10 / WIN11
#define OS      REDHAT

void get_os_name()
{
    // 先判断大类：Linux 还是 Windows
#if ((OS & 0xF0) == LINUX)
    printf("当前系统大类：Linux\n");
    // 细分Linux发行版
    #if OS == REDHAT
        printf("具体系统：RedHat\n");
    #elif OS == UBUNTU
        printf("具体系统：Ubuntu\n");
    #elif OS == OPENSUSE
        printf("具体系统：OpenSUSE\n");
    #else
        printf("未知Linux发行版\n");
    #endif

#elif ((OS & 0xF0) == WINDOWS)
    printf("当前系统大类：Windows\n");
    // 细分Windows版本
    #if OS == WINXP
        printf("具体系统：Windows XP\n");
    #elif OS == WIN7
        printf("具体系统：Windows 7\n");
    #elif OS == WIN10
        printf("具体系统：Windows 10\n");
    #elif OS == WIN11
        printf("具体系统：Windows 11\n");
    #else
        printf("未知Windows版本\n");
    #endif

#else
    printf("未知操作系统\n");
#endif
}

#if 0
int main(void)
{
    get_os_name();
    return 0;
}
#endif