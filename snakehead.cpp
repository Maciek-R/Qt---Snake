#include "SnakeHead.h"
#include <QBrush>
#include "Apple.h"
#include "SnakeBody.h"
#include "Game.h"

//extern Game* game;

SnakeHead::SnakeHead(QGraphicsItem *parent){

    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);

    dir = Direction::Right;
    wantedDir = Direction::None;
 //   setFlag(QGraphicsItem::ItemIsFocusable,true);
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


    if(wantedDir!=Direction::None)
    {
        if(dir == Direction::Left || dir==Direction::Right)
        {
            int a = ((int)(futureX)) / 50;
            int b = ((int)((this->pos().x()))) / 50;
            if(a!=b)
            {
                qreal diff = futureX - this->pos().x();
                if(dir == Direction::Right)
                    futureX = a*50;
                if(dir == Direction::Left)
                    futureX = b*50;
                if(wantedDir == Direction::Up)
                    futureY -= fabs(diff);
                else if(wantedDir == Direction::Down)
                    futureY += fabs(diff);
                dir = wantedDir;
                wantedDir = Direction::None;
            }
        }
        else if(dir == Direction::Up || dir==Direction::Down)
        {
            int a = ((int)(futureY)) / 50;
            int b = ((int)((this->pos().y()))) / 50;
            if(a!=b)
            {
                qreal diff = futureY - this->pos().y();
                if(dir == Direction::Down)
                    futureY = a*50;
                if(dir == Direction::Up)
                    futureY = b*50;
                if(wantedDir == Direction::Left)
                    futureX -= fabs(diff);
                else if(wantedDir == Direction::Right)
                    futureX += fabs(diff);

                dir = wantedDir;
                wantedDir = Direction::None;
            }
        }

    }


    if(snakeBodies.isEmpty())
    {
        prevPos.setX(this->pos().x());
        prevPos.setY(this->pos().y());
    }
    else
    {
        prevPos.setX(snakeBodies.last()->pos().x());
        prevPos.setY(snakeBodies.last()->pos().y());
    }


    moveBodies();
    setPos(futureX, futureY);

}

void SnakeHead::changeWantedDirection(Direction dir)
{
    this->wantedDir = dir;
}

void SnakeHead::moveBodies(){

    for(int i=snakeBodies.size()-1; i>0; --i)
    {
        snakeBodies[i]->setPos(snakeBodies[i-1]->pos());
    }
    if(!snakeBodies.isEmpty())
    {
        snakeBodies[0]->setPos(this->pos());
    }
}
