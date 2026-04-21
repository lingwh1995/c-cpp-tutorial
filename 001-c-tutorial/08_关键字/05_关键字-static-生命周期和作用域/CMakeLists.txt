cmake_minimum_required(VERSION 3.28)

# 1. 获取编号前缀
if(NOT PARENT_PROJ_ID)
    get_filename_component(DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    set(MY_ID ${DIR_NAME})
else()
    set(MY_ID ${PARENT_PROJ_ID})
endif()

# 2. 扫描源码
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE INCS CONFIGURE_DEPENDS "inc/*.h")

foreach(S_FILE ${SRCS})
    file(READ ${S_FILE} CONTENT)
    if(CONTENT MATCHES "int main")
        # 1. 获取不带后缀的文件名 (用于 Target Name): 如 main
        get_filename_component(B_NAME ${S_FILE} NAME_WE)

        # 2. 获取带后缀的文件名 (用于 Output Name): 如 main.c
        get_filename_component(F_NAME ${S_FILE} NAME)

        # 3. 内部目标名保持纯净: 08_05_main
        set(TARGET_NAME "${MY_ID}_${B_NAME}")

        # 4. 【关键改动】输出文件名设为带 .c 的格式: 08_05_main.c
        set(OUTPUT_NAME "${MY_ID}_${F_NAME}")

        if(NOT TARGET ${TARGET_NAME})
            # 内部依然使用不带点的 TARGET_NAME 以防报错
            add_executable(${TARGET_NAME} ${SRCS} ${INCS})

            # 通过属性修改，让 CLion 列表和生成的 exe 显示为 08_05_main.c
            set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")

            target_include_directories(${TARGET_NAME} PRIVATE
                    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src"
            )

            message(STATUS "Loaded: ${OUTPUT_NAME}")
        endif()
    endif()
endforeach()