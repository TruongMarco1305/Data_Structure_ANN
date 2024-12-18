#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include "sorting/ISort.h"

template<class T>
class BubbleSort: public ISort<T>{
public:
    void sort(T values[], int n, int(*order)(T& lhs, T& rhs)){
        bool swapped;
        for(int i = 0; i < n - 1; i++){
            swapped = false;
            for(int j = 0; j < n - i - 1; j++){
                if(order(values[j],values[j+1]) == 1){
                    swap(values[j],values[j+1]);
                    swapped = true;
                }
            }
            if(!swapped) break;
        }
    }
};

#endif /* BUBBLESORT_H */