/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* fromVertex = this->getVertexNode(from);
        if(!fromVertex) throw VertexNotFoundException(this->vertex2str(from));
        typename AbstractGraph<T>::VertexNode* toVertex = this->getVertexNode(to);
        if(!toVertex) throw VertexNotFoundException(this->vertex2str(to));
        if(fromVertex->equals(toVertex)){
            fromVertex->connect(toVertex,weight);
            return;
        }
        fromVertex->connect(toVertex,weight);
        toVertex->connect(fromVertex,weight);
    }
    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* fromVertex = this->getVertexNode(from);
        if(!fromVertex) throw VertexNotFoundException(this->vertex2str(from));
        typename AbstractGraph<T>::VertexNode* toVertex = this->getVertexNode(to);
        if(!toVertex) throw VertexNotFoundException(this->vertex2str(to));
        if(!fromVertex->getEdge(toVertex)){
            typename AbstractGraph<T>::Edge temp(this->getVertexNode(from),this->getVertexNode(to));
            throw EdgeNotFoundException(this->edge2Str(temp));
        }
        if(fromVertex->equals(toVertex)){
            fromVertex->removeTo(toVertex);
            return;
        }
        fromVertex->removeTo(toVertex);
        toVertex->removeTo(fromVertex);
    }
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* vertexNode = this->getVertexNode(vertex);
        if(!vertexNode) throw VertexNotFoundException(this->vertex2str(vertex));
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it;
        for(it = this->nodeList.begin(); it != this->nodeList.end(); ++it){
            typename AbstractGraph<T>::VertexNode* v = *it;
            if(v->getEdge(vertexNode))v->removeTo(vertexNode);
            if(vertexNode->getEdge(v))vertexNode->removeTo(v);
        }
        this->nodeList.removeItem(vertexNode);
        delete vertexNode;
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T>* graph = new UGraphModel<T>(vertexEQ,vertex2str);
        for(int i = 0; i < nvertices; i++){
            graph->add(vertices[i]);
        }
        for(int i = 0; i < nedges; i++){
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
