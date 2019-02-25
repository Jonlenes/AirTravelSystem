#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "GUI/PopUp.h"
#include "GUI/NewTrip.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    try {
        QString path = QFileDialog::getOpenFileName(this, " ");
        if(!airTransport) airTransport = new PathAirTransport();
        airTransport->readFileTransport(path.toStdString().c_str());
        ui->verticalLayoutPrintGraph->addWidget(widgetGraph);
        widgetGraph->setGraph(airTransport->getGraph());
        widgetGraph->drawGraph();

        ui->plainTextEditOutVoos->clear();
        ui->tableWidgetTimes->clear();
        ui->tableWidgetTimes->setRowCount(0);

        ui->tableWidgetCitys->clear();
        ui->tableWidgetCitys->setColumnWidth(0, 35);
        ui->tableWidgetCitys->setColumnWidth(1, 130);

        vector<PathAirTransport::citysIndex> vectorCity = airTransport->getAllCitysIndex();
        ui->tableWidgetCitys->setRowCount(vectorCity.size());
        int i = 0;
        foreach (PathAirTransport::citysIndex item, vectorCity) {
            ui->tableWidgetCitys->setItem(i, 0, new QTableWidgetItem(QString::number(item.index)));
            ui->tableWidgetCitys->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(item.name)));
            i++;
        }

    } catch (string e) {
        QMessageBox::critical(this, "Erro", QString::fromStdString(e));
        airTransport = __null;
    }
}

void MainWindow::initGUI()
{
    setWindowTitle("Air travel");
    setMouseTracking(true);
    airTransport = __null;
    widgetGraph = new WidgetGraph(this);
    ui->verticalLayoutPrintGraph->addWidget(widgetGraph);
    ui->plainTextEditOutVoos->setFixedHeight(70);

    ui->tableWidgetTimes->setFixedWidth(200);
    ui->tableWidgetTimes->verticalHeader()->hide();
    ui->tableWidgetTimes->horizontalHeader()->hide();
    ui->tableWidgetTimes->horizontalScrollBar()->hide();
    ui->tableWidgetTimes->setFocusPolicy(Qt::NoFocus);
    ui->tableWidgetTimes->setColumnCount(2);

    ui->tableWidgetCitys->setFixedWidth(200);
    ui->tableWidgetCitys->verticalHeader()->hide();
    ui->tableWidgetCitys->horizontalHeader()->hide();
    ui->tableWidgetCitys->horizontalScrollBar()->hide();
    ui->tableWidgetCitys->setFocusPolicy(Qt::NoFocus);
    ui->tableWidgetCitys->setColumnCount(2);

    ui->plainTextEditOutVoos->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::on_actionNew_Trip_triggered()
{
    if(!airTransport)
    {
        QMessageBox::information(this, "Warning", "No travel file was loaded.");
        return;
    }

    QStringList strList;
    vector<string> vectorCity = airTransport->getAllCitys();
    foreach (string item, vectorCity) {
        strList.append(QString::fromStdString(item));
    }

    QString cityOrigin;
    QString cityDestination;
    Date timeOut;
    Date timeArrival;
    int days;

    NewTrip form(this, strList, cityOrigin, cityDestination, timeOut, timeArrival, days);
    form.exec();
    if(cityOrigin == "" || cityDestination == "") return;

    myList::List<PathAirTransport::timesCitys> timesCitys;
    myList::List<int> listVertexPath;
    myList::List<int> listEdgePath;

    ui->plainTextEditOutVoos->setPlainText(QString::fromStdString(airTransport->findBetterPath(
                                                               cityOrigin.toStdString(),
                                                               cityDestination.toStdString(),
                                                               timeOut,
                                                               timeArrival,
                                                               days,
                                                               timesCitys,
                                                               listVertexPath,
                                                               listEdgePath)));
    if(ui->plainTextEditOutVoos->placeholderText() != "Nao há caminho.")
        widgetGraph->drawBestPath(listVertexPath);

    ui->tableWidgetTimes->clear();
    ui->tableWidgetTimes->setRowCount(timesCitys.count());
    ui->tableWidgetTimes->setColumnWidth(0, 150);
    ui->tableWidgetTimes->setColumnWidth(1, 45);
    for(int i = 0; i < timesCitys.size(); i++)
    {
        ui->tableWidgetTimes->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(timesCitys[i].city)));
        ui->tableWidgetTimes->setItem(i, 1, new QTableWidgetItem(QString::number(timesCitys[i].time)));
    }
}
