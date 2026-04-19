# 设置当前子项目的名称
project(048_calculator_static C)

# 自动搜集 src 下的所有 .c 文件
file(GLOB SOURCES "src/*.c")

# 定义可执行文件
add_executable(048_calculator_static ${SOURCES})

# 如果有头文件目录，加入包含路径
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/inc")
    target_include_directories(048_calculator_static PRIVATE inc)
endif()
