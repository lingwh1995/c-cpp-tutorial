cmake_minimum_required(VERSION 3.28)

# 获取当前文件夹名并提取数字前缀
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if(DIR_NAME MATCHES "^([0-9]+)")
    set(PROJECT_ID ${CMAKE_MATCH_1})
else()
    # 如果文件夹没数字，用安全的文件夹名代替
    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" PROJECT_ID ${DIR_NAME})
endif()

# 定义总项目名 (这只是给 CMake 内部归档用的，不影响生成的文件名)
project(Practice_${PROJECT_ID} C)
set(CMAKE_C_STANDARD 23)

# 扫描 src 目录下所有 .c 文件（多文件必须全部参与编译）
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.c")

# 遍历每一个 .c 文件
foreach(SOURCE_PATH IN LISTS ALL_SOURCES)

    # 只处理包含 main 函数的文件
    file(READ "${SOURCE_PATH}" SOURCE_CODE)
    string(FIND "${SOURCE_CODE}" "int main(" MAIN_FOUND)
    if(MAIN_FOUND EQUAL -1)
        message(STATUS "Skip (no main): ${SOURCE_PATH}")
        continue()
    endif()

    get_filename_component(FULL_FILE_NAME ${SOURCE_PATH} NAME)
    get_filename_component(BASE_NAME ${SOURCE_PATH} NAME_WE)

    set(TARGET_NAME "${PROJECT_ID}_${FULL_FILE_NAME}")
    set(OUTPUT_NAME "${PROJECT_ID}_${BASE_NAME}")

    # 把所有 .c 一起编译
    add_executable("${TARGET_NAME}" ${ALL_SOURCES})

    target_include_directories("${TARGET_NAME}" PRIVATE inc src)
    set_target_properties("${TARGET_NAME}" PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")

    message(STATUS "Build Target: ${TARGET_NAME} -> ${OUTPUT_NAME}.exe")

endforeach()