#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "sorting/ISort.h"
#include "stacknqueue/Stack.h"

template<class T>
class QuickSort: public ISort<T>{
public:
    void sort(int values[], int n, int(*order)(T& lhs, T& rhs)){
        Stack<T> s;
        s.push(0);
        s.push(n-1);
        int top = 1;
        int l,h;
        while(top >= 0){
            h = s.pop();
            top--;
            l = s.pop();
            top--;

            // int p = partition(values,l,h);
            int x = values[h];
            int i = (l - 1);
            for (int j = l; j <= h - 1; j++) { 
                if (order(values[j],x) <= 0) { 
                    i++; 
                    swap(values[i], values[j]); 
                } 
            } 
            swap(values[i + 1], values[h]); 
            int p = i + 1;

            if(p - 1 > l){
                s.push(l);
                top++;
                s.push(p - 1);
                top++;
            }

            if(p + 1 < h){
                s.push(p + 1);
                top++;
                s.push(h);
                top++;
            }
        }
    }
};

#endif /* QUICKSORT_H */