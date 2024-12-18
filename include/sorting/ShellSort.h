#ifndef SHELLSORT_H
#define SHELLSORT_H
#include "sorting/ISort.h"
#include "list/XArrayList.h"

template<class T>
class ShellSort: public ISort<T>{
private:
    XArrayList<int> num_segments_list;
    int num_phases;
public:
    ShellSort(int num_segments[], int num_phases){
        for(int i = 0; i < num_phases; i++){
            num_segments_list.add(num_segments[i]);
        }
        this->num_phases = num_phases;
    }

    void sort(T values[], int n, int(*order)(T& lhs, T& rhs)){
        for (int phase = this->num_phases-1; phase >= 0; --phase){
            int segments = this->num_segments_list.get(phase); 
            for (int segment_idx = 0; segment_idx < segments; ++segment_idx) {
                for (int i = segment_idx; i < n; i += segments) {
                    T temp = values[i];
                    int j = i - segments;
                    while (j >= 0 && order(values[j],temp) == 1) {
                        values[j + segments] = values[j];
                        j -= segments;
                    }
                    values[j + segments] = temp;
                }
            }
        }
    }
};

#endif /* SHELLSORT_H */