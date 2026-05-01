cmake_minimum_required(VERSION 3.28)

if(NOT PARENT_PROJ_ID)
    get_filename_component(DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    set(MY_ID ${DIR_NAME})
else()
    set(MY_ID ${PARENT_PROJ_ID})
endif()

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

            message(STATUS "Loaded: ${TARGET_NAME}")
        endif()
    endif()
endforeach()
