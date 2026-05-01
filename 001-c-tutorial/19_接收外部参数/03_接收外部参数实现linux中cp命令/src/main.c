# include <stdio.h>
# include <stdlib.h>

/**
 * 在终端执行测试复制文本文件 .\main.exe a.txt b.txt
 * 在终端执行测试复制图片文件 .\main.exe a.jpg b.jpg
 *
 * 实现类似于linux中cp的命令
 * @param argc 参数个数
 * @param argv 参数列表
 * @return
 */
int main(const int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "用法: %s <source file> <dst file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *src_file = fopen(argv[1], "rb");
    if (src_file == NULL)
    {
        fprintf(stderr, "error: can not open source file! '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    FILE *dst_file = fopen(argv[2], "wb");
    if (dst_file == NULL)
    {
        fprintf(stderr, "error: can not create dst file! '%s'\n", argv[2]);
        fclose(src_file);
        return EXIT_FAILURE;
    }

    /**
     * 复制文件逻辑(效率低) v1.0
     */
    /*
    // 把文件指针移动到文件结束
    fseek(src_file, 0, SEEK_END);
    // 获取文件总字节大小
    int len = ftell(src_file);
    rewind(src_file);
    for (int i = 0; i < len; i++)
    {
        fputc(fgetc(src_file), dst_file);
    }*/

    /**
     * 复制文件逻辑(效率高) v2.0
     */
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0)
    {
        fwrite(buffer, 1, bytes_read, dst_file);
    }

    fclose(src_file);
    fclose(dst_file);
    // 函数即将结束，指针马上销毁，赋 NULL 无意义，所以注释掉
    // fpi = NULL;
    // fpo = NULL;
    return 0;
}