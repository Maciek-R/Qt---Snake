#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

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
    void qwerty();

private:
    Ui::SnakeWindow *ui;
   //  QTimer * timer;
};

#endif // SNAKEWINDOW_H
