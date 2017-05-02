#include "snakewindow.h"
#include "ui_snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnakeWindow)
{


    ui->setupUi(this);


}

void SnakeWindow::qwerty()
{
    qDebug() << "AAA";
}

SnakeWindow::~SnakeWindow()
{
    delete ui;
}


