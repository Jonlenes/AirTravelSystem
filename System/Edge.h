#ifndef EDGE_H
#define EDGE_H

#include<iostream>
#include "Date.h"
using namespace std;
using namespace myTime;

namespace EdgeData {
class Edge
{
public:
    Edge();
    Edge(string codVoo, Date hoursChegada, Date hoursSaida, int &index);

    double getPeso();
    Date gethoursChegada() const;
    Date getHoursSaida() const;
    int getDestino() const;
    int getIndex() const;
    string getCodVoo() const;

    void setDestino(int vertexDestino);
    void setIndex(int index);

private:
    int index;
    int vertexDestino;
    Date hoursSaida;
    Date hoursChegada;
    string codVoo;

};
}
#endif // EDGE_H
