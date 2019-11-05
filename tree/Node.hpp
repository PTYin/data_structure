//
// Created by Peter on 2019/9/24.
//

#ifndef DATA_STRUCTURE_NODE_HPP
#define DATA_STRUCTURE_NODE_HPP

#define CLUE    true
namespace pty
{
    template<typename T>
    class PrimitiveNode;

    template<typename T>
    class ThreadedNode;

    template<typename T>
    class AVLTreeNode;

    template<typename T>
    class TreapNode;

    template <typename T>
    class RedBlackNode;

    template<typename T, typename Node=PrimitiveNode<T>>
    class BinaryTree;

    template<typename T, typename Node=ThreadedNode<T>>
    class ThreadedBinaryTree;

    template<typename T, typename Node=PrimitiveNode<T>>
    class SearchTree;

    template<typename T, typename Node=PrimitiveNode<T>>
    class HuffmanTree;

    template<typename T, typename Node=AVLTreeNode<T>>
    class AVLTree;

    template<typename T, typename Node=TreapNode<T>>
    class Treap;

    template<typename T, typename Node=PrimitiveNode<T>>
    class Splay;

    template <typename T>  // TODO
    class RedBlack;
    /*
     * 节点类
     * 重载比较运算符
     * 接口包括前序、中序、后序、层次遍历以该节点为根节点的子树，并对每个节点执行回调函数*/
    template<typename T>
    class PrimitiveNode
    {
        using Node = PrimitiveNode<T>;

        friend class BinaryTree<T, Node>;

        friend class SearchTree<T, Node>;

        friend class HuffmanTree<T, Node>;

        friend class Splay<T, Node>;

    protected:
        T value;
        void *father;
        void *left_child;
        void *right_child;

        explicit PrimitiveNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                               void *_right_child = nullptr) :
                value(_value), father(_father), left_child(_left_child), right_child(_right_child)
        {}

    public:
        T& get()
        { return value; }

        PrimitiveNode *&left()
        {
            return (decltype(this) &) left_child;
        }

        PrimitiveNode *&right()
        {
            return (decltype(this) &) right_child;
        }

        PrimitiveNode *&fa()
        {
            return (decltype(this) &) father;
        }

        bool operator<(const Node &other) const
        { return value < other.value; }

        bool operator<=(const Node &other) const
        { return value <= other.value; }

        bool operator>(const Node &other) const
        { return value > other.value; }

        bool operator>=(const Node &other) const
        { return value >= other.value; }

        bool operator==(const Node &other) const
        { return value == other.value; }

        bool operator!=(const Node &other) const
        { return value != other.value; }

        // 以该节点为根节点进行遍历（前序、中序、后序）
        template<typename F>
        void traversal(F const &callback, int type)
        {
            Stack<decltype(this)> container({this});
            Stack<decltype(this)> visited;
            while (!container.is_empty())
            {
                decltype(this) node = container.pop();
                if (!visited.is_empty() && visited.top() == node)  // 访问过
                {
                    visited.pop();
                    callback(node);
                }
                else
                {
                    visited.push(node);
                    if (type == 2)
                        container.push(node);
                    if (node->right_child)
                        container.push(node->right());
                    if (type == 1)
                        container.push(node);
                    if (node->left_child)
                        container.push(node->left());
                    if (type == 0)
                        container.push(node);
                }
            }
        }

