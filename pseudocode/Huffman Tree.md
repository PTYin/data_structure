# Huffman Tree

```cpp
template<typename C>
Node* build(C container, int size)
{
    Node** array = new Node*[size];
    for(int i=0;i<size;i++)
        array[i] = new Node(container[i]);
    Heap<Node *>heap([](Node* node1, Node* node2)->bool
                     {
                        return *node1 <= *node2; 
                     });
    heap.heapify(array, size);  // 从array建堆
    Node* fa = nullptr;
    while(!heap.empty())
    {
        Node* node1 = heap.pop();
        Node* node2 = heap.pop();
        fa = new Node(*node1+*node2);
        fa->left() = node1;
        fa->right() = node2;
        node1->fa() = node2->fa() = fa;
        heap.insert(fa);
    }
    return fa;
}
```

