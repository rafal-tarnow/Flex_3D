#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickTextDocument>
#include <QTextOption>
#include <QtWebView/QtWebView>
#include <QtWebEngineQuick>
#include <QQuickStyle>
#include <QQmlContext>
#include "Backend.hpp"

int main(int argc, char *argv[])
{

    qDebug() << "START SOURCE_DIR = " << QString(SOURCE_DIR);

    QtWebView::initialize();
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Flex3D");
    app.setOrganizationDomain("flex3d.com");
    app.setApplicationName("Flex3D");

    QQuickStyle::setStyle(QLatin1String("Imagine"));

    QQmlApplicationEngine engine;
    Backend backend(&engine);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("SOURCE_DIR", QString(SOURCE_DIR));
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.loadFromModule("Flex3D", "Main");

    return app.exec();
}
