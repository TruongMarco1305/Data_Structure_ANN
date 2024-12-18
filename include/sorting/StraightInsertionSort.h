#ifndef STRAIGHTINSERTIONSORT_H
#define STRAIGHTINSERTIONSORT_H
#include "sorting/ISort.h"

template<class T>
class StraightInsertionSort: public ISort<T>{
public:
    void sort(T values[], int n, int(*order)(T& lhs, T& rhs)){
        for (int i = 1; i < n; ++i) {
            T key = values[i];
            int j = i - 1;

            while (j >= 0 && order(values[j],key) == 1) {
                values[j + 1] = values[j];
                j = j - 1;
            }
            values[j + 1] = key;
        }
    }
};

#endif /* STRAIGHTINSERTIONSORT_H */