#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "game.h"
#include <QDateTime>

class Timer: public QObject
{
    Q_OBJECT

private:
    QTimer * timer;
  //  QTime * time;
  //  QElapsedTimer * elapsedTimer;
    Game * game;
    qint64 lastFrameTimeMillis;

public:
    Timer(Game *);


public slots:
    void method();
};

#endif // TIMER_H
