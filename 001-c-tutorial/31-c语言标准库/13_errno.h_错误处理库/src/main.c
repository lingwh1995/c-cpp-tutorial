#include <errno.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("nonexistent.txt", "r");
    if (fp == NULL)
    {
        printf("Error code: %d\n", errno);
        printf("Error message: %s\n", strerror(errno));
        perror("fopen failed");  // 快捷方式
    }
    return 0;
}