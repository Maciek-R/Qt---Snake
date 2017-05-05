#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <fstream>
#include <string>
#include <QDebug>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QLabel* labels[10];
    void initLabels();
    void readScoresFromFile();
};

#endif // DIALOG_H
