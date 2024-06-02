#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ScadControllerClient.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LocalSocketIPCClient", "Main");

    return app.exec();
}
