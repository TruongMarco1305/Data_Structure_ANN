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

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&, T&) = 0) {
        if (this->count <= 1) return;

        typename DLinkedList<T>::Node* sortedHead = nullptr;

        for (int size = 1; size < this->count; size *= 2) {
            typename DLinkedList<T>::Node* curr = this->head->next; 
            typename DLinkedList<T>::Node* sortedTail = this->head;

            while (curr && curr != this->tail) {
                typename DLinkedList<T>::Node* leftNode = curr;
                typename DLinkedList<T>::Node* second;

                //typename DLinkedList<T>::Node* rightNode = split(leftNode,size)
                typename DLinkedList<T>::Node* rightNode;
                typename DLinkedList<T>::Node* temp = leftNode;
                for(int i = 1; temp && temp != this->tail && i < size; i++){
                    temp = temp->next;
                }
                if(!temp || temp == this->tail) rightNode = nullptr;
                else{
                    second = temp->next;
                    temp->next = this->tail;
                    if (second) second->prev = nullptr;
                    rightNode = second;
                }
                
                // curr = split(rightNode, size);
                temp = rightNode;
                for(int i = 1; temp && temp != this->tail && i < size; i++){
                    temp = temp->next;
                }
                if(!temp || temp == this->tail) curr = nullptr;
                else{
                    second = temp->next;
                    temp->next = this->tail;
                    if (second) second->prev = nullptr;
                    curr = second;
                }

                // typename DLinkedList<T>::Node* merged = merge(leftNode, rightNode, comparator);
                typename DLinkedList<T>::Node* merged;
                if (!leftNode){
                    merged = rightNode;
                } else if (!rightNode){
                    merged = leftNode;
                } else {
                    typename DLinkedList<T>::Node dummy;
                    typename DLinkedList<T>::Node* curr = &dummy;

                    while (leftNode && leftNode != this->tail && rightNode && rightNode != this->tail) {
                        if (this->compare(leftNode->data, rightNode->data, comparator) <= 0) {
                            curr->next = leftNode;
                            leftNode->prev = curr;
                            leftNode = leftNode->next;
                        } else {
                            curr->next = rightNode;
                            rightNode->prev = curr;
                            rightNode = rightNode->next;
                        }
                        curr = curr->next;
                    }

                    while (leftNode && leftNode != this->tail) {
                        curr->next = leftNode;
                        leftNode->prev = curr;
                        leftNode = leftNode->next;
                        curr = curr->next;
                    }
                    while (rightNode && rightNode != this->tail) {
                        curr->next = rightNode;
                        rightNode->prev = curr;
                        rightNode = rightNode->next;
                        curr = curr->next;
                    }

                    curr->next = this->tail;
                    this->tail->prev = curr;

                    merged = dummy.next;
                }

                sortedTail->next = merged;
                merged->prev = sortedTail;

                while (sortedTail->next && sortedTail->next != this->tail) {
                    sortedTail = sortedTail->next;
                }
            }

            sortedTail->next = this->tail;
            this->tail->prev = sortedTail;
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

#endif /* DLINKEDLISTSE_H */

