
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zmq.h"
#include <QCloseEvent>
#include "market_snapshot.h"
#include <QDebug>
#include <qalgorithms.h>
//QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
MainWindow* MainWindow::s_instance = NULL;
QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_instance = this;
    m_userSettings = new QSettings("zy1205", "TradingMonitor", this);
    ui->actionconnect->setEnabled(false);
    ip =m_userSettings->value("ip", "101.132.173.17").toString();
    SendPort=m_userSettings->value("SendPort", 33334).toInt();
    SnapshotPort=m_userSettings->value("SnapshotPort", 33333).toInt();
    OrderPort=m_userSettings->value("OrderPort", 33335).toInt();
    qDebug()<<"ip"<<ip<<"SendPort"<<SendPort<<"SnapshotPort"<<SnapshotPort<<"OrderPort"<<OrderPort;
    SnapshotRecmq=new SnapshotReceive();
    OrderRecmq=new OrderReceive();
    SnapshotRecmq->start();
    OrderRecmq->start();
    messageboxset=new Set();
    messageboxset->setdefault(ip,SendPort,SnapshotPort,OrderPort);
    connect(messageboxset,SIGNAL(acceptIpPort(QString,int,int,int)),this,SLOT(acceptIpPort(QString,int,int,int)));
       connect(SnapshotRecmq,SIGNAL(receivemessage(QString,QDateTime,double,double,double,double,double,double,double,double)),this,SLOT(showmessage(QString,QDateTime,double,double,double,double,double,double,double,double)),Qt::QueuedConnection);
       connect(OrderRecmq,SIGNAL(receivemessage(QString,QDateTime,int)),this,SLOT(showmessage(QString,QDateTime,int)),Qt::QueuedConnection);
    sentmq=new sent();
    ui->pushButton->setEnabled(false);
}


MainWindow::~MainWindow()
{
    this->deleteLater();
    delete ui;
}
void MainWindow::showmessage(QString strat,QDateTime timer,double mean,double down,double stop_down,double up,double stop_up ,double mid,double mean_up,double mean_down){

    if(!isclear){
        if(ui->comboBox->findText(strat)==-1)
        {

            QCustomPlot *plot=new QCustomPlot();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->addGraph();
            plot->graph(0)->setPen(QPen(Qt::blue));

            plot->graph(0)->setName("down");
            plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::blue, 1), QBrush(Qt::white), 3));

            plot->graph(1)->setPen(QPen(Qt::yellow));
            plot->graph(1)->setName("stop_down");
            plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::yellow,1), QBrush(Qt::white), 3));

            plot->graph(2)->setPen(QPen(Qt::gray));
            plot->graph(2)->setName("up");
            plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::gray, 1), QBrush(Qt::white), 3));

            plot->graph(3)->setPen(QPen(Qt::red));
            plot->graph(3)->setName("stop_up");
            plot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::red, 1), QBrush(Qt::white), 3));

            plot->graph(4)->setPen(QPen(Qt::green));
            plot->graph(4)->setName("mid");
            plot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::green, 1), QBrush(Qt::white), 3));

            plot->graph(5)->setPen(QPen(Qt::cyan));
            plot->graph(5)->setName("mean");
            plot->graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::cyan, 1), QBrush(Qt::white), 3));

            plot->graph(6)->setName("buy");
            plot->graph(6)->setLineStyle(QCPGraph::lsNone);
            plot->graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, QPen(Qt::red, 2), QBrush(Qt::white), 10));

            plot->graph(7)->setName("sell");
            plot->graph(7)->setLineStyle(QCPGraph::lsNone);
            plot->graph(7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangleInverted, QPen(Qt::yellow, 2), QBrush(Qt::white), 10));


            plot->graph(8)->setPen(QPen(Qt::magenta));
            plot->graph(8)->setName("mean_up");
            plot->graph(8)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::magenta, 1), QBrush(Qt::white), 3));

            plot->graph(9)->setPen(QPen(Qt::darkMagenta));
            plot->graph(9)->setName("mean_down");
            plot->graph(9)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::darkMagenta, 1), QBrush(Qt::white), 3));

            plot->hide();
            myTracer *mytracer0;
            myTracer *mytracer1;
            myTracer *mytracer2;
            myTracer *mytracer3;
            myTracer *mytracer4;
            myTracer *mytracer5;
            myTracer *mytracer6;
            myTracer *mytracer7;
            mytracer0=new myTracer(plot,myTracer::DataTracer);
            mytracer1=new myTracer(plot,myTracer::DataTracer);
            mytracer2=new myTracer(plot,myTracer::DataTracer);
            mytracer3=new myTracer(plot,myTracer::DataTracer);
            mytracer4=new myTracer(plot,myTracer::DataTracer);
            mytracer5=new myTracer(plot,myTracer::DataTracer);
            mytracer6=new myTracer(plot,myTracer::DataTracer);
            mytracer7=new myTracer(plot,myTracer::DataTracer);
            mytracerList0.append(mytracer0);
            mytracerList1.append(mytracer1);
            mytracerList2.append(mytracer2);
            mytracerList3.append(mytracer3);
            mytracerList4.append(mytracer4);
            mytracerList5.append(mytracer5);
