#include "Backend.hpp"
#include <QDebug>
#include <QQmlComponent>
#include <QQuickItem>
#include <QFile>


Backend::Backend(QQmlEngine *parent) :
    QObject(parent),
    engine(parent)
{

}

Backend::~Backend()
{

}

void Backend::testBackendCall()
{
    qDebug() << __FUNCTION__;
    qDebug() << "C++ Backend delete file !!";
}


void Backend::trimEngineComponentCache()
{
    qDebug() << __FUNCTION__;
    if(engine){
        qDebug() << "engine->trimComponentCache()";
        engine->trimComponentCache();
    }
}

void Backend::clearEngineComponentCache()
{
    qDebug() << __FUNCTION__;
    if(engine){
        qDebug() << "engine->clearComponentCache()";
        engine->clearComponentCache();
    }
}
