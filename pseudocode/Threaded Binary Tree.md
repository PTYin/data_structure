# Threaded Binary Tree

```cpp

void makeThreaded(Node* _root)
{
    Node* prev = nullptr;
    _root->traversal([&prev, this](Node* node)
                     {
                         if(node->LTag = CLUE || node->left() == nullptr)
                         {
                             node->LTag = CLUE;
                             node->left = prev;
                         }
                         if(prev && (prev->right() == nullptr || prev->RTag == CLUE))
                         {
                             prev->RTag = CLUE;
                             prev->right() = node;
                         }
                         prev = node;
                     })  // 中序遍历
}
```