mytracerList6.append(mytracer6);
mytracerList7.append(mytracer7);
            plot->legend->setVisible(true);

            plot->setParent(ui->widget);
            plots.append(plot);
            ui->comboBox->addItem(strat);
            plot->setGeometry(0,0,ui->widget->width(),ui->widget->height());

            connect(plot,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(mouseWheel(QWheelEvent*)));
            connect(plot,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(mouseDoubleClick(QMouseEvent*)));
            connect(plot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePress(QMouseEvent*)));

        }

        if(plots[ui->comboBox->findText(strat)]->graphCount()==0)
        {
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->addGraph();
            plots[ui->comboBox->findText(strat)]->graph(0)->setPen(QPen(Qt::blue));

            plots[ui->comboBox->findText(strat)]->graph(0)->setName("down");
            plots[ui->comboBox->findText(strat)]->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::blue, 1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(1)->setPen(QPen(Qt::yellow));
            plots[ui->comboBox->findText(strat)]->graph(1)->setName("stop_down");
            plots[ui->comboBox->findText(strat)]->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::yellow,1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(2)->setPen(QPen(Qt::gray));
            plots[ui->comboBox->findText(strat)]->graph(2)->setName("up");
            plots[ui->comboBox->findText(strat)]->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::gray, 1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(3)->setPen(QPen(Qt::red));
            plots[ui->comboBox->findText(strat)]->graph(3)->setName("stop_up");
            plots[ui->comboBox->findText(strat)]->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::red, 1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(4)->setPen(QPen(Qt::green));
            plots[ui->comboBox->findText(strat)]->graph(4)->setName("mid");
            plots[ui->comboBox->findText(strat)]->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::green, 1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(5)->setPen(QPen(Qt::cyan));
            plots[ui->comboBox->findText(strat)]->graph(5)->setName("mean");
            plots[ui->comboBox->findText(strat)]->graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::cyan, 1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(6)->setName("buy");
            plots[ui->comboBox->findText(strat)]->graph(6)->setLineStyle(QCPGraph::lsNone);
            plots[ui->comboBox->findText(strat)]->graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, QPen(Qt::red, 2), QBrush(Qt::white), 10));

            plots[ui->comboBox->findText(strat)]->graph(7)->setName("sell");
            plots[ui->comboBox->findText(strat)]->graph(7)->setLineStyle(QCPGraph::lsNone);
            plots[ui->comboBox->findText(strat)]->graph(7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangleInverted, QPen(Qt::yellow, 2), QBrush(Qt::white), 10));

            plots[ui->comboBox->findText(strat)]->graph(8)->setName("mean_up");
            plots[ui->comboBox->findText(strat)]->graph(8)->setLineStyle(QCPGraph::lsNone);
            plots[ui->comboBox->findText(strat)]->graph(8)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::magenta, 1), QBrush(Qt::white), 3));

            plots[ui->comboBox->findText(strat)]->graph(9)->setName("mean_down");
            plots[ui->comboBox->findText(strat)]->graph(9)->setLineStyle(QCPGraph::lsNone);
            plots[ui->comboBox->findText(strat)]->graph(9)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, QPen(Qt::darkMagenta, 1), QBrush(Qt::white), 3));


        }
