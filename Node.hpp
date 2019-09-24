//
// Created by Peter on 2019/9/24.
//

#ifndef DATA_STRUCTURE_NODE_HPP
#define DATA_STRUCTURE_NODE_HPP

namespace pty
{
    template <typename T>
    class BinaryTree;
    template <typename T>
    class ThreadedBinaryTree;
    /*
     * 节点类
     * 重载比较运算符
     * 接口包括前序、中序、后序、层次遍历以该节点为根节点的子树，并对每个节点执行回调函数*/
    template <typename T>
    class Node
    {
        friend class BinaryTree<T>;
        friend class ThreadedBinaryTree<T>;
    protected:
        T value;
        Node* father;
        Node* left_child;
        Node* right_child;
        bool LTag;
        bool RTag;
        explicit Node(T _value, Node* _father=nullptr, Node* _left_child=nullptr, Node* _right_child=nullptr):
                value(_value),father(_father),left_child(_left_child),right_child(_right_child),LTag(false),RTag(false){}
        // 以该节点为根节点进行遍历（前序、中序、后序）
        template <typename F>
        void traversal(F const &callback, int type)
        {
            Stack<Node *>container({this});
            Stack<Node *>visted;
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
        T get() const { return value;}
        bool operator<(const Node& other) const { return value < other.value;}
        bool operator<=(const Node& other) const { return value <= other.value;}
        bool operator>(const Node& other) const { return value > other.value;}
        bool operator>=(const Node& other) const { return value >= other.value;}
        bool operator==(const Node& other) const {return value == other.value;}
        bool operator!=(const Node& other) const {return value != other.value;}
        // 以该节点为根节点进行前序遍历
        template <typename F>
        void traversal_pre(F const &callback){traversal(callback, 0);}
        // 以该节点为根节点进行中序遍历
        template <typename F>
        void traversal_in(F const &callback){traversal(callback, 1);}
        // 以该节点为根节点进行后序遍历
        template <typename F>
        void traversal_post(F const &callback){traversal(callback, 2);}
        // 以该节点为根节点进行层次遍历
        template <typename F>
        void traversal_level(F const &callback)
        {
            Queue<Node*> container({this});
            while (!container.is_empty())
            {
                Node* node = container.pop();
                if(node == nullptr)
                    continue;
                callback(node);
                container.push(node->left_child);
                container.push((node->right_child));
            }
        }
    };
}
#endif //DATA_STRUCTURE_NODE_HPP
