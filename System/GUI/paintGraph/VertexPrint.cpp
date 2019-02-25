#include "GUI/paintGraph/VertexPrint.h"
#include "GUI/paintGraph/EdgePrint.h"
#include "GUI/paintGraph/WidgetGraph.h"

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QToolTip>


VertexPrint::VertexPrint(WidgetGraph *widgetGrafo, QString name, int cor, int i)
    : grafico(widgetGrafo)
{
    this->cor = cor;
    this->i = i;
    setAcceptHoverEvents(true);
    this->name = name;
}

void VertexPrint::addEdge(EdgePrint *edge)
{
    ListaEdge << edge;
}

QRectF VertexPrint::boundingRect() const
{
    qreal ajustar = 2;
    return QRectF( -10 - ajustar, -10 - ajustar, 3 + ajustar, 3 + ajustar);

}

void VertexPrint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->setBrush(QBrush(Qt::green));

    if(cor)
        painter->setPen(QPen(Qt::red, 3));
    else
        painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

    if(!cor){
        painter->setPen(QPen(Qt::blue, 4));
        painter->setFont(QFont(QString("Arial"), 15));
        painter->drawText(QPoint(0, -15), QString::number(i));
    }
}

void VertexPrint::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
    QToolTip::showText(QPoint(pos().x(), pos().y()), "Teste");
}
