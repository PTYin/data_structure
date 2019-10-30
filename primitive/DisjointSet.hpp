//
// Created by Peter on 2019/10/30.
//

#ifndef DATA_STRUCTURE_DISJOINTSET_HPP
#define DATA_STRUCTURE_DISJOINTSET_HPP

#include <map>
namespace pty
{
    namespace DisjointSet
    {
        using std::map;

        template <typename T>
        struct Node
        {
            T val;
            Node* fa;
            Node():fa(this){std::cout << "Default Node created!";}

            explicit Node(T _val) : val(_val), fa(this){}

//            Node(Node&& o) : fa(this), val(o.val){}

            Node* findRoot()
            {
                return fa == this ? this : fa->findRoot();
            }

            const Node* findRoot() const
            {
                return fa == this ? this : (const Node*)fa->findRoot();
            }

            void join(Node& o)
            {
                findRoot()->fa = o.findRoot();
            }

            bool equivalent(const Node& o) const
            {
                return findRoot() == o.findRoot();
            }

            T value()
            {
                return val;
            }

            Node& operator=(T _value)
            {
                val = _value;
                return *this;
            }

        };

        template <typename T>
        class DisjointSets
        {
        private:
            int n;
            Node<T>* nodes;
        public:

            DisjointSets():n(0),nodes(nullptr){}

            explicit DisjointSets(int _size) : n(_size)
            {
                nodes = new Node<T>[_size];
            }

            virtual ~DisjointSets()
            {
                delete[] nodes;
            }

            int size() const
            {
                return n;
            }

            Node<T>* begin() const
            {
                return nodes;
            }

            Node<T>* end() const
            {
                return nodes + n;
            }

            Node<T>& operator[](int index)
            {
                return nodes[index];
            }

        };
    }
}
#endif //DATA_STRUCTURE_DISJOINTSET_HPP
