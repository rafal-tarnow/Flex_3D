#include "ScadControllerServer.hpp"
#include <QDataStream>
#include <QDebug>

QJSEngine * ScadControllerServer::s_engine = nullptr;
ScadControllerServer* ScadControllerServer::instance = nullptr;
QMutex ScadControllerServer::mutex;

ScadControllerServer* ScadControllerServer::getInstance(QObject *parent) {
    QMutexLocker locker(&mutex);
    if (instance == nullptr) {
        instance = new ScadControllerServer(parent);
    }
    return instance;
}

ScadControllerServer *ScadControllerServer::create(QQmlEngine *, QJSEngine *engine){
    getInstance(engine);

    //create method implementation form qt documentation
    // The instance has to exist before it is used. We cannot replace it.
    Q_ASSERT(instance);
    // The engine has to have the same thread affinity as the singleton.
    Q_ASSERT(engine->thread() == instance->thread());
    // There can only be one engine accessing the singleton.
    if (s_engine)
        Q_ASSERT(engine == s_engine);
    else
        s_engine = engine;
    // Explicitly specify C++ ownership so that the engine doesn't delete
    // the instance.
    QJSEngine::setObjectOwnership(instance,
                                  QJSEngine::CppOwnership);
    return instance;
}

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
    clientSocket->close();
    if (server->isListening()) {
        server->close();
    }
}

void ScadControllerServer::handleNewConnection() {
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QLocalSocket::readyRead, this, &ScadControllerServer::readClientData);
    updateScadState();
    qDebug() << "Client connected...";
}

void ScadControllerServer::readClientData() {
    // Implementacja funkcji do czytania danych od klienta, jeśli potrzebna
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

void ScadControllerServer::updateScadState()
{
    sendResizeCommand();
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
    resize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

void ScadControllerServer::resize(uint32_t width, uint32_t height)
{
    state.width = width;
    state.height = height;
    sendResizeCommand();
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

void ScadControllerServer::sendMouseDoubleClickEvent(QMouseEvent *event)
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_MOUSE_DBL_CLICK) << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
        clientSocket->flush();
        qDebug() << "MouseDoubleClickEvent command sent to client with data: " << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
    }
}

void ScadControllerServer::sendMouseMoveEvent(QMouseEvent *event)
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_MOUSE_MOVE) << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
        clientSocket->flush();
        qDebug() << "MouseMoveEvent command sent to client with data: " << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
    }
}

void ScadControllerServer::sendMousePressEvent(QMouseEvent *event)
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_MOUSE_PRESS) << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
        clientSocket->flush();
        qDebug() << "MousePressEvent command sent to client with data: " << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
    }
}

void ScadControllerServer::sendMouseReleaseEvent(QMouseEvent *event)
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_MOUSE_RELEASE) << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
        clientSocket->flush();
        qDebug() << "MouseReleaseEvent command sent to client with data: " << event->type() << event->position() << event->button() << event->buttons() << event->modifiers();
    }
}

void ScadControllerServer::sendWheelEvent(QWheelEvent *event)
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_WHEEL) << event->position() << event->globalPosition() << event->pixelDelta() << event->angleDelta() << event->buttons() << event->modifiers() << event->phase() << event->inverted();
        clientSocket->flush();
    }
}

void ScadControllerServer::sendResizeCommand()
{
    if (clientSocket && clientSocket->isOpen()) {
        QDataStream out(clientSocket);
        out.setVersion(QDataStream::Qt_5_15);
        out << uint8_t(CMD_RESIZE) << state.width << state.height;
        clientSocket->flush();
        qDebug() << "Resize command sent to client with width and height :" << state.width << " " << state.height;
    }
}
