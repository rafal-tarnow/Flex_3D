#include "ScadControllerClient.hpp"
#include <QDataStream>
#include <QDebug>

ScadControllerClient::ScadControllerClient(QObject *parent)
    : QObject(parent) {
    socket = new QLocalSocket(this);

    reconnectTimer = new QTimer(this);
    reconnectTimer->setInterval(5000); // Próba ponownego połączenia co 5 sekund

    connect(socket, &QLocalSocket::readyRead, this, &ScadControllerClient::readServerData);
    connect(socket, &QLocalSocket::errorOccurred, this, &ScadControllerClient::handleSocketError);
    connect(reconnectTimer, &QTimer::timeout, this, &ScadControllerClient::attemptReconnect);

    attemptReconnect();
}

ScadControllerClient::~ScadControllerClient() {
    socket->disconnectFromServer();
}

void ScadControllerClient::updateGLView()
{
    qDebug() << __PRETTY_FUNCTION__;
    if (socket && socket->isOpen()) {
        QDataStream out(socket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_UPDATE_GL);
        socket->flush();
        qDebug() << "Upadate GL command sent to server.";
    }
}

void ScadControllerClient::attemptReconnect() {
    if (socket->state() == QLocalSocket::UnconnectedState) {
        qDebug() << "Attempting to connect to server...";
        socket->connectToServer("scad_server_test");
    }
}

void ScadControllerClient::handleSocketError(QLocalSocket::LocalSocketError socketError) {
    qDebug() << "Socket error occurred:" << socketError;
    if (socketError == QLocalSocket::ServerNotFoundError ||
        socketError == QLocalSocket::ConnectionRefusedError ||
        socketError == QLocalSocket::PeerClosedError) {
        reconnectTimer->start();
    }
}

void ScadControllerClient::readServerData() {
    qDebug() << __PRETTY_FUNCTION__;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    while (socket->bytesAvailable() > 0) {
        in.startTransaction();

        uint8_t command;
        in >> command;

        if (command == CMD_PREVIEW) {
            if (!in.commitTransaction())
                return;
            emit preview();
        } else if (command == CMD_RENDER) {
            if (!in.commitTransaction())
                return;
            emit render();
        } else if (command == CMD_OPEN_FILE) {
            QString filePath;
            in >> filePath;
            if (!in.commitTransaction())
                return;
            emit openFile(filePath);
        } else {
            in.rollbackTransaction();
            return;
        }
    }
}
