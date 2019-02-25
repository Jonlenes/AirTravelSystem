#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PathAirTransport.h"
#include "GUI/paintGraph/WidgetGraph.h"
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

    void on_actionNew_Trip_triggered();

private:
    Ui::MainWindow *ui;
    PathAirTransport *airTransport;
    WidgetGraph *widgetGraph;

    void initGUI();
};

#endif // MAINWINDOW_H
