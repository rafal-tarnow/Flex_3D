#pragma once
#include <QObject>
#include <QQmlEngine>

class FileIO: public QObject{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit FileIO(QObject *parent = nullptr);
    Q_INVOKABLE void saveFile(const QString & fileDir, const QString & fileName, const QString & text);
    Q_INVOKABLE QString readFile(const QString & fileDir, const QString & fileName);
};
