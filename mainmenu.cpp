#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "snakewindow.h"
#include "dialog.h"

Mainmenu::Mainmenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainmenu)
{
    ui->setupUi(this);
}

Mainmenu::~Mainmenu()
{
    delete ui;
}

void Mainmenu::on_pushButton_2_clicked()
{
    this->close();
}

void Mainmenu::on_pushButton_clicked()
{
    SnakeWindow * sW = new SnakeWindow();
    sW->show();
     //sW->show();
}

void Mainmenu::on_pushButton_3_clicked()
{
    Dialog * dial = new Dialog();
    dial->setModal(true);
    dial->exec();
}
