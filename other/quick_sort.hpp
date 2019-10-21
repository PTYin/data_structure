//
// Created by Peter on 2019/9/15.
//
#include "../primitive/Stack.hpp"
#include "../primitive/Queue.hpp"
#include <algorithm>

namespace pty
{
    template<typename T>
    static void swap(T &e1, T &e2)
    {
        T temp = e1;
        e1 = e2;
        e2 = temp;
    }

    template<typename T, typename CONTAINER>
    void quick_sort_stack(CONTAINER array, int left, int right, bool (*comparator)(T, T) = [](T e1, T e2) -> bool
    { return e1 < e2; })  // 去递归，用栈实现
    {
        using std::pair;
        Stack<pair<int, int>> _stack({pair<int, int>(left, right)});
        while (!_stack.is_empty())
        {
            pair<int, int> temp = _stack.pop();
            int _left = temp.first, _right = temp.second;
            if (_left >= _right)
                continue;
            T &pivot = array[_left];
            int l = _left + 1, r = _right;
            while (l < r)
            {
                while (l <= _right && comparator(array[l], pivot))
                    l++;
                while (r >= _left && comparator(pivot, array[r]))
                    r--;

                if (l < r)
                    swap(array[l++], array[r--]);
            }
            if (!comparator(pivot, array[r]))
                swap(pivot, array[r]);
            _stack.push_all({pair<int, int>(_left, r - 1), pair<int, int>(r + 1, _right)});
        }
    }

    template<typename T, typename CONTAINER>
    void quick_sort_queue(CONTAINER array, int left, int right, bool (*comparator)(T, T) = [](T e1, T e2) -> bool
    { return e1 < e2; })  // 去递归，用栈实现
    {
        using std::pair;
        Queue<pair<int, int>> queue({pair<int, int>(left, right)});
        while (!queue.is_empty())
        {
            pair<int, int> temp = queue.pop();
            int _left = temp.first, _right = temp.second;
            if (_left >= _right)
                continue;
            T &pivot = array[_left];
            int l = _left + 1, r = _right;
            while (l < r)
            {
                while (l <= _right && comparator(array[l], pivot))
                    l++;
                while (r >= _left && comparator(pivot, array[r]))
                    r--;

                if (l < r)
                    swap(array[l++], array[r--]);
            }
            if (!comparator(pivot, array[r]))
                swap(pivot, array[r]);
            queue.push_all({pair<int, int>(_left, r - 1), pair<int, int>(r + 1, _right)});
        }
    }

    template<typename T, typename CONTAINER>
    void quick_sort_recursive(CONTAINER array, int left, int right, bool (*comparator)(T, T) = [](T e1, T e2) -> bool
    { return e1 < e2; })
    {
        if (left >= right)
            return;
        T &pivot = array[left];
        int l = left + 1, r = right;
        while (l < r)// post_condition: l == r + 1
        {
            while (l <= right && comparator(array[l], pivot))
                l++;
            while (r >= left && comparator(pivot, array[r]))
                r--;
            if (l < r)
                swap(array[l++], array[r--]);
        }
        if (!comparator(pivot, array[r]))
            swap(pivot, array[r]);
        quick_sort_recursive(array, left, r - 1, comparator);
        quick_sort_recursive(array, r + 1, right, comparator);
    }
}