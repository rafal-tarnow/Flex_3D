#pragma once

#include <QObject>
#include <QString>
#include <QLocalServer>
#include <QLocalSocket>
#include <QQmlEngine>

class ScadControllerServer : public QObject {
    Q_OBJECT
    QML_ELEMENT

    enum Commands{
        CMD_PREVIEW = 0,
        CMD_RENDER,
        CMD_OPEN_FILE,
        CMD_UPDATE_GL
    };

public:
    explicit ScadControllerServer(QObject *parent = nullptr);
    ~ScadControllerServer();
    Q_INVOKABLE void preview();
    Q_INVOKABLE void render();
    Q_INVOKABLE void openFile(const QString &filePath);

signals:
    void updateGLView();

private slots:
    void handleNewConnection();
    void readClientData();

private:
    QLocalServer *server;
    QLocalSocket *clientSocket;
};
