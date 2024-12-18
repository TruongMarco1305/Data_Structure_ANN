#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "sorting/ISort.h"
#include "heap/Heap.h"

template<class T>
class HeapSort: public ISort<T>{
public:
    void sort(T values[], int n, int(*order)(T& lhs, T& rhs)){
        Heap<T> heap(order);
        heap.heapify(values,n);
        for(int i = 0; i < n; i++){
            values[i] = heap.peek();
            heap.pop();
        }
    }
};

#endif /* HEAPSORT_H */