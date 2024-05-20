#pragma once
#include <QObject>
#include <QQmlEngine>
#include <QUrl>

class FileIO: public QObject{
    Q_OBJECT
public:
    explicit FileIO(QObject *parent = nullptr);

    bool copyFile(const QString &fromFilePaht, const QString &toFilePaht, QString &errorString);

    bool saveFile(const QUrl &fileUrl, const QString &text, QString &errorString);
    bool saveFile(const QString &fileDir, const QString &fileName, const QString &text, QString &errorString);
    bool saveFile(const QString &filePath, const QString &text, QString &errorString);

    bool readFile(const QString &fileDir, const QString &fileName, QString &fileContent, QString &errorString);
    bool readFile(const QString & filePath, QString &fileContent, QString &errorString);
    bool readFile(const QUrl & fileUrl, QString &fileContent, QString &errorString);
};
