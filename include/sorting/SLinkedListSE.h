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

#ifndef SLINKEDLISTSE_H
#define SLINKEDLISTSE_H
#include "list/SLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class SLinkedListSE: public SLinkedList<T>{
public:    
    void sort(int (*comparator)(T&, T&) = 0) {
        if (this->count <= 1) return;

        typename SLinkedList<T>::Node* sortedHead = nullptr;

        for (int size = 1; size < this->count; size *= 2) {
            typename SLinkedList<T>::Node* curr = this->head->next; 
            typename SLinkedList<T>::Node* sortedTail = this->head;

            while (curr && curr != this->tail) {
                typename SLinkedList<T>::Node* leftNode = curr;
                typename SLinkedList<T>::Node* second;

                //typename SLinkedList<T>::Node* rightNode = split(leftNode,size)
                typename SLinkedList<T>::Node* rightNode;
                typename SLinkedList<T>::Node* temp = leftNode;
                for(int i = 1; temp && temp != this->tail && i < size; i++){
                    temp = temp->next;
                }
                if(!temp || temp == this->tail) rightNode = nullptr;
                else{
                    second = temp->next;
                    temp->next = this->tail;
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
                    curr = second;
                }

                // typename SLinkedList<T>::Node* merged = merge(leftNode, rightNode, comparator);
                typename SLinkedList<T>::Node* merged;
                if (!leftNode){
                    merged = rightNode;
                } else if (!rightNode){
                    merged = leftNode;
                } else {
                    typename SLinkedList<T>::Node dummy;
                    typename SLinkedList<T>::Node* curr = &dummy;

                    while (leftNode && leftNode != this->tail && rightNode && rightNode != this->tail) {
                        if (this->compare(leftNode->data, rightNode->data, comparator) <= 0) {
                            curr->next = leftNode;
                            leftNode = leftNode->next;
                        } else {
                            curr->next = rightNode;
                            rightNode = rightNode->next;
                        }
                        curr = curr->next;
                    }

                    while (leftNode && leftNode != this->tail) {
                        curr->next = leftNode;
                        leftNode = leftNode->next;
                        curr = curr->next;
                    }
                    while (rightNode && rightNode != this->tail) {
                        curr->next = rightNode;
                        rightNode = rightNode->next;
                        curr = curr->next;
                    }

                    curr->next = this->tail;
                    merged = dummy.next;
                }
                sortedTail->next = merged;
                while (sortedTail->next && sortedTail->next != this->tail) {
                    sortedTail = sortedTail->next;
                }
            }
            sortedTail->next = this->tail;
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

#endif /* SLINKEDLISTSE_H */

