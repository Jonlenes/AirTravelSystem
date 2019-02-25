#ifndef NEWTRIP_H
#define NEWTRIP_H

#include <QDialog>
#include <QLineEdit>
#include "Date.h"
using namespace myTime;

namespace Ui {
class NewTrip;
}

class NewTrip : public QDialog
{
    Q_OBJECT

public:
    explicit NewTrip(QWidget *parent, QStringList strList, QString &cityOrigin,
                     QString &cityDestination, Date &timeOut, Date &timeArrival, int &days);
    ~NewTrip();

    void openPopUp(QLineEdit *le);

private slots:
    void onLineOrigem();
    void onLineDestino();

    void on_pushButtonSeekPaths_clicked();

private:
    Ui::NewTrip *ui;
    QStringList strList;
    QString selecao;

    QString *cityOrigin;
    QString *cityDestination;
    Date *timeOut;
    Date *timeArrival;
    int *days;
};

#endif // NEWTRIP_H
