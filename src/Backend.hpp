#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include "FileIO.hpp"

class Backend : public QObject{
    Q_OBJECT

    Q_PROPERTY(QUrl workspaceLocation READ workspaceLocation CONSTANT)
    Q_PROPERTY(QUrl currentEditorFileUrl READ currentEditorFileUrl WRITE setCurrentEditorFileUrl NOTIFY currentEditorFileUrlChanged FINAL)
    Q_PROPERTY(QString currentEditorFileText READ currentEditorFileText WRITE setCurrentEditorFileText NOTIFY currentEditorFileTextChanged FINAL)
public:
    explicit Backend(QQmlEngine *parent);
    ~Backend();

    QUrl workspaceLocation();

    QUrl currentEditorFileUrl();
    void setCurrentEditorFileUrl(QUrl editorFileUrl);

    QString currentEditorFileText();
    void setCurrentEditorFileText(QString text);

    Q_INVOKABLE void testBackendCall();
    Q_INVOKABLE void saveCurrentEditorFile();
    Q_INVOKABLE void trimEngineComponentCache();
    Q_INVOKABLE void clearEngineComponentCache();
    Q_INVOKABLE void createNewComponent(const QString &componentName);

signals:
    void currentEditorFileUrlChanged();
    void currentEditorFileTextChanged();

private:
    QString convertFirstLetterToLowerCase(const QString &input);

private:
    QQmlEngine *engine = nullptr;
    QUrl mCurrentEditorFileUrl;
    QUrl mWorkspaceLocation;
    QString mCurrentEditorFileTxt;
    FileIO fileIO;
};
