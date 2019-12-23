# Dijkstra Algorithm

```c++
void dijkstra(int from, int to)
{
	Heap<Node> heap;
	heap.insert(Node(id=from, dis=0));
    while(!heap.empty())
    {
        Node node = heap.pop();
        if(visited[node.id])
            continue;
        visited[node.id] = true;
        dis[node.id] = node.dis;
        
        for(Edge edge:edges[node.id])
        {
            if(!visited[edge.to]&&dis[node.id]+edge.weight<dis[edge.to])
                heap.insert(Node(edge.to, dis[node.id]+edge.weight))
        }
    }
}
```

