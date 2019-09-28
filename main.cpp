#include <cstring>
#include <random>

#include "DoubleLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Heap.hpp"
#include "quick_sort.hpp"
#include "tree/Node.hpp"
#include "tree/BinaryTree.hpp"
#include "tree/ThreadedBinaryTree.hpp"
#include "tree/SearchTree.hpp"
#include "tree/HuffmanTree.hpp"
#include "tree/AVLTree.hpp"

using namespace pty;
using std::cout;
using std::endl;

void doubleLinkedList_test();

void stack_test();

void queue_test();

void heap_test();

void quick_sort_test();

void binaryTree_test();

void threadedBinaryTree_test();

void searchTree_test();

void huffmanTree_test();

void AVLTree_test();

int main()
{
    cout << endl << "DoubleLinkedList:##########################" << endl;
    doubleLinkedList_test();
    cout << endl << "Stack:##########################" << endl;
    stack_test();
    cout << endl << "Queue:##########################" << endl;
    queue_test();
    cout << endl << "Heap:##########################" << endl;
    heap_test();
    cout << endl << "quick_sort:##########################" << endl;
    quick_sort_test();
    cout << endl << "BinaryTree:##########################" << endl;
    binaryTree_test();
    cout << endl << "ThreadedBinaryTree:##########################" << endl;
    threadedBinaryTree_test();
    cout << endl << "SearchTree:##########################" << endl;
    searchTree_test();
    cout << endl << "HuffmanTree:##########################" << endl;
    huffmanTree_test();
    cout << endl << "AVLTree:##########################" << endl;
    AVLTree_test();
    return 0;
}

void AVLTree_test()
{
    AVLTree<int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << tree;
    for (int i = 4; i <= 8; i++)
    {
        tree.remove(i);
    }
    cout << tree;
}

void huffmanTree_test()
{
//    int array[] = {13, 7, 2, 5};
//    int array[] = {1, 2, 2, 3, 6};
    int array[] = {9, 7, 6, 6};
    HuffmanTree<int> huffmanTree(array, sizeof(array) / sizeof(int));
    cout << huffmanTree << endl;
}

void searchTree_test()
{
    bool pos;
    std::array<int, 10> array{};
    for (unsigned long long i = 0; i < array.size(); i++)
        array[i] = i;
    unsigned seed = *((unsigned *) (&pos - 4));
    // 随机打乱一维数组
    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));
    // 从混乱数组中构造搜索树
    SearchTree<int> searchTree(array);
    cout << searchTree << endl;
    // 向搜索树插入
    searchTree.insert(0x7fffffff);
    // 查找第k小的元素
    cout << "3rd smallest:" << searchTree.find_kth_small(3)->get() << endl;
    cout << "4 is the " << searchTree.kth(4) << " smallest in the tree" << endl;
    // 删除元素
    for (int i = 0; i < array.size(); i++)
    {
        auto node = searchTree.search(array[i]);
        cout << node->get() << endl;
        searchTree.remove(node);
//        cout << searchTree << endl;
    }
    searchTree.remove(searchTree.search(0x7fffffff));
    cout << searchTree.size() << endl;
}

