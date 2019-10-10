//
// Created by Peter on 2019/10/8.
//

#ifndef DATA_STRUCTURE_TREAP_HPP
#define DATA_STRUCTURE_TREAP_HPP

#include "Node.hpp"
#include "SearchTree.hpp"

namespace pty
{
    template <typename T, typename Node>
    class Treap : public SearchTree<T, Node>  // TODO
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
            o << "(" << node->key << "," << node->value << ")" << std::endl;
            print_tree(o, node->left(), indent + 1, true);
            print_tree(o, node->right(), indent + 1, false);
        }
    protected:
        void zag(Node* node)
        {
            Node *rChild = node->right();
            node->right() = rChild->left();

            PARENT_REFERENCE(node) = rChild;
            rChild->fa() = node->fa();

            node->fa() = rChild;
            rChild->left() = node;

            if(node->right())
                node->right()->fa() = node;
        }

        void zig(Node* node)
        {
            Node *lChild = node->left();
            node->left() = lChild->right();

            PARENT_REFERENCE(node) = lChild;
            lChild->fa() = node->fa();

            node->fa() = lChild;
            lChild->right() = node;

            if(node->left())
                node->left()->fa() = node;
        }

        void percolateUp(Node* node)
        {
            while(node->fa() && node->key < node->fa()->key)
                IS_LCHILD(node) ? zig(node->fa()) : zag(node->fa());
        }

    public:

        Treap() : SearchTree<T, Node>(){}

        explicit Treap(const T &_root) : SearchTree<T, Node>(_root){}

        Treap(std::initializer_list<T> list) : SearchTree<T, Node>()
        {
            for (auto item:list)
                this->insert(item);
        }

        template<typename CONTAINER>
        explicit Treap(CONTAINER container) : SearchTree<T, Node>()
        {
            for (auto iterator = container.begin(); iterator != container.end(); iterator++)
                insert(*iterator);
        }

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
            this->n++;
            Node* node = new Node(value, this->bestMatch);
            node->value < this->bestMatch->value ? this->bestMatch->left() = node : this->bestMatch->right() = node;
            percolateUp(node);
        }

        int remove(Node *node) override
        {
            if (!this->size())
                return 0;

            while (node->left() && node->right())
                node->left()->key < node->right()->key ? zig(node) : zag(node);

            if (!node->left() && !node->right())  // 没有左右儿子
            {
                PARENT_REFERENCE(node) = nullptr;
                this->n--;
                delete node;
            }
            else if (!node->right())  // 只有左儿子
            {
                this->n--;
                PARENT_REFERENCE(node) = node->left();
                node->left()->fa() = node->fa();
                delete node;
            }
            else if (!node->left())  // 只有右儿子
            {
                this->n--;
                PARENT_REFERENCE(node) = node->right();
                node->right()->fa() = node->fa();
                delete node;
            }
            return 1;
        }

        using SearchTree<T, Node>::remove;

        friend std::ostream &operator<<(std::ostream &o, const Treap &tree)
        {
            Node *node = tree.root;
            tree.print_tree(o, node, 0, true);
            return o;
        }
    };
}
#endif //DATA_STRUCTURE_TREAP_HPP
