//
// Created by Peter on 2019/10/30.
//

#ifndef DATA_STRUCTURE_DISJOINTSET_HPP
#define DATA_STRUCTURE_DISJOINTSET_HPP
namespace pty
{
    namespace DisjointSet
    {
        template <typename T>
        class Node
        {
        private:
            T value;
            Node* fa;
        public:
            Node():fa(this){}

            Node(T value_) : value(value_),fa(this){}

            Node* findRoot() const
            {
                return fa == this ? this : fa->findRoot();
            }

            void join(const Node& o)
            {
                findRoot()->fa = o.findRoot();
            }

            bool operator==(const Node& o) const
            {
                return findRoot() == o.findRoot();
            }
        };

        template <typename T>
        class DisjointSets
        {
        private:
            int n;
            Node<T>* nodes;
        public:
            explicit DisjointSets(int size_) : n(size_)
            {
                nodes = new Node<T>[size_];
            }

            virtual ~DisjointSets()
            {
                delete[] nodes;
            }

            int size() const
            {
                return n;
            }

        };
    }
}
#endif //DATA_STRUCTURE_DISJOINTSET_HPP
