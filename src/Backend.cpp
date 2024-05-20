#include "Backend.hpp"
#include <QDebug>
#include <QQmlComponent>
#include <QQuickItem>
#include <QFile>
#include <QDir>


Backend::Backend(QQmlEngine *parent) :
    QObject(parent),
    engine(parent),
    mWorkspaceLocation("file:" + QString(SOURCE_DIR) +  "/develop_project/")
{

}

Backend::~Backend()
{

}

QUrl Backend::workspaceLocation()
{
    return mWorkspaceLocation;
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

void Backend::createNewComponent(const QString &componentName)
{
    qDebug() << __FUNCTION__;


    QString componentFolderPath = mWorkspaceLocation.toLocalFile() + "/" + componentName;

    QDir componentFolder(componentFolderPath);
    if (componentFolder.exists()) {
        qDebug() << "ERROR: folder already exists: " << componentFolderPath;
        return;
    }

    if (!componentFolder.mkpath(".")) {
        qDebug() << "ERROR: Failed to create folder: " << componentFolderPath;
        return;
    }

    QString componentFilePath = mWorkspaceLocation.toLocalFile() + "/" + componentName + "/" + componentName + ".qml";
    QString copyError;

    fileIO.copyFile(":/resources/ComponentTemplate.qml", componentFilePath, copyError);
}
