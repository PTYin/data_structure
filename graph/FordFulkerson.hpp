//
// Created by Peter on 2019/11/19.
//

#ifndef DATA_STRUCTURE_FORDFULKERSON_HPP
#define DATA_STRUCTURE_FORDFULKERSON_HPP

#include "../primitive/Queue.hpp"
#include <cstring>
#include <vector>
#include <map>

namespace pty::FordFulkerson
{

    template <typename T>
    static inline T min(T a, T b)
    {
        return a <= b ? a : b;
    }

    const int INF = 0x3f3f3f3f;

    template<typename T>
    struct Edge
    {
        int from, to;
        T capacity, flow;
        Edge(int _from, int _to, T _capacity, T _flow):from(_from), to(_to), capacity(_capacity), flow(_flow){}
        bool operator<(const Edge& o) const
        {
            return capacity == o.capacity ? to < o.to : capacity < o.capacity;
        }
    };

    int n;
    template <typename T>
    T* augment;

    int* path;

    std::vector<int>* map;  // G[i][j]表示结点i的第j条边在edges数组中的序号

    template <typename T>
    std::vector<Edge<T>> edges;

    template <typename T>
    void init(int _n)
    {
        n = _n;
        map = new std::vector<int>[n+1];
    }

    template <typename T>
    inline void addEdge(int v1, int v2, T capacity)
    {

        edges<T>.emplace_back(v1, v2, capacity, 0);
        edges<T>.emplace_back(v2, v1, 0, 0);

        map[v1].push_back(edges<T>.size()-2);
        map[v2].push_back(edges<T>.size()-1);
    }

    template <typename T>
    T FordFulkerson(int source, int target)
    {
        T flow = 0;
        augment<T> = new T[n+1];
        path = new int[n+1];  // 按顶点找边编号

        while (true)
        {
            Queue<int> queue;
            memset(augment<T>, 0, (n+1)*sizeof(T));

            augment<T>[source] = INF;
//            augment<T>[source] = -1;
            queue.push(source);
            while (!queue.is_empty() && !augment<T>[target])
            {
                int vertex = queue.pop();
                for(int id:map[vertex])
                {
                    Edge<T>& edge = edges<T>[id];
                    if(!augment<T>[edge.to] && edge.capacity > edge.flow)
                    {
                        path[edge.to] = id^1;  // 记的是反向边
                        augment<T>[edge.to] = min(augment<T>[vertex], edge.capacity-edge.flow);
//                        augment<T>[edge.to] = augment<T>[vertex] == -1 ? edge.capacity-edge.flow : min(augment<T>[vertex], edge.capacity-edge.flow);
                        queue.push(edge.to);
                    }
                }
            }

            if(!augment<T>[target])
                break;

            for(int u=target;u!=source;u=edges<T>[path[u]].to)
            {
                Edge<T>& edge1 = edges<T>[path[u]];
                edge1.flow -= augment<T>[target];
                edges<T>[path[u]^1].flow += augment<T>[target];
            }

            flow += augment<T>[target];
        }

        delete[] augment<T>;
        delete[] path;
        map = nullptr;
        edges<T>.clear();

        return flow;
    }



    int matching(std::vector<std::pair<int, int>>& graph, std::vector<int> left, std::vector<int> right)
    {
        delete[] map;

        n = left.size()+right.size()+2;
        map = new std::vector<int>[n];
        for(int v:left)
            addEdge<int>(0, v, 1);

        for(int v:right)
            addEdge<int>(v, n-1, 1);

        for(auto pair:graph)
            addEdge<int>(pair.first, pair.second, INF);

        return FordFulkerson<int>(0, n-1);
    }
}

#endif //DATA_STRUCTURE_FORDFULKERSON_HPP
