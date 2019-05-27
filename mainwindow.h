#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "receive.h"

#include <QList>
#include <QDateTime>
#include "sent.h"
#include <QThread>
#include "qcustomplot.h"

#include "mytracer.h"
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
//     QThread *sentthread;


private:
    Ui::MainWindow *ui;

    QCPItemTracer *tracer = nullptr;// 跟踪的点
        QCPItemText *label = nullptr;   // 显示的数值
        QCPItemLine *arrow = nullptr;   // 箭头
//        AxisTag *mTag1;
//        AxisTag *mTag2;

public slots:
    void showmessage(QString strat,QDateTime timer,double mean,double down,double stop_down,double up,double stop_up ,double mid);


    void sendData(QString strat,QString modifyType,QString modify);
private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);
 void mouseWheel(QWheelEvent * event);
  void mouseDoubleClick(QMouseEvent*);
  void mouseMove(QMouseEvent*);
  void on_checkBox_clicked(bool checked);

protected:
    void resizeEvent(QResizeEvent *event);
void closeEvent( QCloseEvent * event );
private:
bool zoom=false;
    QStringList m_stratmodel;
    QMap<QString,QVector<QDateTime>>  m_timerList;
//QList<AxisTag *> mtagList0;
//QList<AxisTag *> mtagList1;
//QList<AxisTag *> mtagList2;
//QList<AxisTag *> mtagList3;
//QList<AxisTag *> mtagList4;
//QList<AxisTag *> mtagList5;
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
