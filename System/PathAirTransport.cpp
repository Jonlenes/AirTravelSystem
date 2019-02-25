#include "PathAirTransport.h"
#include "Util.h"
#include "Date.h"
#include <fstream>
#include <string.h>
#include <QDebug>
#include <queue>
using namespace std;
using namespace myTime;

PathAirTransport::PathAirTransport()
{
    graph = __null;
}

PathAirTransport::PathAirTransport(const char *path)
{
    graph = __null;
    readFileTransport(path);
}

void PathAirTransport::readFileTransport(const char *path)
{
    if(graph) delete graph;
    graph = new Graph();

    fstream fileTransp(path);
    string lineVoo;
    int i = 0;
    char *lineVooChar;
    char codVoo[50];
    char cityOrigem[100];
    char cityDestino[100];
    int hoursSaida[2];
    int hoursChegada[2];

    if(fileTransp.is_open()) {
        try {
            while(fileTransp.good()) {
                getline(fileTransp, lineVoo);
                lineVooChar = (char *) lineVoo.c_str();

                //if(lineVoo == "AFRANCE9518 Hamburg 08:57 Dubai 09:24 09:51 Florenca 10:18")
                    //qDebug() << QString::fromStdString(lineVoo);

                sscanf(lineVooChar, "%[^ ] %[^ ] %d:%d %[^ ] %d:%d", codVoo, cityOrigem, &hoursSaida[0], &hoursSaida[1], cityDestino, &hoursChegada[0], &hoursChegada[1]);
                lineVooChar = Util::remove(lineVooChar, ' ', 5);
                graph->setVertex(Vertex(cityOrigem));
                graph->setVertex(Vertex(cityDestino));
                graph->setEdge(cityOrigem, cityDestino, Edge(codVoo, Date(hoursChegada[0], hoursChegada[1]), Date(hoursSaida[0], hoursSaida[1]), i));
                strcpy(cityOrigem, cityDestino);

                while(sscanf(lineVooChar, "%d:%d %[^ ] %d:%d", &hoursSaida[0], &hoursSaida[1], cityDestino, &hoursChegada[0], &hoursChegada[1]) == 5) {
                    lineVooChar = Util::remove(lineVooChar, ' ', 3);
                    graph->setVertex(Vertex(cityDestino));
                    graph->setEdge(cityOrigem, cityDestino, Edge(codVoo, myTime::Date(hoursChegada[0], hoursChegada[1]), myTime::Date(hoursSaida[0], hoursSaida[1]), i));
                    strcpy(cityOrigem, cityDestino);
                }
            }
        } catch (...) {
            throw string("file with datas invalid.");
        }
    } else {
        throw string("Erro path file.");
    }
    fileTransp.close();
    graph->printGraphTemporaria();
}

string PathAirTransport::findBetterPath(string origem, string destino, Date hoursDepature,
                                        Date hoursArrivel, int qtdeDays, myList::List<timesCitys> &listTimes,
                                        myList::List<int> &listVerticePath, myList::List<int> &listEdgePath)
{
    int previus = -1;
    string path;

    this->listTimes = &listTimes;
    this->listVerticePath = &listVerticePath;
    this->listEdgePath = &listEdgePath;

    initializeSingleSource(graph, graph->getIndexVertice(origem), hoursDepature);
    dijkstra(graph);
    printPath(graph, graph->getIndexVertice(origem), graph->getIndexVertice(destino), previus, path);
    if(!listTimes.isEmpty() && path != "Nao há caminho.")
    {
        double totalTime = listTimes[listTimes.count() - 1].time;
        int daysSpent = ((int) (totalTime / 24));
        double timeDay = daysSpent == 0 ? (hoursDepature.toDouble() + totalTime) : (totalTime -  (daysSpent * 24));
        if(daysSpent > qtdeDays || (daysSpent == qtdeDays && timeDay > hoursArrivel.toDouble()))
            path = "Nenhum caminho encontrado que chegasse ao destino até as " + hoursArrivel.toString() + ".";
    }
    return path;
}

void PathAirTransport::initializeSingleSource(Graph *&graph, int start, myTime::Date &hoursDepature)
{
    for(int i = 0; i < graph->getQtdeVertices(); i++)
    {
        graph->getVertex(i).setD(INT_MAX);
        graph->getVertex(i).setPredecessor(-1);
        graph->getVertex(i).setEdgeVisit(-1);
        graph->getVertex(i).setHoursDepature(__null);
    }
    graph->getVertex(start).setD(0);
    graph->getVertex(start).setHoursDepature(&hoursDepature);
}

