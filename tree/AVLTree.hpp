//
// Created by Peter on 2019/9/27.
//

#ifndef DATA_STRUCTURE_AVLTREE_HPP
#define DATA_STRUCTURE_AVLTREE_HPP

#include "SearchTree.hpp"

#define STATURE(p)          (p ? p->height : 0)
#define FACTOR(x)           (STATURE(x->left())-STATURE(x->right()))
#define AVL_BALANCED(x)     (-2 < FACTOR(x) && FACTOR(x) < 2)
#define PARENT_REFERENCE(x) (x->fa() ? ( (x->fa()->left() == x ? x->fa()->left() : x->fa()->right()) ) : this->root)
#define IS_LCHILD(x)        (x->fa()->left() == x)

namespace pty
{
    template<typename T, typename Node>
    class AVLTree : public SearchTree<T, Node>
    {
    protected:
        // 返回节点左右子树中高度更高的子树根节点
        Node *tallerChild(Node *node)
        {
            if (FACTOR(node) > 0)
                return node->left();
            else if (FACTOR(node) < 0)
                return node->right();
            else
                return (node->fa() ? (node->fa()->left() == node ? node->left() : node->right()) : node->left());
        }
        // 从下到上更新高度
        void updateHeight(Node *node)
        {
            node->height = FACTOR(node) >= 0 ? STATURE(node->left()) + 1 : STATURE(node->right()) + 1;
        }
        // 根据中序遍历顺序修改节点失衡部分，最终结构为b为根节点，a为b左儿子，c为b右儿子，T0、T1为a左右子树，T2、T3为c左右子树
        Node *connect34(Node *a, Node *b, Node *c, Node *T0, Node *T1, Node *T2, Node *T3)
        {
            a->left() = T0;
            if (T0)
                T0->fa() = a;
            a->right() = T1;
            if (T1)
                T1->fa() = a;
            updateHeight(a);

            c->left() = T2;
            if (T2)
                T2->fa() = c;
            c->right() = T3;
            if (T3)
                T3->fa() = c;
            updateHeight(c);

            b->left() = a;
            b->right() = c;
            a->fa() = c->fa() = b;
            updateHeight(b);

            return b;
        }
        // 根据情况进行调整
        Node *rotateAt(Node *node)
        {
            Node *fa = node->fa();
            Node *pa = fa->fa();
            if (IS_LCHILD(fa))
            {
                if (IS_LCHILD(node))  // LL
                {
                    fa->fa() = pa->fa();
                    return connect34(node, fa, pa, node->left(), node->right(), fa->right(), pa->right());
                }
                else  // LR
                {
                    node->fa() = pa->fa();
                    return connect34(fa, node, pa, fa->left(), node->left(), node->right(), pa->right());
                }
            }
            else
            {
                if (!IS_LCHILD(node))  // RR
                {
                    fa->fa() = pa->fa();
                    return connect34(pa, fa, node, pa->left(), fa->left(), node->left(), node->right());
                }
                else  // RL
                {
                    node->fa() = pa->fa();
                    return connect34(pa, node, fa, pa->left(), node->left(), node->right(), fa->right());
                }
            }
        }

    public:

        AVLTree() : SearchTree<T, Node>()
        {}

        explicit AVLTree(const T &_root) : SearchTree<T, Node>(_root)
        {}

        AVLTree(std::initializer_list<T> list) : SearchTree<T, Node>()
        {
            for (auto item:list)
                this->insert(item);
        }

        template<typename CONTAINER>
        explicit AVLTree(CONTAINER container) : SearchTree<T, Node>()
        {
            for (auto iterator = container.begin(); iterator != container.end(); iterator++)
                insert(*iterator);
        }
        // 重载父类插入方法
        void insert(Node *fa, const T &_value, bool insert_as_left_child) override
        {
            insert(_value);
        }
        // 插入节点
        void insert(const T &value) override
        {
            if (!this->n)
            {
                this->bestMatch = this->root = new Node(value);
                this->n++;
                return;
            }
            if (this->search(value))
                return;
            Node *node = new Node(value, this->bestMatch);
            this->bestMatch->get() > node->get() ? this->bestMatch->left() = node : this->bestMatch->right() = node;
            this->n++;
            for (Node *x = this->bestMatch; x; x = x->fa())
            {
                if (!AVL_BALANCED(x))
                {
                    Node *&reference = PARENT_REFERENCE(x);
                    reference = rotateAt(tallerChild(tallerChild(x)));
                    break;
                }
                else
                {
                    updateHeight(x);
                }
            }
        }

        using SearchTree<T, Node>::remove;
        // 删除
        int remove(Node *node) override
        {
            SearchTree<T, Node>::remove(node);
            for (Node *x = this->bestMatch; x; x = x->fa())
            {
                if (!AVL_BALANCED(x))
                {
                    Node *&reference = PARENT_REFERENCE(x);
                    x = reference = rotateAt(tallerChild(tallerChild(x)));
                    updateHeight(x);
                }
            }
            return 1;
        }
    };
}
#endif //DATA_STRUCTURE_AVLTREE_HPP
