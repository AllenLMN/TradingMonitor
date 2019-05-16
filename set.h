#ifndef SET_H
#define SET_H

#include <QDialog>

namespace Ui {
class Set;
}

class Set : public QDialog
{
    Q_OBJECT

public:
    explicit Set(QWidget *parent = 0);
    ~Set();
void setdefault(QString ip ,int SendPort,int SnapshotPort,int OrderPort);
private slots:
    void on_buttonBox_accepted();
signals:
void acceptIpPort(QString ip ,int SendPort,int SnapshotPort,int OrderPort);
private:
    Ui::Set *ui;
};

#endif // SET_H
