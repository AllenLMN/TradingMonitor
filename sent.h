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
    void run();
       void close();
    void setStrat(QString strat){
        m_strat=strat;
    }
    void setModifyType(QString modifyType){
        m_modifyType=modifyType;
    }
    void setModify(QString modify){
        m_modify=modify;
    }
    QString getStrat()
    {
        return m_strat;
    }
    QString getModifyType()
    {
        return m_modifyType;
    }
    QString getModify()
    {
        return m_modify;
    }
private:
    QString m_strat;
    QString m_modifyType;
    QString m_modify;
};

#endif // SENT_H
