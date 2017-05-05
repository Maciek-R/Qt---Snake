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

class SnakeHead: public QObject, public QGraphicsRectItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    static const int PIXELS_PER_SECONDS = 300;
    enum Direction{None, Left, Right, Up, Down};
    SnakeHead(QGraphicsItem* parent=NULL);

    void moveBodies();
    void move(qint64 diffTime);
    void changeWantedDirection(Direction dir);

    std::vector<SnakeBody*> snakeBodies;
    QPointF prevPos;    //prev position of last element

    ~SnakeHead();
    Direction getDir();
    QPointF getPositionOfLastElement();
    void setAnimation();
    void addAnimationForNewBody();
    void connectLastElement();
    void animate();
    std::vector<QPointF*> nextPoints;
    bool isAnimating = false;
private:
    QParallelAnimationGroup* group;
    QPropertyAnimation * animation;
    void setAnimationsForBodies();
    Direction wantedDir;
    Direction dir;

    std::vector<Direction> nextDirs;
    int getDuration(int i, int j, bool flag);

};

#endif // SNAKEHEAD_H
