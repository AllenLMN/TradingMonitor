#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "receive.h"

#include <QList>
#include <QDateTime>
#include "sent.h"
#include <QThread>
#include "qcustomplot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    receive *recmq;
    QThread *recthread;
    sent *sentmq;
     QThread *sentthread;

private:
    Ui::MainWindow *ui;
signals:


    void serialAppend(QString strat,QDateTime timer, double down,double stop_down,double up,double stop_up ,double mid);
public slots:
    void showmessage(QString strat,QDateTime timer,double down,double stop_down,double up,double stop_up ,double mid);


    void sendData(QString strat,QString modifyType,QString modify);
private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:

    QStringList m_stratmodel;
    QMap<QString,QVector<QDateTime>>  m_timerList;
    QMap<QString,double>  maxList;
    QMap<QString,double>  minList;
//    QMap<QString,QVector<double>>  m_TickerList;

//    QMap<QString,QVector<double>> m_downList;
//    QMap<QString,QVector<double>> m_stop_downList;
//    QMap<QString,QVector<double>> m_upList;
//    QMap<QString,QVector<double>> m_stop_upList;
//    QMap<QString,QVector<double>> m_midList;
//        QMap<QString,double>  m_timerList;
//        QMap<QString,double>  m_TickerList;

//        QMap<QString,double> m_downList;
//        QMap<QString,double> m_stop_downList;
//        QMap<QString,double> m_upList;
//        QMap<QString,double> m_stop_upList;
//        QMap<QString,double> m_midList;
    QList<QCustomPlot *> plots;

//   QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
};

#endif // MAINWINDOW_H
