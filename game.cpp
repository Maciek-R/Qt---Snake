#include "Game.h"



Game::Game(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
}

void Game::resizeEvent(QResizeEvent *event)
{
    QRectF bounds = scene->sceneRect();
    fitInView(bounds, Qt::KeepAspectRatio);
}
Game::~Game()
{

}

void Game::start()
{
    initBoard();
    initItems();

  //  lastFrameTimeMillis =  QDateTime::currentMSecsSinceEpoch();
  //  timer = new QTimer(this);
  //  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkCollision()));
  //  timer->start(10);
}
void Game::initBoard()
{
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
}
void Game::initItems()
{
    snakeHead = new SnakeHead();
    scene->addItem(snakeHead);

    apple = new Apple();
    apple->setPos(300,300);
    scene->addItem(apple);

    SnakeBody * snakeBody = new SnakeBody();
    snakeBody->setPos(100, 50);
    snakeHead->snakeBodies.push_back(snakeBody);
    scene->addItem(snakeBody);
}

void Game::nextMove(qint64 differenceTime)
{
    snakeHead->move(differenceTime);

    int typeOfCollision = checkingCollisions();

    if(typeOfCollision==1)
    {
        isPaused = true;
        SnakeBody * snakeBody = new SnakeBody();
        snakeBody->setPos(snakeHead->getPositionOfLastElement());
        snakeHead->snakeBodies.push_back(snakeBody);
        scene->addItem(snakeBody);
    }
    else if(checkCrash())
    {
      //  timer->stop();
        emit stopTimer();

        qDebug() << "punkty: " <<points;

        emit gameOver(points);
    }
}

bool Game::checkCrash()
{
    qreal snakeX = snakeHead->pos().x();
    qreal snakeY = snakeHead->pos().y();


    for(int i=33; i<snakeHead->snakeBodies.size(); ++i)
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

    if (event->key() == Qt::Key_Up){

        snakeHead->changeDirection(SnakeHead::Direction::Up);

    }

    if (event->key() == Qt::Key_Down){

        snakeHead->changeDirection(SnakeHead::Direction::Down);


    }

    if (event->key() == Qt::Key_Right){

        snakeHead->changeDirection(SnakeHead::Direction::Right);

    }

    if (event->key() == Qt::Key_Left){

        snakeHead->changeDirection(SnakeHead::Direction::Left);
    }


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

            if(isPaused)
            {
                randNewApple();
                isPaused=false;
                ++points;
            }

            return 0;
        }
        else
        {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::yellow);
            apple->setBrush(brush);

            return 1;
        }

}
void Game::randNewApple()
{
    apple->setPos(rand()%750, rand()%750);
}
