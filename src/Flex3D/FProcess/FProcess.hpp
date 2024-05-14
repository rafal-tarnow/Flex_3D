#pragma once
#include <QProcess>
#include <QQmlEngine>

class FProcess: public QProcess{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString program READ program WRITE setProgram NOTIFY programChanged FINAL)
public:
    explicit FProcess(QObject *parent = nullptr);

    Q_INVOKABLE void start();

    QString program() const;
    void setProgram(const QString & program);

signals:
    void programChanged();
};
