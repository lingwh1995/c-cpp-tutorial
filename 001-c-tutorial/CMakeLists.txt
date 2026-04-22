cmake_minimum_required(VERSION 3.28)
project(C_Tutorial_Master C)

# 统一全局配置
set(CMAKE_C_STANDARD 23)

if(WIN32)
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        add_compile_options("-finput-charset=UTF-8")
    endif()
endif()

# 1. 扫描第一层目录 (分类文件夹)
file(GLOB categories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(category ${categories})
    set(category_full_path "${CMAKE_CURRENT_SOURCE_DIR}/${category}")

    if(IS_DIRECTORY "${category_full_path}"
       AND NOT category STREQUAL "cmake-build-debug"
       AND NOT category MATCHES "^\\.")

        # 2. 扫描第二层子目录 (具体项目文件夹)
        file(GLOB projects RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${category}/*")

        foreach(project_path ${projects})
            set(full_project_path "${CMAKE_CURRENT_SOURCE_DIR}/${project_path}")

            if(IS_DIRECTORY "${full_project_path}" AND EXISTS "${full_project_path}/CMakeLists.txt")

                # 获取二级目录的文件名
                get_filename_component(project_name "${full_project_path}" NAME)

                # 3. 提取编号 (纯数字组合，如 01_03)
                string(REGEX MATCH "^[0-9]+" cat_id "${category}")
                string(REGEX MATCH "^[0-9]+" proj_id "${project_name}")

                if(cat_id AND proj_id)
                    set(safe_id "${cat_id}_${proj_id}")
                else()
                    # 如果没有数字，生成一个绝对安全的英文 ID
                    string(MD5 safe_id "${project_path}")
                    string(SUBSTRING "${safe_id}" 0 6 safe_id)
                    set(safe_id "ext_${safe_id}")
                endif()

                # 4. 关键：通过 CACHE 传递纯英文数字 ID 给子项目，供其 add_executable 使用
                set(PARENT_PROJ_ID "${safe_id}" CACHE INTERNAL "Safe ID for subproject target names")

                # 指定构建目录 (如 build_01_03)
                add_subdirectory("${project_path}" "build_${safe_id}")
            endif()
        end foreach()
    endif()
end foreach()
