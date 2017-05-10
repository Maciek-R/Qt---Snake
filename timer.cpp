#include "timer.h"

Timer::Timer(Game * game)
{
    this->game = game;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


    lastFrameTimeMillis =  QDateTime::currentMSecsSinceEpoch();
    timer->start(10);
}

void Timer::update()
{
    auto tmp = QDateTime::currentMSecsSinceEpoch();
    auto differenceTime = tmp - lastFrameTimeMillis;
    lastFrameTimeMillis = tmp;

    game->nextMove(differenceTime);
}
void Timer::stop()
{
    timer->stop();
}
