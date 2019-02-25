#ifndef VERTICE_H
#define VERTICE_H

#include <QGraphicsItem>
#include <QList>


class WidgetGraph;
class EdgePrint;

class VertexPrint : public QGraphicsItem
{
public:
    VertexPrint(WidgetGraph *widgetGrafo,  QString name, int cor = 0, int i = 0);
    void addEdge(EdgePrint *edge);

    QString getName() { return name; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);

private:
    QList <EdgePrint *> ListaEdge;
    WidgetGraph *grafico;
    int cor;
    int i;
    QString name;
};
#endif // VERTICE_H
