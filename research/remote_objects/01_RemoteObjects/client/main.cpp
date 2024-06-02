#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Client.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QSharedPointer<ServerControllerReplica> ptr;
    QRemoteObjectNode repNode; // create remote object node
    repNode.connectToNode(QUrl(QStringLiteral("local:openScadControllerReplica"))); // connect with remote host node
    ptr.reset(repNode.acquire<ServerControllerReplica>()); // acquire replica of source from host node
    Client rswitch(ptr); // create cl0 pass reference of replica to it

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("RemoteObjects", "Main");

    qDebug() << "App runing";

    return app.exec();
}

