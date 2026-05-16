#include <stdio.h>
#include <stdlib.h>
#include <cJSON.h>

// 1. 测试生成 JSON 字符串
void test_create_json() {
    printf("--- 开始测试：生成 JSON ---\n");

    // 创建根对象 {}
    cJSON *root = cJSON_CreateObject();

    // 添加基本数据类型
    cJSON_AddStringToObject(root, "name", "张三");
    cJSON_AddNumberToObject(root, "age", 25);
    cJSON_AddBoolToObject(root, "is_developer", 1);

    // 添加一个嵌套的子对象
    cJSON *skills = cJSON_CreateObject();
    cJSON_AddStringToObject(skills, "primary", "Java");
    cJSON_AddStringToObject(skills, "secondary", "C");
    cJSON_AddItemToObject(root, "skills", skills);

    // 添加一个数组 [1, 2, 3]
    int id_array[3] = {101, 102, 103};
    cJSON *ids = cJSON_CreateIntArray(id_array, 3);
    cJSON_AddItemToObject(root, "project_ids", ids);

    // 将 cJSON 结构体渲染为带缩进的可读字符串
    char *json_string = cJSON_Print(root);
    printf("生成的 JSON 字符串:\n%s\n\n", json_string);

    // 释放内存（必须释放 Print 生成的字符串和 root 对象）
    free(json_string);
    cJSON_Delete(root);
}

// 2. 测试解析 JSON 字符串
void test_parse_json() {
    printf("--- 开始测试：解析 JSON ---\n");

    // 模拟一段接收到的 JSON 字符串
    const char *json_raw = "{\n"
                           "  \"name\": \"李四\",\n"
                           "  \"age\": 30,\n"
                           "  \"is_developer\": true\n"
                           "}";

    // 解析字符串到 cJSON 结构体
    cJSON *root = cJSON_Parse(json_raw);
    if (root == NULL) {
        printf("JSON 解析失败！\n");
        return;
    }

    // 安全地获取字段值
    cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        printf("解析成功 -> 姓名: %s\n", name->valuestring);
    }

    cJSON *age = cJSON_GetObjectItemCaseSensitive(root, "age");
    if (cJSON_IsNumber(age)) {
        printf("解析成功 -> 年龄: %d\n", age->valueint);
    }

    cJSON *is_developer = cJSON_GetObjectItemCaseSensitive(root, "is_developer");
    if (cJSON_IsBool(is_developer)) {
        printf("解析成功 -> 是否为开发者: %s\n", cJSON_IsTrue(is_developer) ? "是" : "否");
    }

    // 释放内存
    cJSON_Delete(root);
}

int main() {
    // 运行测试
    test_create_json();
    test_parse_json();
    return 0;
}