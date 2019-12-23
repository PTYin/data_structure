#include <cstring>
#include <random>
#include <ctime>

#include "primitive/DoubleLinkedList.hpp"
#include "primitive/Stack.hpp"
#include "primitive/Queue.hpp"
#include "primitive/Heap.hpp"
#include "other/quick_sort.hpp"
#include "tree/BinaryTree.hpp"
#include "tree/ThreadedBinaryTree.hpp"
#include "tree/SearchTree.hpp"
#include "tree/HuffmanTree.hpp"
#include "tree/AVLTree.hpp"
#include "tree/Splay.hpp"
#include "tree/Treap.hpp"
#include "string/KMP.hpp"
#include "graph/dijkstra.hpp"
#include "graph/kruskal.hpp"
#include "graph/Hierholzer.hpp"
#include "graph/prim.hpp"
#include "graph/FordFulkerson.hpp"

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

void splay_test();

void treap_test();

void KMP_test();

void dijkstra_test();

void kruskal_test();

void hierholzer_test();

void prim_test();

void FordFulkerson_test();

int main()
{
//    cout << endl << "DoubleLinkedList:##########################" << endl;
//    doubleLinkedList_test();
//    cout << endl << "Stack:##########################" << endl;
//    stack_test();
//    cout << endl << "Queue:##########################" << endl;
//    queue_test();
//    cout << endl << "Heap:##########################" << endl;
//    heap_test();
//    cout << endl << "quick_sort:##########################" << endl;
//    quick_sort_test();
//    cout << endl << "BinaryTree:##########################" << endl;
//    binaryTree_test();
//    cout << endl << "ThreadedBinaryTree:##########################" << endl;
//    threadedBinaryTree_test();
//    cout << endl << "SearchTree:##########################" << endl;
//    searchTree_test();
//    cout << endl << "HuffmanTree:##########################" << endl;
//    huffmanTree_test();
    cout << endl << "AVLTree:##########################" << endl;
    AVLTree_test();
//    cout << endl << "Splay:##########################" << endl;
//    splay_test();
//    cout << endl << "treap:##########################" << endl;
//    treap_test();
//    cout << endl << "KMP:##########################" << endl;
//    KMP_test();
//    cout << endl << "dijkstra:##########################" << endl;
//    dijkstra_test();
//    cout << endl << "kruskal:##########################" << endl;
//    kruskal_test();
//    cout << endl << "hierholzer:##########################" << endl;
//    hierholzer_test();
//    cout << endl << "prim:##########################" << endl;
//    prim_test();
//    cout << endl << "FordFulkerson:##########################" << endl;
//    FordFulkerson_test();

    return 0;
}

void FordFulkerson_test()
{
    using namespace FordFulkerson;
    init<int>(4);
    addEdge(1, 2, 8);
    addEdge(1, 3, 3);
    addEdge(2, 3, 1);
    addEdge(2, 4, 6);
    addEdge(3, 4, 5);
    cout << "max flow answer:" << FordFulkerson::FordFulkerson<int>(1, 4) << endl;

    // matching problem
    std::vector<std::pair<int, int>> graph;
    graph.emplace_back(1, 6);
    graph.emplace_back(3, 2);
    graph.emplace_back(3, 4);
    graph.emplace_back(3, 6);
    graph.emplace_back(5, 6);
    cout << "matching problem answer:" << matching(graph, {1, 3, 5}, {2, 4, 6}) << endl;
}

void prim_test()
{
    std::vector<prim::Edge<int>> edges[100];
    prim::addDoubleEdge(edges, 1, 2, 4);
    prim::addDoubleEdge(edges, 1, 4, 6);
    prim::addDoubleEdge(edges, 1, 7, 7);
    prim::addDoubleEdge(edges, 2, 3, 12);
    prim::addDoubleEdge(edges, 3, 4, 9);
    prim::addDoubleEdge(edges, 3, 5, 1);
    prim::addDoubleEdge(edges, 3, 6, 2);
    prim::addDoubleEdge(edges, 3, 8, 10);
    prim::addDoubleEdge(edges, 4, 5, 13);
    prim::addDoubleEdge(edges, 4, 7, 2);
    prim::addDoubleEdge(edges, 5, 6, 5);
    prim::addDoubleEdge(edges, 5, 7, 11);
    prim::addDoubleEdge(edges, 5, 8, 8);
    prim::addDoubleEdge(edges, 6, 8, 7);
    prim::addDoubleEdge(edges, 7, 8, 14);
    
    std::vector<prim::Edge<int>> trace = prim::prim(8, 14, 1, edges);
    for(auto edge:trace)
    {
        cout << edge.from << "<->" << edge.to << ": " << edge.weight << endl;
    }
}

