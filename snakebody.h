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
    void addAnimation();

    int indexQueue;
    QSequentialAnimationGroup *seqGroup;

    void clear();
    void conn();
public slots:
    void changed();
};

#endif // SNAKEBODY_H
