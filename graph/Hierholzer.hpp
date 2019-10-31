//
// Created by Peter on 2019/10/31.
//

#ifndef DATA_STRUCTURE_HIERHOLZER_HPP
#define DATA_STRUCTURE_HIERHOLZER_HPP

#include <vector>
#include <cstring>
#include "../primitive/Stack.hpp"

namespace pty
{
    namespace Hierholzer
    {
        int count = 0;
        bool* visited;

        template <typename T>
        struct Edge
        {
            int id, to;
            T weight;
            Edge(int _to, T _weight, const Edge* o = nullptr):to(_to),weight(_weight)
            {
                if(o)
                    id = o->id;
                else
                    id = count++;
            }
//            Edge(const Edge& o):id(o.id), to(o.to), weight(o.weight){}
        };

        template <typename T>
        void addDoubleEdge(std::vector<Edge<T>>* edges, int from, int to, T weight)
        {
            edges[from].emplace_back(to, weight);
            edges[to].emplace_back(from, weight, &edges[from].back());
        }

        int n = 0, m;

        template <typename T>
        std::vector<Edge<T>>* init()
        {
            std::cin >> n >> m;
            auto* edges = new std::vector<Edge<T>>[n + 1];

            for(int i=1;i<=m;i++)
            {
                int id1, id2, weight;
                std::cin >> id1 >> id2 >> weight;
                addDoubleEdge(edges, id1, id2, weight);

            }
            return edges;
        }

        // keep the edge to b in edges[a] have the same id with the edge to a in edge[b]
        template <typename T>
        DoubleLinkedList<Edge<T>> Hierholzer(int first=0, int _size = 0, int _edges = 0, const std::vector<Edge<T>>* edges = nullptr)
        {
            bool toDelete = false;
            n = _size;
            m = _edges;

            if(!edges)
            {
                edges = init<T>();
                toDelete = true;
            }
            DoubleLinkedList<Edge<T>> trace;

            visited = new bool[m];
            int* invalidCount = new int[n + 1];
            memset(visited, false, m * sizeof(bool));
            memset(invalidCount, 0, (n + 1) * sizeof(int));

            int last = first;
            typename DoubleLinkedList<Edge<T>>::iterator toInsert = trace.front();

            while (first != -1)
            {
                bool stop = false;
                while (!stop)
                {
                    stop = true;
                    for(Edge<T> edge:edges[last])
                    {
                        if(visited[edge.id])
                            continue;
                        stop = false;
                        visited[edge.id] = true;
                        invalidCount[last]++;
                        invalidCount[edge.to]++;
                        last = edge.to;
                        trace.insert_after(toInsert, edge);
                        if(toInsert != typename DoubleLinkedList<Edge<T>>::iterator())
                            toInsert++;
                        else
                            toInsert = trace.front();
                        break;
                    }
                }

                first = -1;
                for(auto it=trace.begin(); it != trace.end(); it++)
                {
                    if(invalidCount[(*it).to]!=edges[(*it).to].size())
                    {
                        first = (*it).to;
                        last = first;
                        toInsert = it;
                        break;
                    }
                }

            }

            if(toDelete)
                delete[] edges;
            return trace;
        }
    }
}
#endif //DATA_STRUCTURE_HIERHOLZER_HPP
