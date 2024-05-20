#include "FileIO.hpp"
#include <QFile>
#include <QDebug>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

bool FileIO::copyFile(const QString &fromFilePath, const QString &toFilePath, QString &errorString)
{
    QFile sourceFile(fromFilePath);
    if (!sourceFile.exists()) {
        errorString = "Source file does not exist.";
        qDebug() << "Error:" << errorString;
        return false;
    }

    if (!sourceFile.copy(toFilePath)) {
        errorString = sourceFile.errorString();
        qDebug() << "Failed to copy file from" << fromFilePath << "to" << toFilePath << "Error:" << errorString;
        return false;
    }

    qDebug() << "Successfully copied file from" << fromFilePath << "to" << toFilePath;
    return true;
}

bool FileIO::saveFile(const QUrl &fileUrl, const QString &text, QString &errorString)
{
    QString filePath = fileUrl.toLocalFile();
    return saveFile(filePath, text, errorString);
}

bool FileIO::saveFile(const QString &fileDir, const QString &fileName, const QString &text, QString &errorString)
{
    QString filePath = fileDir + "/" + fileName;
    return saveFile(filePath, text, errorString);
}

bool FileIO::saveFile(const QString &filePath, const QString &text, QString &errorString)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text;
        file.close();
        qDebug() << "Saved file:" << filePath;
        return true;
    } else {
        errorString = file.errorString();
        qDebug() << "Can't open file to write:" << filePath << "Error:" << errorString;
        return false;
    }
}

bool FileIO::readFile(const QString &fileDir, const QString &fileName, QString &fileContent, QString &errorString)
{
    QString filePath = fileDir + "/" + fileName;
    return readFile(filePath, fileContent, errorString);
}

bool FileIO::readFile(const QString &filePath, QString &fileContent, QString &errorString)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileContent = in.readAll();
        file.close();
        qDebug() << "Read file:" << filePath;
        return true;
    } else {
        errorString = file.errorString();
        qDebug() << "Can't open file to read:" << filePath << "Error:" << errorString;
        return false;
    }
}

bool FileIO::readFile(const QUrl &fileUrl, QString &fileContent, QString &errorString)
{
    QString filePath = fileUrl.toLocalFile();
    return readFile(filePath, fileContent, errorString);
}
