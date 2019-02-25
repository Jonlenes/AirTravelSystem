#ifndef ARESTA_H
#define ARESTA_H

#include <QGraphicsItem>

class VertexPrint;

class EdgePrint : public QGraphicsItem
{
public:
    EdgePrint(VertexPrint *origem, VertexPrint *final, QString name, bool cor = 0);
    ~EdgePrint();
    void ajustar();

    QString getName() { return name; }
    VertexPrint *getOrigin() { return origem; }
    VertexPrint *getDestination() { return final; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    VertexPrint *origem, *final;
    QPointF PtOrigem;
    QPointF PtFinal;
    qreal TamSeta;
    bool cor;
    QString name;
};
#endif // ARESTA_H