        // 以该节点为根节点进行层次遍历
        template<typename F>
        void traversal_level(F const &callback)
        {
            Queue<decltype(this)> container({this});
            while (!container.is_empty())
            {
                decltype(this) node = container.pop();
                if (node == nullptr)
                    continue;
                callback(node);
                container.push(node->left());
                container.push((node->right()));
            }
        }
    };


    template<typename T>
    class ThreadedNode : protected PrimitiveNode<T>
    {
        using Node = ThreadedNode<T>;

        friend class BinaryTree<T, Node>;

        friend class ThreadedBinaryTree<T, Node>;

    public:
        using PrimitiveNode<T>::get;

        ThreadedNode *&fa()
        {
            decltype(this) null = nullptr;
            return (decltype(this) &) null;
        }

        ThreadedNode *&left()
        {
            return (decltype(this) &) this->left_child;
        }

        ThreadedNode *&right()
        {
            return (decltype(this) &) this->right_child;
        }

        template<typename F>
        void traversal(const F &callback, int type)
        {
            Stack<ThreadedNode *> container({this});
            Stack<ThreadedNode *> visted;
            while (!container.is_empty())
            {
                ThreadedNode *node = container.pop();
                if (!visted.is_empty() && visted.top() == node)  // 访问过
                {
                    visted.pop();
                    callback(node);
                }
                else
                {
                    visted.push(node);
                    if (type == 2)
                        container.push(node);
                    if (node->right_child && node->RTag != CLUE)
                        container.push(node->right());
                    if (type == 1)
                        container.push(node);
                    if (node->left_child && node->LTag != CLUE)
                        container.push(node->left());
                    if (type == 0)
                        container.push(node);
                }
            }
        }
    protected:
        bool LTag;
        bool RTag;

        explicit ThreadedNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                              void *_right_child = nullptr) :
                PrimitiveNode<T>(_value, _father, _left_child, _right_child), LTag(false), RTag(false)
        {}
    };

    template<typename T>
    class AVLTreeNode : protected PrimitiveNode<T>
    {
        using Node = AVLTreeNode<T>;

        friend class BinaryTree<T, Node>;

        friend class SearchTree<T, Node>;

        friend class AVLTree<T, Node>;


    protected:

        int height;

        explicit AVLTreeNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                             void *_right_child = nullptr) : PrimitiveNode<T>(_value, _father, _left_child,
                                                                              _right_child), height(1)
        {}

    public:

        using PrimitiveNode<T>::get;

        AVLTreeNode *&left()
        {
            return (decltype(this) &) this->left_child;
        }

        AVLTreeNode *&right()
        {
            return (decltype(this) &) this->right_child;
        }

        AVLTreeNode *&fa()
        {
            return (decltype(this) &) this->father;
        }

        // 以该节点为根节点进行遍历（前序、中序、后序）
        template<typename F>
        void traversal(F const &callback, int type)
        {
            Stack<decltype(this)> container({this});
            Stack<decltype(this)> visited;
            while (!container.is_empty())
            {
                decltype(this) node = container.pop();
                if (!visited.is_empty() && visited.top() == node)  // 访问过
                {
                    visited.pop();
                    callback(node);
                }
                else
                {
                    visited.push(node);
                    if (type == 2)
                        container.push(node);
                    if (node->right_child)
                        container.push(node->right());
                    if (type == 1)
                        container.push(node);
                    if (node->left_child)
                        container.push(node->left());
                    if (type == 0)
                        container.push(node);
                }
            }
        }
    };

    template <typename T>
    class TreapNode : protected PrimitiveNode<T>
    {
        using Node = TreapNode<T>;

        friend class BinaryTree<T, Node>;

        friend class SearchTree<T, Node>;

        friend class Treap<T, Node>; // TODO

    public:

        using PrimitiveNode<T>::get;
        TreapNode *&left()
        {
            return (decltype(this) &) this->left_child;
        }

        TreapNode *&right()
        {
            return (decltype(this) &) this->right_child;
        }

        TreapNode *&fa()
        {
            return (decltype(this) &) this->father;
        }

        // 以该节点为根节点进行遍历（前序、中序、后序）
        template<typename F>
        void traversal(F const &callback, int type)
        {
            Stack<decltype(this)> container({this});
            Stack<decltype(this)> visited;
            while (!container.is_empty())
            {
                decltype(this) node = container.pop();
                if (!visited.is_empty() && visited.top() == node)  // 访问过
                {
                    visited.pop();
                    callback(node);
                }
                else
                {
                    visited.push(node);
                    if (type == 2)
                        container.push(node);
                    if (node->right_child)
                        container.push(node->right());
                    if (type == 1)
                        container.push(node);
                    if (node->left_child)
                        container.push(node->left());
                    if (type == 0)
                        container.push(node);
                }
            }
        }

    protected:
        int key;
        explicit TreapNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                             void *_right_child = nullptr) : PrimitiveNode<T>(_value, _father, _left_child,
                                                                              _right_child),key(rand())
        {}

    };

    typedef enum {RED, BLACK} Color;

    template <typename T>
    class RedBlackNode :  protected AVLTreeNode<T>
    {
        using Node = RedBlackNode<T>;

        friend class BinaryTree<T, Node>;

        friend class SearchTree<T, Node>;

        friend class RedBlack<T>; // TODO

    protected:

        Color color;
        explicit RedBlackNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                           void *_right_child = nullptr) : AVLTreeNode<T>(_value, _father, _left_child,
                                                                            _right_child),color(RED)
        {}

        Node *&left()
        {
            return (decltype(this) &) this->left_child;
        }

        Node *&right()
        {
            return (decltype(this) &) this->right_child;
        }

        Node *&fa()
        {
            return (decltype(this) &) this->father;
        }

        // 以该节点为根节点进行遍历（前序、中序、后序）
        template<typename F>
        void traversal(F const &callback, int type)
        {
            Stack<decltype(this)> container({this});
            Stack<decltype(this)> visited;
            while (!container.is_empty())
            {
                decltype(this) node = container.pop();
                if (!visited.is_empty() && visited.top() == node)  // 访问过
                {
                    visited.pop();
                    callback(node);
                }
                else
                {
                    visited.push(node);
                    if (type == 2)
                        container.push(node);
                    if (node->right_child)
                        container.push(node->right());
                    if (type == 1)
                        container.push(node);
                    if (node->left_child)
                        container.push(node->left());
                    if (type == 0)
                        container.push(node);
                }
            }
        }
    };
}
#endif //DATA_STRUCTURE_NODE_HPP
