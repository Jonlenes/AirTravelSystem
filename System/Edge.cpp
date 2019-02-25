#include "Edge.h"

using namespace EdgeData;
Edge::Edge()
{

}

Edge::Edge(string codVoo, Date hoursChegada, Date hoursSaida, int &index)
{
    this->codVoo = codVoo;
    this->hoursChegada = hoursChegada;
    this->hoursSaida = hoursSaida;
    this->index = index;
    index++;
}

double Edge::getPeso()
{
    return (hoursChegada - hoursSaida);
}

Date Edge::gethoursChegada() const
{
    return this->hoursChegada;
}

Date Edge::getHoursSaida() const
{
    return this->hoursSaida;
}

int Edge::getDestino() const
{
    return this->vertexDestino;
}

int Edge::getIndex() const
{
    return this->index;
}

string Edge::getCodVoo() const
{
    return this->codVoo;
}

void Edge::setDestino(int vertexDestino)
{
    this->vertexDestino = vertexDestino;
}

void Edge::setIndex(int index)
{
    this->index = index;
}
