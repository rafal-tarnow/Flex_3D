#include "ScadControllerServer.hpp"
#include <QDataStream>
#include <QDebug>

ScadControllerServer::ScadControllerServer(QObject *parent)
    : QObject(parent), clientSocket(nullptr) {
    QLocalServer::removeServer("scad_server_test"); //Removes any server instance that might cause a call to listen() to fail and returns true if successful; otherwise returns false. This function is meant to recover from a crash, when the previous server instance has not been cleaned up
    server = new QLocalServer(this);
    connect(server, &QLocalServer::newConnection, this, &ScadControllerServer::handleNewConnection);

    if (!server->listen("scad_server_test")) {
        qCritical() << "Unable to start the server:" << server->errorString();
    } else {
        qDebug() << "Server started...";
    }
}

ScadControllerServer::~ScadControllerServer() {
    if (server->isListening()) {
        server->close();
    }
}

void ScadControllerServer::handleNewConnection() {
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QLocalSocket::readyRead, this, &ScadControllerServer::readClientData);
    qDebug() << "Client connected...";
}

void ScadControllerServer::readClientData() {
    // Implementacja funkcji do czytania danych od klienta, jeśli potrzebna
    qDebug() << __PRETTY_FUNCTION__;
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_15);

    while (clientSocket->bytesAvailable() > 0) {
        in.startTransaction();

        uint8_t command;
        in >> command;

        if (command == CMD_UPDATE_GL) {
            if (!in.commitTransaction())
                return;
            emit updateGLView();
        }else {
            in.rollbackTransaction();
            return;
        }
    }
}

void ScadControllerServer::preview() {
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_PREVIEW);
        clientSocket->flush();
        qDebug() << "Preview command sent to client.";
    }
}

void ScadControllerServer::render() {
    //qDebug() << __PRETTY_FUNCTION__;
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_RENDER);
        clientSocket->flush();
        qDebug() << "Render command sent to client.";
    }
}

void ScadControllerServer::show()
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_SHOW);
        clientSocket->flush();
        qDebug() << "Show command sent to client.";
    }
}

void ScadControllerServer::hide()
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_HIDE);
        clientSocket->flush();
        qDebug() << "Hide command sent to client.";
    }
}

void ScadControllerServer::resizeF(float width, float height)
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_RESIZE) << uint32_t(width) << uint32_t(height);
        clientSocket->flush();
        qDebug() << "Resize command sent to client with width and height :" << uint32_t(width) << " " << uint32_t(height);
    }
}

void ScadControllerServer::openFile(const QString &filePath) {
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_OPEN_FILE) << filePath;
        clientSocket->flush();
        qDebug() << "OpenFile command sent to client with path:" << filePath;
    }
}
