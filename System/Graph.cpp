#include "Graph.h"
#include <iostream>
#include <QDebug>
using namespace std;

Graph::Graph()
{

}

void Graph::setEdge(string strOrigem, string strDestino, Edge edge)
{
    edge.setDestino(getIndexVertice(strDestino));
    edge.setIndex(listEdge.count());
    listEdge.append(edge);
    listAdj[getIndexVertice(strOrigem)].append(edge.getIndex());
}

void Graph::setVertex(Vertex vertex)
{
    if (mapVertice.find(vertex.getName()) == mapVertice.end())
    {
        mapVertice[vertex.getName()] = listVertes.size();
        listVertes.append(vertex);
        listAdj.append(myList::List<int>());
    }
}

double Graph::getPesoPathActual(int vertice, int edgeSaida) const
{
    double diffHours;

    if(listVertes[vertice].getHoursDepature())
        diffHours = listEdge[edgeSaida].getHoursSaida() - *listVertes[vertice].getHoursDepature();
    else {
        if(listVertes[vertice].getEdgeVisit() == -1)
            return listVertes[vertice].getD();
        diffHours = (listEdge[edgeSaida].getHoursSaida() -
                     listEdge[listVertes[vertice].getEdgeVisit()].gethoursChegada());
    }
    if(diffHours < 0 || (diffHours < 0.5 && listEdge[listVertes[vertice].getEdgeVisit()].getCodVoo() !=
                         listEdge[edgeSaida].getCodVoo())) diffHours += 24;
    return (listVertes[vertice].getD() + diffHours);
}

double Graph::getDtoVertice(int vertice, int edge)
{
    if(getVertex(vertice).getEdgeVisit() == -1) return getVertex(vertice).getD();;
    double diff = getEdge(getVertex(vertice).getEdgeVisit()).gethoursChegada() - getEdge(edge).gethoursChegada();
    if(diff > 0) return (getVertex(vertice).getD() + diff);
    return getVertex(vertice).getD();
}

double Graph::getPesoAresta(int idxAresta) const
{
    return getEdge(idxAresta).getPeso();
}

int Graph::getIndexVertice(string name) const
{
    return mapVertice.find(name)->second;
}

Vertex &Graph::getVertex(int index)
{
    return listVertes[index];
}

Edge Graph::getEdge(int index) const
{
    return listEdge[index];
}

Edge Graph::getEdge(int indexVertex, int indexEdge) const
{
    return listEdge[listAdj[indexVertex][indexEdge]];
}

int Graph::getQtdeVertices() const
{
    return listVertes.count();
}

int Graph::getQtdeEdges() const
{
    return listEdge.count();
}

int Graph::getQtdeEdges(int indexVertex) const
{
    return listAdj[indexVertex].count();
}

void Graph::printGraphTemporaria()
{
    for(int i = 0; i < listAdj.size(); i++) {
        for(int j = 0; j < listAdj[i].size(); j++) {
            qDebug() << QString::fromStdString(getEdge(listAdj[i][j]).getCodVoo() +  "\t" +
                                               getVertex(i).getName() + "\t" +
                                               getEdge(listAdj[i][j]).getHoursSaida().toString() + "\t" +
                                               getVertex(getEdge(listAdj[i][j]).getDestino()).getName() + "\t" +
                                               getEdge(listAdj[i][j]).gethoursChegada().toString() + "\t");
        }
    }
}

vector<string> Graph::getKeys()
{
    vector<string> keys;
    transform(mapVertice.begin(), mapVertice.end(), back_inserter(keys), RetrieveKey());
    return keys;
}
