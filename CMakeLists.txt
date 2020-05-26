cmake_minimum_required (VERSION 2.8.11)
project(PokeDiamond)

# TODO: Add commands

enable_language(ASM)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.c" "*.cpp")

add_executable(PokeDiamond ${SOURCES})
target_include_directories(PokeDiamond PRIVATE include include-mw arm9/lib/include)

add_executable(calcrom .travis/calcrom/calcrom.cpp)
target_include_directories(calcrom PRIVATE /usr/local/include)
