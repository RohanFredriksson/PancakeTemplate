cmake_minimum_required(VERSION 3.14)

project(game)
add_subdirectory(dependencies/pancake/)

if (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -g")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_VERBOSE_MAKEFILE ON)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -g")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -fsanitize=address")
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

include_directories(include)

file(GLOB_RECURSE source_files src/*.cpp)
add_custom_command(
    OUTPUT main.cpp
    COMMAND ./generate.py ${source_files}
    DEPENDS ./generate.py ${source_files}
)

list(FILTER source_files EXCLUDE REGEX ".*main.cpp$")
add_executable(${PROJECT_NAME} ${source_files} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC pancake)
target_link_libraries(${PROJECT_NAME} PUBLIC pancake)