#include "SnakeBody.h"
#include <QBrush>

SnakeBody::SnakeBody(QGraphicsItem *parent)
    :QObject(), QGraphicsRectItem(parent)
{

    // draw
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);


    seqGroup = new QSequentialAnimationGroup();
   // connect(seqGroup, SIGNAL(currentAnimationChanged(QAbstractAnimation*)), this, SLOT(changed()));
}

void SnakeBody::addAnimation()
{

}
void SnakeBody::clear()
{
    seqGroup->clear();
}

void SnakeBody::changed()
{
    //qDebug() <<"now";
    ++indexQueue;

}

void SnakeBody::conn()
{
    connect(seqGroup, SIGNAL(currentAnimationChanged(QAbstractAnimation*)), this, SLOT(changed()));
}
