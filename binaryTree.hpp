//
// Created by Peter on 2019/9/19.
//

#ifndef DATA_STRUCTURE_BINARYTREE_HPP
#define DATA_STRUCTURE_BINARYTREE_HPP

#include <iostream>
#include "stack.hpp"

namespace pty
{
    template <typename T>
    class binaryTree
    {
    public:
        class Node
        {
            friend class binaryTree;

        protected:
            T value;
            Node* father;
            Node* left_child;
            Node* right_child;
            explicit Node(T _value, Node* _father=nullptr, Node* _left_child=nullptr, Node* _right_child=nullptr):
                    value(_value),father(_father),left_child(_left_child),right_child(_right_child){}
            // 以该节点为根节点进行遍历（前序、中序、后序）
            void traversal(void (*callback)(Node*), int type)
            {
                stack<Node *>container({this});
                stack<Node *>visted;
                while (!container.is_empty())
                {
                    Node* node = container.pop();
                    if(node != nullptr)
                    {
                        if(!visted.is_empty()&&visted.top()==node)  // 访问过
                        {
                            visted.pop();
                            callback(node);
                        } else
                        {
                            visted.push(node);
                            if(type == 2)
                                container.push(node);
                            container.push(node->right_child);
                            if(type == 1)
                                container.push(node);
                            container.push(node->left_child);
                            if(type == 0)
                                container.push(node);
                        }
                    }
                }
            }

        public:
            T get(){ return value;}
            bool operator<(const Node& other){ return value < other.value;}
            bool operator<=(const Node& other){ return value <= other.value;}
            bool operator>(const Node& other){ return value > other.value;}
            bool operator>=(const Node& other){ return value >= other.value;}
            bool operator==(const Node& other){return value == other.value;}
            bool operator!=(const Node& other){return value != other.value;}
            void traversal_pre(void (*callback)(Node*)){traversal(callback, 0);}
            void traversal_in(void (*callback)(Node*)){traversal(callback, 1);}
            void traversal_post(void (*callback)(Node*)){traversal(callback, 2);}
        };

    protected:
        // 根节点
        Node* root;
        const T* values;
        const int* in_order;
        const int* pre_order;
        const int* post_order;
        int n;
        // 递归以凸入表示法打印树
        void printTree(std::ostream& o, Node* node, int indent, bool left) const
        {
            if(node == nullptr || !n)
                return;
            for(int i = 0; i < indent; i++)
                o<<"\t";
            if(indent == 0)
                o << "root:";
            else
                left ? o << "left: " : o << "right:";
            o<<node->value<<std::endl;
            printTree(o, node->left_child, indent+1, true);
            printTree(o, node->right_child, indent+1, false);
        }
        // 从中序和前序构造
        void build_from_in_pre(bool left, Node* fa, int root_pre, int begin_in, int end_in)
        {
            for(int i = begin_in; i < end_in; i++)
            {
                if(in_order[i] == pre_order[root_pre])
                {
                    Node* node = new Node(values[pre_order[root_pre]], fa);
                    if(fa != nullptr)
                    {
                        left ? fa->left_child = node: fa->right_child = node;
                    } else
                    {
                        root = node;
                    }
                    build_from_in_pre(true, node, root_pre+1, begin_in, i);
                    build_from_in_pre(false, node, root_pre+i-begin_in+1, i+1, end_in);
                }
            }
        }
        // 从中序和后序构造
        void build_from_in_post(bool left, Node* fa, int root_post, int begin_in, int end_in)
        {
            for(int i = begin_in; i < end_in; i++)
            {
                if(in_order[i] == post_order[root_post])
                {
                    Node* node = new Node(values[post_order[root_post]], fa);
                    if(fa != nullptr)
                    {
                        left ? fa->left_child = node: fa->right_child = node;

                    } else
                    {
                        root = node;
                    }
                    build_from_in_post(true, node, root_post-end_in+i, begin_in, i);
                    build_from_in_post(false, node, root_post-1, i+1, end_in);
                }
            }
        }
    public:
        explicit binaryTree(T _root):values(nullptr),pre_order(nullptr),in_order(nullptr),post_order(nullptr),n(1)
        {
            root = new Node(_root);
        }
        // 从前序、后序中的一个和中序序列构建树
        binaryTree(int size, const T _values[], const int _in_order[] = nullptr, const int _pre_order[] = nullptr, const int _post_order[] = nullptr):
                values(_values),pre_order(_pre_order),in_order(_in_order),post_order(_post_order),n(size)
        {
            if(pre_order && in_order)
                build_from_in_pre(true, nullptr, 0, 0, n);
            else if(post_order && in_order)
                build_from_in_post(true, nullptr, n-1, 0, n);
        }
        virtual ~binaryTree()
        {
            traversal_post([](Node* node){delete(node);});
        }
        //  插入到某节点的儿子节点处
        void insert(Node* fa, const T _value, bool insert_as_left_child)
        {
            Node* node = new Node(_value, fa);
            if(insert_as_left_child)
            {
                if(fa->left_child == nullptr)
                    n++;
                fa->left_child = node;
            }
            else
            {
                if(fa->right_child == nullptr)
                    n++;
                fa->right_child = node;
            }
        }
        // 删除以位置node节点为根的子树，并返回该子树原先的规模
        int remove(Node* node)
        {
            int count = 0;
            node->father->left_child == node?node->father->left_child = nullptr:node->father->right_child = nullptr;
            node->traversal_post([&count](Node* node)
                                {
                                    delete(node);
                                    count++;
                                });
            n -= count;
            return count;
        }
        // 将以node节点为根节点的子树从当前树种摘除，并将其转换为一棵独立的树
        binaryTree& secede(Node* node)
        {
            auto new_tree = new binaryTree(root->value);
            int count = 0;
            node->father->left_child == node?node->father->left_child = nullptr:node->father->right_child = nullptr;
            node->father = nullptr;
            node->traversal_post([&count](Node* node)
                                 {
                                     count++;
                                 });
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
            return n==0;
        }

        void traversal_pre(void (*callback)(Node*)=[](Node* node){std::cout<<node->value;}){root->traversal_pre(callback);}
        void traversal_in(void (*callback)(Node*)=[](Node* node){std::cout<<node->value;}){root->traversal_in(callback);}
        void traversal_post(void (*callback)(Node*)=[](Node* node){std::cout<<node->value;}){root->traversal_post(callback);}

        friend std::ostream& operator<<(std::ostream& o, const binaryTree& tree)
        {
            Node* node = tree.root;
            tree.printTree(o, node, 0, true);
            return o;
        }
    };
}
#endif //DATA_STRUCTURE_BINARYTREE_HPP
