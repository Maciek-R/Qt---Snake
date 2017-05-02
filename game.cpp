#include "Game.h"



Game::Game(QWidget *parent): QGraphicsView(parent){

    // set the scene
    scene = new QGraphicsScene(0,0,800,600);
    setScene(scene);

    fitInView(scene->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
  //  centerOn(0,0);
//fitInView(0,0,scene->width(), scene->height());

  //  setFocusPolicy();
}

void Game::nextStep(qint64 differenceTime)
{

    snakeHead->move(differenceTime);
    int typeOfCollision = checkCollision();
    if(typeOfCollision==1)
    {
        SnakeBody * snakeBody = new SnakeBody();
        snakeBody->setPos(snakeHead->prevPos);

        // snakeHead->moveBodies();
        snakeHead->snakeBodies.append(snakeBody);


        scene->addItem(snakeBody);
    }


}

void Game::start(){
    // create snakeHead
    snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
    snakeHead->setFocus();

    // create a fruit
    apple = new Apple();
    apple->setPos(300,300);
    scene->addItem(apple);
}


void Game::keyPressEvent(QKeyEvent * event)
{
    // move up
    if (event->key() == Qt::Key_Up){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Up);
      /*  prevPos = pos();
        int xPos = x();
        int yPos = y() - boundingRect().height();
        setPos(xPos,yPos);
        moveBodies();*/
    }

    // move down
    if (event->key() == Qt::Key_Down){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Down);

      /*  prevPos = pos();
        int xPos = x();
        int yPos = y() + boundingRect().height();
        setPos(xPos,yPos);
        moveBodies();*/
    }

    // move right
    if (event->key() == Qt::Key_Right){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Right);

      /*  prevPos = pos();
        int xPos = x() + boundingRect().width();
        int yPos = y();
        setPos(xPos,yPos);
        moveBodies();*/
    }

    // move left
    if (event->key() == Qt::Key_Left){

        snakeHead->changeWantedDirection(SnakeHead::Direction::Left);

       /* prevPos = pos();
        int xPos = x() - boundingRect().width();
        int yPos = y();
        setPos(xPos,yPos);
        moveBodies();*/
    }

    int typeOfCollision = checkCollision();
    if(typeOfCollision==1)
    {
        SnakeBody * snakeBody = new SnakeBody();
        snakeBody->setPos(snakeHead->prevPos);

        snakeHead->snakeBodies.append(snakeBody);


        scene->addItem(snakeBody);
    }



    // elongate if collides with Fruit
   /* QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        if (typeid(*cItems[i]) == typeid(Fruit)){
            // fruit found in collision list
            elongate();
        }
    }*/
}
int Game::checkCollision()
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


            return 1;
        }

}
