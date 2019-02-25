#include "PopUp.h"
#include "ui_PopUp.h"

PopUp * PopUp::popUp = __null;

PopUp::PopUp(QWidget *parent, QString title, QStringList strValues,
             QString  &strFiltro, bool multiSelection) :
    QDialog(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle(title);

    if(multiSelection) ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->listWidget->clear();

    this->strFiltro = &strFiltro;
    ui->listWidget->addItems(strValues);

    ui->pushButtonFiltrar->setFocus();
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::on_pushButtonFiltrar_clicked()
{
    if(ui->listWidget->selectedItems().count() == 0)
    {
        *strFiltro = "";
        close();
        return;
    }
    QListWidgetItem *itemLast = ui->listWidget->selectedItems().at(ui->listWidget->selectedItems().count() - 1);
    foreach (QListWidgetItem *i, ui->listWidget->selectedItems()) {
        *strFiltro += i->text();
        if(i != itemLast) *strFiltro += ",";
    };
    close();
}

void PopUp::showPopUp(QWidget *parent, QStringList strValues, QString &strFiltro, QString title, bool multiSelection)
{
    popUp = new PopUp(parent, title, strValues, strFiltro, multiSelection);
    popUp->exec();
    delete popUp;
    popUp = __null;
}


void PopUp::on_pushButtonLimpar_clicked()
{
    foreach (QListWidgetItem *i, ui->listWidget->selectedItems()) {
            ui->listWidget->setItemSelected(i, false);
    };
}
