//
// Created by peter on 19-9-6.
//

#ifndef DATA_STRUCTURE_STACK_HPP
#define DATA_STRUCTURE_STACK_HPP

#include "DoubleLinkedList.hpp"

namespace pty
{
    template<typename T>
    class Stack : protected DoubleLinkedList<T>
    {
        using Node = typename DoubleLinkedList<T>::Node;
        using iterator = typename DoubleLinkedList<T>::iterator;
    public:
        Stack() : DoubleLinkedList<T>()
        {}

        Stack(std::initializer_list<T> list) : DoubleLinkedList<T>(list)
        {}  // 给定列表依次入栈
        void push(T _data)  // 推入栈中
        {
            this->push_back(_data);
        }

        void push_all(std::initializer_list<T> list)
        {
            for (auto element:list)
            {
                push(element);
            }
        }

        T pop()  // 弹出
        {
            return this->pop_back();
        }

        T top() const  // 获得栈顶元素
        {
            return *(this->back());
        }

        void clear()
        {
            DoubleLinkedList<T>::clear();
        }

        unsigned int size() const
        {
            return this->length;
        }

        bool is_empty() const
        {
            return this->length == 0;
        }

        friend std::ostream &operator<<(std::ostream &io, const Stack &stack)
        {
            io << "[ ";
            if (stack.length != 0)
                for (auto element:stack)
                {
                    io << element << " | ";
                }
            return io;
        }
    };
}

#endif //DATA_STRUCTURE_STACK_HPP
