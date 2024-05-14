#include "EngineQml.hpp"
#include <QFile>

EngineQml::EngineQml(QQmlEngine *parent) :
    QObject(parent)
{
    engine = parent;
}

void EngineQml::trimComponentCache()
{
    qDebug() << __FUNCTION__;
    if(engine){
        qDebug() << "engine->trimComponentCache()";
        engine->trimComponentCache();
    }
}

void EngineQml::clearComponentCache()
{
    qDebug() << __FUNCTION__;
    if(engine){
        qDebug() << "engine->clearComponentCache()";
        engine->clearComponentCache();
    }
}
