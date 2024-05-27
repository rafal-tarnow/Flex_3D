#include <QApplication>
#include <QQmlApplicationEngine>
#include "ClientWidget.hpp"
#include "../config.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientWidget w;
    w.resize(WIDTH, HEIGHT);
    w.show();    

    const QUrl url(QStringLiteral("qrc:/client/Main.qml"));
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &a,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);


    return a.exec();
}


