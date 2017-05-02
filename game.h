#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "SnakeHead.h"
#include "Apple.h"
#include <QKeyEvent>
#include <QTimer>


class Game: public QGraphicsView{

public:

    Game(QWidget* parent=NULL);

    void start();


    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene* scene;

public:

    SnakeHead* snakeHead;
    Apple* apple;
    int checkCollision();
    void nextStep(qint64 differenceTime);
};

#endif // GAME_H
