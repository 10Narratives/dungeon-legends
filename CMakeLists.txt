cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(DungeonLegends)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(src)
add_subdirectory(resources)
add_subdirectory(tests)
add_subdirectory(docs)

add_executable(${PROJECT_NAME} main.cpp)
