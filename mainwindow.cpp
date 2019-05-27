#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zmq.h"
#include <QCloseEvent>
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
    connect(recmq,SIGNAL(receivemessage(QString,QDateTime,double,double,double,double,double,double)),this,SLOT(showmessage(QString,QDateTime,double,double,double,double,double,double)),Qt::QueuedConnection);
    recmq->moveToThread(recthread);
    recthread->start();
    sentmq=new sent();

    //    sentthread=new  QThread();
    //    connect(sentthread, SIGNAL(started()),sentmq, SLOT(run()));
    //        connect(sentthread, SIGNAL(finished()), sentmq, SLOT(close()));
    //    sentmq->moveToThread(sentthread);



}


MainWindow::~MainWindow()
{


    this->deleteLater();

    delete ui;
}
void MainWindow::showmessage(QString strat,QDateTime timer,double mean,double down,double stop_down,double up,double stop_up ,double mid){

    if(ui->comboBox->findText(strat)==-1)
    {
        ui->comboBox->addItem(strat);
        QCustomPlot *plot=new QCustomPlot();
        plot->addGraph();
        plot->addGraph();
        plot->addGraph();
        plot->addGraph();
        plot->addGraph();
        plot->addGraph();
        plot->hide();
        myTracer *mytracer0;
        myTracer *mytracer1;
        myTracer *mytracer2;
        myTracer *mytracer3;
        myTracer *mytracer4;
        myTracer *mytracer5;
        mytracer0=new myTracer(plot,myTracer::DataTracer);
        mytracer1=new myTracer(plot,myTracer::DataTracer);
        mytracer2=new myTracer(plot,myTracer::DataTracer);
        mytracer3=new myTracer(plot,myTracer::DataTracer);
        mytracer4=new myTracer(plot,myTracer::DataTracer);
        mytracer5=new myTracer(plot,myTracer::DataTracer);
        mytracerList0.append(mytracer0);
        mytracerList1.append(mytracer1);
        mytracerList2.append(mytracer2);
        mytracerList3.append(mytracer3);
        mytracerList4.append(mytracer4);
        mytracerList5.append(mytracer5);
//        mytracer0->updatePosition();
//        AxisTag *mTag0;
//        AxisTag *mTag3;
//        AxisTag *mTag1;
//        AxisTag *mTag2;
//        AxisTag *mTag4;
//        AxisTag *mTag5;
//        mTag0 = new AxisTag(plot->graph(0)->valueAxis());
//        mTag0->setPen(plot->graph(0)->pen());
//        mTag1 = new AxisTag(plot->graph(1)->valueAxis());
//        mTag1->setPen(plot->graph(1)->pen());
//        mTag2 = new AxisTag(plot->graph(2)->valueAxis());
//        mTag2->setPen(plot->graph(2)->pen());
//        mTag3 = new AxisTag(plot->graph(3)->valueAxis());
//        mTag3->setPen(plot->graph(3)->pen());
//        mTag4 = new AxisTag(plot->graph(4)->valueAxis());
//        mTag4->setPen(plot->graph(4)->pen());
//        mTag5 = new AxisTag(plot->graph(5)->valueAxis());
//        mTag5->setPen(plot->graph(5)->pen());
        plot->legend->setVisible(true);
//        mtagList0.append(mTag0);
//        mtagList1.append(mTag1);
//        mtagList2.append(mTag2);
//        mtagList3.append(mTag3);
//        mtagList4.append(mTag4);
//        mtagList5.append(mTag5);
        plot->setParent(ui->widget);
        plots.append(plot);
        plot->setGeometry(0,0,ui->widget->width(),ui->widget->height());
//        plot->axisRect()->addAxis(QCPAxis::atRight);
//        plot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(100); // add some padding to have space for tags
//        plot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(100); // add some padding to have space for tags

        connect(plot,SIGNAL(mouseWheel(QWheelEvent*)),this,SLOT(mouseWheel(QWheelEvent*)));
        connect(plot,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(mouseDoubleClick(QMouseEvent*)));
        connect(plot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(mouseMove(QMouseEvent*)));

    }




    QVector<QDateTime> timerlist;

double max=0;double min=0;
    if(m_timerList.isEmpty()||m_timerList.value(strat).isEmpty()||(timer!=m_timerList.value(strat).last()))
    {

        if(m_timerList.keys().contains(strat))
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
                             maxList.remove(strat);
                              maxList.insert(strat,max);

                              min=minList.value(strat);
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
            timerlist=m_timerList.value(strat);
            timerlist.append(timer);
            m_timerList.remove(strat);
            m_timerList.insert(strat,timerlist);


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
            timerlist.append(timer);
            m_timerList.insert(strat,timerlist);


        }
//        double graph0Value = plots[ui->comboBox->findText(strat)]->graph(0)->dataMainValue(plots[ui->comboBox->findText(strat)]->graph(0)->dataCount()-1);
//        mtagList0[ui->comboBox->findText(strat)]->updatePosition(graph0Value);
//        mtagList0[ui->comboBox->findText(strat)]->setText(QString::number(graph0Value, 'f', 2));

//        double graph1Value = plots[ui->comboBox->findText(strat)]->graph(1)->dataMainValue(plots[ui->comboBox->findText(strat)]->graph(1)->dataCount()-1);
//        mtagList1[ui->comboBox->findText(strat)]->updatePosition(graph1Value);
//        mtagList1[ui->comboBox->findText(strat)]->setText(QString::number(graph1Value, 'f', 2));

//        double graph2Value = plots[ui->comboBox->findText(strat)]->graph(2)->dataMainValue(plots[ui->comboBox->findText(strat)]->graph(2)->dataCount()-1);
//        mtagList2[ui->comboBox->findText(strat)]->updatePosition(graph2Value);
//        mtagList2[ui->comboBox->findText(strat)]->setText(QString::number(graph2Value, 'f', 2));


//        double graph3Value = plots[ui->comboBox->findText(strat)]->graph(3)->dataMainValue(plots[ui->comboBox->findText(strat)]->graph(3)->dataCount()-1);
//        mtagList3[ui->comboBox->findText(strat)]->updatePosition(graph3Value);
//        mtagList3[ui->comboBox->findText(strat)]->setText(QString::number(graph3Value, 'f', 2));


//        double graph4Value = plots[ui->comboBox->findText(strat)]->graph(4)->dataMainValue(plots[ui->comboBox->findText(strat)]->graph(4)->dataCount()-1);
//        mtagList4[ui->comboBox->findText(strat)]->updatePosition(graph4Value);
//        mtagList4[ui->comboBox->findText(strat)]->setText(QString::number(graph4Value, 'f', 2));


//        double graph5Value = plots[ui->comboBox->findText(strat)]->graph(5)->dataMainValue(plots[ui->comboBox->findText(strat)]->graph(5)->dataCount()-1);
//        mtagList5[ui->comboBox->findText(strat)]->updatePosition(graph5Value);
//        mtagList5[ui->comboBox->findText(strat)]->setText(QString::number(graph5Value, 'f', 2));

        plots[ui->comboBox->currentIndex()]->show();
        if(strat==ui->comboBox->currentText())
        {
            qDebug()<<m_timerList[ui->comboBox->currentText()].last();
        }
        plots[ui->comboBox->findText(strat)]->xAxis->setTicker(dateTicker);

        plots[ui->comboBox->findText(strat)]->xAxis->setLabel("time");
        plots[ui->comboBox->findText(strat)]->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                                                              QCP::iSelectLegend | QCP::iSelectPlottables);


        plots[ui->comboBox->findText(strat)]->graph(0)->setPen(QPen(Qt::blue));
        //设置右上角图形标注名称
        plots[ui->comboBox->findText(strat)]->graph(0)->setName("down");

        plots[ui->comboBox->findText(strat)]->graph(0)->addData(timer.toSecsSinceEpoch(),down);

        plots[ui->comboBox->findText(strat)]->graph(1)->setPen(QPen(Qt::yellow));
        //设置右上角图形标注名称
        plots[ui->comboBox->findText(strat)]->graph(1)->setName("stop_down");

        plots[ui->comboBox->findText(strat)]->graph(1)->addData(timer.toSecsSinceEpoch(),stop_down);


        plots[ui->comboBox->findText(strat)]->graph(2)->setPen(QPen(Qt::gray));
        //设置右上角图形标注名称
        plots[ui->comboBox->findText(strat)]->graph(2)->setName("up");

        plots[ui->comboBox->findText(strat)]->graph(2)->addData(timer.toSecsSinceEpoch(),up);


        plots[ui->comboBox->findText(strat)]->graph(3)->setPen(QPen(Qt::red));
        //设置右上角图形标注名称
        plots[ui->comboBox->findText(strat)]->graph(3)->setName("stop_up");

        plots[ui->comboBox->findText(strat)]->graph(3)->addData(timer.toSecsSinceEpoch(),stop_up);


        plots[ui->comboBox->findText(strat)]->graph(4)->setPen(QPen(Qt::green));
        //设置右上角图形标注名称
        plots[ui->comboBox->findText(strat)]->graph(4)->setName("mid");

        plots[ui->comboBox->findText(strat)]->graph(4)->addData(timer.toSecsSinceEpoch(),mid);

        plots[ui->comboBox->findText(strat)]->graph(5)->setPen(QPen(Qt::cyan));
        //设置右上角图形标注名称
        plots[ui->comboBox->findText(strat)]->graph(5)->setName("mean");

        plots[ui->comboBox->findText(strat)]->graph(5)->addData(timer.toSecsSinceEpoch(),mean);
        if(zoom)
        {
//            plots[ui->comboBox->findText(strat)]->graph(0)->rescaleValueAxis(false);
//            plots[ui->comboBox->findText(strat)]->graph(1)->rescaleValueAxis(false);
//            plots[ui->comboBox->findText(strat)]->graph(2)->rescaleValueAxis(false);
//            plots[ui->comboBox->findText(strat)]->graph(3)->rescaleValueAxis(false);
//            plots[ui->comboBox->findText(strat)]->graph(4)->rescaleValueAxis(false);
//            plots[ui->comboBox->findText(strat)]->graph(5)->rescaleValueAxis(false);
            plots[ui->comboBox->findText(strat)]->replot();
        }else
        {
//            plots[ui->comboBox->findText(strat)]->graph(0)->rescaleValueAxis(true);
//            plots[ui->comboBox->findText(strat)]->graph(1)->rescaleValueAxis(true);
//            plots[ui->comboBox->findText(strat)]->graph(2)->rescaleValueAxis(true);
//            plots[ui->comboBox->findText(strat)]->graph(3)->rescaleValueAxis(true);
//            plots[ui->comboBox->findText(strat)]->graph(4)->rescaleValueAxis(true);
//            plots[ui->comboBox->findText(strat)]->graph(5)->rescaleValueAxis(true);
            if((max-min)<10){
                plots[ui->comboBox->findText(strat)]->yAxis->setRange(min-1,max+1);
            }else
            {
                plots[ui->comboBox->findText(strat)]->yAxis->setRange(min-10,max+10);
            }

            plots[ui->comboBox->findText(strat)]->xAxis->setRange(timerlist.last().toSecsSinceEpoch(), 1000, Qt::AlignRight);
            plots[ui->comboBox->findText(strat)]->replot();
        }

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
    qDebug()<<strat<<modifyType<<modify;

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
//        plots[ui->comboBox->currentIndex()]->graph(0)
//        plots[ui->comboBox->currentIndex()]->graph(1)->rescaleValueAxis(true);
//        plots[ui->comboBox->currentIndex()]->graph(2)->rescaleValueAxis(true);
//        plots[ui->comboBox->currentIndex()]->graph(3)->rescaleValueAxis(true);
//        plots[ui->comboBox->currentIndex()]->graph(4)->rescaleValueAxis(true);
//        plots[ui->comboBox->currentIndex()]->graph(5)->rescaleValueAxis(true);
        plots[ui->comboBox->currentIndex()]->axisRect()->setRangeZoomFactor(2,1);

    }
}
 void MainWindow::mouseMove(QMouseEvent* e)
 {
double pos = plots[ui->comboBox->currentIndex()]->xAxis->pixelToCoord(e->pos().x());

if(ui->comboBox->count()>1)
     {
   double x=pos;
   QString xlabel=QDateTime::fromSecsSinceEpoch(x).toString("hh:mm:ss");
     int index=m_timerList.value(ui->comboBox->currentText()).indexOf(QDateTime::fromSecsSinceEpoch(x));
   qDebug()<<QDateTime::fromSecsSinceEpoch(x);
if(index>=0)
{
    double graph0Value = plots[ui->comboBox->currentIndex()]->graph(0)->dataMainValue(index);
    double graph1Value = plots[ui->comboBox->currentIndex()]->graph(1)->dataMainValue(index);
    double graph2Value = plots[ui->comboBox->currentIndex()]->graph(2)->dataMainValue(index);
    double graph3Value = plots[ui->comboBox->currentIndex()]->graph(3)->dataMainValue(index);
    double graph4Value = plots[ui->comboBox->currentIndex()]->graph(4)->dataMainValue(index);
    double graph5Value = plots[ui->comboBox->currentIndex()]->graph(5)->dataMainValue(index);

    mytracerList0[ui->comboBox->currentIndex()]->updatePosition(x,graph0Value);
     mytracerList1[ui->comboBox->currentIndex()]->updatePosition(x,graph1Value);
      mytracerList2[ui->comboBox->currentIndex()]->updatePosition(x,graph2Value);
       mytracerList3[ui->comboBox->currentIndex()]->updatePosition(x,graph3Value);
        mytracerList4[ui->comboBox->currentIndex()]->updatePosition(x,graph4Value);
         mytracerList5[ui->comboBox->currentIndex()]->updatePosition(x,graph5Value);
 mytracerList0[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph0Value)+")");
 mytracerList1[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph1Value)+")");
 mytracerList2[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph2Value)+")");
 mytracerList3[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph3Value)+")");
 mytracerList4[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph4Value)+")");
 mytracerList5[ui->comboBox->currentIndex()]->setText("("+xlabel+","+QString::number(graph5Value)+")");

}


     }


 }
void MainWindow::mouseDoubleClick(QMouseEvent*)

{
    zoom=false;
    for (int i=0;i<plots.count();i++)
    {
        plots[i]->xAxis->setRange(m_timerList.value(ui->comboBox->itemText(i)).last().toSecsSinceEpoch(), 1000, Qt::AlignRight);

    }

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
            break;
        case 1:
        default:
            ui->checkBox->setChecked(false);
            break;
        }
    }

}