QMap<QDateTime,QDateTime> timerlist;

        double max=0;double min=0;
        if(m_timerList.isEmpty()||m_timerList.value(strat).isEmpty()||(!m_timerList.value(strat).keys().contains(timer)))
        {
            if(maxList.contains(strat))
            {
                max=maxList.value(strat);
            }

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
            if(mean_up>max)
            {
                max=mean_up;
            }
            if(mean_down>max)
            {
                max=mean_down;
            }
            if(maxList.contains(strat))
            {
                maxList.remove(strat);
            }

            maxList.insert(strat,max);
            if(minList.contains(strat))
            {
                min=minList.value(strat);
            }

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
            if(mean_up<min)
            {
                min=mean_up;
            }
            if(mean_down<min)
            {
                min=mean_down;
            }
            if(minList.contains(strat))
            {
                minList.remove(strat);
            }

            minList.insert(strat,min);
            if(m_timerlastList.contains(strat))
            {
                if(timer>m_timerlastList.value(strat))
                {
                    m_timerlastList.remove(strat);
                    m_timerlastList.insert(strat,timer);
                }
            }else
            {
                m_timerlastList.insert(strat,timer);
            }
            if(m_timerfirstList.contains(strat))
            {
                if(timer<m_timerfirstList.value(strat))
                {
                    m_timerfirstList.remove(strat);
                    m_timerfirstList.insert(strat,timer);
                }
            }else
            {
                m_timerfirstList.insert(strat,timer);
            }


            if(m_timerList.contains(strat))
            {
                timerlist=m_timerList.value(strat);
            }
//            if(!timerlist.keys().contains(timer))
//            {
//                int timerlistnumber=timerlist.count()-1;
//                if(timerlistnumber!=-1)
//                { while(timerlist[timerlistnumber]>timer)
//                    {
//                        timerlistnumber--;
//                        if(timerlistnumber<0)
//                        {
//                            break;
//                        }

//                    }
                    timerlist.insert(timer,timer);
//                }else
//                {
//                    timerlist.append(timer);
//                }
//            }
            if(m_timerList.contains(strat))
            {
                m_timerList.remove(strat);
            }
            m_timerList.insert(strat,timerlist);
            plots[ui->comboBox->currentIndex()]->show();

            plots[ui->comboBox->findText(strat)]->xAxis->setTicker(dateTicker);

            plots[ui->comboBox->findText(strat)]->xAxis->setLabel("time");
            plots[ui->comboBox->findText(strat)]->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                                                  QCP::iSelectLegend | QCP::iSelectPlottables);


            plots[ui->comboBox->findText(strat)]->graph(0)->addData(timer.toSecsSinceEpoch(),down);
            plots[ui->comboBox->findText(strat)]->graph(1)->addData(timer.toSecsSinceEpoch(),stop_down);
            plots[ui->comboBox->findText(strat)]->graph(2)->addData(timer.toSecsSinceEpoch(),up);
            plots[ui->comboBox->findText(strat)]->graph(3)->addData(timer.toSecsSinceEpoch(),stop_up);
            plots[ui->comboBox->findText(strat)]->graph(4)->addData(timer.toSecsSinceEpoch(),mid);
            plots[ui->comboBox->findText(strat)]->graph(5)->addData(timer.toSecsSinceEpoch(),mean);
            plots[ui->comboBox->findText(strat)]->graph(8)->addData(timer.toSecsSinceEpoch(),mean_up);
            plots[ui->comboBox->findText(strat)]->graph(9)->addData(timer.toSecsSinceEpoch(),mean_down);
            if(zoom)
            {
                plots[ui->comboBox->findText(strat)]->replot();
            }else
            {
                if((max-min)<10){
                    plots[ui->comboBox->findText(strat)]->yAxis->setRange(min-1,max+1);
                }else
                {
                    plots[ui->comboBox->findText(strat)]->yAxis->setRange(min-10,max+10);
                }

                //qDebug()<<timerlist.first()<<timerlist.last();
                plots[ui->comboBox->findText(strat)]->xAxis->setRange(m_timerfirstList.value(strat).toSecsSinceEpoch(), m_timerlastList.value(strat).toSecsSinceEpoch()-m_timerfirstList.value(strat).toSecsSinceEpoch()+1, Qt::AlignLeft);
                plots[ui->comboBox->findText(strat)]->replot();
            }

        }}
}
void MainWindow::showmessage(QString contract,QDateTime timer,int side)
{

    if(!isclear)
    {

        //qDebug()<<"contract"<<contract;
        //qDebug()<<"timer.toString"<<timer.toString("yyyy-MM-dd hh:mm");
        //qDebug()<<"timer.toString"<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm");
        if(m_timerList.count() >0)
        {
            for(int i=0;i<ui->comboBox->count();i++)
            {
                if(ui->comboBox->itemText(i).contains(contract))
                {
                    if(side==OrderSide::Buy)
                    {
                        //                    //qDebug()<<"timer2"<<timer<<"Buy"<<side;
                        if(orderbuymap.contains(ui->comboBox->itemText(i)+QString::number(side)))
                        {
                            if(orderbuymap.contains(ui->comboBox->itemText(i)+QString::number(side)))
                            {
                                orderbuymap.remove(ui->comboBox->itemText(i)+QString::number(side));

                            }
                            orderbuymap.insert(ui->comboBox->itemText(i)+QString::number(side),timer);

                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").addSecs(60).toString("yyyy-MM-dd hh:mm");

                            int index;
                            int j=m_timerList.value(ui->comboBox->itemText(i)).count()-1;
                            if((j==-1)||(timer>m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)))
                            {
                                index=-1;
                            }else
                            {
                                while(m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)>timer)
                                {

                                    //                            //qDebug()<<"jjjj"<<j;
                                    j--;
                                    if(j<0)
                                    {
                                        break;
                                    }

                                }

                            }
                            //qDebug()<<"jjj"<<j;
                            //qDebug()<<contract<<"xxxxxx"<<m_timerList.value(ui->comboBox->itemText(i)).at(j);

                            index=j;
                            //qDebug()<<"jjjj"<<j;
                            if(index!=-1)
                            {
                                //qDebug()<<"index2"<<index;
                                if(plots[i]->graphCount()>0)
                                {
                                    double value=plots[i]->graph(4)->dataMainValue(index);
                                    qDebug()<<"value"<<value;
                                    plots[i]->graph(6)->addData(timer.toSecsSinceEpoch(),value);

                                }
                            }

                        }else
                        {


                            orderbuymap.insert(ui->comboBox->itemText(i)+QString::number(side),timer);
                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").toString("yyyy-MM-dd hh:mm");
                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").addSecs(60).toString("yyyy-MM-dd hh:mm");
                            int index;
                            int j=m_timerList.value(ui->comboBox->itemText(i)).count()-1;
                            if((j==-1)||(timer>m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)))
                            {
                                index=-1;
                            }else
                            {
                                while(m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)>timer)
                                {


                                    j--;
                                    if(j<0)
                                    {
                                        break;
                                    }
                                }

                            }
                            //qDebug()<<"jjj"<<j;
                            //qDebug()<<contract<<"xxxxxx"<<m_timerList.value(ui->comboBox->itemText(i)).at(j);
                            index=j;
                            //qDebug()<<"jjjj"<<j;
                            if(index!=-1)
                            {
                                //qDebug()<<"index2"<<index;
                                if(plots[i]->graphCount()>0)
                                {
                                    double value=plots[i]->graph(4)->dataMainValue(index);
                                    //qDebug()<<"value"<<value;
                                    plots[i]->graph(6)->addData(timer.toSecsSinceEpoch(),value);
                                }
                            }


                            //
                        }

                        //                    //qDebug()<<"side"<<side;
                        //            plots[ui->comboBox->findText(contract)];
                    }else if(side==OrderSide::Sell)
                    {
                        //                    //qDebug()<<"timer2"<<timer<<"Sell"<<side;
                        if(ordersellmap.contains(ui->comboBox->itemText(i)+QString::number(side)))
                        {
                            if(ordersellmap.contains(ui->comboBox->itemText(i)+QString::number(side)))
                            {
                                ordersellmap.remove(ui->comboBox->itemText(i)+QString::number(side));

                            }
                            ordersellmap.insert(ui->comboBox->itemText(i)+QString::number(side),timer);
                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").toString("yyyy-MM-dd hh:mm");
                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").addSecs(60).toString("yyyy-MM-dd hh:mm");

                            int index;
                            int j=m_timerList.value(ui->comboBox->itemText(i)).count()-1;
                            //qDebug()<<"jjj"<<j;

                            if((j==-1)||(timer>m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)))
                            {
                                index=-1;
                            }else
                            {
                                while(m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)>timer)
                                {


                                    j--;
                                    if(j<0)
                                    {
                                        break;
                                    }
                                }

                            }
                            //qDebug()<<contract<<"xxxxxx"<<m_timerList.value(ui->comboBox->itemText(i)).at(j);
                            index=j;
                            //qDebug()<<"jjjj"<<j;
                            if(index!=-1)
                            {
                                //qDebug()<<"index2"<<index;
                                if(plots[i]->graphCount()>0)
                                {
                                    double value=plots[i]->graph(4)->dataMainValue(index);
                                    //qDebug()<<"value"<<value;
                                    plots[i]->graph(7)->addData(timer.toSecsSinceEpoch(),value);
                                }
                            }


                        }else
                        {


                            ordersellmap.insert(ui->comboBox->itemText(i)+QString::number(side),timer);
                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").toString("yyyy-MM-dd hh:mm");
                            //qDebug()<<QDateTime::fromString(timer.toString("yyyy-MM-dd hh:mm"),"yyyy-MM-dd hh:mm").addSecs(60).toString("yyyy-MM-dd hh:mm");

                            int index;
                            int j=m_timerList.value(ui->comboBox->itemText(i)).count()-1;
                            if((j==-1)||(timer>m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)))
                            {
                                index=-1;
                            }else
                            {
                                while(m_timerList.value(ui->comboBox->itemText(i)).keys().at(j)>timer)
                                {


                                    j--;
                                    if(j<0)
                                    {
                                        break;
                                    }
                                }

                            }
                            //qDebug()<<"jjj"<<j;
                            //qDebug()<<contract<<"xxxxxx"<<m_timerList.value(ui->comboBox->itemText(i)).at(j);
                            index=j;
                            //qDebug()<<"jjjj"<<j;
                            if(index!=-1)
                            {
                                if(plots[i]->graphCount()>0)
                                {
                                    //                            //qDebug()<<"index2"<<index;
                                    double value=plots[i]->graph(4)->dataMainValue(index);
                                    //                            //qDebug()<<"value"<<value;
                                    plots[i]->graph(7)->addData(timer.toSecsSinceEpoch(),value);
                                }
                            }

                        }
                    }
                }

            }

            //    if(ui->comboBox->findText(contract)!=-1)
            //    {

            //

            //    }
        }
        //    plots[ui->comboBox->findText(contract)]->xAxis->setLabel("time");
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

    sentmq->run(strat,modifyType,modify);
    //qDebug()<<strat<<modifyType<<modify;

}

