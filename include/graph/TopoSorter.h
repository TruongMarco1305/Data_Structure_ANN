/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        //TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
        if(!mode) return dfsSort(sorted);
        return bfsSort(sorted); 
    }
    DLinkedList<T> bfsSort(bool sorted=true){ 
        //TODO
        DLinkedList<T> result;
        int size = this->graph->size();
        if(size == 0) return result;

        DLinkedList<T> vertices = this->graph->vertices();
        DLinkedListSE<T> sortingVertices(vertices);
        if(sorted) sortingVertices.sort();

        xMap<T,int> inDegree(this->hash_code);
        typename DLinkedListSE<T>::Iterator it;
        for (it = sortingVertices.begin(); it != sortingVertices.end(); ++it){
            T vertex = *it;
            inDegree.put(vertex,this->graph->inDegree(vertex));
        }

        Queue<T> bfsQueue;
        for (it = sortingVertices.begin(); it != sortingVertices.end(); ++it){
            T vertex = *it;
            if (inDegree.get(vertex) == 0){
                bfsQueue.push(vertex);
            }
        }

        while(!bfsQueue.empty()){
            T vertex = bfsQueue.peek();
            bfsQueue.pop();
            result.add(vertex);

            DLinkedList<T> adjacencyList = this->graph->getOutwardEdges(vertex);
            typename DLinkedList<T>::Iterator it;
            for (it = adjacencyList.begin(); it != adjacencyList.end(); ++it){
                T neighbor = *it;
                inDegree.get(neighbor) --;
                if(inDegree.get(neighbor) == 0 && (!bfsQueue.contains(neighbor))){
                    bfsQueue.push(neighbor);
                }
            }
        }
        return result;
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
        DLinkedList<T> result;
        int size = this->graph->size();
        if(size == 0) return result;

        DLinkedListSE<T> sortingVertices(this->graph->vertices());
        if(sorted) sortingVertices.sort();
        Stack<T> dfsStack;

        xMap<T,bool> visited(this->hash_code);
        typename DLinkedListSE<T>::Iterator it;
        for (it = sortingVertices.begin(); it != sortingVertices.end(); ++it){
            T vertex = *it;
            visited.put(vertex,false);
        }

        for (it = sortingVertices.begin(); it != sortingVertices.end(); ++it){
            T vertex = *it;
            if(!visited.get(vertex)){
                dfsStack.push(vertex);
                visited.get(vertex) = true;
                while(!dfsStack.empty()){
                    T top = dfsStack.peek();
                    bool allNeighborsVisited = true;

                    DLinkedList<T> adjacencyList = this->graph->getOutwardEdges(top);
                    typename DLinkedList<T>::Iterator it;
                    for (it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
                        T adjacencyVertex = *it;
                        if (!visited.get(adjacencyVertex)) {
                            dfsStack.push(adjacencyVertex);
                            visited.get(adjacencyVertex) = true;
                            allNeighborsVisited = false;
                            break;
                        }
                    }
                    if (allNeighborsVisited) {
                        dfsStack.pop();
                        result.add(0,top);
                    }
                }
            }
        }
        return result;
    }

protected:

    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int));
    xMap<T, int> vertex2outDegree(int (*hash)(T&, int));
    DLinkedList<T> listOfZeroInDegrees();

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

