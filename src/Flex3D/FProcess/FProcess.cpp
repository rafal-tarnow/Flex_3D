#include "FProcess.hpp"
#include <QFile>

FProcess::FProcess(QObject *parent) :
    QProcess(parent)
{

}

void FProcess::start()
{
    QProcess::start();
}

QString FProcess::program() const
{
    return QProcess::program();
}

void FProcess::setProgram(const QString &newProgram)
{
    if(newProgram != program()){
        QProcess::setProgram(newProgram);
        emit programChanged();
    }
}
