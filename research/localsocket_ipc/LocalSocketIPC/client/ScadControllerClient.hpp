#pragma once

#include <QObject>
#include <QString>
#include <QLocalSocket>
#include <QTimer>
#include <QQmlEngine>

class ScadControllerClient : public QObject {
    Q_OBJECT
    QML_ELEMENT

    enum Commands{
        CMD_PREVIEW = 0,
        CMD_RENDER,
        CMD_OPEN_FILE,
        CMD_UPDATE_GL
    };

public:
    explicit ScadControllerClient(QObject *parent = nullptr);
    ~ScadControllerClient(); 
    Q_INVOKABLE void updateGLView();

signals:
    void preview();
    void render();
    void openFile(const QString &filePath);

private slots:
    void readServerData();
    void handleSocketError(QLocalSocket::LocalSocketError socketError);
    void attemptReconnect();

private:
    QLocalSocket *socket;
    QTimer *reconnectTimer;
};
