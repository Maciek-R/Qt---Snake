#include <QApplication>
#include "Game.h"
#include "timer.h"
Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->start();

    Timer tim(game);

    return a.exec();
}
