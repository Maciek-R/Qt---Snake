#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "SnakeBody.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QList>
#include <QPointF>
#include <typeinfo>
#include <QDebug>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <vector>

class SnakeHead: public QGraphicsRectItem{

public:
    static const int PIXELS_PER_SECONDS = 300;
    enum Direction{None, Left, Right, Up, Down};
    SnakeHead(QGraphicsItem* parent=NULL);

    void moveBodies();
    void move(qint64 diffTime);
    void changeDirection(Direction dir);

    std::vector<SnakeBody*> snakeBodies;
    QPointF prevPos;    //prev position of last element

    ~SnakeHead();
    Direction getDir();
    QPointF getPositionOfLastElement();


private:
    Direction dir;
};

#endif // SNAKEHEAD_H
