#include "snakewindow.h"
#include "ui_snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnakeWindow)
{


  //  Game *game = new Game();
  //  game->show();
  //  game->start();

    // set the scene



    ui->setupUi(this);

    connect(ui->graphicsView, SIGNAL(gameOver(int)), this, SLOT(end(int)) );


    ui->graphicsView->scene = new QGraphicsScene(this);
//    ui->graphicsView->scene->setSceneRect(-1.25, -1.25, 2.5, 2.5);

    ui->graphicsView->setScene(ui->graphicsView->scene);


    ui->graphicsView->show();
    ui->graphicsView->start();
  //  QRectF rect = ui->graphicsView->scene->sceneRect();
  //ui->graphicsView->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);

  //  QRectF rect = ui->graphicsView->scene->sceneRect();
  //  ui->graphicsView->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);
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

void SnakeWindow::resizeEvent(QResizeEvent *event)
{
    //QRectF bounds = ui->graphicsView->scene->sceneRect();
   // bounds.setWidth(bounds.width()*0.9);
   //     bounds.setHeight(bounds.height()*0.9);
  //  rect.setWidth(rect.width()/2);
  //  rect.setHeight(rect.height()/2);
 //   ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
   // ui->graphicsView->centerOn(400, 400);
}


void SnakeWindow::qwerty()
{
    qDebug() << "AAA";
}

SnakeWindow::~SnakeWindow()
{
    delete ui;
}


