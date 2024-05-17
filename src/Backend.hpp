#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>

class Backend : public QObject{
    Q_OBJECT
public:
    explicit Backend(QQmlEngine *parent);
    ~Backend();

    Q_INVOKABLE void testBackendCall();
    Q_INVOKABLE void trimEngineComponentCache();
    Q_INVOKABLE void clearEngineComponentCache();

private:
    QQmlEngine *engine = nullptr;
};
