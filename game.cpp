#include "Game.h"



Game::Game(QWidget *parent): QObject(), QGraphicsView(parent)
{




   // QRectF rect = this->scene->sceneRect();
   // this->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);

  //  fitInView(scene->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
  //  centerOn(0,0);
//fitInView(0,0,scene->width(), scene->height());

  //  setFocusPolicy();

}

void Game::resizeEvent(QResizeEvent *event)
{
    QRectF bounds = scene->sceneRect();
   // QRectF bounds = QRectF(0, 0, 800, 800);
    fitInView(bounds, Qt::KeepAspectRatio);
}

void Game::start(){

    QGraphicsRectItem * item1 = new QGraphicsRectItem();
    QGraphicsRectItem * item2 = new QGraphicsRectItem();
    item1->setPos(0, 0);
    item2->setPos(800, 800);
    scene->addItem(item1);
    scene->addItem(item2);


    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    QGraphicsRectItem * line1 = new QGraphicsRectItem();
    QGraphicsRectItem * line2 = new QGraphicsRectItem();
    QGraphicsRectItem * line3 = new QGraphicsRectItem();
    QGraphicsRectItem * line4 = new QGraphicsRectItem();
    line1->setBrush(brush);
    line2->setBrush(brush);
    line3->setBrush(brush);
    line4->setBrush(brush);
    line1->setPos(0, 0);
    line2->setPos(0, 0);
    line3->setPos(800, 800);
    line4->setPos(800, 800);
    line1->setRect(0,0,800,10);
    line2->setRect(0,0,10,800);
    line3->setRect(-800,-10,800,10);
    line4->setRect(-10,-800,10, 800);


    scene->addItem(line1);
    scene->addItem(line2);
    scene->addItem(line3);
    scene->addItem(line4);

    // create snakeHead
    snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
   // snakeHead->setFocus();


    // create a fruit
    apple = new Apple();
    apple->setPos(300,300);
    scene->addItem(apple);

    SnakeBody * snakeBody = new SnakeBody();
    snakeBody->indexQueue=0;
    snakeBody->setPos(100, 50);
    snakeHead->snakeBodies.push_back(snakeBody);
    scene->addItem(snakeBody);

    snakeBody = new SnakeBody();
    snakeBody->indexQueue=0;
    snakeBody->setPos(50, 50);
    snakeHead->snakeBodies.push_back(snakeBody);
    scene->addItem(snakeBody);

    snakeHead->setAnimation();

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkCollision()));
    timer->start(10);
}

void Game::checkCollision()
{
    //qDebug() << "AAAAA";



    if(!timerEnable) return;
    if(snakeHead->isAnimating) return;


    int typeOfCollision = checkingCollisions();

  //  if(isPaused)
   // {
   //     return;
   // }

    if(typeOfCollision==1)
    {

     //   if(isPaused){

            isPaused = false;
       // }
        timerEnable = false;
        snakeHead->isAnimating = true;

        //isPaused = true;
        SnakeBody * snakeBody = new SnakeBody();
        snakeBody->setPos(snakeHead->getPositionOfLastElement());
        snakeHead->snakeBodies.push_back(snakeBody);
        scene->addItem(snakeBody);


        snakeHead->connectLastElement();
       // snakeHead->setAnimation();

        snakeHead->animate();

        randNewApple();

        timerEnable = true;
        snakeHead->isAnimating = false;

      //  snakeHead->addAnimationForNewBody();
    }
    else if(checkCrash())
    {
        timer->stop();

        //wyswietlenie okna z podaniem imienia
        //zapisanie wyniku
        //wyswietlenie tablicy wynikow


        qDebug() << "punkty: " <<points;


        emit gameOver(points);
    }
    //snakeHead->addAnimationForBodies();


}

bool Game::checkCrash()
{
    qreal snakeX = snakeHead->pos().x();
    qreal snakeY = snakeHead->pos().y();


    for(int i=1; i<snakeHead->snakeBodies.size(); ++i)
    {
        qreal bodyX = snakeHead->snakeBodies[i]->pos().x();
        qreal bodyY = snakeHead->snakeBodies[i]->pos().y();

        if (!(snakeX > bodyX + apple->boundingRect().width()-1 || snakeX + snakeHead->boundingRect().width()-1 <= bodyX ||
            snakeY > bodyY + apple->boundingRect().height()-1 || snakeY + snakeHead->boundingRect().height()-1 <= bodyY))
        {
            return true;
        }
    }

    if((snakeX < 10) || (snakeX+snakeHead->boundingRect().width() > 790) ||
         snakeY < 10 || (snakeY+snakeHead->boundingRect().height() > 790)   )
        return true;

    return false;

}



void Game::keyPressEvent(QKeyEvent * event)
{
    timerEnable = false;
    if(snakeHead->isAnimating) return;
    // move up
    if (event->key() == Qt::Key_Up){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Up);
snakeHead->setAnimation();

    }

    // move down
    if (event->key() == Qt::Key_Down){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Down);
snakeHead->setAnimation();

    }

    // move right
    if (event->key() == Qt::Key_Right){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Right);

snakeHead->setAnimation();
    }

    // move left
    if (event->key() == Qt::Key_Left){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Left);
snakeHead->setAnimation();

    }
    if (event->key() == Qt::Key_Space){

       snakeHead->animate();
       for(int i=0; i<snakeHead->nextPoints.size(); ++i)
       {
           qDebug() << snakeHead->nextPoints[i]->x() << " " << snakeHead->nextPoints[i]->y();
       }
       return;


    }

timerEnable = true;
}
int Game::checkingCollisions()
{
    qreal snakeX = snakeHead->pos().x();
    qreal snakeY = snakeHead->pos().y();

    qreal appleX = apple->pos().x();
    qreal appleY = apple->pos().y();

        if (snakeX > appleX + apple->boundingRect().width()-1 || snakeX + snakeHead->boundingRect().width()-1 <= appleX ||
            snakeY > appleY + apple->boundingRect().height()-1 || snakeY + snakeHead->boundingRect().height()-1 <= appleY)
        {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::red);
            apple->setBrush(brush);


            return 0;
        }

        else
        {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::yellow);
            apple->setBrush(brush);

            ++points;
            return 1;
        }

}
void Game::randNewApple()
{
    apple->setPos(rand()%750, rand()%750);
}
