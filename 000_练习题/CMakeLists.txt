# 1. 必须有版本声明，确保独立运行不报错
cmake_minimum_required(VERSION 3.28)

# 2. 获取文件夹名并处理名称冲突
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REGEX MATCH "^[0-9]+" PROJECT_ID ${DIR_NAME})

if(PROJECT_ID)
    # 使用 ID + 部分文件夹名，既合法又唯一
    set(SAFE_TARGET_NAME "${DIR_NAME}")
    # 过滤掉非英文数字字符（保留数字和下划线，满足 CMake 规范）
    string(REGEX REPLACE "[^a-zA-Z0-9_]" "_" SAFE_TARGET_NAME ${SAFE_TARGET_NAME})
    set(SAFE_TARGET_NAME "${SAFE_TARGET_NAME}_main.c")
else()
    set(SAFE_TARGET_NAME "target_${DIR_NAME}_main.c")
endif()

project(${SAFE_TARGET_NAME} C)

# 3. 继承或独立设置标准
if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 23)
endif()

# 4. 扫描源码（添加 CONFIGURE_DEPENDS 让 CMake 在文件增删时自动刷新）
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

if(SOURCES)
    add_executable(${SAFE_TARGET_NAME} ${SOURCES})
    target_include_directories(${SAFE_TARGET_NAME} PRIVATE inc src)
    message(STATUS "Build Target: ${SAFE_TARGET_NAME}")
endif()