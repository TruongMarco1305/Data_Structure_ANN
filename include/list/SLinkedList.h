/*
 * File:   SLinkedList.h
 */

#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class SLinkedList : public IList<T>
{
public:
    class SNode;        // Forward declaration
    class Iterator;    // Forward declaration

protected:
    SNode *head; // this SNode does not contain user's data
    SNode *tail; // this SNode does not contain user's data
    int count;
    bool (*itemEqual)(T &lhs, T &rhs);        // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(SLinkedList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    SLinkedList(
        void (*deleteUserData)(SLinkedList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0);
    SLinkedList(const SLinkedList<T> &list);
    SLinkedList<T> &operator=(const SLinkedList<T> &list);
    ~SLinkedList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T &get(int index);
    int indexOf(T item);
    bool contains(T item);
    string toString(string (*item2str)(T &) = 0);
    // Inherit from IList: END

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(SLinkedList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    bool contains(T array[], int size)
    {
        int idx = 0;
        for (SLinkedList<T>::Iterator it = begin(); it != end(); it++)
        {
            if (!equals(*it, array[idx++], this->itemEqual))
                return false;
        }
        return true;
    }

    /*
     * free(SLinkedList<T> *list):
     *  + to remove user's data (type T, must be a pointer type, e.g.: int*, Point*)
     *  + if users want a SLinkedList removing their data,
     *      he/she must pass "free" to constructor of SLinkedList
     *      Example:
     *      SLinkedList<T> list(&SLinkedList<T>::free);
     */
    static void free(SLinkedList<T> *list)
    {
        typename SLinkedList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }

    /* begin, end and Iterator helps user to traverse a list forwardly
     * Example: assume "list" is object of SLinkedList

     SLinkedList<char>::Iterator it;
     for(it = list.begin(); it != list.end(); it++){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

    /* last, beforeFirst and BWDIterator helps user to traverse a list backwardly
     * Example: assume "list" is object of SLinkedList

     SLinkedList<char>::BWDIterator it;
     for(it = list.last(); it != list.beforeFirst(); it--){
            char item = *it;
            std::cout << item; //print the item
     }
     */

protected:
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }
    void copyFrom(const SLinkedList<T> &list);
    void removeInternalData();
    SNode *getPreviousNodeOf(int index);

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    class SNode
    {
    public:
        T data;
        SNode *next;
        friend class SLinkedList<T>;

    public:
        SNode(SNode *next = 0)
        {
            this->next = next;
        }
        SNode(T data, SNode *next = 0)
        {
            this->data = data;
            this->next = next;
        }
    };

    //////////////////////////////////////////////////////////////////////
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        SNode *pNode;

    public:
        Iterator(SLinkedList<T> *pList = 0, bool begin = true)
        {
            if (begin)
            {
                if (pList != 0)
                    this->pNode = pList->head->next;
                else
                    pNode = 0;
            }
            else
            {
                if (pList != 0)
                    this->pNode = pList->tail;
                else
                    pNode = 0;
            }
            this->pList = pList;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            SNode *pNext = pNode->next;
            if (removeItemData != 0)
                removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }

        T &operator*()
        {
            return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            pNode = pNode->next;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
};
//////////////////////////////////////////////////////////////////////
// Define a shorter name for SLinkedList:

template <class T>
using SList = SLinkedList<T>;

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
SLinkedList<T>::SLinkedList(
    void (*deleteUserData)(SLinkedList<T> *),
    bool (*itemEqual)(T &, T &))
{
    // TODO
    this->tail = new SNode();
    this->head = new SNode(this->tail);
    this->count = 0;
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;
}

template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList<T> &list)
{
    // TODO
    this->tail = new SNode();
    this->head = new SNode(this->tail);
    this->count = 0;
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;
    for (SLinkedList<T>::Iterator it : list){
        T node = *it;
        this->add(node);
    }
}

template <class T>
SLinkedList<T> &SLinkedList<T>::operator=(const SLinkedList<T> &list)
{
    // TODO
    this->copyFrom(list);
    return *this;
}

template <class T>
SLinkedList<T>::~SLinkedList()
{
    // TODO
    this->removeInternalData();
    delete this->head;
    delete this->tail;
}

template <class T>
void SLinkedList<T>::add(T e)
{
    // TODO
    if (this->count == 0)
    {
        SNode *newNode = new SNode(e, this->tail);
        this->head->next = newNode;
        this->count++;
        return;
    }
    SNode* prevTail = this->head->next;
    while(prevTail->next != this->tail) prevTail = prevTail->next;
    SNode *newNode = new SNode(e, this->tail);
    prevTail->next = newNode;
    this->count++;
}
template <class T>
void SLinkedList<T>::add(int index, T e)
{
    // TODO
    if (index < 0 || index > count)
        throw out_of_range("Index is out of range!");
    SNode *newNode;
    if (index == 0)
    {
        newNode = new SNode(e,this->head->next);
        this->head->next = newNode;
        this->count++;
        return;
    }

    if (index == this->count)
    {
        this->add(e);
        return;
    }

    newNode = new SNode(e);
    SNode *current = this->head->next;
    SNode *prev = nullptr;
    int i = 0;
    while (i < index)
    {
        prev = current;
        current = current->next;
        i++;
    }
    prev->next = newNode;
    newNode->next = current;
    this->count++;
}

