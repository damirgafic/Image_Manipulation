#ifndef DIALOG_H
#define DIALOG_H
#include "mylabel.h"
#include <QDialog>
#include <QCheckBox>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    MyLabel l;

private slots:
    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_5_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
