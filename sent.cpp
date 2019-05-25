#include "sent.h"
#include <QDateTime>
sent::sent(QObject *parent) : QObject(parent)
{
    context=new zmq::context_t(1);
    socket=new zmq::socket_t(*context,ZMQ_PUB);
     socket->connect("tcp://101.132.173.17:33334");
}
void sent::run()
{

//    zmq::context_t context(1);
//      zmq::socket_t socket(context, ZMQ_PUB);
    QString mode="tcp";
//            QString name="101.132.173.17:22222";
//     QString address = mode + "://" + name;

    socket->connect("tcp://101.132.173.17:33334");


    MarketSnapshot shot;
////      while (std::cin >> a) {
////        timeval t=QDateTime::currentDateTime().toTime_t();
//        snprintf(shot.ticker, sizeof(shot.ticker), "%s", a);
////        char buffer[1024];
//        memcpy(buffer, &shot, sizeof(shot));
//        socket.send(buffer, sizeof(buffer));
//        gettimeofday(&t, NULL);
//        printf("sent %s at %ld %ld\n", a, t.tv_sec, t.tv_usec);
//      }
//        MarketSnapshot *shot=reinterpret_cast<MarketSnapshot*>(a);
        strcpy(shot.ticker, (const char*) getStrat().toLatin1().data());
qDebug()<<"shot->ticker"<<shot.ticker;
//shot.time.tv_usec=QDateTime::currentDateTime().toTime_t();
        if(getModifyType()=="down")
        {
            shot.bids[0]=getModify().toDouble();
        }else if(getModifyType()=="stop_down")
        {
            shot.bids[1]=getModify().toDouble();
        }else if(getModifyType()=="up")
        {
            shot.asks[0]=getModify().toDouble();
        }else if(getModifyType()=="stop_up")
        {
            shot.asks[1]=getModify().toDouble();
        }
        char buffer[1024];
        memcpy(buffer, &shot, sizeof(shot));
socket->send(buffer,sizeof(buffer));

//quit();
//terminate();
//wait();
//        if(tv_usec!=shot->time.tv_usec)
//        {
//            tv_sec=shot->time.tv_sec;
//            tv_usec=shot->time.tv_usec;
////             qDebug()<<"shot->time"<<shot->time.tv_usec<<QDateTime::fromTime_t(shot->time.tv_usec);
//            ActionController::instance()->show(shot->ticker,QDateTime::fromTime_t(shot->time.tv_sec),shot->bids[0],shot->bids[1],shot->asks[0],shot->asks[1],shot->last_trade);

//        }


//                   shot->Show(stdout);

}
void sent::close(){
    context->close();
    socket->close();
    delete context;
    delete socket;
    this->deleteLater();
}
