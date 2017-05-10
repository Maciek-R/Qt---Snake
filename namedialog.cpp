#include "namedialog.h"
#include "ui_namedialog.h"

NameDialog::NameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameDialog)
{
    ui->setupUi(this);
}

NameDialog::~NameDialog()
{
    delete ui;
}

void NameDialog::on_pushButton_clicked()
{
    name = ui->lineEdit->text().toStdString();
    insertResult();

    Dialog dialog;
    dialog.setModal(true);
    dialog.exec();

    this->close();
}

void NameDialog::setPoints(int points)
{
    this->points = points;
    ui->label->setText(ui->label->text() + " " + QString::number(points));
}

void NameDialog::insertResult()
{
    std::fstream plik;
    plik.open("D:/Qt/Projekty/BESTSNAKE/scores.txt", std::ios::in | std::ios::out);


    if(plik.is_open())
    {
        std::string tekst;
        std::string names[5];
        int results[5];
        int i=0;
        while(std::getline(plik, tekst))
        {
            names[i] = tekst;
            plik >> results[i];
            std::getline(plik, tekst);
            ++i;
        }

        for(i=0; i<5; ++i)
        {
            if(points >= results[i]) break;
        }

        for(int j=4; j>i; --j)
        {
            name[j] = name[j-1];
            results[j] = results[j-1];
        }

        if(i<5)
        {
            names[i] = name;
            results[i] = points;

        }
        plik.close();
        plik.open("D:/Qt/Projekty/BESTSNAKE/scores.txt", std::ios::out);

        for(int x=0; x<5; ++x)
        {
            plik << names[x] <<"\n";
            plik << results[x] <<"\n";
        }
        plik.close();

        for(int x=0; x<5; ++x)
        {
            QString s = QString::fromStdString(names[x]);
            qDebug(qUtf8Printable(s));
            qDebug() << results[x];
        }

    }
    else
    {
        qDebug() << "Nie udało się otworzyć pliku";
    }
}
