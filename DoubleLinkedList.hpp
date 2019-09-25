//
// Created by peter on 19-9-5.
//
#ifndef DATA_STRUCTURE_DOUBLELINKEDLIST_HPP
#define DATA_STRUCTURE_DOUBLELINKEDLIST_HPP

#include <iostream>
#include <initializer_list>

namespace pty
{
/*
 * 双向链表类容器*/
    template<typename T>
    class DoubleLinkedList
    {
    protected:
        /*
         * 节点类*/
        struct Node
        {
            T data;  // 数据
            Node *prev;  // 前节点
            Node *next;  // 后节点
            explicit Node(T _data, Node *_prev = nullptr, Node *_next = nullptr) : data(_data), prev(_prev), next(_next)
            {}

            /*
             * 数据，前节点和后节点分别相等认为两个节点相等*/
            bool operator==(const Node *other)
            {
                return data == other->data && prev == other->prev && next == other->next;
            }

        public:
            T value()
            {
                return data;
            }
        };

    public:
        /*
         * 迭代器
         * 在Node类不可见的前提下用来代替指针实现对节点的访问
         * 实现算法独立于使用的容器类型，兼容range-based型for循环
         * 将doubleLinkedList设置为iterator的友元类以调用指针*/
        class iterator
        {
        protected:
            Node *pt;  // 基于指针
            friend class DoubleLinkedList;

        public:
            explicit iterator(Node *_pt = nullptr) : pt(_pt)
            {}

            T &operator*() const
            {
                return pt->data;
            }

            iterator &operator=(const iterator &) = default;

            iterator &operator++()  // ++Iterator
            {
                pt = pt->next;
                return *this;
            }

            iterator operator++(int)   // Iterator++
            {
                iterator tmp = *this;
                pt = pt->next;
                return tmp;
            }

            iterator &operator--()  // --Iterator
            {
                pt = pt->prev;
                return *this;
            }

            iterator operator--(int)  // Iterator--
            {
                iterator tmp = *this;
                pt = pt->prev;
                return tmp;
            }

            bool operator==(const iterator &it)
            {
                return pt == it.pt;
            }

            bool operator!=(const iterator &it)
            {
                return pt != it.pt;
            }
        };

    protected:
        iterator it_head;  // 头指针 i.e. 头迭代器
        iterator it_tail;  // 尾指针 i.e. 尾迭代器
        int length;  // 容器内元素长度

    public:
        DoubleLinkedList() : it_head(nullptr), it_tail(nullptr), length(0)
        {}

        DoubleLinkedList(std::initializer_list<T> list)  // 可变长度参数列表，初始化时同时加入到容器中
        {
            length = list.size();
            typename std::initializer_list<T>::iterator it = list.begin();
            it_tail.pt = it_head.pt = new Node(*it);
            it++;
            for (; it != list.end(); it++)
            {
                Node *present = new Node(*it, it_tail.pt);
                it_tail.pt->next = present;
                it_tail++;
            }
        }

        virtual ~DoubleLinkedList()  // 释放容器中所有node指针
        {
            if (length != 0)
                for (iterator next = it_head, present = next++; next.pt != nullptr; present = next++)
                {
                    delete present.pt;
                }
            delete it_tail.pt;
        }

        /*
         * 提供range-based for所需的成员函数begin()和end()*/
        iterator begin() const
        {
            return it_head;
        }

        iterator end() const
        {
            return iterator(nullptr);
        }

        const iterator &front() const  // 返回头迭代器
        {
            return it_head;
        }

        const iterator &back() const  // 返回尾迭代器
        {
            return it_tail;
        }

        unsigned int size() const
        {
            return length;
        }

        void clear()  // 释放容器中所有node指针，将类内属性赋值
        {
            if (length != 0)
                for (iterator next = it_head, present = next++; next.pt != nullptr; present = next++)
                {
                    delete present.pt;
                }
            delete it_tail.pt;
            it_head.pt = it_tail.pt = nullptr;
            length = 0;
        }

        void remove(iterator it_node)  // 删除某节点
        {
            if (it_node.pt == nullptr) return;
            if (it_node.pt->prev != nullptr)
                it_node.pt->prev = it_node.pt->next;
            if (it_node.pt->next != nullptr)
                it_node.pt->next = it_node.pt->prev;
        }

        bool is_empty() const
        {
            return length == 0;
        }