void MainWindow::on_pushButton_clicked()
{
    switch( QMessageBox::information( this, tr("sent tip"), tr("Do you really want to sent?"), tr("Yes"), tr("No"), 0, 1 ) )
    {
    case 0:

        if((ui->comboBox_2->currentText()!="")&&(ui->lineEdit->text()!="")&&(ui->lineEdit->text()!=NULL)&&ui->checkBox->isChecked())
        {
            sendData(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->lineEdit->text());

        }

        ui->checkBox->setChecked(false);
        ui->pushButton->setEnabled(false);
        break;
    case 1:
    default:
        //        ui->checkBox->setChecked(false);
        break;
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

void MainWindow::mouseWheel(QWheelEvent * event)
{
    zoom=true;

    if((QApplication::keyboardModifiers() == Qt::ControlModifier) ){

        plots[ui->comboBox->currentIndex()]->axisRect()->setRangeZoomFactor(1,2.2);

    }else{


        plots[ui->comboBox->currentIndex()]->axisRect()->setRangeZoomFactor(2,1);

    }
}
void MainWindow::mousePress(QMouseEvent* e)
{
    double pos = plots[ui->comboBox->currentIndex()]->xAxis->pixelToCoord(e->pos().x());

    if(ui->comboBox->count()>1)
    {
        double x=pos;
        QString xlabel=QDateTime::fromSecsSinceEpoch(x).toString("hh:mm:ss");
        //        int index=m_timerList.value(ui->comboBox->currentText()).indexOf(QDateTime::fromSecsSinceEpoch(x));
        //        //qDebug()<<"index222"<<index;
        int index;
        int j=m_timerList.value(ui->comboBox->currentText()).count()-1;
        if(j>-1)
        {
//            while(m_timerList.value(ui->comboBox->currentText()).keys().at(j)>QDateTime::fromSecsSinceEpoch(x))
//            {

//                //                            //qDebug()<<"jjjj"<<j;
//                j--;
//                if(j<0)
//                {
//                    break;
//                }

//            }


            index= m_timerList.value(ui->comboBox->currentText()).keys().indexOf(QDateTime::fromSecsSinceEpoch(x));
            qDebug()<<"index"<<index;
            if(index>=0)
            {
                if(plots[ui->comboBox->currentIndex()]->graphCount()>0)
                {
                    double graph0Value = plots[ui->comboBox->currentIndex()]->graph(0)->dataMainValue(index);
                    double graph1Value = plots[ui->comboBox->currentIndex()]->graph(1)->dataMainValue(index);
                    double graph2Value = plots[ui->comboBox->currentIndex()]->graph(2)->dataMainValue(index);
                    double graph3Value = plots[ui->comboBox->currentIndex()]->graph(3)->dataMainValue(index);
                    double graph4Value = plots[ui->comboBox->currentIndex()]->graph(4)->dataMainValue(index);
                    double graph5Value = plots[ui->comboBox->currentIndex()]->graph(5)->dataMainValue(index);
                    double graph6Value = plots[ui->comboBox->currentIndex()]->graph(8)->dataMainValue(index);
                    double graph7Value = plots[ui->comboBox->currentIndex()]->graph(9)->dataMainValue(index);

                    //double graph0Value = plots[ui->comboBox->currentIndex()]->graph(0)->dataMainValue(plots[ui->comboBox->currentIndex()]->graph(0)->dataCount()-1);

                    //double graph1Value = plots[ui->comboBox->currentIndex()]->graph(1)->dataMainValue(plots[ui->comboBox->currentIndex()]->graph(1)->dataCount()-1);

                    //double graph2Value = plots[ui->comboBox->currentIndex()]->graph(2)->dataMainValue(plots[ui->comboBox->currentIndex()]->graph(2)->dataCount()-1);

                    //double graph3Value =plots[ui->comboBox->currentIndex()]->graph(3)->dataMainValue(plots[ui->comboBox->currentIndex()]->graph(3)->dataCount()-1);

                    //double graph4Value = plots[ui->comboBox->currentIndex()]->graph(4)->dataMainValue(plots[ui->comboBox->currentIndex()]->graph(4)->dataCount()-1);

                    //double graph5Value = plots[ui->comboBox->currentIndex()]->graph(5)->dataMainValue(plots[ui->comboBox->currentIndex()]->graph(5)->dataCount()-1);
                    qDebug()<<"graph0Value"<<graph0Value;
                    qDebug()<<"graph1Value"<<graph1Value;
                    qDebug()<<"graph2Value"<<graph2Value;
                    qDebug()<<"graph3Value"<<graph3Value;
                    qDebug()<<"graph4Value"<<graph4Value;
                    qDebug()<<"graph5Value"<<graph5Value;

                    mytracerList0[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph0Value);
                    mytracerList1[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph1Value);
                    mytracerList2[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph2Value);
                    mytracerList3[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph3Value);
                    mytracerList4[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph4Value);
                    mytracerList5[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph5Value);
                    mytracerList6[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph6Value);
                    mytracerList7[ui->comboBox->currentIndex()]->updatePosition(m_timerList.value(ui->comboBox->currentText()).keys().at(index).toSecsSinceEpoch(),graph7Value);



                    mytracerList0[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph0Value)+")");
                    mytracerList1[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph1Value)+")");
                    mytracerList2[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph2Value)+")");
                    mytracerList3[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph3Value)+")");
                    mytracerList4[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph4Value)+")");
                    mytracerList5[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph5Value)+")");
                    mytracerList6[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph6Value)+")");
                    mytracerList7[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph7Value)+")");

                }

            }

        }

    }


}
void MainWindow::mouseDoubleClick(QMouseEvent*)

