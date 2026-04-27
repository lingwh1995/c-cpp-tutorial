#include <stdio.h>

/**
 * 将整数数组数据写入文本文件
 *
 * 该函数创建一个包含10个整数的数组，并将其以文本格式写入到file_int.txt文件中。
 * 演示了C语言中文件写入操作的基本流程，包括文件打开、错误检查、数据写入和文件关闭。
 * 同时展示了文件缓冲机制的工作原理：数据先写入缓冲区，关闭文件时才真正写入磁盘。
 */
void fprintf_int_to_text_file()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_int.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    for (int i = 0; i < len; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%d ", arr[i]);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

/**
 * 将双精度浮点数数组数据写入文本文件
 *
 * 该函数创建一个包含10个双精度浮点数的数组，并将其以文本格式（保留两位小数）
 * 写入到file_double.txt文件中。演示了浮点数的文件写入操作和缓冲机制的工作原理。
 */
void fprintf_double_to_text_file()
{
    const double arr[] = { 1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.0, 10.0 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_double.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    for (int i = 0; i < len; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%.2f ", arr[i]);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

/**
 * 将字符串数组数据写入文本文件
 *
 * 该函数创建一个包含3个字符串的二维数组（"tulun"、"hello"、"world"），
 * 并将其以文本格式写入到file_str.txt文件中。演示了字符串的文件写入操作
 * 和缓冲机制的工作原理。
 */
void fprintf_str_to_text_file()
{
    const char arr[3][10] = {
        { "tulun" },
        { "hello" },
        { "world" }
    };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_str.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    for (int i = 0; i < len; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%s ", arr[i]);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

/**
 * 打印相对于文件开头的当前偏移量（以字节为单位）
 *
 * 该函数创建一个包含10个整数的数组，并以文本格式写入到file.txt文件中。
 * 在每次写入一个整数后，使用ftell()函数获取并打印当前文件指针相对于文件开头的偏移量（以字节为单位）。
 * 用于演示ftell函数的使用方法和文件写入过程中偏移量的变化规律。
 */
void fprintf_with_ftell_test()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file.txt", "w");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给缓冲区中写入内容......\n");
    printf("%p\n", fp);
    for (int i = 0; i < len; i++)
    {
        // 把内容写入到缓冲区，如果缓冲区写满了，也是会写入到文件中的，并非一直往缓冲区中写入
        fprintf(fp, "%d ", arr[i]);
        const long pos = ftell(fp);
        printf("当前偏移：%ld\n", pos);
    }

    /**
     * 写文件与缓冲区
     * 只有执行了关闭函数或缓冲区写满之后，才把缓冲区中的内容真正写入到对应的文件中
     *    这样设计的目的是为了提高性能和效率，不然会多次给磁盘文件中写入内容，要是读取到了一百万个数字，程序运行一次就会给磁盘中写入一百万次数据
     */
    printf("结束给缓冲区中写入内容......\n");
    printf("开始给文件中写入内容......\n");
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

/**
 * 从文本文件中读取整数数组数据
 *
 * 该函数从file_int.txt文件中读取10个整数数据并存储到数组中，然后打印每个读取的整数值。
 * 演示了C语言中文本文件的读取操作，包括文件打开、错误检查、使用fscanf逐个数读取数据以及文件关闭。
 * 同时展示了文件读取过程中的缓冲机制：系统一次性从磁盘读取一块数据到缓冲区，程序从缓冲区获取数据。
 */
void fscanf_int_from_text_file()
{
    int arr[10] = { 0 };
    FILE *fp = fopen("file_int.txt", "r");
    const int len = 10;
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始从文件中读取内容......\n");
    for (int i = 0; i < len; i++)
    {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("读取第 %d 个数据失败或文件已结束\n", i);
            break;
        }
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    /**
     * 读文件与缓冲区
     * C语言文件操作使用缓冲机制提高性能
     * 读取时:系统一次性从磁盘读取一块数据到缓冲区,程序从缓冲区获取数据
     * 写入时:数据先写入缓冲区,缓冲区满或关闭文件时才真正写入磁盘
     */
    printf("结束从文件中读取内容......\n");
    fclose(fp);
    fp = NULL;
}

/**
 * 将整数数组数据以二进制格式写入文件
 *
 * 该函数创建一个包含10个整数的数组，并使用fwrite函数将其以二进制格式写入到file_int.txt文件中。
 * 演示了C语言中二进制文件的写入操作，与文本文件写入不同，二进制写入直接保存内存中的原始数据，
 * 不使用格式化转换，效率更高且占用空间更小。适用于需要快速读写大量数据的场景。
 */
void fwrite_int_to_binary_file()
{
    const int arr[] = { 12, 23, 34, 45, 56, 67, 78, 89, 90, 100 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_bin.txt", "wb");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始给文件中写入内容......\n");
    // 一次性把数组中所有内容直接以二进制形式写入到文件中
    fwrite(arr, sizeof(int), len, fp);
    fclose(fp);
    printf("结束给文件中写入内容......\n");
    fp = NULL;
}

void fread_int_from_binary_file()
{
    int arr[10] = { 0 };
    const int len = sizeof(arr) / sizeof(arr[0]);
    // 打开一个文件流对象
    FILE *fp = fopen("file_bin.txt", "rb");
    if (fp == NULL)
    {
        printf("error opening file\n");
        return;
    }
    printf("开始从文件中读取内容......\n");
    // 一次性把数组中所有内容直接以二进制形式读取到数组中
    fread(arr, sizeof(int), len, fp);
    // ferror() 用于检查文件流是否发生了错误
    if (ferror(fp))
    {
        printf("读取文件时发生错误\n");
        fclose(fp);
        return;
    }
    fclose(fp);
    printf("结束从文件中读取内容......\n");
    fp = NULL;
}

/**
 * 测试各种合法和非法的路径格式
 *
 * 该函数系统地测试多种路径格式，包括合法路径、非法路径、特殊字符路径等，
 * 帮助理解fopen函数对不同路径格式的处理方式和错误信息。
 */
void fopen_test_path_formats()
{
    // 测试用例结构体
    typedef struct {
        const char* path;
        const char* description;
        int should_succeed; // 1表示预期成功，0表示预期失败
    } PathTest;

    // 定义测试用例
    PathTest tests[] = {
        // 合法路径
        {"file_bin.txt", "合法：当前目录下的文件", 1},
        {"./file_bin.txt", "合法：使用./表示当前目录", 1},
        {"data/test.txt", "合法：子目录中的文件（正斜杠）", 0},  // 目录可能不存在

        // 空路径和无效路径
        {"", "非法：空字符串路径", 0},
        {"/", "非法：根目录（不是文件）", 0},

        // 包含转义字符的路径（编译时会被解释）
        {"file\tname.txt", "非法：包含制表符", 0},
        {"file\nname.txt", "非法：包含换行符", 0},

        // 不存在的目录
        {"nonexistent/file.txt", "非法：目录不存在", 0},
        {"a/b/c/d/e/f/file.txt", "非法：多层不存在的目录", 0},

        // 绝对路径测试
        {"/tmp/test_file.txt", "合法：macOS临时文件绝对路径", 0},  // 取决于权限
        {"/root/test.txt", "非法：需要root权限", 0},

        // 包含空格的路径
        {"my file.txt", "合法：包含空格的文件名", 0},  // 文件可能不存在
        {"my folder/test.txt", "合法：路径包含空格", 0},  // 目录可能不存在

        // 超长文件名
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt",
         "边界：超长文件名", 0},

        // 特殊字符（某些系统允许）
        {"file-name.txt", "合法：包含连字符", 0},
        {"file_name.txt", "合法：包含下划线", 0},
        {"file.name.test.txt", "合法：多个点号", 0},

        // 中文路径（依赖系统编码）
        {"测试文件.txt", "测试：中文文件名", 0},

        // 大小写测试
        {"FILE_BIN.TXT", "测试：大写扩展名", 0},
        {"File_Bin.Txt", "测试：混合大小写", 0},
    };

    int total_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    int failed = 0;

    // 执行测试
    for (int i = 0; i < total_tests; i++)
    {
        printf("[测试 %d/%d] %s\n", i + 1, total_tests, tests[i].description);
        printf("  路径: \"%s\"\n", tests[i].path);

        // 尝试打开文件
        FILE *fp = fopen(tests[i].path, "rb");

        if (fp != NULL)
        {
            printf("  结果: ✓ 成功打开\n");
            fclose(fp);

            if (tests[i].should_succeed)
            {
                printf("  状态: PASS（预期成功，实际成功）\n");
                passed++;
            }
            else
            {
                printf("  状态: FAIL（预期失败，实际成功）\n");
                failed++;
            }
        }
        else
        {
            printf("  结果: ✗ 打开失败\n");
            printf("  错误: ");
            perror("");

            if (!tests[i].should_succeed)
            {
                printf("  状态: PASS（预期失败，实际失败）\n");
                passed++;
            }
            else
            {
                printf("  状态: FAIL（预期成功，实际失败）\n");
                failed++;
            }
        }

        printf("\n");
    }

    // 打印测试总结
    printf("========== 测试总结 ==========\n");
    printf("总测试数: %d\n", total_tests);
    printf("通过: %d\n", passed);
    printf("失败: %d\n", failed);
    printf("通过率: %.2f%%\n", (float)passed / total_tests * 100);
    printf("================================\n");
}

int main()
{
    //fprintf_int_to_text_file();
    //fprintf_double_to_text_file
    //fprintf_str_to_text_file();
    //fprintf_with_ftell_test();
    //fscanf_int_from_text_file();
    //fwrite_int_to_binary_file();
    //fread_int_from_binary_file();
    //fopen_test_path_formats();
    return 0;
}