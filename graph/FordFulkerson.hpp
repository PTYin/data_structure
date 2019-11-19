//
// Created by Peter on 2019/11/19.
//

#ifndef DATA_STRUCTURE_FORDFULKERSON_HPP
#define DATA_STRUCTURE_FORDFULKERSON_HPP

#include "../primitive/Queue.hpp"
#include <cstring>
#include <vector>
#include <map>

namespace pty
{
    namespace FordFulkerson
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
            int to;
            T capacity, flow;
            Edge(int _to, T _capacity, T _flow): to(_to), capacity(_capacity), flow(_flow){}
        };

        template <typename T>
        class ResidualEdge
        {

            int v1, v2;
            T capacity;
            ResidualEdge(int _v1, int _v2, T _capacity):v1(_v1), v2(_v2), capacity(_capacity){}
        };

        int n, m;
        template <typename T>
        T* augment;

        int* path;

        template <typename T>
        std::map<Edge<T>, int> reverseEdge;

        template <typename T>
        std::vector<Edge<T>>* edges = nullptr;

        template <typename T>
        inline void addEdge(int v1, int v2, T capacity)
        {
            edges<T>[v1].emplace_back(v2, capacity, 0);
            edges<T>[v2].emplace_back(v1, 0, 0);

            reverseEdge<T>[edges<T>[v1].back()] = edges<T>[v2].size()-1;
            reverseEdge<T>[edges<T>[v2].back()] = edges<T>[v1].size()-1;
        }

        template <typename T>
        T FordFulkerson(int source, int target)
        {
            T flow = 0;
            while (true)
            {
                Queue<int> queue;
                augment<T> = new T[n];
                memset(augment<T>, 0, n);

                path = new int[n];  // 按顶点找边编号

                queue.push(source);
                while (!queue.is_empty() && !augment<T>[target])
                {
                    int vertex = queue.pop();
                    for(Edge<T> edge:edges<T>)
                    {
                        if(!augment<T>[vertex] && edge.capacity > edge.flow)
                        {
                            path[edge.to] = reverseEdge<T>[edge];  // 记的是反向边
                            augment<T>[edge.to] = min(augment<T>[vertex], edge.capacity-edge.flow);
                            queue.push(edge.to);
                        }
                    }
                }

                if(!augment<T>[target])
                    break;

                for(int u=target;u!=source;u=edges<T>[u][path[u]])
                {
                    edges<T>[u][path[u]].flow -= augment<T>[u];
                    edges<T>[u][path[u]^1].flow += augment<T>[u];
                }

                flow += augment<T>[target];
            }

            return flow;
        }
    }

}

#endif //DATA_STRUCTURE_FORDFULKERSON_HPP
