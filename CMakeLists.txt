cmake_minimum_required(VERSION 3.25)
project(alpha1_proxy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-frtti -fexceptions)
add_compile_options(-O3)
add_compile_options(-Wl,--kill-at)

MACRO(RECURSE_FILES return_list filter)
    FILE(GLOB_RECURSE new_list ${filter})
    SET(file_list "")
    FOREACH(file_path ${new_list})
        SET(file_list ${file_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES file_list)
    SET(${return_list} ${file_list})
ENDMACRO()

RECURSE_FILES(cpp_file_list ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(c_file_list ${SOURCE_DIR}/*.c)

add_library(
        alpha1_proxy
        SHARED
        ${cpp_file_list}
        ${c_file_list}
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "winhttp")

target_link_options(alpha1_proxy PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/module/winhttp.def")

# add src dir as include dir
target_include_directories(alpha1_proxy PRIVATE ${SOURCE_DIR})
# add include dir as include dir
target_include_directories(alpha1_proxy PRIVATE ${INCLUDE_DIR})
# add shared dir as include dir
target_include_directories(alpha1_proxy PUBLIC ${SHARED_DIR})