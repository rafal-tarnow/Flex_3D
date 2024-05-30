#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ServerController.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    ServerController srcServerController; // create simple switch
    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica"))); // create host node without Registry
    srcNode.enableRemoting(&srcServerController);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("RemoteObjects", "Main");

    return app.exec();
}
