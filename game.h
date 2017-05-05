#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "SnakeHead.h"
#include "Apple.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include <QDateTime>


class Game:  public QObject, public QGraphicsView
{
    Q_OBJECT
    bool checkCrash();
public:

    Game(QWidget* parent=NULL);

    void start();


    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene* scene;

    bool isPaused = false;
    void randNewApple();
public slots:
     void checkCollision();
signals:
     void gameOver(int);
public:
      qint64 lastFrameTimeMillis;
     int points = 0;
    QTimer * timer;
    bool timerEnable=true;
    SnakeHead* snakeHead;
    Apple* apple;
    int checkingCollisions();
    void setAnimation();
    void resizeEvent(QResizeEvent *event);
};

#endif // GAME_H
