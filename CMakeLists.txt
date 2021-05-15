cmake_minimum_required (VERSION 3.15)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
project(PokeDiamond)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# TODO: Add commands

enable_language(ASM)

if(APPLE)
    include_directories(/usr/local/include)
endif(APPLE)

add_compile_options(-fms-extensions)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.c" "*.cpp")

add_executable(PokeDiamond ${SOURCES})
target_include_directories(PokeDiamond PRIVATE include include-mw arm9/lib/include arm7/lib/include arm9/modules/05/include arm9/modules/21/include arm9/modules/59/include arm9/modules/63/include)

add_executable(calcrom .github/calcrom/calcrom.cpp)
target_include_directories(calcrom PRIVATE /usr/local/include)

add_executable(knarc tools/knarc/Source.cpp tools/knarc/Narc.cpp tools/knarc/fnmatch.c)

add_executable(jsonproc tools/jsonproc/jsonproc.cpp)
target_include_directories(jsonproc PRIVATE SYSTEM tools/jsonproc)

add_executable(o2narc tools/o2narc/o2narc.cpp)
add_executable(msgenc tools/msgenc/msgenc.cpp)
