cmake_minimum_required(VERSION 3.7)
project(data_structure_190905)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC main.cpp doubleLinkedList.hpp stack.hpp queue.hpp)
add_executable(usage ${SRC})