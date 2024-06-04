#pragma once

#include <QObject>
#include <QString>
#include <QLocalServer>
#include <QLocalSocket>
#include <QQmlEngine>
#include <QMouseEvent>
#include <QMutex>
#include <QWheelEvent>

class ScadControllerServer : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

    enum Commands{
        CMD_PREVIEW = 0,
        CMD_RENDER,
        CMD_OPEN_FILE,
        CMD_UPDATE_GL,
        CMD_HIDE,
        CMD_SHOW,
        CMD_RESIZE,
        CMD_MOUSE_DBL_CLICK,
        CMD_MOUSE_MOVE,
        CMD_MOUSE_PRESS,
        CMD_MOUSE_RELEASE,
        CMD_WHEEL
    };

    struct State {
        uint32_t width;
        uint32_t height;
    };

public:
    static ScadControllerServer* getInstance(QObject *parent = nullptr);
    static ScadControllerServer *create(QQmlEngine *qmlEngine, QJSEngine *);
    ~ScadControllerServer();
    Q_INVOKABLE void preview();
    Q_INVOKABLE void render();
    Q_INVOKABLE void show();
    Q_INVOKABLE void hide();
    Q_INVOKABLE void resizeF(float width, float height);
    Q_INVOKABLE void resize(uint32_t width, uint32_t height);
    Q_INVOKABLE void openFile(const QString &filePath);
    Q_INVOKABLE void sendMouseDoubleClickEvent(QMouseEvent *event);
    Q_INVOKABLE void sendMouseMoveEvent(QMouseEvent *event);
    Q_INVOKABLE void sendMousePressEvent(QMouseEvent *event);
    Q_INVOKABLE void sendMouseReleaseEvent(QMouseEvent *event);
    Q_INVOKABLE void sendWheelEvent(QWheelEvent *event);

signals:
    void updateGLView();

private slots:
    void handleNewConnection();
    void readClientData();

private:
    ScadControllerServer(QObject *parent = nullptr);
    ScadControllerServer(const ScadControllerServer&) = delete;
    ScadControllerServer& operator=(const ScadControllerServer&) = delete;

    static QJSEngine *s_engine;
    static ScadControllerServer* instance;
    static QMutex mutex;

    void updateScadState();
    void sendResizeCommand();
    State state;
    QLocalServer *server;
    QLocalSocket *clientSocket;
};
