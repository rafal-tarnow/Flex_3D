#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include "FileIO.hpp"

class Backend : public QObject{
    Q_OBJECT

    Q_PROPERTY(QUrl currentEditorFileUrl READ currentEditorFileUrl WRITE setCurrentEditorFileUrl NOTIFY currentEditorFileUrlChanged FINAL)
    Q_PROPERTY(QString currentEditorFileText READ currentEditorFileText WRITE setCurrentEditorFileText NOTIFY currentEditorFileTextChanged FINAL)
public:
    explicit Backend(QQmlEngine *parent);
    ~Backend();

    QUrl currentEditorFileUrl();
    void setCurrentEditorFileUrl(QUrl editorFileUrl);

    QString currentEditorFileText();
    void setCurrentEditorFileText(QString text);

    Q_INVOKABLE void testBackendCall();
    Q_INVOKABLE void saveCurrentEditorFile();
    Q_INVOKABLE void trimEngineComponentCache();
    Q_INVOKABLE void clearEngineComponentCache();

signals:
    void currentEditorFileUrlChanged();
    void currentEditorFileTextChanged();

private:
    QQmlEngine *engine = nullptr;
    QUrl mCurrentEditorFileUrl;
    QString mCurrentEditorFileTxt;
    FileIO fileIO;
};
