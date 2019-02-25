#include "WidgetGraph.h"
#include "EdgePrint.h"
#include "VertexPrint.h"
#include "Util.h"
#include <math.h>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <fstream>
#include <QFileDialog>
#include <QScrollBar>
#include <QToolTip>
using namespace std;

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

WidgetGraph::WidgetGraph(QWidget *p)
    : QGraphicsView(p), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
    setCacheMode(CacheBackground);

    graph = __null;

    listVertexPrint = new myList::List<VertexPrint *>;
    listEdgePrint = new myList::List<EdgePrint *>;
    this->scene = scene;
    listEdgeBestpath = __null;
    listVertexBestpath = __null;

    connect(this->verticalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(slotScrollBar()));
    connect(this->horizontalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(slotScrollBar()));
}

WidgetGraph::~WidgetGraph()
{
    if(listEdgeBestpath) delete listEdgeBestpath;
    if(listVertexBestpath) delete listVertexBestpath;
}

void WidgetGraph::setGraph(Graph &graph)
{
    this->graph = &graph;
}

void WidgetGraph::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
    this->scene->update();
}

void WidgetGraph::slotScrollBar()
{
    this->scene->update();
}

void WidgetGraph::addEdgePrint(int origin, int destination, QString name, int cor)
{
    EdgePrint *edgePrint = new EdgePrint(listVertexPrint->at(origin), listVertexPrint->at(destination), name, cor);
    scene->addItem(edgePrint);
    listEdgePrint->append(edgePrint);
    scene->update();
}

void WidgetGraph::addVertexPrint(int index, int color, qreal x, qreal y, QString name)
{
    VertexPrint *vertexPrint = new VertexPrint(this, name, color, index);
    scene->addItem(vertexPrint);
    vertexPrint->setPos(x, y);
    listVertexPrint->append(vertexPrint);
    scene->update();
}

void WidgetGraph::drawGraph()
{
    if(graph)
    {
        scene->clear();
        delete listVertexPrint;
        delete listEdgePrint;
        listVertexPrint = new myList::List<VertexPrint *>;
        listEdgePrint = new myList::List<EdgePrint *>;

        QPoint *centerCircle = new QPoint(this->width()/2.0, this->height()/2.0);
        double ray = 5 * (this->height()/12.0);
        int qtdeVertices = graph->getQtdeVertices();
        int qtdeEdges;

        if(qtdeVertices > 20) ray = (ray * qtdeVertices) / 20.0;

        for(int i = 0; i < qtdeVertices; i++)
            addVertexPrint(i, 0, qreal(centerCircle->x() + ray * cos(i * (TwoPi/qtdeVertices))),
                           qreal(centerCircle->y() - ray * sin(i * (TwoPi/qtdeVertices))),
                           QString::fromStdString((graph->getVertex(i)).getName()));

        for(int i = 0; i < qtdeVertices; i++)
        {
            qtdeEdges = graph->getQtdeEdges(i);
            for(int j = 0; j < qtdeEdges; j++)
                addEdgePrint(i, graph->getEdge(i, j).getDestino(),
                             QString::fromStdString(graph->getEdge(i, j).getCodVoo()) , 0);
        }
    }
}
void WidgetGraph::drawBestPath(const myList::List<int> &listBestVertex)
{
    clearBestPath();
    listVertexBestpath = new myList::List<VertexPrint *>;
    listEdgeBestpath = new myList::List<EdgePrint *>;

    for(int i = 0; i < listBestVertex.count(); i++)
    {
        VertexPrint *vert = listVertexPrint->at(listBestVertex.at(i));
        VertexPrint *newVert = new VertexPrint(this, vert->getName(), 1, i);
        newVert->setPos(vert->pos());
        listVertexBestpath->append(newVert);
        scene->addItem(newVert);
    }

    VertexPrint *ori = listVertexBestpath->at(0);
    VertexPrint *des = listVertexBestpath->at(1);
    for(int i = 2; i < listVertexBestpath->count() + 1; i++)
    {
        EdgePrint *newEdge = new EdgePrint(ori, des, "", 1);
        listEdgeBestpath->append(newEdge);
        scene->addItem(newEdge);
        ori = des;
        if(i != listVertexBestpath->count()) des = listVertexBestpath->at(i);
    }
}

void WidgetGraph::clearBestPath()
{
    if(listEdgeBestpath && listVertexBestpath){
        VertexPrint *Vert;
        EdgePrint *Arest;

        while(!listVertexBestpath->isEmpty()){
            Vert = listVertexBestpath->takeAt(0);
            scene->removeItem(Vert);
        }
        while(!listEdgeBestpath->isEmpty()){
            Arest = listEdgeBestpath->takeAt(0);
            scene->removeItem(Arest);
        }
        delete listVertexBestpath;
        delete listEdgeBestpath;
        listVertexBestpath = NULL;
        listEdgeBestpath = NULL;
        this->scene->update();
    }
}

void WidgetGraph::mouseMoveEvent(QMouseEvent *e)
{
    for(int i = 0; i < listVertexPrint->count(); i++)
    {
        QPointF pos = listVertexPrint->at(i)->pos();
        long long difX = (pos.x() - e->windowPos().x());
        long long difY = (pos.y() - e->windowPos().y());
        if(std::abs(difX) <= 20 && std::abs(difY) <= 20)
            QToolTip::showText(QPoint(pos.x(), pos.y()), listVertexPrint->at(i)->getName());
    }
}
