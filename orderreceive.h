
#ifndef ORDERRECEIVE_H
#define ORDERRECEIVE_H

#include <QObject>

#include "zmq.h"
#include "nzmqt/nzmqt.hpp"
#include "order.h"
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QSettings>
class OrderReceive : public QThread
{
    Q_OBJECT
public:
     OrderReceive();
    zmq::context_t *context;
    zmq::socket_t *sock;
    QString m_ip;
    int m_port;
    void pause();
    void resume();
    bool stopped=false;
signals:
 void receivemessage(QString contract,QDateTime timer,int side);
public slots:
      void run();
      void closereceive();
      void connect(QString ip,int port);
private:
     QMutex   m_mutex;
       QSettings* m_userSettings = nullptr; ///< 用户设置
};

#endif // ORDERRECEIVE_H
