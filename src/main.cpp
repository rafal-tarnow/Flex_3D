#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickTextDocument>
#include <QTextOption>
#include <QtWebView/QtWebView>
#include <QtWebEngineQuick>
#include <QQuickStyle>
#include <QQmlContext>
#include "EngineQml.hpp"

int main(int argc, char *argv[])
{
    QtWebView::initialize();
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Flex3D");
    app.setOrganizationDomain("flex3d.com");
    app.setApplicationName("Flex3D");

    QQuickStyle::setStyle(QLatin1String("Imagine"));

    QQmlApplicationEngine engine;
    EngineQml engineController(&engine);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    qmlRegisterType<EngineQml>("Flex3D", 1, 0, "EngineQml");
    engine.rootContext()->setContextProperty("qmlEngine", &engineController);
    engine.rootContext()->setContextProperty("SOURCE_DIR", QString(SOURCE_DIR));
    engine.loadFromModule("Flex3D", "Main");

    return app.exec();
}
