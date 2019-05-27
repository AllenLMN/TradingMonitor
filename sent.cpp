#include "sent.h"
#include <QDateTime>
sent::sent(QObject *parent) : QObject(parent)
{
    context=new zmq::context_t(1);
    socket=new zmq::socket_t(*context,ZMQ_PUB);
    socket->connect("tcp://101.132.173.17:33334");
}
void sent::run(QString m_strat,QString m_modifyType,QString m_modify)
{



    socket->connect("tcp://101.132.173.17:33334");


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
    memcpy(buffer, &shot, sizeof(shot));
    socket->send(buffer,sizeof(buffer));



}
void sent::close(){
    context->close();

    socket->close();
    delete context;
    delete socket;


    this->deleteLater();
}
