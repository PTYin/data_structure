//
// Created by peter on 19-9-6.
//

#ifndef DATA_STRUCTURE_STACK_HPP
#define DATA_STRUCTURE_STACK_HPP

#include "doubleLinkedList.hpp"

namespace pty
{
    template <typename T>
    class stack:protected doubleLinkedList<T>
    {
        using Node = typename doubleLinkedList<T>::Node;
        using iterator = typename doubleLinkedList<T>::iterator;
    public:
        stack():doubleLinkedList<T>(){}
        stack(std::initializer_list<T> list):doubleLinkedList<T>(list){}  // 给定列表依次入栈
        void push(T _data)  // 推入栈中
        {
            this->push_back(_data);
        }
        void push_all(std::initializer_list<T> list)
        {
            for(auto element:list)
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
            doubleLinkedList<T>::clear();
        }
        unsigned int size() const
        {
            return this->length;
        }

        bool is_empty() const
        {
            return this->length==0;
        }
        friend std::ostream& operator<<(std::ostream& io, const stack& stack)
        {
            io<<"[ ";
            if(stack.length != 0)
                for(auto element:stack)
                {
                    io<<element<<" | ";
                }
            return io;
        }
    };
}

#endif //DATA_STRUCTURE_STACK_HPP
