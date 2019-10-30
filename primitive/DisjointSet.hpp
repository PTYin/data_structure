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
            Node():fa(this){}

            explicit Node(T _val) : val(_val), fa(this){}

            Node(const Node& o) : fa(this), val(o.val){}

            Node(const Node&& o) : fa(this), val(o.val){}

            Node& operator=(const Node& o)
            {
                val = o.val;
                fa = this;
                return *this;
            }

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

        template <typename Index, typename Value=Index>
        class DisjointSets
        {
        private:
            map<Index, Node<Value>> nodes;
        public:

            DisjointSets():nodes(){}

            unsigned long long size() const
            {
                return nodes.size();
            }

            Node<Index>* begin() const
            {
                return nodes.begin();
            }

            Node<Index>* end() const
            {
                return nodes.end();
            }

            Node<Index>& operator[](Index index)
            {
                return nodes[index];
            }

        };
    }
}
#endif //DATA_STRUCTURE_DISJOINTSET_HPP
