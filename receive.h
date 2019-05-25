#ifndef RECEIVE_H
#define RECEIVE_H

#include <QObject>

#include "zmq.h"
#include "nzmqt/nzmqt.hpp"
#include "market_snapshot.h"
#include <QDebug>
#include <QDateTime>
class receive : public QObject
{
    Q_OBJECT
public:
    explicit receive(QObject *parent = nullptr);

    zmq::context_t *context;
    zmq::socket_t *sock;
signals:
 void receivemessage(QString strat,QDateTime timer,double down,double stop_down,double up,double stop_up ,double mid);
public slots:
      void run();
      void close();
};

#endif // RECEIVE_H
