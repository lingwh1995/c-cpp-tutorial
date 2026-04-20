cmake_minimum_required(VERSION 3.28)

# 1. 获取当前文件夹名并提取数字前缀
get_filename_component(DIR_NAME src NAME)
if(DIR_NAME MATCHES "^([0-9]+)")
    set(PROJECT_ID ${CMAKE_MATCH_1})
else()
    # 如果文件夹没数字，用安全的文件夹名代替
    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" PROJECT_ID ${DIR_NAME})
endif()

# 定义总项目名 (这只是给 CMake 内部归档用的，不影响生成的文件名)
project(Practice_${PROJECT_ID} C)
set(CMAKE_C_STANDARD 23)

# 2. 扫描 src 目录下的所有 .c 文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

# 3. 遍历每一个 .c 文件
foreach(SOURCE_PATH IN LISTS SOURCES)

    # 【关键修改】：获取带后缀的文件全名，例如 "main.c"
    get_filename_component(FULL_FILE_NAME ${SOURCE_PATH} NAME)

    # 提取不带后缀的文件名，用于输出文件名（保持 .exe 干净）
    get_filename_component(BASE_NAME ${SOURCE_PATH} NAME_WE)

    # 拼接 Target 名称：000_main.c
    set(TARGET_NAME "${PROJECT_ID}_${FULL_FILE_NAME}")

    # 拼接输出文件名：000_main (生成后会自动补 .exe)
    set(OUTPUT_NAME "${PROJECT_ID}_${BASE_NAME}")

    # 创建可执行目标
    add_executable("${TARGET_NAME}" ${SOURCE_PATH})

    # 设置包含目录
    target_include_directories("${TARGET_NAME}" PRIVATE inc src)

    # 【核心】：让 Target 名和最终的文件名分开
    set_target_properties("${TARGET_NAME}" PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")

    # 打印你要求的格式
    message(STATUS "Build Target: ${TARGET_NAME} -> ${OUTPUT_NAME}.exe")

endforeach()