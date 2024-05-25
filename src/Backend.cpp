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


    //CREATE NEW COMPONENT DIR

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

    //COPY NEW COMPONENT TEMPLATE

    QString componentFilePath = mWorkspaceLocation.toLocalFile() + "/" + componentName + "/" + componentName + ".qml";

    QString componentTemplateFilePath = ":/resources/ComponentTemplate.qml";
    QString componentTemplateTxt;
    QString errorString;

    if(!fileIO.readFile(componentTemplateFilePath, componentTemplateTxt, errorString)){
        qDebug() << "[ERROR] Can't read template File: " << errorString;
    }

    //PREPARE OpenSCAD SCRIPTS NAMES AND PATH

    QString openScadFileNameBase = convertFirstLetterToLowerCase(componentName);
    QString openScadFilePath = mWorkspaceLocation.toLocalFile() + "/" + componentName + "/" + openScadFileNameBase + ".scad";


    //FORMAT QML FILE TEXT (change in text line: 'source "%1.scad"' to 'source "componentName.scad"'

    QString componentFileText = componentTemplateTxt.arg(openScadFileNameBase);

    //SAVE QML FILE

    if(!fileIO.saveFile(componentFilePath,componentFileText, errorString)){
        qDebug() << "[ERROR] Can't save qml file: " << errorString;
    }

    //SAVE OpenSCAD FILE

    if(!fileIO.copyFile(":/resources/ComponentTemplate.scad", openScadFilePath, errorString)){
        qDebug() << "[ERROR] Failed to copy file: " << errorString;
    }
}

QString Backend::convertFirstLetterToLowerCase(const QString &input) {
    QString output = input;
    if (output.isEmpty()) {
        return output;
    }

    QChar firstChar = output[0];

    if (firstChar.isUpper()) {
        output[0] = firstChar.toLower();
    }
    return output;
}
