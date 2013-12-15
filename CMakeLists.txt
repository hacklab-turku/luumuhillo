cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_COMPILER g++)
project(luumuhillo)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SFML 2 COMPONENTS graphics audio window network system)
include_directories(${SFML_INCLUDE_DIR})

add_definitions(-std=c++0x -g -pthread -fpermissive)

FILE(GLOB sources source/*)
add_executable(luumuhillo ${sources})
target_link_libraries(luumuhillo ${SFML_LIBRARIES})

