#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickTextDocument>
#include <QTextOption>
#include <QtWebView/QtWebView>
#include <QtWebEngineQuick>

int main(int argc, char *argv[])
{
    QtWebView::initialize();
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Flex3D");
    app.setOrganizationDomain("flex3d.com");
    app.setApplicationName("Flex3D");


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("SOURCE_DIR", QString(SOURCE_DIR));
    engine.loadFromModule("Flex3D", "Main");


    return app.exec();
}