template <class T>
typename SLinkedList<T>::SNode *SLinkedList<T>::getPreviousNodeOf(int index)
{
    /**
     * Returns the SNode preceding the specified index in the singly linked list.
     */
    // TODO
    int i = 0;
    SNode* prev = this->head;
    while (i < index){
        prev = prev->next;
        i ++;
    }
    return prev;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    // TODO
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is out of range!");

    if (this->count == 1)
    {
        SNode *tempNode = this->head->next;
        T deleteData = tempNode->data;
        this->head->next = this->tail;
        this->count--;
        delete tempNode;
        return deleteData;
    }

    if (index == 0)
    {
        SNode *tempNode = this->head->next;
        T deleteData = tempNode->data;
        this->head->next = tempNode->next;
        this->count--;
        delete tempNode;
        return deleteData;
    }

    SNode *current = this->head->next;
    SNode* prev = nullptr;
    int i = 0;
    while (i < index)
    {
        prev = current;
        current = current->next;
        i++;
    }
    T deleteData = current->data;
    prev->next = current->next;
    delete current;
    this->count--;
    return deleteData;
}

template <class T>
bool SLinkedList<T>::empty()
{
    // TODO
    return this->count == 0;
}

template <class T>
int SLinkedList<T>::size()
{
    // TODO
    return this->count;
}

template <class T>
void SLinkedList<T>::clear()
{
    // TODO
    this->removeInternalData();
}

template <class T>
T &SLinkedList<T>::get(int index)
{
    // TODO
    if (index < 0 || index >= count)
        throw out_of_range("Index is out of range!");
    SNode *current = this->head->next;
    int i = 0;
    SLinkedList<T>::Iterator it = this->begin();
    for(it; it != this->end(); ++it){
        if (i == index) break;
    }
    return *it;
}

template <class T>
int SLinkedList<T>::indexOf(T item)
{
    // TODO
    int index = 0;
    for(SLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it){
        T data = *it;
        if(this->equals(data,item,this->itemEqual)) return index;
        index ++;
    }
    return -1;
}

template <class T>
bool SLinkedList<T>::removeItem(T item, void (*removeItemData)(T))
{
    // TODO
    int index = 0;
    for(SLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it){
        T data = *it;
        if(this->equals(data,item,this->itemEqual)){
            if (removeItemData)
            {
                removeItemData(data);
            }
            this->removeAt(index);
            return true;
        }
        index ++;
    }
    return false;
}

template <class T>
bool SLinkedList<T>::contains(T item)
{
    // TODO
    return this->indexOf(item) != -1;
}

template <class T>
string SLinkedList<T>::toString(string (*item2str)(T &))
{
    /**
     * Converts the list into a string representation, where each element is formatted using a user-provided function.
     * If no custom function is provided, it directly uses the element's default string representation.
     * Example: If the list contains {1, 2, 3} and the provided function formats integers, calling toString would return "[1, 2, 3]".
     *
     * @param item2str A function that converts an item of type T to a string. If null, default to string conversion of T.
     * @return A string representation of the list with elements separated by commas and enclosed in square brackets.
     */
    // TODO
    if (this->count == 0)
        return "[]";

    stringstream ss;
    ss << "[";
    for(SLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it){
        T data = *it;
        if (item2str)
        {
            ss << item2str(data) << ", ";
        }
        else
        {
            ss << data << ", ";
        }
    }
    string ans = ss.str();
    ans.pop_back();
    ans.pop_back();
    ans += "]";
    return ans;
}

template <class T>
void SLinkedList<T>::copyFrom(const SLinkedList<T> &list)
{
    /**
     * Copies the contents of another doubly linked list into this list.
     * Initializes the current list to an empty state and then duplicates all data and pointers from the source list.
     * Iterates through the source list and adds each element, preserving the order of the nodes.
     */
    // TODO
    this->removeInternalData();
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;
    if (list.count == 0) return;
    for(SLinkedList<T>::Iterator it : list){
        T data = *it;
        this->add(data);
    }
}

template <class T>
void SLinkedList<T>::removeInternalData()
{
    /**
     * Clears the internal data of the list by deleting all nodes and user-defined data.
     * If a custom deletion function is provided, it is used to free the user's data stored in the nodes.
     * Traverses and deletes each SNode between the head and tail to release memory.
     */
    // TODO
    if (this->count == 0)
        return;
    if (this->deleteUserData)
    {
        this->deleteUserData(this);
    }
    else
    {
        for(SLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it){
            it.remove();
        }
    }
    head->next = tail;
    this->count = 0;
}

#endif /* SLINKEDLIST_H */