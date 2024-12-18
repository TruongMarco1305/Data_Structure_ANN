/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef XARRAYLISTSE_H
#define XARRAYLISTSE_H
#include "list/XArrayList.h"
#include "sorting/ISort.h"

template<class T>
class XArrayListSE: public XArrayList<T>{
public:    
    void sort(int (*comparator)(T&, T&) = 0) {
        for(int i = 0; i < this->count - 1; i++){
            for(int j = i + 1; j < this->count; j++){
                if(this->compare(this->data[i],this->data[j],comparator)){
                    swap(this->data[i],this->data[j]);
                }
            }
        }
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* XARRAYLISTSE_H */

