#include "NewTrip.h"
#include "ui_NewTrip.h"
#include "GUI/PopUp.h"
#include "Date.h"
#include <QMessageBox>
#include <QAction>

NewTrip::NewTrip(QWidget *parent, QStringList strList, QString &cityOrigin,
                 QString &cityDestination, Date &timeOut, Date &timeArrival, int &days) :
    QDialog(parent),
    ui(new Ui::NewTrip)
{
    ui->setupUi(this);
    setWindowTitle("New trip");
    window()->layout()->setSizeConstraint(QLayout::SetFixedSize);

    QAction *myActionSeekOr = ui->lineEditOrigem->addAction(QIcon(":/Imagens/iconBtn.png"), QLineEdit::TrailingPosition);
    connect(myActionSeekOr, SIGNAL(triggered()), this, SLOT(onLineOrigem));

    QAction *myActionSeekD = ui->lineEditDestination->addAction(QIcon(":/Imagens/iconBtn.png"), QLineEdit::TrailingPosition);
    connect(myActionSeekD, SIGNAL(triggered()), this, SLOT(onLineDestino()));

    this->strList = strList;
    this->cityOrigin = &cityOrigin;
    this->cityDestination = &cityDestination;
    this->timeOut = &timeOut;
    this->timeArrival = &timeArrival;
    this->days = &days;

    ui->lineEditTimeOut->setInputMask("##:##");
    ui->lineEditTimeArrival->setInputMask("##:##");
    ui->lineEditTimeOut->setText("0600");
    ui->lineEditTimeArrival->setText("0000");
}

NewTrip::~NewTrip()
{
    delete ui;
}

void NewTrip::openPopUp(QLineEdit *le)
{
    selecao = "";
    PopUp::showPopUp(le, strList, selecao, "Selecione uma cidade", false);
    le->setText(selecao);
}

void NewTrip::onLineOrigem()
{
    openPopUp(ui->lineEditOrigem);
}

void NewTrip::onLineDestino()
{
    openPopUp(ui->lineEditDestination);
}

void NewTrip::on_pushButtonSeekPaths_clicked()
{

    if(ui->lineEditOrigem->text() == "" || ui->lineEditDestination->text() == "")
        QMessageBox::information(this, "Warning", "Destination and/or origin are blank.");
    else
    {
        try {
            //Validando os hórarios
            myTime::Date(ui->lineEditTimeArrival->text().toStdString());
            myTime::Date(ui->lineEditTimeOut->text().toStdString());

            *cityOrigin = ui->lineEditOrigem->text();
            *cityDestination = ui->lineEditDestination->text();
            *timeOut = myTime::Date(ui->lineEditTimeOut->text().toStdString());
            *timeArrival = myTime::Date(ui->lineEditTimeArrival->text() == "00:00" ? "24:00" : ui->lineEditTimeArrival->text().toStdString());
            *days = ui->spinBoxDays->value();

            //if(timeArrival->toString() == "00:00") { delete timeArrival; timeArrival = new myTime::Date("24:00"); }

            close();

        } catch (std::string exp) {
            QMessageBox::information(this, "Warning", QString::fromStdString(exp));
        }
    }
}
