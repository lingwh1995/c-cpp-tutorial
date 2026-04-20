cmake_minimum_required(VERSION 3.28)
project(clang_workspace C)

# 统一全局配置
set(CMAKE_C_STANDARD 23)

if(WIN32)
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        # 仅设置输入编码，避免 iconv 转换错误
        add_compile_options("-finput-charset=UTF-8")
    endif()
endif()

# 自动扫描子目录
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)

        # 提取文件夹开头的数字作为中间编译路径名 (如 "048_c语言..." -> "build_048")
        # 这一步是解决 "Invalid argument" 报错的关键：让中间产物路径不含中文
        string(REGEX MATCH "^[0-9]+" dir_id ${child})
        if(dir_id)
            set(bin_dir "build_${dir_id}")
        else()
            set(bin_dir "build_extra_${child}")
        endif()

        # 添加子项目，指定英文中间路径
        add_subdirectory(${child} ${bin_dir})
    endif()
endforeach()
