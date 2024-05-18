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

QUrl Backend::currentEditorFileUrl()
{
    return mCurrentEditorFileUrl;
}

QString Backend::currentEditorFileText()
{
    return mCurrentEditorFileTxt;
}

void Backend::setCurrentEditorFileText(QString text)
{
    if(text != mCurrentEditorFileTxt){
        mCurrentEditorFileTxt = text;
        emit currentEditorFileTextChanged();
    }
}

void Backend::setCurrentEditorFileUrl(QUrl editorFileUrl)
{
    qDebug() << __FUNCTION__ << editorFileUrl;
    if(editorFileUrl != mCurrentEditorFileUrl){
        QString fileContent;
        QString fileError;
        if(!fileIO.readFile(editorFileUrl, fileContent, fileError)){
            qDebug() << "Can't read file: " << editorFileUrl << " " << fileError;
            return;
        }
        setCurrentEditorFileText(fileContent);
        mCurrentEditorFileUrl = editorFileUrl;
        emit currentEditorFileUrlChanged();
    }
}

void Backend::testBackendCall()
{
    qDebug() << __FUNCTION__;
    qDebug() << "C++ Backend delete file !!";
}

void Backend::saveCurrentEditorFile()
{
    QString errorFile;
    if(!fileIO.saveFile(mCurrentEditorFileUrl, mCurrentEditorFileTxt, errorFile)){
        qDebug() << "Can't save current editor file: " << errorFile;
    }
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
