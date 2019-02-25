#ifndef PATHAIRTRANSPORT_H
#define PATHAIRTRANSPORT_H

#include "Graph.h"

class PathAirTransport
{
public:
    PathAirTransport();
    PathAirTransport(const char *path);

    struct timesCitys {
        timesCitys() {}
        timesCitys(double time, string city) : time(time), city(city) { }
        void operator = (timesCitys &tc) { time = tc.time; city = tc.city; }
        double time;
        string city;
    };
    struct citysIndex{
        citysIndex() { index = 0;}
        citysIndex(int index, string name) { this->index = index; this->name = name; }
        string name;
        int index;
    };

    void readFileTransport(const char * path);
    string findBetterPath(string origin, string destination, myTime::Date hoursDepature, myTime::Date hoursArrivel, int qtdeDays, myList::List<timesCitys> &listTimes, myList::List<int> &listVerticePath, myList::List<int> &listEdgePath);

    vector<string> getAllCitys();
    vector<citysIndex> getAllCitysIndex();
    Graph &getGraph() const;

protected:
    Graph *graph;
    myList::List<timesCitys> *listTimes;
    myList::List<int> *listVerticePath;
    myList::List<int> *listEdgePath;


    void initializeSingleSource(Graph *&graph, int start, myTime::Date &hoursDepature);
    void relax(Graph *&graph, int u, int v, int edgeSaida, double edge);
    void bellmanFord(Graph *&graph, int start);
    void dijkstra(Graph *&graph);
    void printPath(Graph *&graph, int origin, int destination, int &previus, string &strSaida);
    string montLineOut(int previus, int vertex);
};

#endif // PATHAIRTRANSPORT_H
