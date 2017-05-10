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


class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=NULL);
    ~Game();

    void start();

    void keyPressEvent(QKeyEvent *event);

    bool isPaused = false;
    void randNewApple();
    void nextMove(qint64 differenceTime);

signals:
     void gameOver(int);
     void stopTimer();
private:
    QGraphicsScene* scene;
    bool checkCrash();
    int points = 0;
    SnakeHead* snakeHead;
    Apple* apple;
    int checkingCollisions();
    void resizeEvent(QResizeEvent *event);
    void initBoard();
    void initItems();
};

#endif // GAME_H
