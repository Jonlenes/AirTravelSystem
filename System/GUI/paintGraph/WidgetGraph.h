#ifndef WIDGETGRAFO_H
#define WIDGETGRAFO_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "DataStructures/Queue.h"
#include "DataStructures/Stack.h"
#include "DataStructures/List.h"
#include "Graph.h"
#include <QAction>

class VertexPrint;
class EdgePrint;
class QLabel;

class WidgetGraph : public QGraphicsView
{
    Q_OBJECT
public:
    WidgetGraph(QWidget *p = 0);
    ~WidgetGraph();

    void setGraph(Graph &graph);
    void drawGraph();

    void addEdgePrint(int origin, int destination, QString name, int cor);
    void addVertexPrint(int index, int color, qreal x, qreal y, QString name);

    void drawBestPath(const myList::List<int> &listBestVertex);
    void clearBestPath();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:
    void slotScrollBar();

private:
    int timerId;
    QGraphicsScene *scene;
    myList::List<VertexPrint *> *listVertexPrint;
    myList::List<EdgePrint *> *listEdgePrint;
    Graph *graph;

    /*Será usado apenas para permitir que
     * o usuário possa "limpar" o melhor
     * caminho, ou seja, apagar as linhas
     * vermelhas*/
    myList::List<VertexPrint*> *listVertexBestpath;
    myList::List<EdgePrint*> *listEdgeBestpath;
};
#endif // WIDGETGRAFO_H
