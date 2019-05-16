#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snapshotreceive.h"

#include <QList>
#include <QDateTime>
#include "sent.h"
#include <QThread>
#include "qcustomplot.h"
#include "orderreceive.h"
#include "mytracer.h"
#include "set.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* s_instance;

    static MainWindow* instance(){
        return s_instance;
    }
    SnapshotReceive *SnapshotRecmq;
//    QThread *SnapshotRecthread;
    sent *sentmq;
    OrderReceive *OrderRecmq;
//    QThread *OrderRecthread;
//     QThread *sentthread;
Set *messageboxset;
QSettings* m_userSettings = nullptr; ///< 用户设置
QString ip ;int SendPort;int SnapshotPort;int OrderPort;
private:
    Ui::MainWindow *ui;

    QCPItemTracer *tracer = nullptr;// 跟踪的点
        QCPItemText *label = nullptr;   // 显示的数值
        QCPItemLine *arrow = nullptr;   // 箭头
//        AxisTag *mTag1;
//        AxisTag *mTag2;

public slots:
    void showmessage(QString strat,QDateTime timer,double mean,double down,double stop_down,double up,double stop_up ,double mid);
    void showmessage(QString contract,QDateTime timer,int side);


    void sendData(QString strat,QString modifyType,QString modify);
private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);
 void mouseWheel(QWheelEvent * event);
  void mouseDoubleClick(QMouseEvent*);
  void mousePress(QMouseEvent*);
  void on_checkBox_clicked(bool checked);

  void on_actionconnect_triggered();

  void on_actionDisconnect_triggered();

  void on_actionClear_triggered();
void acceptIpPort(QString ip ,int SendPort,int SnapshotPort,int OrderPort);
void on_pushButton_2_clicked();

protected:
    void resizeEvent(QResizeEvent *event);
void closeEvent( QCloseEvent * event );
private:
bool isclear=false;
bool isdisconnect=false;
bool zoom=false;
    QStringList m_stratmodel;
    QMap<QString,QMap<QDateTime,QDateTime>>  m_timerList;
    QMap<QString,QDateTime>  m_timerfirstList;
    QMap<QString,QDateTime>  m_timerlastList;
     QMap<QString,QDateTime>  orderbuymap;
       QMap<QString,QDateTime>  ordersellmap;
    QList<myTracer *> mytracerList0;
    QList<myTracer *> mytracerList1;
    QList<myTracer *> mytracerList2;
    QList<myTracer *> mytracerList3;
    QList<myTracer *> mytracerList4;
    QList<myTracer *> mytracerList5;
    QList<QCustomPlot *> plots;
    QMap<QString,double>  maxList;
        QMap<QString,double>  minList;
//   QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
};

#endif // MAINWINDOW_H
