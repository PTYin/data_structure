//
// Created by Peter on 2019/9/15.
//

#ifndef DATA_STRUCTURE_HEAP_HPP
#define DATA_STRUCTURE_HEAP_HPP

#include <vector>
#include <iostream>
#include <functional>
#include <assert.h>

#define DEFAULT_VOLUME                  100
#define INDEX_VALID(i, size)            0 <= i && i < size
#define PARENT_VALID(i)                 i > 0
#define LCHILD_VALID(i, size)           (i << 1) + 1< size
#define RCHILD_VALID(i, size)           (i << 1) + 2 < size
#define PARENT(i)                       (i - 1) >> 1
#define LCHILD(i)                       (i << 1) + 1
#define RCHILD(i)                       (i << 1) + 2
#define MORE_PRIOR(a, b)                comparator(container[a], container[b]) ? a : b
#define MOST_PRIOR(a, b, c)             comparator(container[a], container[b]) ? (comparator(container[a], container[c]) ? \
                                        a : (comparator(container[b], container[c]) ? b : c))  \
                                        : (comparator(container[b], container[c]) ? b : c)
namespace pty
{
    using std::vector;

    template<typename T>
    class Heap
    {
    private:
        void swap(int i, int j)
        {
            if (i == j)
                return;
            T temp = container[i];
            container[i] = container[j];
            container[j] = temp;
        }

    protected:
        int length;

        vector<T> container;

        bool (*comparator)(T, T);  // 优先级比较器，默认a < b则a的优先级大于b的优先级
        void percolateUp(int index)
        {
            if (PARENT_VALID(index))
            {
                int parent = PARENT(index);
                int more_prior = MORE_PRIOR(index, parent);
                if (more_prior != index)
                    return;
                swap(index, parent);
                percolateUp(parent);  // assert: more_prior == parent

            }
        }

        void percolateDown(int index)
        {
            if (RCHILD_VALID(index, length))  // 既有左孩子又有右孩子
            {
                int most_prior = MOST_PRIOR(index, LCHILD(index), RCHILD(index));
                if (most_prior == index)
                    return;
                swap(index, most_prior);
                percolateDown(most_prior);
            }
            else if (LCHILD_VALID(index, length))
            {
                int more_prior = MORE_PRIOR(index, LCHILD(index));
                if (more_prior == index)
                    return;
                swap(index, more_prior);
                percolateDown(more_prior);
            }
            else
                return;
        }

    public:
        explicit Heap(int _volume = DEFAULT_VOLUME,
                      bool (*_comparator)(T, T) = [](T prior, T o) -> bool
                      { return prior <= o; })
                : length(0), comparator(_comparator), container(_volume)
        {}

        void clear()
        {
            container.clear();
            length = 0;
        }

        Heap(const Heap &other) : length(other.length), comparator(other.comparator), container(other.container)
        {
            for (int i = 0; i <= other.length; i++)
            {
                container[i] = other.container[i];
            }
        }

        T pop()
        {
            assert(length>0);
            T temp = container[0];
            container[0] = container[--length];
            percolateDown(0);
            return temp;
        }

        T top() const
        {
            return container[0];
        }

        void insert(T element)
        {
            container[length] = element;
            length++;
            percolateUp(length - 1);
        }

        template <typename CONTAINER>
        void heapify(CONTAINER array, int size)  // 从一个无序数组以O(n)时间复杂度建堆
        {
            if (!size)
                return;
            for (int i = 0; i < size; i++)
            {
                container[i] = array[i];
            }
            length = size;
            for (int i = PARENT(length - 1); INDEX_VALID(i, length); i--)
                percolateDown(i);
        }

        Heap &operator=(const Heap &) = default;

        bool is_empty() const
        {
            return length == 0;
        }

        int size() const
        {
            return length;
        }

        friend std::ostream &operator<<(std::ostream &o, const Heap &h)
        {
            for (int i = 0; i < h.length; i++)
                o << "[" << i << ":" << h.container[i] << "]";
            return o;
        }
    };
}

#endif //DATA_STRUCTURE_HEAP_HPP
