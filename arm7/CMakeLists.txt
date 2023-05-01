cmake_minimum_required (VERSION 3.15)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
project(DP_Arm7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# TODO: Add commands

enable_language(ASM)

add_compile_options(-fms-extensions)

file(GLOB_RECURSE SOURCES "*.c" "*.cpp" "*.s")

add_executable(DP_Arm7 ${SOURCES})
target_include_directories(DP_Arm7 PRIVATE lib/include)
target_compile_definitions(DP_Arm7 PUBLIC __CLION_IDE__)
