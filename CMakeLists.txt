cmake_minimum_required(VERSION 3.7)
project(data_structure)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC main.cpp
        primitive/DoubleLinkedList.hpp
        primitive/Stack.hpp
        primitive/Queue.hpp
        primitive/Heap.hpp
        other/quick_sort.hpp
        tree/BinaryTree.hpp
        tree/ThreadedBinaryTree.hpp
        tree/Node.hpp
        tree/SearchTree.hpp
        tree/HuffmanTree.hpp
        tree/AVLTree.hpp
        tree/Treap.hpp
        tree/Splay.hpp
        tree/RedBlack.hpp
        string/KMP.hpp
        graph/dijkstra.hpp
        primitive/DisjointSet.hpp
        graph/kruskal.hpp graph/Hierholzer.hpp graph/prim.hpp other/FFT.hpp)
add_executable(usage ${SRC})