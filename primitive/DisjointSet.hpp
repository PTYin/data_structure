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

        class DisjointSets
        {
        private:
            std::map<int, int> fa;
        public:
            DisjointSets():fa(){}
            void add(int e)
            {
                if(!fa.count(e))
                    fa[e] = e;
            }
            void add(std::initializer_list<int> list)
            {
                for(int e:list)
                {
                    add(e);
                }
            }
            void clear()
            {
                fa.clear();
            }
            int find(int e) const
            {
                return e == fa.at(e) ? e : find(fa.at(e));
            }
            bool equivalent(int e1, int e2) const
            {
                return find(e1) == find(e2);
            }
            void _union(int e1, int e2)
            {
                fa[find(e1)] = find(e2);
            }
        };
    }
}
#endif //DATA_STRUCTURE_DISJOINTSET_HPP