void PathAirTransport::relax(Graph *&graph, int u, int v, int edgeSaida, double edge)
{
    if(graph->getVertex(v).getD() > graph->getPesoPathActual(u, edgeSaida) + edge) {
        graph->getVertex(v).setD(graph->getPesoPathActual(u, edgeSaida) + edge);
        graph->getVertex(v).setPredecessor(u);
        graph->getVertex(v).setEdgeVisit(edgeSaida);
    }
}

void PathAirTransport::bellmanFord(Graph *&graph, int start)
{
    try {
        graph->getVertex(start).setD(0);
        for(int i = 0; i < graph->getQtdeVertices(); i++)
            for(int j = 0; j < graph->getQtdeEdges(i); j++)
                relax(graph, i, graph->getEdge(i, j).getDestino(), graph->getEdge(i, j).getIndex(), graph->getEdge(i, j).getPeso());

        /*for(int i = 0; i < graph->getQtdeVertices(); i++)
            for(int j = 0; j < graph->getQtdeEdges(i); j++)
                if(graph->getVertex(graph->getEdge(i, j).getDestino()).getD() > graph->getVertex(i).getD() + graph->getEdge(i, j).getPeso())
                    throw string("O grafo contém ciclos negativos.");*/
    } catch (string exp) {
        qDebug() << QString::fromStdString(exp);
    }
}

void PathAirTransport::dijkstra(Graph *&graph)
{
    //qDebug() << "dijkstra";
    try {
        myList::List<Vertex*> listVert;
        int i, index;

        for(int i = 0; i < graph->getQtdeVertices(); i++)
            listVert.append(&graph->getVertex(i));

        while(!listVert.isEmpty()) {

            Vertex vert = *listVert[0];
            index = 0;
            for(i = 1; i < listVert.count(); i++)
                if(vert.getD() > listVert[i]->getD())
                {
                    vert = *listVert[i];
                    index = i;
                }
            listVert.removeAt(index);
            index = graph->getIndexVertice(vert.getName());

            for(int j = 0; j < graph->getQtdeEdges(index); j++)
            {
                relax(graph, index, graph->getEdge(index, j).getDestino(),
                      graph->getEdge(index, j).getIndex(), graph->getEdge(index, j).getPeso());
            }
        }
    } catch (string exp) {
        qDebug() << QString::fromStdString(exp);
    }
}

void PathAirTransport::printPath(Graph *&graph, int origin, int destination, int &previus, string &strSaida)
{
    if(origin == destination) {
        if(previus != -1)
        {
            strSaida += montLineOut(previus, destination) + "\n";
            listEdgePath->append(graph->getVertex(destination).getEdgeVisit());
        }
        previus = origin;
        listTimes->append(timesCitys(graph->getVertex(previus).getD(), graph->getVertex(previus).getName()));
        listVerticePath->append(previus);
    } else if (graph->getVertex(destination).getPredecessor() == -1)
        strSaida = "Nao há caminho.";
    else
    {
        printPath(graph, origin, graph->getVertex(destination).getPredecessor(), previus, strSaida);
        if(previus != -1)
        {
            strSaida += montLineOut(previus, destination) + "\n";
            listEdgePath->append(graph->getVertex(destination).getEdgeVisit());
        }
        previus = destination;
        listTimes->append(timesCitys(graph->getVertex(previus).getD(), graph->getVertex(previus).getName()));
        listVerticePath->append(previus);
    }
}

string PathAirTransport::montLineOut(int previus, int vertex)
{
    return (graph->getEdge(graph->getVertex(vertex).getEdgeVisit()).getCodVoo() + "\t" +
                           graph->getVertex(previus).getName() + "\t" +
                           graph->getEdge(graph->getVertex(vertex).getEdgeVisit()).getHoursSaida().toString() + "\t" +
                           graph->getVertex(vertex).getName() + "\t" +
                           graph->getEdge(graph->getVertex(vertex).getEdgeVisit()).gethoursChegada().toString());
}


vector<string> PathAirTransport::getAllCitys()
{
    return graph->getKeys();
}

Graph &PathAirTransport::getGraph() const
{
    return *graph;
}

vector<PathAirTransport::citysIndex> PathAirTransport::getAllCitysIndex()
{
    vector<citysIndex> cityIndex;
    for(int i = 0; i < graph->getQtdeVertices(); i++)
    {
        cityIndex.push_back(citysIndex(graph->getIndexVertice(graph->getVertex(i).getName()),
                                       graph->getVertex(i).getName()));
    }
    return cityIndex;
}
