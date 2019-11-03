//
// Created by Peter on 2019/10/31.
//

#ifndef DATA_STRUCTURE_PRIM_HPP
#define DATA_STRUCTURE_PRIM_HPP

#include <vector>
#include "../primitive/Heap.hpp"

namespace pty
{
    namespace prim
    {
        template <typename T>
        struct Edge
        {
            int from;
            int to;
            T weight;
            Edge() = default;
            Edge(int _from, int _to, T _weight):from(_from), to(_to),weight(_weight){}
            bool operator<=(const Edge& o) const
            {
                return weight <= o.weight;
            }
        };

        template <typename T>
        void addDoubleEdge(std::vector<Edge<T>>* edges, int from, int to, T weight)
        {
            edges[from].emplace_back(from, to, weight);
            edges[to].emplace_back(to, from, weight);
        }

        int n, m;

        template <typename T>
        static std::vector<Edge<T>>* init()
        {
            std::cin >> n >> m;
            auto* edges = new std::vector<Edge<T>>[n+1];
            for(int i=1;i<=m;i++)
            {
                int id1, id2, weight;
                std::cin >> id1 >> id2 >> weight;
                edges[id1].emplace_back(id1, id2, weight);
                edges[id2].emplace_back(id2, id1, weight);
            }
            return edges;
        }

        template <typename T>
        std::vector<Edge<T>> prim(int _n, int _m, int first = 0, std::vector<Edge<T>>* edges = nullptr)
        {
            bool toDelete = false;
            n = _n;
            m = _m;
            if(!edges)
            {
                edges = init<T>();
                toDelete = true;
            }

            Heap<Edge<T>> heap;
            std::vector<Edge<T>> paths;
            bool* visited = new bool[n+1];
            memset(visited, false, (n+1) * sizeof(bool));

            heap.insert(Edge<T>(first, first, 0));
            while (!heap.is_empty())
            {
                Edge<T> event = heap.pop();

                if(visited[event.to])
                    continue;
                visited[event.to] = true;
                paths.push_back(event);
                for(Edge<T> edge:edges[event.to])
                {
                    if(visited[edge.to])
                        continue;
                    heap.insert(edge);
                }
            }


            if(toDelete)
                delete[] edges;
            return paths;
        }
    }
}
#endif //DATA_STRUCTURE_PRIM_HPP
