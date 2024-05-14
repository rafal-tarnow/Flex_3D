#pragma once
#include <QObject>
#include <QQmlEngine>

class EngineQml: public QObject{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EngineQml(QQmlEngine *parent);
    Q_INVOKABLE void trimComponentCache();
    Q_INVOKABLE void clearComponentCache();
private:
    QQmlEngine *engine = nullptr;
};
