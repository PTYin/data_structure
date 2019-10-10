//
// Created by Peter on 2019/10/9.
//

#ifndef DATA_STRUCTURE_SPLAY_HPP
#define DATA_STRUCTURE_SPLAY_HPP
#include "Node.hpp"
#include "SearchTree.hpp"


namespace pty
{
    template <typename T, typename Node>
    class Splay : public SearchTree<T, Node>
    {
    private:
        void attachAsLChild(Node* parent, Node* lc)
        {
            parent->left() = lc;
            if(lc) lc->fa() = parent;
        }
        void attachAsRChild(Node* parent, Node* rc)
        {
            parent->right() = rc; if(rc) rc->fa() = parent;
        }
    protected:

        int remove(Node *node) override
        {
            //assert: node == this->root
            if(node->left() == nullptr)
            {
                this->root = node->right();
                if(this->root)
                    node->right()->fa() = nullptr;
            }
            else if(node->right() == nullptr)
            {
                this->root = node->left();
                if(this->root)
                    node->left()->fa() = nullptr;
            }
            else
            {
                Node *leftTree = node->left();
                node->left() = nullptr;
                leftTree->fa() = nullptr;
                this->root = node->right();
                this->root->fa() = nullptr;
                search(node->get());
                this->root->left() = leftTree;
                leftTree->fa() = this->root;
            }
            delete node;
            this->n--;
            return 1;
        }

        Node *splay(Node* node)
        {
            if(!node)
                return nullptr;
            Node *fa;
            Node *pa;
            Node *pafa;
            while((fa = node->fa()) && (pa = fa->fa()))
            {
                pafa = pa->fa();
                if(IS_LCHILD(node))
                {
                    if(IS_LCHILD(fa))  // LL
                    {
                        attachAsLChild(pa, fa->right());
                        attachAsLChild(fa, node->right());
                        attachAsRChild(fa, pa);
                        attachAsRChild(node, fa);
                    }
                    else  // LR
                    {
                        attachAsLChild(fa, node->right());
                        attachAsRChild(pa, node->left());
                        attachAsLChild(node, pa);
                        attachAsRChild(node, fa);
                    }
                }
                else
                {
                    if(!IS_LCHILD(fa))  // RR
                    {
                        attachAsRChild(pa, fa->left());
                        attachAsRChild(fa, node->left());
                        attachAsLChild(fa, pa);
                        attachAsLChild(node, fa);
                    }
                    else  // RL
                    {
                        attachAsRChild(fa, node->left());
                        attachAsLChild(pa, node->right());
                        attachAsRChild(node, pa);
                        attachAsLChild(node, fa);
                    }
                }
                if(!pafa)
                    node->fa() = nullptr;
                else
                    pa == pafa->left() ? attachAsLChild(pafa, node) : attachAsRChild(pafa, node);
            }
            if((fa = node->fa()) != nullptr)
            {
                if(IS_LCHILD(node))
                {
                    attachAsLChild(fa, node->right());
                    attachAsRChild(node, fa);
                }
                else
                {
                    attachAsRChild(fa, node->left());
                    attachAsLChild(node, fa);
                }
            }
            node->fa() = nullptr;
            return node;

        }

    public:

        Splay() : SearchTree<T, Node>(){}

        explicit Splay(const T &_root) : SearchTree<T, Node>(_root){}

        Splay(std::initializer_list<T> list) : SearchTree<T, Node>()
        {
            for (auto item:list)
                this->insert(item);
        }

        template<typename CONTAINER>
        explicit Splay(CONTAINER container) : SearchTree<T, Node>()
        {
            for (auto iterator = container.begin(); iterator != container.end(); iterator++)
                insert(*iterator);
        }

        Node *search(const T &element) override
        {
            Node *node = SearchTree<T, Node>::search(element);
            this->root = splay(node ? node : this->bestMatch);
            return this->root;
        }

        void insert(const T &value) override
        {
            if(!this->root)
            {
                this->n++;
                this->root = new Node(value);
                return;
            }
            if( value == search(value)->get())
                return;
            this->n++;
            Node *node = this->root;
            if(this->root->get() < value)  // 插入到原root右上
            {
                node->fa() = this->root = new Node(value, nullptr, node, node->right());
                if(node->right() != nullptr)
                {
                    node->right()->fa() = this->root;
                    node->right() = nullptr;
                }
            }
            else  // 插入到原root左上
            {
                node->fa() = this->root = new Node(value, nullptr, node->left(), node);
                if(node->left() != nullptr)
                {
                    node->left()->fa() = this->root;
                    node->left() = nullptr;
                }
            }
        }


        using SearchTree<T, Node>::remove;

    };

}
#endif //DATA_STRUCTURE_SPLAY_HPP
