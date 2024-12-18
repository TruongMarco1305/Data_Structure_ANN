#ifndef STRAIGHTSELECTIONSORT_H
#define STRAIGHTSELECTIONSORT_H
#include "sorting/ISort.h"

template<class T>
class StraightSelectionSort: public ISort<T>{
public:
    void sort(T values[], int n, int(*order)(T& lhs, T& rhs)){
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (order(values[j],values[min_idx]) == -1) {
                    min_idx = j; 
                }
            }
            swap(values[i], values[min_idx]);
        }
    }
};

#endif /* STRAIGHTSELECTIONSORT_H */