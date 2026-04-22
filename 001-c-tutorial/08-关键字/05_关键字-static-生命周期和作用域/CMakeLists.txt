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
        # 获取带后缀的文件名 (如 main.c)
        get_filename_component(F_NAME ${S_FILE} NAME)

        # 【关键改动】直接将目标名设为带 .c 的格式: 01_xxx_main.c
        # 这样 CLion 的 Run/Debug 列表就会显示后缀了
        set(TARGET_NAME "${MY_ID}_${F_NAME}")

        if(NOT TARGET ${TARGET_NAME})
            add_executable(${TARGET_NAME} ${SRCS} ${INCS})

            target_include_directories(${TARGET_NAME} PRIVATE
                    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src"
            )

            message(STATUS "Loaded: ${TARGET_NAME}")
        endif()
    endif()
endforeach()