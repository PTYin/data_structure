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

//        template <typename Vertex>
//        DisjointSet::DisjointSets<Vertex> nodes;

        DisjointSet::DisjointSets djs;

        template <typename T, typename Vertex=int>
        struct Edge
        {
            Vertex from, to;
            T weight;
            Edge(Vertex _from, Vertex _to, T _weight):from(_from), to(_to),weight(_weight)
            {
                djs.add({from, to});
            }

            bool operator<(const Edge& o) const
            {
                return weight < o.weight;
            }
        };

        template <typename T, typename Vertex>
        static std::vector<Edge<T, Vertex>>& init()
        {
            int m;
            std::cin >> m;
            auto *edges = new std::vector<Edge<T, Vertex>>;

            for(int i=1;i<=m;i++)
            {
                int from, to;
                T weight;
                std::cin >> from >> to >> weight;
                edges->emplace_back(from, to, weight);
            }
            return *edges;
        }

        template <typename T, typename Vertex=int>
        std::vector<Edge<T, Vertex>>& kruskal(std::vector<Edge<T, Vertex>>& edges)  // don't forget to delete
        {
            using Edge = Edge<T, Vertex>;
            
            auto* trace = new std::vector<Edge>;
            bool toDelete = false;
            if(edges.empty())
            {
                edges = init<T, Vertex>();
                toDelete = true;
            }
            quick_sort_recursive<Edge&>(edges, 0, edges.size()-1);
            for(Edge edge:edges)
            {
                if(djs.equivalent(edge.from, edge.to))  // 在一个集合里
                    continue;
                djs._union(edge.from, edge.to);
                trace->push_back(edge);
            }
            if(toDelete)
                delete &edges;

            return *trace;
        }

    }
}
#endif //DATA_STRUCTURE_KRUSKAL_HPP
