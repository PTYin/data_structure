//
// Created by Peter on 2019/9/19.
//

#ifndef DATA_STRUCTURE_BINARYTREE_HPP
#define DATA_STRUCTURE_BINARYTREE_HPP

#include <iostream>
#include "../Stack.hpp"
#include "../Queue.hpp"
#include "Node.hpp"

namespace pty
{
    /*
     * 二叉树类型
     * 支持操作包括：
     * 1.   从前序、后序中的一个和中序序列构建树
     * 2.   插入到某节点的左或右儿子节点处
     * 3.   删除以位置node节点为根的子树，并返回该子树原先的规模
     * 4.   将以node节点为根节点的子树从当前树种摘除，并将其转换为一棵独立的树
     * 5.   返回大小
     * 6.   返回是否为空
     * 7.   重载==运算符，比较两棵树
     * 8.   以凸入表示法打印树
     * 9.   前序、中序、后序遍历树*/
    template<typename T, class Node>
    class BinaryTree
    {
    private:
        // 递归以凸入表示法打印树
        void print_tree(std::ostream &o, Node *node, int indent, bool left) const
        {
            if (node == nullptr || !n)
                return;
            for (int i = 0; i < indent; i++)
                o << "\t";
            if (indent == 0)
                o << "root:";
            else
                left ? o << "left: " : o << "right:";
            o << node->value << std::endl;
//            if (node->LTag != CLUE)
            print_tree(o, node->left(), indent + 1, true);
//            if (node->RTag != CLUE)
            print_tree(o, node->right(), indent + 1, false);
        }

    protected:
        // 隐藏默认构造函数
        explicit BinaryTree() : root(nullptr), values(nullptr), pre_order(nullptr), in_order(nullptr),
                                post_order(nullptr), n(0)
        {}

        // 根节点
        Node *root;
        const T *values;
        const int *in_order;
        const int *pre_order;
        const int *post_order;
        int n;

        // 从中序和前序构造
        void build_from_in_pre(bool left, Node *fa, int root_pre, int begin_in, int end_in)
        {
            for (int i = begin_in; i < end_in; i++)
            {
                if (in_order[i] == pre_order[root_pre])
                {
                    Node *node = new Node(values[pre_order[root_pre]], fa);
                    if (fa != nullptr)
                    {
                        left ? fa->left() = node : fa->right() = node;
                    }
                    else
                    {
                        root = node;
                    }
                    build_from_in_pre(true, node, root_pre + 1, begin_in, i);
                    build_from_in_pre(false, node, root_pre + i - begin_in + 1, i + 1, end_in);
                }
            }
        }

        // 从中序和后序构造
        void build_from_in_post(bool left, Node *fa, int root_post, int begin_in, int end_in)
        {
            for (int i = begin_in; i < end_in; i++)
            {
                if (in_order[i] == post_order[root_post])
                {
                    Node *node = new Node(values[post_order[root_post]], fa);
                    if (fa != nullptr)
                    {
                        left ? fa->left() = node : fa->right() = node;

                    }
                    else
                    {
                        root = node;
                    }
                    build_from_in_post(true, node, root_post - end_in + i, begin_in, i);
                    build_from_in_post(false, node, root_post - 1, i + 1, end_in);
                }
            }
        }

    public:
        explicit BinaryTree(T _root) : values(nullptr), pre_order(nullptr), in_order(nullptr), post_order(nullptr), n(1)
        {
            root = new Node(_root);
        }

        // 从前序、后序中的一个和中序序列构建树
        BinaryTree(int size, const T _values[], const int _in_order[] = nullptr, const int _pre_order[] = nullptr,
                   const int _post_order[] = nullptr) :
                values(_values), pre_order(_pre_order), in_order(_in_order), post_order(_post_order), n(size)
        {
            if (pre_order && in_order)
                build_from_in_pre(true, nullptr, 0, 0, n);
            else if (post_order && in_order)
                build_from_in_post(true, nullptr, n - 1, 0, n);
        }

        virtual ~BinaryTree()
        {
            traversal_post([](Node *node)
                           { delete (node); });
        }

        //  插入到某节点的儿子节点处
        virtual void insert(Node *fa, const T &_value, bool insert_as_left_child)
        {
            Node *node = new Node(_value, fa);
            if (insert_as_left_child)
            {
                if (fa->left() == nullptr)
                    n++;
                fa->left() = node;
            }
            else
            {
                if (fa->right() == nullptr)
                    n++;
                fa->right() = node;
            }
        }

        // 删除以位置node节点为根的子树，并返回该子树原先的规模
        virtual int remove(Node *node)
        {
            int count = 0;
            if (node->fa())
                node->fa()->left() == node ? node->fa()->left() = nullptr : node->fa()->right() = nullptr;
            node->traversal([&count](Node *node)
                            {
                                delete (node);
                                count++;
                            }, 2);
            n -= count;
            return count;
        }

        // 将以node节点为根节点的子树从当前树种摘除，并将其转换为一棵独立的树
        virtual BinaryTree &secede(Node *node)
        {
            auto new_tree = new BinaryTree(root->value);
            int count = 0;
            if (node->fa())
                node->fa()->left() == node ? node->fa()->left() = nullptr : node->fa()->right() = nullptr;
            node->fa() = nullptr;
            node->traversal([&count](Node *node)
                            {
                                count++;
                            }, 2);
            n -= count;
            new_tree->root = node;
            new_tree->n = count;
            return *new_tree;
        }

        int size() const
        {
            return n;
        }

        bool is_empty() const
        {
            return n == 0;
        }

        template<typename F>
        void traversal_pre(F const &callback)
        { if (root)root->traversal(callback, 0); }

        template<typename F>
        void traversal_in(F const &callback)
        { if (root)root->traversal(callback, 1); }

        template<typename F>
        void traversal_post(F const &callback)
        { if (root)root->traversal(callback, 2); }

        template<typename F>
        void traversal_level(F const &callback)
        { if (root)root->traversal_level(callback); }

        bool operator==(BinaryTree &other)
        {
            if (n != other.size())
                return false;
            Queue<Node *> comparator;
            bool ans = true;
            root->traversal_level([&comparator](Node *node)
                                  {
                                      comparator.push(node);
                                  });
            other.traversal_level([&](Node *node)
                                  {
                                      if (!comparator.is_empty())
                                      {
                                          if (*node != *comparator.pop())
                                              ans = false;
                                      }
                                      else
                                      {
                                          ans = false;
                                      }
                                  });
            return ans;
        }

        friend std::ostream &operator<<(std::ostream &o, const BinaryTree &tree)
        {
            Node *node = tree.root;
            tree.print_tree(o, node, 0, true);
            return o;
        }
    };
}
#endif //DATA_STRUCTURE_BINARYTREE_HPP
