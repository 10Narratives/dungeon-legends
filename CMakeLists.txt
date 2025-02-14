cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(DungeonLegends)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(engine)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} SFML::Graphics SFML::Audio SFML::Network)
target_link_libraries(${PROJECT_NAME} engine-core)