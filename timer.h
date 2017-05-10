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
    Game * game;
    qint64 lastFrameTimeMillis;

public:
    Timer(Game *);
    void stop();
public slots:
    void update();
};

#endif // TIMER_H
