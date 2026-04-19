cmake_minimum_required(VERSION 3.28)
project(clang_workspace C)

set(CMAKE_C_STANDARD 23)

if(WIN32)
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        add_compile_options("-finput-charset=UTF-8")
    endif()
endif()

file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)

        # --- 核心改进部分 ---
        # 提取文件夹名的前三个数字作为编译目录名 (例如 "048_c语言..." -> "project_048")
        # 这样可以避开 GCC 对中文路径的支持问题
        string(REGEX MATCH "^[0-9]+" dir_prefix ${child})

        if(dir_prefix)
            set(binary_dir_name "project_${dir_prefix}")
        else()
            # 如果没有数字开头，就简单地把整个名字做个哈希或者用个替代名
            set(binary_dir_name "project_sub")
        endif()

        # 使用两个参数的 add_subdirectory:
        # 第一个参数是源码路径 (可以是中文)
        # 第二个参数是编译输出路径 (必须是英文)
        add_subdirectory(${child} ${binary_dir_name})
        # --------------------

    endif()
endforeach()
