#include "snakewindow.h"
#include "ui_snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnakeWindow)
{
    ui->setupUi(this);

    connect(ui->graphicsView, SIGNAL(gameOver(int)), this, SLOT(end(int)) );
    connect(ui->graphicsView, SIGNAL(stopTimer()), this, SLOT(stopTimer()));


    timer = new Timer(ui->graphicsView);
    ui->graphicsView->show();
    ui->graphicsView->start();


}

void SnakeWindow::end(int x)
{
    qDebug() << "x: "<<x;

    NameDialog nDialog;
    nDialog.setModal(true);
    nDialog.setPoints(x);
    nDialog.exec();

    this->close();
}
void SnakeWindow::stopTimer()
{
    timer->stop();
}

SnakeWindow::~SnakeWindow()
{
    delete ui;
}