{
    //    if((QApplication::keyboardModifiers() == Qt::ControlModifier) ){

    //        zoom=false;
    //        for (int i=0;i<plots.count();i++)
    //        {
    //            plots[i]->xAxis->setRange(m_timerfirstList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch(), m_timerlastList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch()-m_timerfirstList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch()+1, Qt::AlignLeft);

    //            //        plots[i]->xAxis->setRange(m_timerList.value(ui->comboBox->itemText(i)).last().toSecsSinceEpoch(), m_timerList.value(ui->comboBox->itemText(i)).count(), Qt::AlignLeft);

    //        }
    //    }


}
void MainWindow::closeEvent( QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("exit tip"), tr("Do you really want exit?"), tr("Yes"), tr("No"), 0, 1 ) )
    {
    case 0:

        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        switch( QMessageBox::information( this, tr("enabled_mod tip"), tr("Do you really want to choose enabled_mod?"), tr("Yes"), tr("No"), 0, 1 ) )
        {
        case 0:

            ui->checkBox->setChecked(true);
            ui->pushButton->setEnabled(true);
            break;
        case 1:
        default:
            ui->checkBox->setChecked(false);
             ui->pushButton->setEnabled(false);
            break;
        }
    }

}

void MainWindow::on_actionconnect_triggered()
{
    messageboxset->open();
    ui->actionDisconnect->setEnabled(true);
    ui->actionconnect->setEnabled(false);
}

