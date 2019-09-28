cmake_minimum_required(VERSION 3.7)
project(data_structure)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC main.cpp DoubleLinkedList.hpp Stack.hpp Queue.hpp Heap.hpp quick_sort.hpp tree/BinaryTree.hpp tree/ThreadedBinaryTree.hpp tree/Node.hpp tree/SearchTree.hpp tree/HuffmanTree.hpp tree/AVLTree.hpp)
add_executable(usage ${SRC})