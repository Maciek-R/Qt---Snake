#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QObject>
#include <QDebug>

class SnakeBody: public QObject, public QGraphicsRectItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    SnakeBody(QGraphicsItem* parent=NULL);
    ~SnakeBody();
};

#endif // SNAKEBODY_H