        void push_front(T _data)  // 从头部添加元素
        {
            if (length == 0)
            {
                it_head.pt = it_tail.pt = new Node(_data);
            }
            else
            {
                it_head.pt->prev = new Node(_data, nullptr, it_head.pt);
                it_head--;
            }
            length++;
        }

        T pop_front()  // 从头部弹出元素
        {
            if (length == 0)
                throw "No element in list!";
            else if (length == 1)
            {
                length = 0;
                T temp = *it_head;
                delete it_head.pt;
                it_head.pt = it_tail.pt = nullptr;
                return temp;
            }
            else
            {
                length--;
                T temp = *it_head;
                Node *temp_pt = it_head.pt;
                (++it_head).pt->prev = nullptr;
                delete temp_pt;
                return temp;
            }
        }

        void push_back(T _data)  // 从尾部添加元素
        {
            if (length == 0)
            {
                it_head.pt = it_tail.pt = new Node(_data);
            }
            else
            {
                it_tail.pt->next = new Node(_data, it_tail.pt);
                it_tail++;
            }
            length++;
        }

        T pop_back()  // 从尾部弹出元素
        {
            if (length == 0)
                throw "No element in list!";
            else if (length == 1)
            {
                length = 0;
                T temp = *it_head;
                delete it_head.pt;
                it_head.pt = it_tail.pt = nullptr;
                return temp;
            }
            else
            {
                length--;
                T temp = *it_tail;
                Node *temp_pt = it_tail.pt;
                (--it_tail).pt->next = nullptr;
                delete temp_pt;
                return temp;
            }
        }

        T get_by_index(unsigned int index) const  // 根据索引返回数据
        {
            if (index >= length)
                throw "Index out of bound!";
            iterator it = it_head;
            while (index--)
                it++;
            return *it;
        }

        void modify(iterator it, T _data)  // 修改某一元素
        {
            *it = _data;
        }

        int find_first_index(T _data) const  // 查找某个数据出现的第一个位置，返回索引
        {
            if (length == 0)
                return -1;
            int index = 0;
            for (auto to_find : *this)
            {
                if (to_find == _data)
                    return index;
                index++;
            }
            return -1;
        }

        int find_last_index(T _data) const  // 查找某个数据出现的最后一个位置，返回索引
        {
            if (length == 0)
                return -1;
            int index = length - 1;
            for (iterator it = it_tail; it != it_head; it--)
            {
                if (*it == _data)
                    return index;
                index--;
            }
            if (*it_head == _data)
                return 0;
            else
                return -1;
        }

        iterator find_first(T _data) const  // 查找某个数据出现的第一个位置
        {
            if (length == 0)
                return iterator(nullptr);
            iterator it = it_head;
            for (auto to_find : *this)
            {
                if (to_find == _data)
                    return it;
                it++;
            }
            return iterator(nullptr);
        }

        iterator find_last(T _data) const  // 查找某个数据出现的最后一个位置
        {
            if (length == 0)
                return iterator(nullptr);
            for (iterator it = it_tail; it != it_head; it--)
            {
                if (*it == _data)
                    return it;
            }
            if (*it_head == _data)
                return it_head;
            else
                return iterator(nullptr);
        }

        void insert_after(iterator it_node, T _data)  // 在某元素之后插入
        {
            if (it_node.pt == nullptr)
                return;
            Node *node_ptr = new Node(_data, it_node.pt, it_node.pt->next);
            if (it_node.pt->next != nullptr)
                it_node.pt->next->prev = node_ptr;
            else
                it_tail.pt = node_ptr;
            it_node.pt->next = node_ptr;
            length++;
        }

        void insert_before(iterator it_node, T _data)  // 在某元素之前插入
        {
            if (it_node.pt == nullptr)
                return;
            Node *node_ptr = new Node(_data, it_node.pt->prev, it_node.pt);
            if (it_node.pt->prev != nullptr)
                it_node.pt->prev->next = node_ptr;
            else
                it_head.pt = node_ptr;
            it_node.pt->prev = node_ptr;
            length++;
        }

        DoubleLinkedList &operator=(const DoubleLinkedList &other)
        {
            clear();
            for (auto element:other)
                push_back(element);
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &io, const DoubleLinkedList &linkedList)  // 打印链表
        {
            io << "NULL" << " <-> ";
            if (linkedList.length != 0)
                for (auto element:linkedList)
                {
                    io << element << " <-> ";
                }
            io << "NULL";
            return io;
        }
    };
}

#endif //DATA_STRUCTURE_DOUBLELINKEDLIST_HPP