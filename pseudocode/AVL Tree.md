# AVL Tree

```cpp
template<typename T>
class AVLTree : public BST<T>
{
private:
    Node* rotateAt(Node* node)
    {
        Node* p = node->fa();
        Node* g = p->fa();
        char* situation = judge(fa, p, g)  // 根据node, p, g的关系判断
        switch(situation)
        {
			case "LL":
                p->fa() = g->fa();
                g->fa() = p;
                p->right() = g;
                updateHeight(g);
                
                updateHeight(p);
                return p;
			case "LR":
                node->fa() = g->fa();
                g->fa() = node;
                p->fa() = node;
                g->right() = node->left();
                p->left() = node->right();
                node->left() = g;
                node->right() = p;
                
                updateHeight(p);
                updateHeight(g);
                updateHeight(node);
                return node;
			case "RL":
                ...;
			case "RR":
                ...;
        }
    }
    Node* searchIn(Node* node, T e)
    {
        if(!node && *node=e)
            return node;
        hot = node;
        if(e < *node)
            return searchIn(node->left(), e);
        else
            return searchIn(node->right(), e);
    }
public:
    void insert(T e)
    {
        Node* node = search(e);
        if(node)
            return;
        if(e < *hot)
            this->hot->left = new Node(e, fa=hot);
        else
            this->hot->right = new Node(e, fa=hot);

        for (Node *x = this->hot; x; x = x->fa())
        {
            if (!AVL_BALANCED(x))
            {
                Node *&reference = PARENT_REFERENCE(x);  // x节点父亲节点对x的引用
                reference = rotateAt(tallerChild(tallerChild(x)));
                break;
            }
            else
            {
                updateHeight(x);
            }
        }
        size++;
    }
    Node* search(T e)
    {
        return searchIn(root, e);
    }
    void remove(T e)
    {
        BST<T>::remove(e);
        for(Node* x=hot; x!=root; x=x->fa())
        {
            if(!AVL_BALANCED(x))
            {
                Node*& reference = PARENT_REFERENCE(x);
                refernce = rotateAt(tallerChild(tallerChild(x)));
            }
            else
            {
                updateHeight(x);
            }
        }
    }
}
```

**重点在于旋转部分以及插入和删除时从底向上的传播**