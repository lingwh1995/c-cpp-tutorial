# 设置当前子项目的名称
project(001_helloworld C)

# 搜集源码
set(SOURCES src/main.c)

# 定义可执行文件
add_executable(001_helloworld ${SOURCES})
