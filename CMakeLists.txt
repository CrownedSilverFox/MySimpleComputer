cmake_minimum_required(VERSION 3.13)
project(MySimpleComputer C)

set(CMAKE_C_STANDARD 99)

set(COMPUTER_SOURCES include/mymemory.h src/mymemory.c)
add_library(libMySimpleComputer STATIC ${COMPUTER_SOURCES})

set(TERM_SOURCES include/myTerm.h src/myTerm.c)
add_library(libMyTerm STATIC ${TERM_SOURCES})

set(CHAR_SOURCES include/myBigChars.h src/myBigChars.c)
add_library(libMyBigChars STATIC ${CHAR_SOURCES})

set(KEY_SOURCES include/myReadkey.h src/myReadKey.c)
add_library(libMyReadKey STATIC ${KEY_SOURCES})

include_directories(include src)

add_executable(MySimpleComputer src/main.c)

target_link_libraries(MySimpleComputer libMySimpleComputer libMyTerm libMyBigChars)