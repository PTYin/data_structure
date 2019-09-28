//
// Created by Peter on 2019/9/24.
//

#ifndef DATA_STRUCTURE_THREADEDBINARYTREE_HPP

#include "BinaryTree.hpp"
#include "Node.hpp"

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
    template<typename T, typename Node>
    class ThreadedBinaryTree : protected BinaryTree<T, Node>
    {
    private:
        // 递归以凸入表示法打印树
        void print_tree(std::ostream &o, Node *node, int indent, bool left) const
        {
            if (node == nullptr || !this->n)
                return;
            for (int i = 0; i < indent; i++)
                o << "\t";
            if (indent == 0)
                o << "root:";
            else
                left ? o << "left: " : o << "right:";
            o << node->value << std::endl;
            if (node->LTag != CLUE)
                print_tree(o, node->left(), indent + 1, true);
            if (node->RTag != CLUE)
                print_tree(o, node->right(), indent + 1, false);
        }

        int remove(Node *node) override
        { return 0; }

        BinaryTree <T, Node> &secede(Node *node) override
        { return *this; }

    public:

        class Iterator
        {
        public:
            Node *pt;  // 基于指针
            explicit Iterator(Node *_pt = nullptr) : pt(_pt)
            {}

            T &operator*() const
            {
                return pt->value;
            }

            Iterator &operator=(const Iterator &) = default;

            Iterator &operator++()  // ++Iterator
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

            Iterator &operator--()  // --Iterator
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

            bool operator==(const Iterator &it)
            {
                return pt == it.pt;
            }

            bool operator!=(const Iterator &it)
            {
                return pt != it.pt;
            }
        };

    protected:
        // 头节点
        Node *head;
        // 尾节点
        Node *tail;

        void makeThreaded(Node *_root)
        {
            Node *prev = nullptr;
            head = nullptr;
            _root->traversal([&prev, this](Node *node)
                             {
                                 if (node->LTag == CLUE || node->left() == nullptr)
                                 {
                                     node->LTag = CLUE;
                                     node->left() = prev;
                                     if (!head)
                                     {
                                         head = node;
                                     }
                                 }
                                 if (prev && (prev->right() == nullptr || prev->RTag == CLUE))
                                 {
                                     prev->RTag = CLUE;
                                     prev->right() = node;
                                 }
                                 prev = node;
                             }, 1);
            tail = prev;
        }

    public:
        // 删除默认构造函数
        ThreadedBinaryTree() = delete;

        explicit ThreadedBinaryTree(const T &_root) : BinaryTree<T, Node>(_root)
        { makeThreaded(this->root); }

        ThreadedBinaryTree(int size, const T _values[], const int _in_order[] = nullptr,
                           const int _pre_order[] = nullptr, const int _post_order[] = nullptr)
                : BinaryTree<T, Node>(size, _values, _in_order, _pre_order, _post_order), head(nullptr), tail(nullptr)
        {
            makeThreaded(this->root);
        }

        // 重定义析构函数，避免导致死循环
        ~ThreadedBinaryTree() override
        {
            this->root = nullptr;
            if (this->n != 0)
                for (Iterator next = Iterator(head), present = next++; next.pt != nullptr; present = next++)
                {
                    delete present.pt;
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
        void insert(Node *fa, const T &_value, bool insert_as_left_child)
        {
            Node *node = new Node(_value, fa);
            if (insert_as_left_child)
            {
                if (fa->LTag == CLUE || fa->left() == nullptr)
                {
                    this->n++;
                    fa->left() = node;
                    fa->LTag = !CLUE;
                }
            }
            else
            {
                if (fa->RTag == CLUE || fa->right() == nullptr)
                {
                    this->n++;
                    fa->right() = node;
                    fa->RTag = !CLUE;
                }
            }
            makeThreaded(this->root);
        }

        static Node *previous(Node *node)
        {
            if (node->LTag == CLUE)
            {
                return node->left();
            }
            Node *right = node->left();
            while (right->RTag != CLUE && right->right())
                right = right->right();
            return right;
        }

        static Node *next(Node *node)
        {
            if (node->RTag == CLUE || node->right() == nullptr)
            {
                return node->right();
            }
            Node *left = node->right();
            while (left->LTag != CLUE && left->left())
                left = left->left();
            return left;
        }

        friend std::ostream &operator<<(std::ostream &o, const ThreadedBinaryTree &tree)
        {
            Node *node = tree.root;
            tree.print_tree(o, node, 0, true);
            return o;
        }
    };
}
#define DATA_STRUCTURE_THREADEDBINARYTREE_HPP

#endif //DATA_STRUCTURE_THREADEDBINARYTREE_HPP
