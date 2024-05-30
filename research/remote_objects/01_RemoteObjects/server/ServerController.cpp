#include "ServerController.hpp"
#include <chrono>

// constructor
ServerController::ServerController(QObject *parent) : ServerControllerSimpleSource(parent)
{
    stateChangeTimer = new QTimer(this); // Initialize timer
    QObject::connect(stateChangeTimer, &QTimer::timeout, this, &ServerController::timeout_slot); // connect timeout() signal from stateChangeTimer to timeout_slot() of simpleSwitch
    stateChangeTimer->start(1000); // Start timer and set timout to 2 seconds
    qDebug() << "Source Node Started";
}

//destructor
ServerController::~ServerController()
{
    stateChangeTimer->stop();
}

void ServerController::server_slot(bool clientState)
{
    qDebug() << "Replica state is " << clientState; // print switch state echoed back by client
}

qint64 currentMicrosecondsSinceEpoch() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return duration.count();
}

void ServerController::timeout_slot(void)
{

    // slot called on timer timeout
    if (currState()){ // check if current state is true, currState() is defined in repc generated rep_simpleswitch_source.h
        //qDebug() << currentMicrosecondsSinceEpoch();
        qDebug() << QDateTime::currentMSecsSinceEpoch();
        setCurrState(false); // set state to false
    }else{
        //qDebug() << currentMicrosecondsSinceEpoch();
        qDebug() << QDateTime::currentMSecsSinceEpoch();
        setCurrState(true); // set state to true
    }
    qDebug() << "Source State is "<<currState();

}

