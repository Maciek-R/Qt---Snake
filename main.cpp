#include <QApplication>
#include "Game.h"
#include "timer.h"
#include "snakewindow.h"
#include "mainmenu.h"
Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



//

    Mainmenu * mainmenu = new Mainmenu();
    mainmenu->show();

  //  Timer tim(game);

    return a.exec();
}
