//
// Created by Peter on 2019/10/30.
//

#ifndef DATA_STRUCTURE_KRUSKAL_HPP
#define DATA_STRUCTURE_KRUSKAL_HPP

#include <vector>
#include "../primitive/DisjointSet.hpp"
//#include "quick_sort.hpp"

namespace pty
{
    namespace kruskal
    {
        template <typename T>
        struct Edge
        {
            DisjointSet::Node<int> from, to;
            T weight;
            Edge(int _from, int _to, T _weight):from(_from), to(_to),weight(_weight){}

            Edge(const Edge& o) : weight(o.weight),from(o.from.val), to(o.to.val){}  // 拷贝构造函数，必须写

            Edge(const Edge&& o) noexcept : weight(o.weight),from(o.from.val), to(o.to.val){}  // 移动构造函数，必须写，否则vector移动元素时会出错

            Edge& operator=(const Edge& o)  // 赋值运算符，防止排序的时候把from和to节点的fa属性也给改了
            {
                weight = o.weight;
                from.val = o.from.val;
                to.val = o.to.val;
                return *this;
            }

            bool operator<(const Edge& o) const
            {
                return weight < o.weight;
            }
        };

        template <typename T>
        static std::vector<Edge<T>>& init()
        {
            int m;
            std::cin >> m;
            auto *edges = new std::vector<Edge<T>>;

            for(int i=1;i<=m;i++)
            {
                int from, to;
                T weight;
                std::cin >> from >> to >> weight;
                edges->emplace_back(from, to, weight);
            }
            return *edges;
        }

        template <typename T>
        std::vector<Edge<T>>& kruskal(std::vector<Edge<T>>& edges)  // don't forget to delete
        {
            auto* trace = new std::vector<Edge<T>>;
            if(edges.empty())
            {
                edges = init<T>();
            }
//            std::sort(edges.begin(), edges.end()-1);
            quick_sort_recursive<Edge<T>&>(edges, 0, edges.size()-1);
            for(Edge<T> edge:edges)
            {
                if(edge.from.equivalent(edge.to))  // 在一个集合里而不是相等
                    continue;
                edge.from.join(edge.to);
                trace->push_back(edge);
            }
            delete &edges;
            return *trace;
        }

    }
}
#endif //DATA_STRUCTURE_KRUSKAL_HPP
