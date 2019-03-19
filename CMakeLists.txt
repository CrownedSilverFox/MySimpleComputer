cmake_minimum_required(VERSION 3.13)
project(MySimpleComputer C)

set(CMAKE_C_STANDARD 99)

set(SOURCES include/myTerm.h include/mymemory.h src/mymemory.c)

include_directories(include src)

add_library(libMySimpleComputer STATIC ${SOURCES})

add_executable(MySimpleComputer src/main.c)

target_link_libraries(MySimpleComputer libMySimpleComputer)