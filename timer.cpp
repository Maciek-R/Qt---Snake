#include "timer.h"

Timer::Timer(Game * game)
{
    this->game = game;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(method()));

   // time = new QTime();
  //  elapsedTimer = new QElapsedTimer();
  //  elapsedTimer->start();
    timer->start(10);

    lastFrameTimeMillis =  QDateTime::currentMSecsSinceEpoch();
   // lastFrame = x;
}

void Timer::method()
{
     //   int x = time->elapsed();
       // auto x = elapsedTimer->elapsed();
//qDebug() << x;

    auto tmp = QDateTime::currentMSecsSinceEpoch();
    auto differenceTime = tmp - lastFrameTimeMillis;
    lastFrameTimeMillis = tmp;

 //   qDebug() << differenceTime;
        game->nextStep(differenceTime);

}
