#  Kruskal Algorithm

```cpp
int find(int x)
{
    return fa[x] == -1?x:find(fa[x]);
}
void union(int a, int b)
{
    fa[find(b)] = find(a);
}
bool same(int a, int b)
{
    return find(a) == find(b);
}
void kruskal()
{
    int ans=0;
    sort(edges, edges.begin(), edges.end());
    for(Edge edge:edges)
    {
        if(same(edge.from, edge.to))
            continue;
        ans += edge.weight;
        union(edge.from, edge.to);
    }
}
```

