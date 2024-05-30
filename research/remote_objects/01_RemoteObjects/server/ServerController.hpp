#pragma once

#include "rep_servercontroller_source.h"

class ServerController : public ServerControllerSimpleSource
{
    Q_OBJECT
public:
    ServerController(QObject *parent = nullptr);
    ~ServerController() override;
    void server_slot(bool clientState) override;
public Q_SLOTS:
    void timeout_slot();
private:
    QTimer *stateChangeTimer;
};
