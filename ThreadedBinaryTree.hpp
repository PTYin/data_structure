//
// Created by Peter on 2019/9/24.
//

#ifndef DATA_STRUCTURE_THREADEDBINARYTREE_HPP

#include "BinaryTree.hpp"
#include "Node.hpp"

#define CLUE    true

namespace pty
{
    /*
     * 线索二叉树类型，继承二叉树类型
     * 新增功能：
     * 1.   给出节点，可获得前驱节点或者后驱节点
     * 2.   可使用range_based的增强型for循环，完全类似线性储存
     * 3.   可简单利用for循环正向、反向进行中序遍历
     * 父类支持操作包括：
     * 1.   从前序、后序中的一个和中序序列构建树
     * 2.   插入到某节点的左或右儿子节点处
     * 3.   删除以位置node节点为根的子树，并返回该子树原先的规模
     * 4.   将以node节点为根节点的子树从当前树种摘除，并将其转换为一棵独立的树
     * 5.   返回大小
     * 6.   返回是否为空
     * 7.   重载==运算符，比较两棵树
     * 8.   以凸入表示法打印树*/
    template <typename T>
    class ThreadedBinaryTree : public BinaryTree<T>
    {
    public:
        using Node = Node<T>;
        class Iterator
        {
        public:
            Node* pt;  // 基于指针
            explicit Iterator(Node* _pt = nullptr): pt(_pt){}
            T& operator*() const
            {
                return pt->value;
            }
            Iterator& operator=(const Iterator &)=default;
            Iterator& operator++()  // ++Iterator
            {
                pt = next(pt);
                return *this;
            }
            Iterator operator++(int)   // Iterator++
            {
                Iterator tmp = *this;
                pt = next(pt);
                return tmp;
            }
            Iterator& operator--()  // --Iterator
            {
                pt = previous(pt);
                return *this;
            }
            Iterator operator--(int)  // Iterator--
            {
                Iterator tmp = *this;
                pt = previous(pt);
                return tmp;
            }
            bool operator==(const Iterator& it)
            {
                return pt == it.pt;
            }
            bool operator!=(const Iterator& it)
            {
                return pt != it.pt;
            }
        };
    protected:
        // 头节点
        Node* head;
        // 尾节点
        Node* tail;
    public:
        // 删除默认构造函数
        ThreadedBinaryTree() = delete;
        ThreadedBinaryTree(int size, const T _values[], const int _in_order[] = nullptr, const int _pre_order[] = nullptr, const int _post_order[] = nullptr)
                        :BinaryTree<T>(size, _values, _in_order, _pre_order, _post_order),head(nullptr),tail(nullptr){}
        // 重定义析构函数，避免导致死循环
        virtual ~ThreadedBinaryTree()
        {
            this->root = nullptr;
            if(this->n!=0)
                for(Iterator next=Iterator(head),present=next++;next.pt != nullptr;present=next++)
                {
                    delete  present.pt;
                }
            delete tail;
        }
        Iterator begin() const
        {
            return Iterator(head);
        }
        static Iterator end()
        {
            return Iterator(nullptr);
        }
        Iterator front() const
        {
            return Iterator(head);
        }
        Iterator back() const
        {
            return Iterator(tail);
        }
        // 重定义insert
        virtual void insert(Node* fa, const T _value, bool insert_as_left_child)
        {
            Node* node = new Node(_value, fa);
            if(insert_as_left_child)
            {
                if(fa->LTag == CLUE || fa->left_child == nullptr)
                {
                    this->n++;
                    fa->left_child = node;
                    fa->LTag = !CLUE;
                }
            }
            else
            {
                if(fa->RTag == CLUE || fa->right_child == nullptr)
                {
                    this->n++;
                    fa->right_child = node;
                    fa->RTag = !CLUE;
                }
            }
        }
        static Node* previous(Node* node)
        {
            if(node->LTag == CLUE)
            {
                return node->left_child;
            }
            Node* right = node->left_child;
            while (right->RTag != CLUE && right->right_child)
                right = right->right_child;
            return right;
        }
        static Node* next(Node* node)
        {
            if(node->RTag == CLUE || node->right_child == nullptr)
            {
                return node->right_child;
            }
            Node* left = node->right_child;
            while (left->LTag != CLUE && left->left_child)
                left = left->left_child;
            return left;
        }
        void makeThreaded()
        {
            Node* prev = nullptr;
            head = nullptr;
            this->traversal_in([&prev,this](Node* node)
                            {
                                if(node->LTag == CLUE || node->left_child == nullptr)
                                {
                                    node->LTag = CLUE;
                                    node->left_child = prev;
                                    if(!head)
                                    {
                                        head = node;
                                    }
                                }
                                if(prev && (prev->right_child == nullptr || prev->RTag == CLUE))
                                {
                                    prev->RTag = CLUE;
                                    prev->right_child = node;
                                }
                                prev = node;
                            });
            tail = prev;
        }
    };
}
#define DATA_STRUCTURE_THREADEDBINARYTREE_HPP

#endif //DATA_STRUCTURE_THREADEDBINARYTREE_HPP
