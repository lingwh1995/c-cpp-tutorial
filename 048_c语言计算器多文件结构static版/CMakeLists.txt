# 自动获取文件夹名并提取数字
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REGEX MATCH "^[0-9]+" PROJECT_ID ${DIR_NAME})

# 构造您要求的命名格式：数字_main.c
if(PROJECT_ID)
    set(TARGET_NAME "${PROJECT_ID}_main.c")
else()
    set(TARGET_NAME "main.c")
endif()

# 定义项目
project(${TARGET_NAME} C)

# 自动搜集源码
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

if(SOURCES)
    # 创建可执行文件
    add_executable(${TARGET_NAME} ${SOURCES})

    # 配置头文件搜索路径
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/inc")
        target_include_directories(${TARGET_NAME} PRIVATE inc)
    endif()
    target_include_directories(${TARGET_NAME} PRIVATE src)
endif()
