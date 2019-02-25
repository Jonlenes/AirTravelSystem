#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    ~PopUp();
     static void showPopUp(QWidget *parent, QStringList strValues, QString &strFiltro, QString title, bool multiSelection);

private slots:
    void on_pushButtonFiltrar_clicked();

    void on_pushButtonLimpar_clicked();

private:
    explicit PopUp(QWidget *parent, QString title, QStringList strValues, QString &strFiltro, bool multiSelection);

    Ui::PopUp *ui;
    QString *strFiltro;
    static PopUp *popUp;
};
#endif // POPUP_H
