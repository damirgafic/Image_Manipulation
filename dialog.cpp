#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include <string>
using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(1);
    l.clear();
    ui->label->setPixmap(QPixmap::fromImage(l.clear()));
    ui->label->show();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_radioButton_toggled(bool checked) // line
{
    l.setType('l');
}

void Dialog::on_radioButton_2_toggled(bool checked) // circle
{
    l.setType('c');
}

void Dialog::on_radioButton_3_toggled(bool checked) // rectangle
{
    l.setType('r');
}

void Dialog::on_radioButton_4_toggled(bool checked) // triangle
{
    l.setType('t');
}

void Dialog::on_pushButton_clicked() // clear image
{
    ui->label->setPixmap(QPixmap::fromImage(l.clear()));
    ui->label->show();

}

void Dialog::on_pushButton_2_clicked() // load button
{
   l.loadImage();

}

void Dialog::on_pushButton_3_clicked() // save button
{
    l.saveImage();
}
void Dialog::on_lineEdit_textEdited(const QString &arg1)
{

}

void Dialog::on_pushButton_5_clicked() // rle save
{
    unsigned char *c=nullptr;
    int f=0;

    l.RLEcompress(c,f,c);

}
