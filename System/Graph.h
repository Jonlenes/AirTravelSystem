#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "DataStructures/List.h"
#include <map>
#include <vector>
using namespace VertexData;
using namespace EdgeData;

class Graph
{
public:
    Graph();
    void setEdge(string strOrigem, string strDestino, Edge edge);
    void setVertex(Vertex vertex);

    double getPesoPathActual(int vertice, int edgeSaida) const;
    double getDtoVertice(int vertice, int edge);
    double getPesoAresta(int idxAresta) const;
    int getIndexVertice(string name) const;
    Vertex &getVertex(int index);
    Edge getEdge(int index) const;
    Edge getEdge(int indexVertex, int indexEdge) const;
    int getQtdeVertices() const;
    int getQtdeEdges() const;
    int getQtdeEdges(int indexVertex) const;

    void printGraphTemporaria(); //Esse método é apenas para testes... deve ser removido
    vector<string> getKeys();
    bool operator < (Vertex &other);

private:
    myList::List<Vertex> listVertes;
    myList::List<Edge> listEdge;
    myList::List< myList::List<int> > listAdj;
    map<string, int> mapVertice;

    struct RetrieveKey
    {
        template <typename T>
        typename T::first_type operator()(T keyValuePair) const
        {
            return keyValuePair.first;
        }
    };
};

#endif // GRAPH_H
