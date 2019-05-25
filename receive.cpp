#include "receive.h"

receive::receive(QObject *parent) : QObject(parent)
{
    context=new zmq::context_t(1);
    sock=new zmq::socket_t(*context,ZMQ_SUB);
}
void receive::run()
{


    //    sock = new  zmq::socket_t(con,ZMQ_SUB);
    //    sock = new QZmq::Socket( QZmq::Socket::Sub);
    QString mode="tcp";
            QString name="101.132.173.17:33333";
     QString address = mode + "://" + name;
    //     QString address ="tcp://localhost:5555";
    sock->setsockopt(ZMQ_SUBSCRIBE,0,0);
    sock->connect("tcp://101.132.173.17:33333");
    char a[1024];
    long tv_sec;
    long tv_usec;
    while(true)
    {
        sock->recv(a,sizeof(a));

        MarketSnapshot *shot=reinterpret_cast<MarketSnapshot*>(a);


        if(tv_usec!=shot->time.tv_usec)
        {
            tv_sec=shot->time.tv_sec;
            tv_usec=shot->time.tv_usec;
//             qDebug()<<"shot->time"<<shot->time.tv_usec<<QDateTime::fromTime_t(shot->time.tv_usec);
//            ActionController::instance()->show(shot->ticker,QDateTime::fromTime_t(shot->time.tv_usec),shot->bids[0],shot->bids[1],shot->asks[0],shot->asks[1],shot->last_trade);
emit receivemessage(shot->ticker,QDateTime::fromTime_t(shot->time.tv_usec),shot->bids[0],shot->bids[1],shot->asks[0],shot->asks[1],shot->last_trade);
        }


//                   shot->Show(stdout);
    }
}
void receive::close(){
    context->close();
    sock->close();
    delete context;
    delete sock;
    this->deleteLater();
}