void threadedBinaryTree_test()
{
    char values[] = {0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int pre_order[] = {1, 2, 4, 5, 3, 6, 7, 8};
    int in_order[] = {4, 2, 5, 1, 7, 6, 8, 3};
    int post_order[] = {4, 5, 2, 7, 8, 6, 3, 1};
    ThreadedBinaryTree<char> threadedBinaryTree(8, values, in_order, pre_order);
    cout << threadedBinaryTree;
    //  像遍历链表一样遍历线索树
    cout << "Traversal Forward: ";
    for (auto item:threadedBinaryTree)
    {
        cout << item << " ";
    }
    cout << endl;
    //  倒序遍历，即镜像中序遍历
    cout << "Traversal Backward: ";
    for (ThreadedBinaryTree<char>::Iterator iterator = threadedBinaryTree.back();
         iterator != ThreadedBinaryTree<char>::end(); iterator--)
    {
        cout << *iterator << " ";
    }
    cout << endl;
    //  向最右节点插入右节点，值为'i'
    threadedBinaryTree.insert(threadedBinaryTree.back().pt, 'i', false);
    cout << "Traversal Forward: ";
    for (auto item:threadedBinaryTree)
    {
        cout << item << " ";
    }
    cout << endl;
}

void binaryTree_test()
{
    //  规定标号为i的节点的值为values[i]
    char values[] = {0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int pre_order[] = {1, 2, 4, 5, 3, 6, 7, 8};
    int in_order[] = {4, 2, 5, 1, 7, 6, 8, 3};
    int post_order[] = {4, 5, 2, 7, 8, 6, 3, 1};
    // 由前序和中序构造树
    BinaryTree<char> binaryTree_from_pre_in(8, values, in_order, pre_order);
    cout << binaryTree_from_pre_in;
    cout << endl << "-----------------------------" << endl;
    // 由后序和中序构造树
    BinaryTree<char> binaryTree_from_post_in(8, values, in_order, nullptr, post_order);
    cout << binaryTree_from_post_in << endl;
    cout << endl
         << (binaryTree_from_pre_in == binaryTree_from_post_in ? "Two Trees Are Same!" : "Two Trees Are Different!")
         << endl;
    //  前序遍历
    cout << "DLR:  ";

    auto fun = [](auto *node)
    { std::cout << node->get(); };

    binaryTree_from_pre_in.traversal_pre(fun);
    cout << endl;
    //  中序遍历
    cout << "LDR:  ";
    binaryTree_from_pre_in.traversal_in(fun);
    cout << endl;
    //  后序遍历
    cout << "LRD:  ";
    binaryTree_from_pre_in.traversal_post(fun);
    cout << endl;
    //  层次遍历
    cout << "Lev:  ";
    binaryTree_from_pre_in.traversal_level(fun);
    cout << endl;
}

void quick_sort_test()
{
    int array[] = {3, 5, 1, 4, 100, 43, 0x7fffffff, 12113, 12, 12, 1, 1, 33, 912};
    // 用递归实现快排
    quick_sort_recursive<int>(array, 0, sizeof(array) / sizeof(int) - 1);
    cout << "!!!Recursive Quick Sort:";
    for (int i : array)
        cout << i << " ";

    cout << endl << "!!!Quick Sort Using Stack:";
    const char *char_array[] = {"I love programming!", "aaa", "aaaa", "aaaaaaaaaaaaaa", "aaaa"};
    // 用栈实现快排
    quick_sort_stack<const char *>(char_array, 0, sizeof(char_array) / sizeof(const char *) - 1,
                                   [](const char *e1, const char *e2) -> bool
                                   {
                                       return strlen(e1) < strlen(e2);
                                   });
    for (const char *i : char_array)
        cout << i << " ";

    cout << endl << "!!!Quick Sort Using Queue:";
    double double_array[] = {1.0, 3.1, 0.4444, 121.21, 21.0, 12, 12901, 101010, 3.1415926535};
    quick_sort_queue<double>(double_array, 0, sizeof(double_array) / sizeof(double) - 1,
                             [](double e1, double e2) -> bool
                             {
                                 return e1 > e2;
                             });
    for (double value : double_array)
        cout << value << " ";
    cout << endl;
}

void heap_test()
{
    Heap<int> h1;
    int array[] = {3, 5, 1, 4, 100, 43, 0x7fffffff, 12113, 12, 12, 1, 1, 33, 912};
    h1.heapify(array, sizeof(array) / sizeof(int));  // 从一个无序数组以O(n)时间复杂度建堆
    while (!h1.is_empty())
        cout << h1.pop() << " ";
    cout << endl;
    Heap<std::string> h2(100, [](std::string string1, std::string string2) -> bool  // 比较器选择大的为优先级较高
    {
        return string1 >= string2;
    });
    h2.insert("aaa");
    h2.insert("bbb");
    h2.insert("ccc");
    cout << h2 << endl;
    while (!h2.is_empty())
        cout << h2.pop() << " ";
    cout << endl;
}

void doubleLinkedList_test()
{
    DoubleLinkedList<int> linkedList({1, 3, 5}); // 建立int链表
    DoubleLinkedList<int>::iterator iterator = linkedList.find_first(1);  // 找到元素1的位置得到迭代器
    linkedList.insert_before(iterator, 1);  // 在1之前插入1
    iterator++;  // 迭代器向后移动指向3
    linkedList.insert_after(iterator, 100);  // 在3之后插入100
    linkedList.push_front(10);  // 在头部压入10
    linkedList.push_back(10);  // 在尾部压如10
    linkedList.modify(linkedList.front(), 12);  // 修改头部10为12
    linkedList.modify(linkedList.back(), 13);  // 修改尾部10为13
    cout << "pop_front:" << linkedList.pop_front() << endl;  // 弹出头部元素并输出
    cout << "pop_back:" << linkedList.pop_back() << endl;  // 弹出尾部元素并输出
    cout << linkedList << endl;  // 输出链表
    linkedList.clear();  // 清空链表
    if (linkedList.is_empty())
        cout << "empty" << endl << "-------------------------" << endl;  // 输出链表是否为空
    DoubleLinkedList<const char *> stringList({"first", "second", "third"});  // 建立字符串常量链表
    stringList.push_back("first");
    stringList.push_back("second");
    cout << stringList << endl;  // 输出链表
    cout << stringList.find_first_index("first") << ":" << stringList.find_last_index("first")
         << endl;  // 输出"first"出现的第一个位置和最后一个位置的索引
    int count = 0;
    for (auto element:stringList)  // range-based for遍历
        count++;
    cout << count << ":" << stringList.size() << endl;  // 输出大小
}

void stack_test()
{
    Stack<double> stack;
    stack.push(1.1);  // 推入栈中
    stack.push_all({1.2, 3.3, 5.5});  // 推入栈中
    cout << stack << endl;
    cout << stack.pop() << endl;  // 弹出
    cout << "top: " << stack.top() << endl;  // 顶部元素
    cout << stack << endl;
}

void queue_test()
{
    Queue<char> queue({'a', 'b', 'c'});  // a -> b -> c
    queue.push_all({'a', 'b', 'c'});  // a -> b
    cout << queue << endl;
    cout << queue.pop() << endl;
    cout << "head: " << queue.head() << ", tail: " << queue.tail() << endl;  // 队首元素和队尾元素
    cout << queue << endl;
}