void MainWindow::on_actionDisconnect_triggered()
{
    ui->actionDisconnect->setEnabled(false);
    ui->actionconnect->setEnabled(true);
    isdisconnect=true;
    OrderRecmq->terminate();
    OrderRecmq->wait();
    SnapshotRecmq->terminate();
    SnapshotRecmq->wait();
    //OrderRecmq->disconnect();
    OrderRecmq->deleteLater();
    SnapshotRecmq->deleteLater();
    sentmq->deleteLater();
    //    SnapshotRecmq->closereceive();
    //    OrderRecmq->closereceive();
    //OrderRecmq->terminate();
    //OrderRecmq->wait();
    //SnapshotRecmq->terminate();
    //SnapshotRecmq->wait();
    //SnapshotRecthread->terminate();
    //SnapshotRecthread->wait();
    //OrderRecthread->terminate();
    //OrderRecthread->wait();
}

void MainWindow::on_actionClear_triggered()
{
    if(!isdisconnect)
    {
        OrderRecmq->terminate();
        OrderRecmq->wait();
        SnapshotRecmq->terminate();
        SnapshotRecmq->wait();
        //OrderRecmq->disconnect();
        OrderRecmq->deleteLater();
        SnapshotRecmq->deleteLater();
        sentmq->deleteLater();
    }

    isclear=true;

    //    plots.clear();
    if(plots.count()>0)
    {
        for(int i=0;i<plots.count();i++)
        {

            plots[i]->graph(0)->data().clear();
            plots[i]->graph(1)->data().clear();
            plots[i]->graph(2)->data().clear();
            plots[i]->graph(3)->data().clear();
            plots[i]->graph(4)->data().clear();
            plots[i]->graph(5)->data().clear();
            plots[i]->graph(6)->data().clear();
            plots[i]->graph(7)->data().clear();
            qDebug()<<plots[i]->graph(0)->data();
            plots[i]->clearGraphs();
            //            plots[i]->xAxis->setRange(m_timerfirstList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch(), m_timerlastList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch()-m_timerfirstList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch()+1, Qt::AlignLeft);

            plots[i]->replot();
            qDebug()<<i;
            if(m_timerList.contains(ui->comboBox->itemText(i)))
            {
                m_timerList.remove(ui->comboBox->itemText(i));
            }

            if(m_timerfirstList.contains(ui->comboBox->itemText(i)))
            {
                m_timerfirstList.remove(ui->comboBox->itemText(i));
            }
            if(m_timerlastList.contains(ui->comboBox->itemText(i)))
            {
                m_timerlastList.remove(ui->comboBox->itemText(i));
            }
            if(orderbuymap.contains(ui->comboBox->itemText(i)))
            {
                orderbuymap.remove(ui->comboBox->itemText(i));
            }
            if(ordersellmap.contains(ui->comboBox->itemText(i)))
            {
                ordersellmap.remove(ui->comboBox->itemText(i));
            }
            if(maxList.contains(ui->comboBox->itemText(i)))
            {
                maxList.remove(ui->comboBox->itemText(i));
            }
            if(minList.contains(ui->comboBox->itemText(i)))
            {
                minList.remove(ui->comboBox->itemText(i));
            }





        }
    }

    isclear=false;
    if(!isdisconnect)
    {
    sentmq=new sent();
    sentmq->connect(ip,SendPort);
    SnapshotRecmq=new SnapshotReceive();

    OrderRecmq=new OrderReceive();

    OrderRecmq->connect(ip,OrderPort);
    SnapshotRecmq->connect(ip,SnapshotPort);
    SnapshotRecmq->start();
    OrderRecmq->start();
    connect(SnapshotRecmq,SIGNAL(receivemessage(QString,QDateTime,double,double,double,double,double,double)),this,SLOT(showmessage(QString,QDateTime,double,double,double,double,double,double)),Qt::QueuedConnection);

    connect(OrderRecmq,SIGNAL(receivemessage(QString,QDateTime,int)),this,SLOT(showmessage(QString,QDateTime,int)),Qt::QueuedConnection);
}

}
void MainWindow::acceptIpPort(QString ip ,int SendPort,int SnapshotPort,int OrderPort){
    //qDebug()<<"ip"<<ip<<"sendport"<<SendPort<<"snapshotport"<<SnapshotPort<<"orderport"<<OrderPort;
    //    sentmq->close();
    //    SnapshotRecmq->close();
    //OrderRecmq->close();
    sentmq=new sent();
    sentmq->connect(ip,SendPort);
    SnapshotRecmq=new SnapshotReceive();

    OrderRecmq=new OrderReceive();

    OrderRecmq->connect(ip,OrderPort);
    SnapshotRecmq->connect(ip,SnapshotPort);
    SnapshotRecmq->start();
    OrderRecmq->start();
    connect(SnapshotRecmq,SIGNAL(receivemessage(QString,QDateTime,double,double,double,double,double,double)),this,SLOT(showmessage(QString,QDateTime,double,double,double,double,double,double)),Qt::QueuedConnection);

    connect(OrderRecmq,SIGNAL(receivemessage(QString,QDateTime,int)),this,SLOT(showmessage(QString,QDateTime,int)),Qt::QueuedConnection);

    m_userSettings->setValue("ip",ip);
    m_userSettings->setValue("SendPort", SendPort);
    m_userSettings->setValue("SnapshotPort", SnapshotPort);
    m_userSettings->setValue("OrderPort", OrderPort);

    //SnapshotRecmq->resume();
    //OrderRecmq->resume();
}

void MainWindow::on_pushButton_2_clicked()
{
    zoom=false;
    for (int i=0;i<plots.count();i++)
    {
        plots[i]->xAxis->setRange(m_timerfirstList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch(), m_timerlastList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch()-m_timerfirstList.value(ui->comboBox->itemText(i)).toSecsSinceEpoch()+1, Qt::AlignLeft);
        plots[i]->replot();
        //        plots[i]->xAxis->setRange(m_timerList.value(ui->comboBox->itemText(i)).last().toSecsSinceEpoch(), m_timerList.value(ui->comboBox->itemText(i)).count(), Qt::AlignLeft);

    }
}
