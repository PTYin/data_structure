# Quick Sort Algorithm

```cpp
<template typename A>
void qsort(A array, int left, int right)
{
    queue<pair<int, int>> q;
    q.push((left, right));
    while(!q.empty())
    {
        l, r = q.pop();
        int pivot = array[l];
        int i = l, j = r;
        while(i<=r&&array[i]<=pivot)
            i++;
        while(j>=r&&array[j]>=pivot)
            j--;
        
        swap(a[i], a[j]);
    }
}
```

