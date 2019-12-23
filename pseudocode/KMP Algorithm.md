# KMP Algorithm

```cpp
int* buildNext(char* pattern)
{
    int* next = new int[strlen(pattern)];
    int j=0, t=next[0]=-1;
    while(j<strlen(pattern)-1)
    {
        if(t < 0 || pattern[j] == pattern[t])
        {
            j++, t++;
            next[j] = pattern[j] != pattern[t] ? t : next[t];
        }
        else
            t = next[t];
    }
    return next;
}
bool match(char* string, char* pattern)
{
    int next[] = buildNext(pattern);
    int i=0, j=0;
    while(i<strlen(string) && j<strlen(pattern))
    {
        if(j < 0 || string[i]==pattern[j])
        {
            i++, j++;
        }
        else
        {
            j = next[j];
        }
    }
    delete[] next;
    if(j == pattern.size())
        return true;
    else
        return false;
}
```

