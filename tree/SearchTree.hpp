//
// Created by Peter on 2019/9/25.
//

#ifndef DATA_STRUCTURE_SEARCHTREE_HPP
#define DATA_STRUCTURE_SEARCHTREE_HPP

#include "BinaryTree.hpp"
#define PARENT_REFERENCE(x) (x->fa() ? ( (x->fa()->left() == x ? x->fa()->left() : x->fa()->right()) ) : this->root)
#define IS_LCHILD(x)        (x->fa()->left() == x)

namespace pty
{
    /*
     * 二叉搜索树类型，继承二叉树
     * 新增操作：
     * 1.   插入元素
     * 2.   删除元素
     * 3.   搜索元素，返回指针
     * 4.   搜索第k小元素
     * 5.   搜索元素，返回是第几小
     * 支持父类操作包括：
     * 1.   从前序、后序中的一个和中序序列构建树
     * 2.   插入到某节点的左或右儿子节点处 （重载）
     * 3.   删除以位置node节点为根的子树，并返回该子树原先的规模 （重载）
     * 4.   将以node节点为根节点的子树从当前树种摘除，并将其转换为一棵独立的树
     * 5.   返回大小
     * 6.   返回是否为空
     * 7.   重载==运算符，比较两棵树
     * 8.   以凸入表示法打印树*/
    template<typename T, typename Node>
    class SearchTree : protected BinaryTree<T, Node>
    {
    protected:
        Node *bestMatch;

        Node *succ(Node *node)
        {
            Node *succ = node->right();
            while (succ->left())
            {
                succ = succ->left();
            }
            return succ;
        }

        BinaryTree <T, Node> &secede(Node *node) override
        {
            return *this;
        }

        void insert(Node *fa, const T &_value, bool insert_as_left_child) override
        {
            insert(_value);
        }

    public:

        SearchTree() : BinaryTree<T, Node>()
        {}

        explicit SearchTree(const T &_root) : BinaryTree<T, Node>(_root)
        {}

        SearchTree(std::initializer_list<T> list) : BinaryTree<T, Node>()
        {
            for (auto item:list)
                insert(item);
        }

        template<typename CONTAINER>
        explicit SearchTree(CONTAINER container):BinaryTree<T, Node>()
        {
            for (auto iterator = container.begin(); iterator != container.end(); iterator++)
                insert(*iterator);
        }

        SearchTree(int size, const T _values[], const int _in_order[] = nullptr, const int _pre_order[] = nullptr,
                   const int _post_order[] = nullptr)
                : BinaryTree<T, Node>(size, _values, _in_order, _pre_order, _post_order)
        {}


        virtual Node *search(const T &element)
        {
            Node *node = this->root;
            while (node && node->value != element)
            {
                bestMatch = node;
                node = node->value > element ? node->left() : node->right();
            }
            return node;
        }

        // 搜索元素，返回是第几小
        int kth(const T &element)
        {
            Stack<Node *> container({this->root});
            Stack<Node *> visted;
            int kth = 0;
            while (!container.is_empty())
            {
                Node *node = container.pop();
                if (!visted.is_empty() && visted.top() == node)  // 访问过
                {
                    visted.pop();
                    kth++;
                    if (node->value == element)
                        return kth;
                }
                else
                {
                    if (node->right())
                        container.push(node->right());
                    visted.push(node);
                    container.push(node);
                    if (node->left())
                        container.push(node->left());
                }
            }
            return -1;
        }

        // 搜索第k小元素
        Node *find_kth_small(int k)
        {
            Stack<Node *> container({this->root});
            Stack<Node *> visted;
            Node *kth = nullptr;
            while (!container.is_empty() && k)
            {
                Node *node = container.pop();
                if (!visted.is_empty() && visted.top() == node)  // 访问过
                {
                    k--;
                    visted.pop();
                    kth = node;
                }
                else
                {
                    if (node->right())
                        container.push(node->right());
                    visted.push(node);
                    container.push(node);
                    if (node->left())
                        container.push(node->left());
                }
            }
            return kth;
        }


        virtual void insert(const T &value)
        {
            if (!this->n)
            {
                this->root = new Node(value);
                this->n++;
                return;
            }
            if (search(value) != nullptr)
                return;
            Node *node = new Node(value, bestMatch);
            if (node->value < bestMatch->value)
                bestMatch->left() = node;
            else
                bestMatch->right() = node;
            this->n++;
        }

        int remove(const T &value)
        {
            Node *node = search(value);
            if (!node)
                return 0;
            else
                return remove(node);
        }

        int remove(Node *node) override
        {
            Node *succ = nullptr;
            if (node->left() == nullptr)
            {
                succ = node->right();
            }
            else if (node->right() == nullptr)
            {
                succ = node->left();
            }
            else  // 左右子树都存在
            {
                succ = this->succ(node);
                std::swap(succ->value, node->value);
                // 此时还是一棵搜索树
                node = succ;
                if (node->left() == nullptr)
                {
                    succ = node->right();
                }
                else if (node->right() == nullptr)
                {
                    succ = node->left();
                }
            }
            if (succ)
                succ->fa() = node->fa();
            if (node->fa())
                IS_LCHILD(node) ? node->fa()->left() = succ : node->fa()->right() = succ;
            else  // 删除根节点
                this->root = succ;
            this->n--;
            bestMatch = node->fa();
            delete node;
            return 1;
        }

        using BinaryTree<T, Node>::clear;
        using BinaryTree<T, Node>::size;
        using BinaryTree<T, Node>::is_empty;

        friend std::ostream &operator<<(std::ostream &o, const SearchTree<T, Node> &tree)
        {
            return o << (BinaryTree<T, Node> &) tree;
        }
    };
}
#endif //DATA_STRUCTURE_SEARCHTREE_HPP
