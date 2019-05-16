#include "set.h"
#include "ui_set.h"

Set::Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);

}

Set::~Set()
{
    delete ui;
}

void Set::on_buttonBox_accepted()
{
    emit acceptIpPort(ui->lineEdit->text(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt());
}
void Set::setdefault(QString ip ,int SendPort,int SnapshotPort,int OrderPort)
{
    ui->lineEdit->setText(ip);
    ui->lineEdit_2->setText(QString::number(SendPort));
    ui->lineEdit_3->setText(QString::number(SnapshotPort));
    ui->lineEdit_4->setText(QString::number(OrderPort));
}
