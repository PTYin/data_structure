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
        protected:
            std::map<int, int> fa;
        public:
            DisjointSets():fa(){}
            virtual void add(int e)
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

            virtual int find(int e)
            {
                return e == fa.at(e) ? e : find(fa.at(e));
            }

            bool equivalent(int e1, int e2) const
            {
                return find(e1) == find(e2);
            }

            virtual void _union(int e1, int e2)
            {
                fa[find(e1)] = find(e2);
            }
        };

        // “路径压缩”与“按秩合并”优化
        class DisjointSetsUpgrade : public DisjointSets
        {
        private:
            std::map<int, int> rank;
        public:
            DisjointSetsUpgrade():DisjointSets(), rank(){}

            using DisjointSets::add;

            void add(int e) override
            {
                if(!fa.count(e))
                {
                    fa[e] = e;
                    rank[e] = 0;
                }
            }

            int find(int e) override
            {
                return e == fa.at(e) ? e : (fa[e] = find(fa.at(e)));
            }

            void _union(int e1, int e2) override
            {
                int fa1 = find(e1), fa2 = find(e2);
                if(rank[fa1] < rank[fa2])
                    fa[fa1] = fa2;
                else
                {
                    if(rank[fa1] == rank[fa2])
                        rank[fa1]++;
                    fa[fa2] = fa1;
                }
            }
        };
    }
}
#endif //DATA_STRUCTURE_DISJOINTSET_HPP
