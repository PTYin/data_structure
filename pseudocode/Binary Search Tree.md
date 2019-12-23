# Binary Search Tree

```cpp
template <typename T>
class BST
{
    Node* hot;
    Node* searchIn(Node* node, T e)
    {
        if(!node || *node == e)
        {
            return node;
        }
        hot = node;
        if(e < *node)
            return searchIn(node->left, e);
        else
	        return searchIn(node->right, e);
    }
    Node* search(T e)
    {
        return searchIn(root, e);
    }
    void insert(T e)
    {
        if(search(e))
            return;
        if(e < *hot)
            hot->left = new Node(e, fa=hot);
        else
            hot->right = new Node(e, fa=hot);
        size++;
    }
    void remove(T e)
    {
        Node* node = search(e);
        Node* actual = node;  // 实际被删除的点
        Node* succ = nullptr;  // 实际被删除的点的替代
        if(!node)
            return;
        if(node 没有孩子 || node只有一个孩子)
        {
            if(node没有左儿子)
                succ = node->right;
            if(node没有右儿子)
                succ = node->left;
        }
        else
        {
            actual = 以node为根节点中序遍历的node下一个节点;
            swap(*node, *actual);
            succ = actual->right;
        }
        根据actual和actual的父亲节点的关系进行acutal父亲与succ的连接;
        delete actual;
        size--;
    }
}
```

