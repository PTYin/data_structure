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

    template <typename T>
    class ThreadedNode;

    template<typename T, typename Node=PrimitiveNode<T>>
    class BinaryTree;

    template<typename T, typename Node=ThreadedNode<T>>
    class ThreadedBinaryTree;

    template<typename T, typename Node=PrimitiveNode<T>>
    class SearchTree;

    template<typename T, typename Node=PrimitiveNode<T>>
    class HuffmanTree;

    /*
     * 节点类
     * 重载比较运算符
     * 接口包括前序、中序、后序、层次遍历以该节点为根节点的子树，并对每个节点执行回调函数*/
    template<typename T>
    class PrimitiveNode
    {
        using Node = PrimitiveNode<T>;
        
        friend class BinaryTree<T, Node>;

        friend class ThreadedBinaryTree<T, Node>;

        friend class SearchTree<T, Node>;

        friend class HuffmanTree<T, Node>;

    protected:
        T value;
        void *father;
        void *left_child;
        void *right_child;

        explicit PrimitiveNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                               void *_right_child = nullptr) :
                value(_value), father(_father), left_child(_left_child), right_child(_right_child)
        {}

         // 以该节点为根节点进行遍历（前序、中序、后序）
        template<typename F>
        void traversal(F const &callback, int type)
        {
            Stack<decltype(this)> container({this});
            Stack<decltype(this)> visted;
            while (!container.is_empty())
            {
                decltype(this) node = container.pop();
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

    public:
        T get() const
        { return value; }

        auto left() -> decltype(this)&
        {
            return (decltype(this)&)left_child;
        }

        auto right() -> decltype(this)&
        {
            return (decltype(this)&)right_child;
        }

        auto fa() -> decltype(this)&
        {
            return (decltype(this)&)father;
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

        // 以该节点为根节点进行前序遍历
        template<typename F>
        void traversal_pre(F const &callback)
        { traversal(callback, 0); }

        // 以该节点为根节点进行中序遍历
        template<typename F>
        void traversal_in(F const &callback)
        { traversal(callback, 1); }

        // 以该节点为根节点进行后序遍历
        template<typename F>
        void traversal_post(F const &callback)
        { traversal(callback, 2); }

        // 以该节点为根节点进行层次遍历
        template<typename F>
        void traversal_level(F const &callback)
        {
            Queue<decltype(this)> container({this});
            while (!container.is_empty())
            {
                decltype(this)node = container.pop();
                if (node == nullptr)
                    continue;
                callback(node);
                container.push(node->left());
                container.push((node->right()));
            }
        }
    };

    template <typename T>
    class ThreadedNode
    {
        using Node = ThreadedNode<T>;

        friend class BinaryTree<T, Node>;

        friend class ThreadedBinaryTree<T, Node>;

        friend class SearchTree<T, Node>;

        friend class HuffmanTree<T, Node>;

    protected:
        T value;
        void *father;
        void *left_child;
        void *right_child;

        bool LTag;
        bool RTag;
        explicit ThreadedNode(const T &_value, void *_father = nullptr, void *_left_child = nullptr,
                              void *_right_child = nullptr) :
                value(_value), father(nullptr), left_child(_left_child), right_child(_right_child),
                LTag(false), RTag(false){}

        // 以该节点为根节点进行遍历（前序、中序、后序）
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

    public:
        T get() const
        { return value; }

        auto fa() -> decltype(this)&
        {
            decltype(this) null = nullptr;
            return (decltype(this)&) null;
        }

        auto left() -> decltype(this)&
        {
            return (decltype(this)&)left_child;
        }

        auto right() -> decltype(this)&
        {
            return (decltype(this)&)right_child;
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

        // 以该节点为根节点进行中序遍历
        template<typename F>
        void traversal_in(F const &callback)
        { traversal(callback, 1); }

        // 以该节点为根节点进行后序遍历
        template<typename F>
        void traversal_post(F const &callback)
        { traversal(callback, 2); }
    };
}
#endif //DATA_STRUCTURE_NODE_HPP
