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

namespace Ui {
class SnakeWindow;
}

class SnakeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SnakeWindow(QWidget *parent = 0);
    ~SnakeWindow();

    void resizeEvent(QResizeEvent *event);
private slots:
    void qwerty();

    void end(int);

private:
    Ui::SnakeWindow *ui;
   //  QTimer * timer;
};

#endif // SNAKEWINDOW_H
