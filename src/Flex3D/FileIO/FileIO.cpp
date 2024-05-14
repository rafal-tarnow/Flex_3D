#include "FileIO.hpp"
#include <QFile>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

void FileIO::saveFile(const QString &fileDir, const QString &fileName, const QString &text)
{
    QString filePath = fileDir + "/" + fileName;
    QFile file;
    file.setFileName(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text;
        file.close();
        qDebug() << "Saved file:" << filePath;
    } else {
        qDebug() << "Can't open file to write:" << filePath;
    }
}

QString FileIO::readFile(const QString &fileDir, const QString &fileName)
{
    QString filePath = fileDir + "/" + fileName;

    QString fileContent;
    QFile file;
    file.setFileName(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileContent = in.readAll();
        file.close();
        qDebug() << "Readed file:" << filePath;
    } else {
        qDebug() << "Can't open file to read:" << filePath;
    }
    return fileContent;
}
