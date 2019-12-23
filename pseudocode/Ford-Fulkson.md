# Ford-Fulkson

```cpp
vector<Edge> edges;
vector<int> G[MAXN];	// 邻接表，G[i][j]表示结点i的第j条边在edges数组的序号
int augment[MAXN];		// 起点到i的可改进量
int path[MAXN];			// 最短路树上p的入弧编号

void maxFlow(int s, int t)
{
    int flow = 0;
    while(true)
    {
        Queue<int> q;
        memset(augment, 0, n*sizeof(int));
        augment[s] = INF;
        q.push(s);
        while(!q.empty()&&!augment[t])  // 寻找增广路
        {
            int v = q.pop();
            for(int id:G[v])
            {
                Edge& edge = edges[id];
                if(!augment[edge.to] && edge.cap > edge.flow)
                {
                    path[edge.to] = id;
                    augment[edge.to] = min(augment[v], edge.cap-edge.flow);
                    q.push(edge.to);
                }
            }
        }
        if(!augment[t])  // 无增广路了
            break;
        for(int u=t;u!=s;u=edges[path[u]].from)  // 更新网络
        {
            edges[path[u]].flow += augment[t];
            edges[path[u]^1].flow -= augment[t];  // 残差网络中的反向边
        }
        flow += augment[t];
    }
}
```

1. 初始化残差网络,即加入一条边的同时加入其反向边,并将反向边的cap和flow均设为0
2. 每次寻找一条增广路
   1. 利用广搜,首先将源点的提升量设为INF(augment[s] = INF),将源点推入队列中
   2. 循环
      1. 每次从队列取出一个顶点v
      2. 遍历v的所有邻边
         1. 若当前边的终点没有被访问过且可以增广(cap>flow)
            1. 则更新augment[edge.to] = min(augment[v], edge.cap-edge.flow)
            2. 更新path[edge.to] = edge.id
            3. 将edge.to推入队列
   3. 若发现无法增广则跳出
   4. 更新网络
      1. 对于path中的边更新flow加上augment[t],并将对应的残差网络中的反向边减去augment[t]
      2. flow += augment[t]

