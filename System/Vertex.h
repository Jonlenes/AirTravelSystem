#ifndef VERTEX_H
#define VERTEX_H

#include "Edge.h"
#include "Date.h"
#include <iostream>
using namespace std;

namespace VertexData {
class Vertex
{
public:
    Vertex();
    Vertex(string name);
    string getName() const;

    void    setD(double d);
    double  getD() const;
    void    setPredecessor(int predecessor);
    int     getPredecessor() const;
    void    setEdgeVisit(int indexEdgeVisit);
    int     getEdgeVisit() const;
    void    setHoursDepature(myTime::Date *hoursDepature);
    myTime::Date *getHoursDepature() const;

    bool operator == (Vertex other);

private:
    void init();

    string name;
    double d;
    int predecessor;
    int indexEdgeVisit;
    myTime::Date *hoursDepature;
};
}
#endif // VERTEX_H
