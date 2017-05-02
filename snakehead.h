#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "SnakeBody.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QList>
#include <QPointF>
#include <typeinfo>
#include <QDebug>

class SnakeHead: public QGraphicsRectItem{
public:
    static const int PIXELS_PER_SECONDS = 300;
    enum Direction{None, Left, Right, Up, Down};
    SnakeHead(QGraphicsItem* parent=NULL);

    void moveBodies();
    void move(qint64 diffTime);
    void changeWantedDirection(Direction dir);

    QList<SnakeBody*> snakeBodies;
    QPointF prevPos;    //prev position of last element
private:
    Direction wantedDir;
    Direction dir;
};

#endif // SNAKEHEAD_H
