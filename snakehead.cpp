#include "SnakeHead.h"
#include <QBrush>
#include "Apple.h"
#include "SnakeBody.h"
#include "Game.h"

//extern Game* game;

//SnakeHead::SnakeHead(QGraphicsItem *parent){

SnakeHead::SnakeHead(QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
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

void SnakeHead::changeDirection(Direction dir)
{
    this->dir = dir;
}






QPointF SnakeHead::getPositionOfLastElement()
{
    QPointF point;

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