void hierholzer_test()
{
    std::vector<Hierholzer::Edge<int>> edges[10];
    Hierholzer::addDoubleEdge(edges, 0, 1, 1);
    Hierholzer::addDoubleEdge(edges, 1, 2, 1);
    Hierholzer::addDoubleEdge(edges, 2, 3, 1);
    Hierholzer::addDoubleEdge(edges, 3, 0, 1);
    Hierholzer::addDoubleEdge(edges, 2, 4, 1);
    Hierholzer::addDoubleEdge(edges, 4, 5, 1);
    Hierholzer::addDoubleEdge(edges, 5, 6, 1);
    Hierholzer::addDoubleEdge(edges, 6, 2, 1);
    Hierholzer::addDoubleEdge(edges, 5, 7, 1);
    Hierholzer::addDoubleEdge(edges, 7, 8, 1);
    Hierholzer::addDoubleEdge(edges, 8, 9, 1);
    Hierholzer::addDoubleEdge(edges, 9, 5, 1);

//    std::vector<std::vector<Hierholzer::Edge<int>>> trace = Hierholzer::Hierholzer(0, 7, 8, edges);
    auto trace = Hierholzer::Hierholzer(0, 9, 12, edges);
//    auto trace = Hierholzer::Hierholzer<int>();

    cout << 0;
    for(Hierholzer::Edge<int> edge:trace)
    {
        cout << "->" << edge.to;
    }
    cout << endl;
}

void kruskal_test()
{
    std::vector<kruskal::Edge<int>> edges;
    edges.emplace_back('A', 'B', 4);
    edges.emplace_back('A', 'D', 6);
    edges.emplace_back('A', 'G', 7);
    edges.emplace_back('B', 'C', 12);
    edges.emplace_back('C', 'D', 9);
    edges.emplace_back('C', 'E', 1);
    edges.emplace_back('C', 'F', 2);
    edges.emplace_back('C', 'H', 10);
    edges.emplace_back('D', 'E', 13);
    edges.emplace_back('D', 'G', 2);
    edges.emplace_back('E', 'F', 5);
    edges.emplace_back('E', 'G', 11);
    edges.emplace_back('E', 'H', 8);
    edges.emplace_back('F', 'H', 7);
    edges.emplace_back('G', 'H', 14);
    std::vector<kruskal::Edge<int>>& trace = kruskal::kruskal(edges);
    for(auto edge:trace)
    {
        cout << (char)edge.from << "<->" << (char)edge.to << ": " << edge.weight << endl;
    }

    delete &trace;
}

void dijkstra_test()
{
    std::vector<dijkstra::Edge> edges[6];
    edges[1].emplace_back(2, 2);
    edges[2].emplace_back(1, 2);

    edges[1].emplace_back(3, 5);
    edges[3].emplace_back(1, 5);

    edges[1].emplace_back(4, 8);
    edges[4].emplace_back(1, 8);

    edges[2].emplace_back(3, 2);
    edges[3].emplace_back(2, 2);

    edges[2].emplace_back(5, 8);
    edges[5].emplace_back(2, 8);

    edges[3].emplace_back(4, 3);
    edges[4].emplace_back(3, 3);

    edges[3].emplace_back(5, 6);
    edges[5].emplace_back(3, 6);

    edges[4].emplace_back(5, 2);
    edges[5].emplace_back(4, 2);
    int* dis = dijkstra::dijkstra(1, 5, edges);
    for(int i=1;i<=5;i++)
    {
        cout << "1 to " << i << ": " << dis[i] << endl;
    }

    delete[] dis;
}

