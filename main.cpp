#include <cstring>

#include "doubleLinkedList.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "quick_sort.hpp"
#include "binaryTree.hpp"

using namespace pty;
using std::cout;
using std::endl;

void doubleLinkedList_test();
void stack_test();
void queue_test();
void heap_test();
void quick_sort_test();
void binaryTree_test();
int main()
{
    cout<<endl<<"doubleLinkedList:##########################"<<endl;
    doubleLinkedList_test();
    cout<<endl<<"stack:##########################"<<endl;
    stack_test();
    cout<<endl<<"queue:##########################"<<endl;
    queue_test();
    cout<<endl<<"heap:##########################"<<endl;
    heap_test();
    cout<<endl<<"quick_sort:##########################"<<endl;
    quick_sort_test();
    cout<<endl<<"binaryTree:##########################"<<endl;
    binaryTree_test();
    return 0;
}

void binaryTree_test()
{
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int pre_order[] = {1, 2, 4, 5, 3, 6, 7, 8};
    int in_order[] = {4, 2, 5, 1, 7, 6, 8, 3};
    int post_order[] = {4, 5, 2, 7, 8, 6, 3, 1};
    // 由前序和中序构造树
    binaryTree<int> binaryTree_from_pre_in(8, values, in_order, pre_order);
    cout << binaryTree_from_pre_in;
    cout<<endl<<"-----------------------------"<<endl;
    // 由后序和中序构造树
    binaryTree<int> binaryTree_from_post_in(8, values, in_order, nullptr, post_order);
    cout << binaryTree_from_post_in<<endl;
    //  前序遍历
    binaryTree_from_pre_in.traversal_pre();
    cout<<endl;
    //  中序遍历
    binaryTree_from_pre_in.traversal_in();
    cout<<endl;
    //  后序遍历
    binaryTree_from_pre_in.traversal_post();
    cout<<endl;
}

void quick_sort_test()
{
    int array[] = {3, 5, 1, 4, 100, 43, 0x7fffffff, 12113, 12, 12, 1, 1, 33, 912};
    // 用递归实现快排
    quick_sort_recursive<int>(array, 0, sizeof(array) / sizeof(int) - 1);
    cout<<"!!!Recursive Quick Sort:";
    for (int i : array)
        cout<< i <<" ";

    cout<<endl<<"!!!Quick Sort Using Stack:";
    const char* char_array[] = {"I love programming!", "aaa", "aaaa", "aaaaaaaaaaaaaa", "aaaa"};
    // 用栈实现快排
    quick_sort_stack<const char*>(char_array, 0, sizeof(char_array) / sizeof(const char*) - 1, [](const char* e1, const char* e2) -> bool
    {
        return strlen(e1) < strlen(e2);
    });
    for (const char* i : char_array)
        cout<< i <<" ";

    cout<<endl<<"!!!Quick Sort Using Queue:";
    double double_array[] = {1.0, 3.1, 0.4444, 121.21, 21.0, 12, 12901, 101010, 3.1415926535};
    quick_sort_queue<double>(double_array, 0, sizeof(double_array) / sizeof(double) - 1, [](double e1, double e2) -> bool
    {
        return  e1 > e2;
    });
    for (double value : double_array)
        cout<<value<<" ";
    cout<<endl;
}

void heap_test()
{
    heap<int> h1;
    int array[] = {3, 5, 1, 4, 100, 43, 0x7fffffff, 12113, 12, 12, 1, 1, 33, 912};
    h1.heapify(array, sizeof(array) / sizeof(int));  // 从一个无序数组以O(n)时间复杂度建堆
    while(!h1.is_empty())
        cout<<h1.pop()<<" ";
    cout << endl;
    heap<std::string> h2(100, [](std::string string1, std::string string2) -> bool  // 比较器选择大的为优先级较高
    {
        return string1 >= string2;
    });
    h2.insert("aaa");
    h2.insert("bbb");
    h2.insert("ccc");
    cout<<h2<<endl;
    while (!h2.is_empty())
        cout<<h2.pop()<<" ";
    cout<<endl;
}
void doubleLinkedList_test()
{
    doubleLinkedList<int> linkedList({1, 3, 5}); // 建立int链表
    doubleLinkedList<int>::iterator iterator = linkedList.find_first(1);  // 找到元素1的位置得到迭代器
    linkedList.insert_before(iterator, 1);  // 在1之前插入1
    iterator++;  // 迭代器向后移动指向3
    linkedList.insert_after(iterator,100);  // 在3之后插入100
    linkedList.push_front(10);  // 在头部压入10
    linkedList.push_back(10);  // 在尾部压如10
    linkedList.modify(linkedList.front(), 12);  // 修改头部10为12
    linkedList.modify(linkedList.back(), 13);  // 修改尾部10为13
    cout<<"pop_front:"<<linkedList.pop_front()<<endl;  // 弹出头部元素并输出
    cout<<"pop_back:"<<linkedList.pop_back()<<endl;  // 弹出尾部元素并输出
    cout<<linkedList<<endl;  // 输出链表
    linkedList.clear();  // 清空链表
    if(linkedList.is_empty())
        cout<<"empty"<<endl<<"-------------------------"<<endl;  // 输出链表是否为空
    doubleLinkedList<const char *> stringList({"first", "second", "third"});  // 建立字符串常量链表
    stringList.push_back("first");
    stringList.push_back("second");
    cout<<stringList<<endl;  // 输出链表
    cout<<stringList.find_first_index("first")<<":"<<stringList.find_last_index("first")<<endl;  // 输出"first"出现的第一个位置和最后一个位置的索引
    int count = 0;
    for(auto element:stringList)  // range-based for遍历
        count++;
    cout<<count<<":"<<stringList.size()<<endl;  // 输出大小
}
void stack_test()
{
    stack<double> stack;
    stack.push(1.1);  // 推入栈中
    stack.push_all({1.2, 3.3 ,5.5});  // 推入栈中
    cout<<stack<<endl;
    cout<<stack.pop()<<endl;  // 弹出
    cout<<"top: "<<stack.top()<<endl;  // 顶部元素
    cout<<stack<<endl;
}
void queue_test()
{
    queue<char> queue({'a', 'b', 'c'});  // a -> b -> c
    queue.push_all({'a', 'b', 'c'});  // a -> b
    cout<<queue<<endl;
    cout<<queue.pop()<<endl;
    cout<<"head: "<<queue.head()<<", tail: "<<queue.tail()<<endl;  // 队首元素和队尾元素
    cout<<queue<<endl;
}