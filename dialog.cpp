#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    initLabels();

    readScoresFromFile();

}

void Dialog::initLabels()
{
    labels[0] = ui->label;
    labels[1] = ui->label_6;
    labels[2] = ui->label_2;
    labels[3] = ui->label_7;
    labels[4] = ui->label_3;
    labels[5] = ui->label_8;
    labels[6] = ui->label_4;
    labels[7] = ui->label_9;
    labels[8] = ui->label_5;
    labels[9] = ui->label_10;
}
void Dialog::readScoresFromFile()
{
    std::fstream plik;
    plik.open("D:/Qt/Projekty/BESTSNAKE/scores.txt", std::ios::in | std::ios::out);


    if(plik.is_open())
    {
        std::string tekst;
        int i=0;
        while(std::getline(plik, tekst))
        {

                labels[i]->setText(QString::fromStdString(tekst));


            ++i;
        }
        plik.close();
    }
    else
    {
        qDebug() << "Nie udało się otworzyć pliku";
    }
}

Dialog::~Dialog()
{
    delete ui;
}
