#ifndef SENT_H
#define SENT_H

#include <QObject>
#include "zmq.h"
#include "nzmqt/nzmqt.hpp"
#include "market_snapshot.h"
#include <QDebug>
#include <QSettings>
class sent : public QObject
{
    Q_OBJECT
public:
    explicit sent(QObject *parent = nullptr);
    zmq::context_t *context;
    zmq::socket_t *sock;
    QString m_ip;
    int m_port;
signals:

public slots:
    void run(QString m_strat,QString m_modifyType,QString m_modify);
       void closereceive();
 void connect(QString ip,int port);
private:
 QSettings* m_userSettings = nullptr; ///< 用户设置

};

#endif // SENT_H
