#include "doubleLinkedList.hpp"
#include "stack.hpp"
#include "queue.hpp"

using namespace pty;
using std::cout;
using std::endl;

void doubleLinkedList_test();
void stack_test();
void queue_test();
int main()
{
    doubleLinkedList_test();
    cout<<"##########################"<<endl;
    stack_test();
    queue_test();
    return 0;
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