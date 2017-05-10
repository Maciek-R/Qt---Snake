#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include "game.h"
#include "namedialog.h"
#include "timer.h"

namespace Ui {
class SnakeWindow;
}

class SnakeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SnakeWindow(QWidget *parent = 0);
    ~SnakeWindow();

private slots:
    void end(int);
    void stopTimer();
private:
    Ui::SnakeWindow *ui;
    Timer * timer;
};

#endif // SNAKEWINDOW_H
