//
// Created by Peter on 2019/10/10.
//

#ifndef DATA_STRUCTURE_REDBLACK_HPP
#define DATA_STRUCTURE_REDBLACK_HPP

#include "Node.hpp"
#include "SearchTree.hpp"

namespace pty
{
    template <typename T>  // TODO
    class RedBlack : public SearchTree<T>
    {
        using Node = RedBlackNode<T>;
    protected:
        void solveDoubleRed(Node* node)
        {

        }
        void solveDoubleBlack(Node* node)
        {

        }
        int updateHeight(Node* node)
        {

        }
    public:
        RedBlack() : SearchTree<T, Node>(){}

        explicit RedBlack(const T &_root) : SearchTree<T, Node>(_root){}

        RedBlack(std::initializer_list<T> list) : SearchTree<T, Node>()
        {
            for (auto item:list)
                this->insert(item);
        }

        template<typename CONTAINER>
        explicit RedBlack(CONTAINER container) : SearchTree<T, Node>()
        {
            for (auto iterator = container.begin(); iterator != container.end(); iterator++)
                insert(*iterator);
        }

        PrimitiveNode<T> *search(const T &element) override;

        void insert(const T &value) override;

        int remove(PrimitiveNode<T> *node) override;
    };

    template<typename T>
    void RedBlack<T>::insert(const T &value)
    {

    }

    template<typename T>
    int RedBlack<T>::remove(PrimitiveNode<T> *node)
    {

    }
}

#endif //DATA_STRUCTURE_REDBLACK_HPP
