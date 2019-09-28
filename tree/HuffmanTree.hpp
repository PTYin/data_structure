//
// Created by Peter on 2019/9/25.
//

#ifndef DATA_STRUCTURE_HUFFMANTREE_HPP
#define DATA_STRUCTURE_HUFFMANTREE_HPP

#include "BinaryTree.hpp"
#include "../Stack.hpp"
#include "../Heap.hpp"

namespace pty
{
    /*Huffman树类
     * 给出容器构造Huffman树
     * 不支持删除、插入节点
     * 支持遍历
     * 返回大小
     * 返回是否为空
     * 重载==运算符，比较两棵树
     * 以凸入表示法打印树
     * 前序、中序、后序遍历树*/
    template<typename T, typename Node>
    class HuffmanTree : public BinaryTree<T>
    {
    private:
        void insert(Node *fa, const T &_value, bool insert_as_left_child) override
        {}

        int remove(Node *node) override
        { return 0; }

        HuffmanTree<T> &secede(Node *node) override
        { return *this; }

    public:
        template<typename CONTAINER>
        explicit HuffmanTree(CONTAINER container, int size):BinaryTree<T>()
        {
            Node **array = new Node *[size];
            for (int i = 0; i < size; i++)
            {
                array[i] = new Node(container[i]);
            }
            Heap<Node *> heap(100, [](Node *node1, Node *node2) -> bool
            {
                return node1->value <= node2->value;
            });
            heap.heapify(array, size);
            Node *fa = nullptr;
            while (!heap.is_empty() && heap.size() != 1)
            {
                Node *node1 = heap.pop();
                Node *node2 = heap.pop();
                this->n += 2;
                fa = new Node(node1->value + node2->value);
                fa->left() = node1;
                fa->right() = node2;
                node1->fa() = node2->fa() = fa;
                heap.insert(fa);
            }
            this->root = fa;
            delete[] array;
        }
    };
}

#endif //DATA_STRUCTURE_HUFFMANTREE_HPP
