#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zmq.h"

#include "market_snapshot.h"
#include <QDebug>
//QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recmq=new receive();

    recthread=new  QThread();
    connect(recthread, SIGNAL(started()),recmq, SLOT(run()));
        connect(recthread, SIGNAL(finished()), recmq, SLOT(close()));
        connect(recmq,SIGNAL(receivemessage(QString,QDateTime,double,double,double,double,double)),this,SLOT(showmessage(QString,QDateTime,double,double,double,double,double)));
    recmq->moveToThread(recthread);
    recthread->start();
    sentmq=new sent();

    sentthread=new  QThread();
    connect(sentthread, SIGNAL(started()),sentmq, SLOT(run()));
        connect(sentthread, SIGNAL(finished()), sentmq, SLOT(close()));
    sentmq->moveToThread(sentthread);



}


MainWindow::~MainWindow()
{
    if (recthread)
    {
        if (recthread->isRunning())
        {
            recthread->quit();
            recthread->wait();
        }
      delete recthread;
       recthread = NULL;
  }
    if (recmq)
    {

        delete recmq;
        recmq = NULL;
    }

   disconnect(sentthread, SIGNAL(started()),sentmq, SLOT(run()));
         disconnect(sentthread, SIGNAL(finished()), sentmq, SLOT(deleteLater()));
         if (sentthread)
         {
             if (sentthread->isRunning())
             {
                 sentthread->quit();
                 sentthread->wait();
             }
           delete sentthread;
            sentthread = NULL;
       }
        if (sentmq)
        {
            delete sentmq;
            sentmq = NULL;
        }

//           this->deleteLater();

    delete ui;
}
void MainWindow::showmessage(QString strat,QDateTime timer,double down,double stop_down,double up,double stop_up ,double mid){
    qDebug()<<"timer"<<timer<<"strat"<<strat<<"down"<<down<<"stop_down"<<stop_down<<"up"<< up<<"stop_up" <<stop_up <<"mid"<< mid;

       if(ui->comboBox->findText(strat)==-1)
   {
       ui->comboBox->addItem(strat);
       QCustomPlot *plot=new QCustomPlot();
       plot->addGraph();
       plot->addGraph();
       plot->addGraph();
       plot->addGraph();
       plot->addGraph();
       plot->hide();
       plot->legend->setVisible(true);

 plot->setParent(ui->widget);
       plots.append(plot);
plot->setGeometry(0,0,ui->widget->width(),ui->widget->height());
//       for(int i=0;i<plots.count()-1;i++)
//       {
//           plots[i]->hide();
//       }
   }
       qDebug()<<"timer.time().elapsed()/1000.0;"<<timer.time().elapsed()/1000.0;

plots[ui->comboBox->currentIndex()]->show();
//QVector<double> downlist;
//QVector<double> stop_downList;
//QVector<double> uplist;
//QVector<double> stop_uplist;
//QVector<double> midlist;
QVector<QDateTime> timerlist;
double max=0;double min=0;
//QVector<double> Tickerlist;
//double Tickerlist;
if(m_timerList.isEmpty()||m_timerList.value(strat).isEmpty()||(timer!=m_timerList.value(strat).last()))
{

          if(m_timerList.keys().contains(strat))
    {

                  max=maxList.value(strat);


                  if(down>max)
                  {
                      max=down;
                  }
                  if(stop_down>max)
                  {
                      max=stop_down;
                  }
                  if(up>max)
                  {
                      max=up;
                  }
                  if(stop_up>max)
                  {
                      max=stop_up;
                  }
                  if(mid>max)
                  {
                      max=mid;
                  }
                  maxList.remove(strat);
                   maxList.insert(strat,max);

                   min=maxList.value(strat);
                  if(down<min)
                  {
                      min=down;
                  }
                  if(stop_down<min)
                  {
                      min=stop_down;
                  }
                  if(up<min)
                  {
                      min=up;
                  }
                  if(stop_up<min)
                  {
                      min=stop_up;
                  }
                  if(mid<min)
                  {
                      min=mid;
                  }
                  minList.remove(strat);
                   minList.insert(strat,min);
////                  downlist=m_downList.value(strat);
////                  downlist.append(down);
//                  m_downList.remove(strat);
////                   m_downList.insert(strat,downlist);
//                m_downList.insert(strat,down);

////                   stop_downList=m_stop_downList.value(strat);
////                   stop_downList.append(stop_down);
//                   m_stop_downList.remove(strat);
////                    m_stop_downList.insert(strat,stop_downList);
//                   m_stop_downList.insert(strat,stop_down);

////                    uplist=m_upList.value(strat);
////                    uplist.append(up);
//                    m_upList.remove(strat);
////                     m_upList.insert(strat,uplist);
//                    m_upList.insert(strat,up);

////                     stop_uplist=m_stop_upList.value(strat);
////                     stop_uplist.append(stop_up);
//                     m_stop_upList.remove(strat);
////                      m_stop_upList.insert(strat,stop_uplist);
//                     m_stop_upList.insert(strat,stop_up);

////                      midlist=m_midList.value(strat);
////                      midlist.append(mid);
//                      m_midList.remove(strat);
////                       m_midList.insert(strat,midlist);
//                      m_midList.insert(strat,mid);


//                               Tickerlist=m_TickerList.value(strat);
////                               Tickerlist.append(Tickerlist.last()+1);
//                               m_TickerList.remove(strat);
////                                m_TickerList.insert(strat,Tickerlist);
//                               m_TickerList.insert(strat,Tickerlist+1);


                   timerlist=m_timerList.value(strat);
                   timerlist.append(timer);
                   m_timerList.remove(strat);
                    m_timerList.insert(strat,timerlist);
//                   m_timerList.insert(strat,timer.toString("yyyy-MM-dd hh:mm:ss"));
//              }


    }else
          {

              if(down>max)
              {
                  max=down;
              }
              if(stop_down>max)
              {
                  max=stop_down;
              }
              if(up>max)
              {
                  max=up;
              }
              if(stop_up>max)
              {
                  max=stop_up;
              }
              if(mid>max)
              {
                  max=mid;
              }

               maxList.insert(strat,max);

               min=maxList.value(strat);
              if(down<min)
              {
                  min=down;
              }
              if(stop_down<min)
              {
                  min=stop_down;
              }
              if(up<min)
              {
                  min=up;
              }
              if(stop_up<min)
              {
                  min=stop_up;
              }
              if(mid<min)
              {
                  min=mid;
              }

               minList.insert(strat,min);
//m_downList.insert(strat,down);
//m_stop_downList.insert(strat,stop_down);
//m_upList.insert(strat,up);
//m_stop_upList.insert(strat,stop_up);
//              downlist.append(down);
//              m_downList.insert(strat,downlist);

//              stop_downList.append(stop_down);
//              m_stop_downList.insert(strat,stop_downList);

//              uplist.append(up);
//              m_upList.insert(strat,uplist);

//              stop_uplist.append(stop_up);
//              m_stop_upList.insert(strat,stop_uplist);

//              midlist.append(mid);
//              m_midList.insert(strat,midlist);


//              Tickerlist.append(0);
//              m_TickerList.insert(strat,Tickerlist);

              timerlist.append(timer);
               m_timerList.insert(strat,timerlist);


          }

//          qDebug()<<"downlist"<<downlist;
//          qDebug()<<"stopup"<<stop_uplist;
//          qDebug()<<timerlist;
//          qDebug()<<Tickerlist;

//             dateTicker
//    textTicker->setSubTickCount(10);
////    textTicker
//    textTicker->addTick(0, timerlist[0]);
//    for(int i=1;i<timerlist.count();i++)
//    {
//        textTicker->addTick(i, timerlist[i]);
//    }
    connect(plots[ui->comboBox->findText(strat)]->xAxis, SIGNAL(rangeChanged(QCPRange)), plots[ui->comboBox->findText(strat)]->xAxis, SLOT(setRange(QCPRange)));
    connect(plots[ui->comboBox->findText(strat)]->yAxis, SIGNAL(rangeChanged(QCPRange)), plots[ui->comboBox->findText(strat)]->yAxis, SLOT(setRange(QCPRange)));

plots[ui->comboBox->findText(strat)]->yAxis->setRange(min-10,max+10);
    plots[ui->comboBox->findText(strat)]->xAxis->setTicker(dateTicker);

plots[ui->comboBox->findText(strat)]->xAxis->setRange(timerlist.first().toTime_t(),timerlist.last().toTime_t());
    plots[ui->comboBox->findText(strat)]->xAxis->setLabel("time");
    plots[ui->comboBox->findText(strat)]->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);


     plots[ui->comboBox->findText(strat)]->graph(0)->setPen(QPen(Qt::blue));
                //设置右上角图形标注名称
     plots[ui->comboBox->findText(strat)]->graph(0)->setName("down");

     plots[ui->comboBox->findText(strat)]->graph(0)->addData(timer.toTime_t(),down);

     plots[ui->comboBox->findText(strat)]->graph(1)->setPen(QPen(Qt::yellow));
                //设置右上角图形标注名称
     plots[ui->comboBox->findText(strat)]->graph(1)->setName("stop_down");

     plots[ui->comboBox->findText(strat)]->graph(1)->addData(timer.toTime_t(),stop_down);


     plots[ui->comboBox->findText(strat)]->graph(2)->setPen(QPen(Qt::gray));
                //设置右上角图形标注名称
     plots[ui->comboBox->findText(strat)]->graph(2)->setName("up");

     plots[ui->comboBox->findText(strat)]->graph(2)->addData(timer.toTime_t(),up);


     plots[ui->comboBox->findText(strat)]->graph(3)->setPen(QPen(Qt::red));
                //设置右上角图形标注名称
     plots[ui->comboBox->findText(strat)]->graph(3)->setName("stop_up");

     plots[ui->comboBox->findText(strat)]->graph(3)->addData(timer.toTime_t(),stop_up);


     plots[ui->comboBox->findText(strat)]->graph(4)->setPen(QPen(Qt::green));
                //设置右上角图形标注名称
     plots[ui->comboBox->findText(strat)]->graph(4)->setName("mid");

     plots[ui->comboBox->findText(strat)]->graph(4)->addData(timer.toTime_t(),mid);

}
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    for(int i=0;i<plots.count();i++)
    {
        plots[i]->resize(ui->widget->width(),ui->widget->height());
    }
}

void MainWindow::sendData(QString strat,QString modifyType,QString modify)
{


    sentthread->terminate();
//    recv::instance().quit();
     sentthread->wait();
//      recv::instance().deleteLater();
    sentmq->setStrat(strat);
    sentmq->setModifyType(modifyType);
    sentmq->setModify(modify);
    qDebug()<<strat<<modifyType<<modify;
    sentthread->start();

}

void MainWindow::on_pushButton_clicked()
{

    if((ui->comboBox_2->currentText()!="")&&(ui->lineEdit->text()!="")&&(ui->lineEdit->text()!=NULL)&&ui->checkBox->isChecked())
    {
        sendData(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->lineEdit->text());

    }


}

void MainWindow::on_comboBox_activated(int index)
{
           for(int i=0;i<plots.count();i++)
           {
               plots[i]->hide();
           }
           plots[index]->show();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
 {
    if ((QApplication::keyboardModifiers() == Qt::ControlModifier) && (event->button() == Qt::LeftButton))
    {
        QMessageBox::aboutQt(NULL, "aboutQt");
    }
}
