//
// Created by Peter on 2019/10/21.
//

#ifndef DATA_STRUCTURE_KMP_HPP
#define DATA_STRUCTURE_KMP_HPP

#include <cstring>

namespace pty
{
    class KMP
    {
    private:
        char* pattern;
        int* next;
        int m;
        void buildNext()
        {
            int j=0;
            next = new int[m+1];
            int t = next[0] = -1;
            while (j < m)
            {
                if(t < 0 || pattern[j] == pattern[t])
                {
                    j++, t++;
                    next[j] = pattern[j] != pattern[t] ? t : next[t];
                }
                else
                    t = next[t];
            }
        }

    public:
        explicit KMP(const char* pattern_ = nullptr) : pattern(nullptr), next(nullptr)
        {
            m = strlen(pattern_);
            pattern = new char[m+1];
            strcpy(pattern, pattern_);
            buildNext();
        }

        virtual ~KMP()
        {
            delete[] pattern;
            delete[] next;
        }

        void setPattern(const char* pattern_)
        {
            m = strlen(pattern_);
            if(m <= strlen(pattern))
            {
                strcpy(pattern, pattern_);
                buildNext();
            }
            else
            {
                delete[] pattern;
                delete[] next;
                pattern = new char[m+1];
                next = new int[m+1];
                strcpy(pattern, pattern_);
                buildNext();
            }
        }

        int findIn(const char* string)
        {
            int n = strlen(string);
            int i=0, j=0;
            while(j < m && i < n)
            {
                if(0 > j || string[i] == pattern[j])
                    i++, j++;
                else
                    j = next[j];
            }
            return i-j <= n-m ? i-j : -1;
        }
    };

}

#endif //DATA_STRUCTURE_KMP_HPP
