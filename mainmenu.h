#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

namespace Ui {
class Mainmenu;
}

class Mainmenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainmenu(QWidget *parent = 0);
    ~Mainmenu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Mainmenu *ui;
};

#endif // MAINMENU_H
