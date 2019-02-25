#include "Vertex.h"
#include <limits.h>
#include <QDebug>
using namespace VertexData;

Vertex::Vertex()
{
    init();
}

Vertex::Vertex(string name) : name(name)
{
    init();
}

string Vertex::getName() const
{
    return this->name;
}

void Vertex::setD(double d)
{
    this->d = d;
}

double Vertex::getD()const
{
    return this->d;
}

void Vertex::setPredecessor(int predecessor)
{
    this->predecessor = predecessor;
}

int Vertex::getPredecessor() const
{
    return this->predecessor;
}

void Vertex::setEdgeVisit(int indexEdgeVisit)
{
    this->indexEdgeVisit = indexEdgeVisit;
}

int Vertex::getEdgeVisit() const
{
    return this->indexEdgeVisit;
}

void Vertex::setHoursDepature(myTime::Date *hoursDepature)
{
    this->hoursDepature = hoursDepature;
}

myTime::Date *Vertex::getHoursDepature() const
{
    return this->hoursDepature;
}

bool Vertex::operator == (Vertex other)
{
    if(other.getName() == name &&
            other.getD() == d &&
            other.getPredecessor() == predecessor &&
            other.getEdgeVisit() == indexEdgeVisit)
        return true;
    return false;
}

void Vertex::init()
{
    d = INT_MAX;
    predecessor = -1;
    indexEdgeVisit = -1;
    hoursDepature = __null;
}
