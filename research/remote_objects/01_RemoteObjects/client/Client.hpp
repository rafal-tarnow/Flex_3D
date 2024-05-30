#ifndef _CLIENT_H
#define _CLIENT_H

#include <QObject>
#include <QSharedPointer>

#include "rep_servercontroller_replica.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QSharedPointer<ServerControllerReplica> ptr);
    ~Client() override;
    void initConnections();// function connect signals and slots of source and client

Q_SIGNALS:
    void echoSwitchState(bool switchState);// this signal is connected with server_slot(..) on the source object and echoes back switch state received from source

public Q_SLOTS:
    void recSwitchState_slot(bool); // slot to receive source state
private:
    bool clientSwitchState; // holds received server switch state
    QSharedPointer<ServerControllerReplica> reptr;// holds reference to replica

};

#endif
