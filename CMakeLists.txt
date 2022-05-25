cmake_minimum_required(VERSION 3.19)

project(work)

set(CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_library(linkedlist STATIC)
target_include_directories(linkedlist PUBLIC include)
target_sources(linkedlist 
    PUBLIC
        include/linkedlist.h
    PRIVATE
        src/linkedlist.cpp
)

enable_testing()
add_subdirectory(tests)

