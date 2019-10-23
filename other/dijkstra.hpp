//
// Created by Peter on 2019/10/23.
//

#ifndef DATA_STRUCTURE_DIJKSTRA_HPP
#define DATA_STRUCTURE_DIJKSTRA_HPP

#include <cstring>
#include "../primitive/Heap.hpp"

const int N = 100000, INF = 0x3f3f3f3f;

namespace pty
{
    namespace dijkstra
    {
        struct Edge
        {
            int to, weight;
            Edge(int to_, int weight_) : to(to_), weight(weight_){}
        };

        struct DiscreteEvent
        {
            int id, dis;
            DiscreteEvent() = default;
            DiscreteEvent(int id_, int dis_) : id(id_), dis(dis_){};
            bool operator<=(const DiscreteEvent& o) const
            {
                return dis <= o.dis;
            }
        };

        int n, m;


        static std::vector<Edge>* init()
        {
            std::cin >> n >> m;
            auto* edges = new std::vector<Edge>[n+1];
            for(int i=1;i<=m;i++)
            {
                int id1, id2, weight;
                std::cin >> id1 >> id2 >> weight;
                edges[id1].emplace_back(id2, weight);
                edges[id2].emplace_back(id1, weight);
            }
            return edges;
        }

        int* dijkstra(int from, int _n = 0, std::vector<Edge>* edges = nullptr)  // Don't forget to delete[]
        {
            bool toDelete = false;
            n = _n;
            if(!edges)
            {
                edges = init();
                toDelete = true;
            }
            int* dis = new int[n+1];
            bool* visited = new bool[n+1];
            memset(dis, INF, (n+1)* sizeof(int));
            memset(visited, false, (n+1) * sizeof(bool));

            Heap<DiscreteEvent> heap;
            heap.insert(DiscreteEvent(from, 0));
            while (!heap.is_empty())
            {
                DiscreteEvent node = heap.pop();

                if(visited[node.id])
                    continue;

                visited[node.id] = true;
                dis[node.id] = node.dis;

                for(auto edge : edges[node.id])
                {
                    if(!visited[edge.to])
                        heap.insert(DiscreteEvent(edge.to, dis[node.id]+edge.weight));
                }
            }

            delete[] visited;
            if(toDelete)
                delete[] edges;

            return dis;
        }
    }
}

#endif //DATA_STRUCTURE_DIJKSTRA_HPP
