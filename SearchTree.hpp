//
// Created by Peter on 2019/9/25.
//

#ifndef DATA_STRUCTURE_SEARCHTREE_HPP
#define DATA_STRUCTURE_SEARCHTREE_HPP

#include "BinaryTree.hpp"

namespace pty
{
    template<typename T>
    class SearchTree : public BinaryTree<T>
    {
        using Node = Node<T>;
    protected:
        Node *bestMatch;
        Node* succ(Node* node)
        {
            Node* succ = node->right_child;
            while (succ->left_child)
            {
                succ = succ->left_child;
            }
            return succ;
        }
    public:
        explicit SearchTree(const T &_root) : BinaryTree<T>(_root)
        {}

        SearchTree(std::initializer_list<T> list) : BinaryTree<T>(list[0])
        {
            for (auto item:list)
                this->insert(item);
        }

        template<typename CONTAINER>
        explicit SearchTree(CONTAINER container):BinaryTree<T>(container[0])
        {
            for (auto iterator = container.begin(); iterator != container.end(); iterator++)
                insert(*iterator);
        }

        SearchTree(int size, const T _values[], const int _in_order[] = nullptr, const int _pre_order[] = nullptr,
                   const int _post_order[] = nullptr)
                : BinaryTree<T>(size, _values, _in_order, _pre_order, _post_order)
        {}

        virtual Node *search(const T &element)
        {
            Node *node = this->root;
            while (node && node->value != element)
            {
                bestMatch = node;
                node = node->value > element ? node->left_child : node->right_child;
            }
            return node;
        }

        Node* find_kth_small(int k)
        {
            Stack<Node *> container({this->root});
            Stack<Node *> visted;
            Node* kth = nullptr;
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
                    if (node->right_child)
                        container.push(node->right_child);
                    visted.push(node);
                    container.push(node);
                    if (node->left_child)
                        container.push(node->left_child);
                }
            }
            return kth;
        }

        void insert(Node *fa, const T &_value, bool insert_as_left_child) override
        {
            insert(_value);
        }

        SearchTree<T> &secede(Node *node) override
        {
            auto new_tree = new SearchTree(this->root->value);
            int count = 0;
            node->father->left_child == node ? node->father->left_child = nullptr : node->father->right_child = nullptr;
            node->father = nullptr;
            node->traversal_post([&count](Node *node)
                                 {
                                     count++;
                                 });
            this->n -= count;
            new_tree->root = node;
            new_tree->n = count;
            return *new_tree;
        }

        virtual void insert(const T &value)
        {
            if (search(value) != nullptr)
                return;
            Node *node = new Node(value, bestMatch);
            if (node->value < bestMatch->value)
                bestMatch->left_child = node;
            else
                bestMatch->right_child = node;
            this->n++;
        }

        int remove(Node *node) override
        {
            Node *succ = nullptr;
            if (node->left_child == nullptr)
            {
                succ = node->right_child;
            }
            else if (node->right_child == nullptr)
            {
                succ = node->left_child;
            }
            else  // 左右子树都存在
            {
                succ = this->succ(node);
                std::swap(succ->value, node->value);
                // 此时还是一棵搜索树
                node = succ;
                if (node->left_child == nullptr)
                {
                    succ = node->right_child;
                }
                else if (node->right_child == nullptr)
                {
                    succ = node->left_child;
                }
            }
            if (succ)
                succ->father = node->father;
            if (node->father)
                node->father->left_child == node ? node->father->left_child = succ : node->father->right_child = succ;
            else  // 删除根节点
                this->root = succ;
            this->n--;
            delete node;
            return 1;
        }
    };
}
#endif //DATA_STRUCTURE_SEARCHTREE_HPP
