cmake_minimum_required(VERSION 3.28)

if(NOT PARENT_PROJ_ID)
    get_filename_component(DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    set(MY_ID ${DIR_NAME})
else()
    set(MY_ID ${PARENT_PROJ_ID})
endif()

# 利用 PkgConfig 自动扫描 MSYS64/UCRT64 下的所有库
find_package(PkgConfig REQUIRED)

# 让 CMake 自动去你指定的 UCRT64 目录下寻找各种库的 .pc 配置文件
set(ENV{PKG_CONFIG_PATH} "D:/software/develop/msys64/ucrt64/lib/pkgconfig")

# =====================================================================
# 终极修复方案：
# 1. 必须使用 pkg_check_modules。
# 2. 后面加上 IMPLICIT_LINK_DIRECTORIES（或者什么都不加，但绝对不能加 REQUIRED）。
# 3. 这样 CMake 会单独评估每一个库。系统里有 glib 就加载 glib，有 cjson 就加载 cjson。
#    就算以后你没装某一个库，它也只会打印个警告，然后继续正确加载已经安装的库！
# 4. cJSON (在 msys2 中它的 pc 名字叫 libcjson)
# =====================================================================
pkg_check_modules(GLOBAL_LIBS libcjson)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE INCS CONFIGURE_DEPENDS "inc/*.h")

foreach(S_FILE ${SRCS})
    file(READ ${S_FILE} CONTENT)
    if(CONTENT MATCHES "int main")
        get_filename_component(F_NAME ${S_FILE} NAME)
        get_filename_component(F_NAME_WE ${S_FILE} NAME_WE)

        set(TARGET_NAME "${MY_ID}_${F_NAME}")

        if(NOT TARGET ${TARGET_NAME})
            add_executable(${TARGET_NAME} ${SRCS} ${INCS})

            set_target_properties(${TARGET_NAME} PROPERTIES
                    OUTPUT_NAME "${MY_ID}_${F_NAME_WE}"
            )

            target_include_directories(${TARGET_NAME} PRIVATE
                    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src"
            )

            # 无论搜到几个库，它们各自的头文件和库路径都会被自动并入这些全局变量中
            target_include_directories(${TARGET_NAME} PRIVATE ${GLOBAL_LIBS_INCLUDE_DIRS})
            target_compile_options(${TARGET_NAME} PRIVATE ${GLOBAL_LIBS_CFLAGS_OTHER})
            target_link_directories(${TARGET_NAME} PRIVATE ${GLOBAL_LIBS_LIBRARY_DIRS})
            target_link_libraries(${TARGET_NAME} PRIVATE ${GLOBAL_LIBS_LIBRARIES})

            message(STATUS "Loaded: ${TARGET_NAME}")
        endif()
    endif()
endforeach()