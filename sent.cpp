#include "sent.h"
#include <QDateTime>
#include "mainwindow.h"
sent::sent(QObject *parent) : QObject(parent)
{
    context=new zmq::context_t(1);
    sock=new zmq::socket_t(*context,ZMQ_PUB);
//sock->setsockopt(ZMQ_SUBSCRIBE,0,0);
//    m_userSettings = new QSettings("zy1205", "TradingMonitor", this);

//    QString ip =m_userSettings->value("ip").toString();
//    int SendPort=m_userSettings->value("SendPort").toInt();


    m_ip=MainWindow::instance()->ip;
    m_port=MainWindow::instance()->SendPort;
     qDebug()<<"addsent"<<m_ip<<":"<<m_port;
    connect(m_ip,m_port);
}
void sent::run(QString m_strat,QString m_modifyType,QString m_modify)
{


//    if(!sock->connected())
//    {
//        break;
//    }
//    sock->connect("tcp://101.132.173.17:33334");


    MarketSnapshot shot;

    strcpy(shot.ticker, (const char*) m_strat.toLatin1().data());
    qDebug()<<"shot->ticker"<<shot.ticker;
    //shot.time.tv_usec=QDateTime::currentDateTime().toTime_t();
    if(m_modifyType=="down")
    {
        shot.bids[0]=m_modify.toDouble();
    }else if(m_modifyType=="stop_down")
    {
        shot.bids[1]=m_modify.toDouble();
    }else if(m_modifyType=="up")
    {
        shot.asks[0]=m_modify.toDouble();
    }else if(m_modifyType=="stop_up")
    {
        shot.asks[1]=m_modify.toDouble();
    }else if(m_modifyType=="mean")
    {
        shot.open_interest=m_modify.toDouble();
    }
    char buffer[1024];
    qDebug()<<buffer;
    memcpy(buffer, &shot, sizeof(shot));
    sock->send(buffer,sizeof(buffer));



}
//void sent::close(){
//    context->close();

//    sock->close();
//    delete context;
//    delete sock;


//    this->deleteLater();
//}
void sent::connect(QString ip,int port)
{
//      sock=zmq::socket_t(*context,ZMQ_SUB);
//    sock=new zmq::socket_t(*context,ZMQ_SUB);
//    sock->setsockopt(ZMQ_SUBSCRIBE,0,0);
    m_ip=ip;
    m_port=port;
qDebug()<<"add"<<ip<<":"<<port;
    QString add="tcp://"+m_ip+":"+QString::number(m_port);
        qDebug()<<"add"<<add;
    sock->connect(add.toStdString());

}
void sent::closereceive(){
    QString add="tcp://"+m_ip+":"+QString::number(m_port);

//    qDebug()<<sock->ptr;
context->close();
    sock->close();
    delete context;
//    delete sock;
//     context->close();
//    sock->disconnect(add.toStdString());

//sock->disconnect("tcp://"+m_ip+":"+QString::number(m_port));
//    context->close();
//    sock->close();


}
