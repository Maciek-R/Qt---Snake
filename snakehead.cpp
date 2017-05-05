#include "SnakeHead.h"
#include <QBrush>
#include "Apple.h"
#include "SnakeBody.h"
#include "Game.h"

//extern Game* game;

//SnakeHead::SnakeHead(QGraphicsItem *parent){

SnakeHead::SnakeHead(QGraphicsItem *parent)
    :QObject(), QGraphicsRectItem(parent)
{
    setRect(0,0,50,50);
    setPos(150, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
    setPen(Qt::NoPen);
    setZValue(1);
    dir = Direction::Right;
    wantedDir = Direction::None;
 //   setFlag(QGraphicsItem::ItemIsFocusable,true);


    nextDirs.push_back(SnakeHead::Direction::Right);
    group = new QParallelAnimationGroup;
}

SnakeHead::~SnakeHead()
{

}
SnakeHead::Direction SnakeHead::getDir()
{
    return dir;
}

void SnakeHead::move(qint64 differenceTime)
{
    qreal futureX;
    qreal futureY;

    qreal transition = double(differenceTime)/1000 * PIXELS_PER_SECONDS;

    if(dir == Direction::Right)
    {
        futureX = this->pos().x()+transition;
        futureY = this->pos().y();
    }
    else if(dir == Direction::Left)
    {
        futureX = this->pos().x()-transition;
        futureY = this->pos().y();
    }

    else if(dir == Direction::Up)
    {
        futureX = this->pos().x();
        futureY = this->pos().y()-transition;
    }

    else if(dir == Direction::Down)
    {
        futureX = this->pos().x();
        futureY = this->pos().y()+transition;
    }


    if(snakeBodies.empty())
    {
        prevPos.setX(this->pos().x());
        prevPos.setY(this->pos().y());
    }
    else
    {
        prevPos.setX(snakeBodies[snakeBodies.size()-1]->pos().x());
        prevPos.setY(snakeBodies[snakeBodies.size()-1]->pos().y());
    }


    moveBodies();
    setPos(futureX, futureY);

}

void SnakeHead::changeWantedDirection(Direction dir)
{
    this->dir = dir;

    nextDirs.push_back(dir);
}

void SnakeHead::setAnimation()
{
    isAnimating = true;
    double distance;
    QPointF point;
    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
    switch(this->dir)
    {
        case SnakeHead::Direction::Right:

            point.setX(750);
            point.setY(this->pos().y());
            distance = 750 - this->pos().x();
            break;
        case SnakeHead::Direction::Left:
            point.setX(0);
            point.setY(this->pos().y());
            distance = this->pos().x();
            break;
        case SnakeHead::Direction::Up:
            point.setX(this->pos().x());
            point.setY(0);
            distance = this->pos().y();
            break;
        case SnakeHead::Direction::Down:
            point.setX(this->pos().x());
            point.setY(750);
            distance = 750 - this->pos().y();
            break;
    }

    double time = (distance/800) * 4000;

    anim->setDuration(time);
    anim->setEndValue(point);



    if(!nextPoints.empty())
    {
        nextPoints[nextPoints.size()-1]->setX(this->pos().x());
        nextPoints[nextPoints.size()-1]->setY(this->pos().y());


    }


     nextPoints.push_back(new QPointF(point));

     group->clear();
     setAnimationsForBodies();
     group->addAnimation(anim);
     group->start();
     isAnimating = false;
}

void SnakeHead::animate()
{
    isAnimating = true;
    double distance;
    QPointF point;
    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
    switch(this->dir)
    {
        case SnakeHead::Direction::Right:

            point.setX(750);
            point.setY(this->pos().y());
            distance = 750 - this->pos().x();
            break;
        case SnakeHead::Direction::Left:
            point.setX(0);
            point.setY(this->pos().y());
            distance = this->pos().x();
            break;
        case SnakeHead::Direction::Up:
            point.setX(this->pos().x());
            point.setY(0);
            distance = this->pos().y();
            break;
        case SnakeHead::Direction::Down:
            point.setX(this->pos().x());
            point.setY(750);
            distance = 750 - this->pos().y();
            break;
    }

    double time = (distance/800) * 4000;

    anim->setDuration(time);
    anim->setEndValue(point);

    group->clear();
    setAnimationsForBodies();
    group->addAnimation(anim);
    group->start();
    isAnimating = false;
}

void SnakeHead::connectLastElement()
{

    int index = snakeBodies[snakeBodies.size()-2]->indexQueue;
    snakeBodies[snakeBodies.size()-1]->indexQueue = index;

    Direction dir = nextDirs[index];


    int x = snakeBodies[snakeBodies.size()-2]->pos().x();
    int y = snakeBodies[snakeBodies.size()-2]->pos().y();
    int XtoSet=x;
    int YtoSet=y;


    switch(dir)
    {
        case Left:
            XtoSet = x+50;
            break;
        case Right:
            XtoSet = x-50;
            break;
        case Up:
            YtoSet = y+50;
            break;
        case Down:
            YtoSet = y-50;
            break;
    }

 /*   int x = snakeBodies[snakeBodies.size()-2]->pos().x();
    int y = snakeBodies[snakeBodies.size()-2]->pos().y();
    int nextX = nextPoints[index]->x();
    int nextY = nextPoints[index]->y();

    int diffX = nextX - x;
    int diffY = nextY - y;

    int XtoSet;
    int YtoSet;
    if(diffX == 0)
    {
        XtoSet = x;
        if(diffY > 0)
            YtoSet = y-50;
        else
            YtoSet = y+50;
    }
    else
    {
        YtoSet = y;
        if(diffX > 0)
            XtoSet = x-50;
        else
            XtoSet = x+50;
    }*/

    snakeBodies[snakeBodies.size()-1]->setX(XtoSet);
    snakeBodies[snakeBodies.size()-1]->setY(YtoSet);
    qDebug() << XtoSet << "   " << YtoSet;
}

void SnakeHead::setAnimationsForBodies()
{
    for(int i=0; i<snakeBodies.size(); ++i)
    {QPropertyAnimation *an;

        QSequentialAnimationGroup * seqGroup = new QSequentialAnimationGroup;

   // snakeBodies[i]->clear();


    bool flag = false;
        for(int j=snakeBodies[i]->indexQueue; j<nextPoints.size(); ++j)
        {

            an = new QPropertyAnimation(snakeBodies[i], "pos");

            an->setDuration(getDuration(i, j, flag));

            if(flag)
                an->setStartValue(QPointF(*nextPoints[j-1]));
            an->setEndValue(QPointF(*nextPoints[j]));



            seqGroup->addAnimation(an);
            flag = true;

        }
        group->addAnimation(seqGroup);
        snakeBodies[i]->seqGroup = seqGroup;
        snakeBodies[i]->conn();

    }

}

void SnakeHead::addAnimationForNewBody()
{
    snakeBodies[snakeBodies.size()-1]->addAnimation();
}

int SnakeHead::getDuration(int i, int j, bool flag)
{
    qDebug() << snakeBodies.size();
    double dist;
    if(flag == true){
        if(nextPoints[j-1]->x() == nextPoints[j]->x())
        {
           dist = fabs(nextPoints[j-1]->y() - nextPoints[j]->y());
        }
        else{
            dist = fabs(nextPoints[j-1]->x() - nextPoints[j]->x());
        }

         double time = (dist/800) * 4000;
         return time;
    }
    else
    {



        if(snakeBodies[i]->pos().x() == nextPoints[j]->x())
        {
           dist = fabs(snakeBodies[i]->pos().y() - nextPoints[j]->y());
        }
        else{
            dist = fabs(snakeBodies[i]->pos().x() - nextPoints[j]->x());
        }

         double time = (dist/800) * 4000;
         return time;
    }

}

QPointF SnakeHead::getPositionOfLastElement()
{//trzeba dokonczyc

    QPointF point;

  /*  switch(dir)
    {
        case Direction::Right:
            point.setX(this->pos().x()-50);
            point.setY(this->pos().y());
            break;
        case Direction::Left:
            point.setX(this->pos().x()+50);
            point.setY(this->pos().y());
            break;
        case Direction::Up:
            point.setX(this->pos().x());
            point.setY(this->pos().y()+50);
            break;
        case Direction::Down:
            point.setX(this->pos().x());
            point.setY(this->pos().y()-50);
            break;
    }
*/

    if(!snakeBodies.empty())
    {
        point.setX(snakeBodies[snakeBodies.size()-1]->pos().x());
        point.setY(snakeBodies[snakeBodies.size()-1]->pos().y());
    }
    else
    {
        point.setX(this->pos().x());
        point.setY(this->pos().y());
    }

    return point;
}

void SnakeHead::moveBodies(){

    for(int i=snakeBodies.size()-1; i>0; --i)
    {
        snakeBodies[i]->setPos(snakeBodies[i-1]->pos());
    }
    if(!snakeBodies.empty())
    {
        snakeBodies[0]->setPos(this->pos());
    }
}
