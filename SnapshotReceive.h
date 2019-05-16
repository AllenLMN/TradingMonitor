#ifndef RECEIVE_H
#define RECEIVE_H

#include <QObject>

#include "zmq.h"
#include "nzmqt/nzmqt.hpp"
#include "market_snapshot.h"
#include <QDebug>
#include <QDateTime>
#include <QSettings>
class SnapshotReceive : public   QThread
{
    Q_OBJECT
public:
     SnapshotReceive();
    QString m_ip;
    int m_port;
    zmq::context_t *context;
    zmq::socket_t *sock;
    void pause();
    void resume();
        bool stopped=false;
signals:
 void receivemessage(QString strat,QDateTime timer,double mean,double down,double stop_down,double up,double stop_up ,double mid);
public slots:
      void run();
      void closereceive();
       void connect(QString ip,int port);
private:
         QMutex   m_mutex;
              QSettings* m_userSettings = nullptr; ///< 用户设置
};

#endif // RECEIVE_H
