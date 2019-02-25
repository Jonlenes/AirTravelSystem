#include "GUI/paintGraph/EdgePrint.h"
#include "GUI/paintGraph/VertexPrint.h"
#include "Util.h"
#include <math.h>
#include <QPainter>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

EdgePrint::EdgePrint(VertexPrint *origem, VertexPrint *final, QString name, bool cor) : TamSeta(10)
{
    setAcceptedMouseButtons(0);
    this->origem = origem;
    this->final = final;
    this->origem->addEdge(this);
    this->final->addEdge(this);
    this->cor = cor;
    this->name = name;
    ajustar();
}

EdgePrint::~EdgePrint()
{
}

void EdgePrint::ajustar()
{
    if(!origem || !final)
        return;
    QLineF line(mapFromItem(origem, qreal(0), qreal(0)), mapFromItem(final, qreal(0), qreal(0)));
    qreal TamLinha = line.length();

    prepareGeometryChange();

    if(TamLinha > qreal(20.)){
        QPointF EdgePrintDeslo((line.dx() * 10) / TamLinha, (line.dy() * 10) / TamLinha);
        PtOrigem = line.p1() + EdgePrintDeslo;
        PtFinal = line.p2() - EdgePrintDeslo;
    }else{
        PtOrigem = PtFinal = line.p1();
    }
}

QRectF EdgePrint::boundingRect() const
{
    if(!origem || !final)
        return QRectF();
    qreal larguraCaneta = 1;
    qreal extra = (larguraCaneta + TamSeta) / 2.0;

    return QRectF(PtOrigem, QSizeF(PtFinal.x() - PtOrigem.x(), PtFinal.y() - PtOrigem.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void EdgePrint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(!origem || !final)
        return;
    QLineF line(PtOrigem, PtFinal);
    if(qFuzzyCompare(line.length(), qreal(0.)))
        return;

    if(cor)
    {
        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::red);
    }
    else
    {
        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::black);
    }

    painter->drawLine(line);

    double angulo = ::acos(line.dx() / line.length());
    if(line.dy() >= 0)
        angulo = TwoPi - angulo;

    QPointF FinalSetaP1 = PtFinal + QPointF(sin(angulo - Pi / 3) * TamSeta,
                                              cos(angulo - Pi / 3) * TamSeta);
    QPointF FinalSetaP2 = PtFinal + QPointF(sin(angulo - Pi + Pi / 3) * TamSeta,
                                            cos(angulo - Pi + Pi / 3) * TamSeta);

    painter->drawPolygon(QPolygonF() << line.p2() << FinalSetaP1 << FinalSetaP2);
}

