// Copyright (C) 2017 Ford Motor Company
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "Client.hpp"

// constructor
Client::Client(QSharedPointer<ServerControllerReplica> ptr) :
    QObject(nullptr), clientSwitchState(false), reptr(ptr)
{
    //connect signal for replica initialized with initialization slot
    initConnections();
    // We can connect to SimpleSwitchReplica signals/slots
    //directly because our Replica was generated by repc
}

//destructor
Client::~Client()
{

}


void Client::initConnections(void)
{
    // initialize connections between signals and slots

    // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
    QObject::connect(reptr.data(), &ServerControllerReplica::currStateChanged, this, &Client::recSwitchState_slot);
    // connect client's echoSwitchState(..) signal with replica's server_slot(..) to echo back received state
    QObject::connect(this, &Client::echoSwitchState, reptr.data(), &ServerControllerReplica::server_slot);
}

qint64 currentMicrosecondsSinceEpoch() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return duration.count();
}

void Client::recSwitchState_slot(bool value)
{
    //qDebug() << currentMicrosecondsSinceEpoch();
    qDebug() << QDateTime::currentMSecsSinceEpoch();
    qDebug() << "Received source state "<< value << reptr.data()->currState();
    clientSwitchState = reptr.data()->currState();
    Q_EMIT echoSwitchState(clientSwitchState); // Emit signal to echo received state back to server
}
