#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QDialog>
#include <fstream>
#include <string>
#include "dialog.h"
#include <QDebug>

namespace Ui {
class NameDialog;
}

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget *parent = 0);
    ~NameDialog();

    void setPoints(int);

private slots:
    void on_pushButton_clicked();

private:
    Ui::NameDialog *ui;
    int points;
    std::string name;
    void insertResult();
};

#endif // NAMEDIALOG_H
