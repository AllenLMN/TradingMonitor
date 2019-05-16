#include "orderreceive.h"
#include <QDebug>
#include "mainwindow.h"
//#include "SnapshotReceive.h"
OrderReceive::OrderReceive()
{
    context=new zmq::context_t(1);
    sock=new zmq::socket_t(*context,ZMQ_SUB);
    sock->setsockopt(ZMQ_SUBSCRIBE,0,0);
//    m_userSettings = new QSettings("zy1205", "TradingMonitor", this);

//    QString ip =m_userSettings->value("ip").toString();
//    int OrderPort=m_userSettings->value("OrderPort").toInt();
    m_ip=MainWindow::instance()->ip;
    m_port=MainWindow::instance()->OrderPort;
     //qDebug()<<"add"<<m_ip<<":"<<m_port;
    connect(m_ip,m_port);

//    sock->connect(std::string("tcp://"+ip+":"+QString::number(port)));
//    sock->connect("tcp://101.132.173.17:33335");
}
void OrderReceive::pause(){
    stopped=true;
//     m_mutex.lock();
}
void OrderReceive::resume(){
    stopped=false;

}
void OrderReceive::run()
{


    while(true)
    {

 QMutexLocker locker(&m_mutex);
//        m_mutex.lock();
        char buffer[1024];
        long long tv_sec;
        long long tv_usec;
//        m_mutex.lock();
//        if(!sock->connected())
//        {
//            break;
//        }
        sock->recv(buffer,sizeof(buffer));

//        MarketSnapshot *shot=reinterpret_cast<MarketSnapshot*>(buffer);

          Order* order = reinterpret_cast<Order*>(buffer);

        if(/*(tv_sec!=order->send_time.tv_sec)&&*/(order->send_time.tv_sec!=0))
        {
            tv_sec=order->send_time.tv_sec;
            tv_usec=order->send_time.tv_usec;

//qDebug()<<"tv_sec"<<tv_sec<<"tv_usec"<<tv_usec;

            emit receivemessage(order->contract,QDateTime::fromTime_t(order->shot_time.tv_sec),order->side);
        }





        //                   shot->Show(stdout);


//     m_mutex.unlock();
    }
}
void OrderReceive::connect(QString ip,int port)
{

//      sock->s=zmq::socket_t(*context,ZMQ_SUB);

    m_ip=ip;
    m_port=port;
    //qDebug()<<"add"<<ip<<":"<<port;
    QString add="tcp://"+m_ip+":"+QString::number(m_port);
    //qDebug()<<"add"<<add;
    sock->connect(add.toStdString());
}
void OrderReceive::closereceive(){
    QString add="tcp://"+m_ip+":"+QString::number(m_port);
// qDebug()<<sock->ptr;
context->close();
    sock->close();
    delete context;
//    delete sock;
//     context->close();
//sock->disconnect()
//    sock->disconnect(add.toStdString());

//    context->close();
//    sock->close();


}