void KMP_test()
{
    KMP kmp("peter");
    cout << kmp.findIn("hello, peter") << endl;
    cout << kmp.findIn("hello, jason") << endl;
    kmp.setPattern("jason");
    cout << kmp.findIn("hello, jason, jason") << endl;
    kmp.setPattern("bbbpapaccd");
    cout << kmp.findIn("0123bbbpapaccd121") << endl;
}

void treap_test()
{

    std::array<int, 10000> array{};  // 顺序数组
    for(int i = 0; i < 10000; i++)
        array[i] = i;

    clock_t start = clock();
    Treap<int> treap(array);
    clock_t finish = clock();
    cout << "Treap clock time(serial insert): " << finish-start << endl;

    treap.clear();

    unsigned seed = start;
    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));

    start = clock();
    for(int i : array)
    {
        treap.insert(i);
    }
    finish = clock();
    cout << "Treap clock time(random insert): " << finish-start << endl;

    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));

    start = clock();
    for(int i : array)
    {
        treap.remove(i);
    }
    finish = clock();
    cout << "Treap clock time(remove): " << finish-start << endl;
    cout << "Treap remains " << treap.size() << endl;
}

void splay_test()
{
    std::array<int, 10000> array{};  // 顺序数组
    for(int i = 0; i < 10000; i++)
        array[i] = i;

    clock_t start = clock();
    Splay<int> splay(array);
    clock_t finish = clock();
    cout << "Splay clock time(serial insert): " << finish-start << endl;


    unsigned seed = start;
    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));

    splay.clear();
    start = clock();
    for(int i : array)
    {
        splay.insert(i);
    }
    finish = clock();
    cout << "Splay clock time(random insert): " << finish-start << endl;

    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));

    start = clock();
    for(int i : array)
    {
        splay.remove(i);
    }
    finish = clock();
    cout << "Splay clock time(random remove): " << finish-start << endl;
    cout << "Splay remains " << splay.size() << endl;
}

void AVLTree_test()
{
    // 分别比较AVL树和普通儿叉搜索树顺序插入和删除的时间

    std::array<int, 10000> array{};  // 顺序数组
    for(int i = 0; i < 10000; i++)
        array[i] = i;


//    std::array<int, 10> array{};
//    for (unsigned long long i = 0; i < array.size(); i++)
//        array[i] = i;
////    unsigned seed = *((unsigned *) (&pos - 4));
//    // 随机打乱一维数组
////    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));
//    // 从混乱数组中构造搜索树
//    AVLTree<int> searchTree(array);
//    searchTree.remove(0);
//    searchTree.remove(1);
//    cout << searchTree << endl;

    clock_t start = clock();
    AVLTree<int> avl(array);
    clock_t finish = clock();
    cout << "AVLTree clock time(insert): " << finish-start << endl;

    start = clock();
    SearchTree<int> search(array);
    finish = clock();
    cout << "SearchTree clock time(insert): " << finish-start << endl;

    start = clock();
    for (int i = avl.size()-1; i >= 0; i--)
    {
        avl.remove(i);
    }
    finish = clock();
    cout << "AVLTree clock time(remove): " << finish-start << endl;

    start = clock();
    for (int i = search.size()-1; i >= 0; i--)
    {
        search.remove(i);
    }
    finish = clock();
    cout << "SearchTree clock time(remove): " << finish-start << endl;
    cout << "AVLTree remains " << avl.size() << "; SearchTree remains " << search.size() << endl;

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
//    int array[] = {3, 5, 1, 4, 100, 43, 0x7fffffff, 12113, 12, 12, 1, 1, 33, 912};
//    std::array<int, 14> array = {3, 5, 1, 4, 100, 43, 0x7fffffff, 12113, 12, 12, 1, 1, 33, 912};
    std::array<int, 15> array = {4, 6, 7, 12, 9, 1, 2, 10, 13, 2, 5, 11, 8, 7, 14};
    // 用递归实现快排
//    quick_sort_recursive<int>(array, 0, sizeof(array) / sizeof(int) - 1);
    quick_sort_recursive<int>(array, 0, array.size()-1);
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