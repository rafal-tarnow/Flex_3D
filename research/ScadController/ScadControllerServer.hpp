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
        CMD_UPDATE_GL,
        CMD_HIDE,
        CMD_SHOW,
        CMD_RESIZE
    };

    struct State {
        uint32_t width;
        uint32_t height;
    };

public:
    explicit ScadControllerServer(QObject *parent = nullptr);
    ~ScadControllerServer();
    Q_INVOKABLE void preview();
    Q_INVOKABLE void render();
    Q_INVOKABLE void show();
    Q_INVOKABLE void hide();
    Q_INVOKABLE void resizeF(float width, float height);
    Q_INVOKABLE void resize(uint32_t width, uint32_t height);
    Q_INVOKABLE void openFile(const QString &filePath);

signals:
    void updateGLView();

private slots:
    void handleNewConnection();
    void readClientData();

private:
    void updateScadState();
    void sendResizeCommand();
    State state;
    QLocalServer *server;
    QLocalSocket *clientSocket;
};
