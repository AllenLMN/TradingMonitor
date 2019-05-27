#ifndef SENT_H
#define SENT_H

#include <QObject>
#include "zmq.h"
#include "nzmqt/nzmqt.hpp"
#include "market_snapshot.h"
#include <QDebug>

class sent : public QObject
{
    Q_OBJECT
public:
    explicit sent(QObject *parent = nullptr);
    zmq::context_t *context;
    zmq::socket_t *socket;
signals:

public slots:
    void run(QString m_strat,QString m_modifyType,QString m_modify);
       void close();



};

#endif // SENT_H
