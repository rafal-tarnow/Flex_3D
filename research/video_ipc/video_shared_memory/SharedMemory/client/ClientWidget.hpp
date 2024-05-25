#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QSharedMemory>
#include <QLabel>
#include <QTimer>

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private:
    void updateImage();

    QSharedMemory sharedMemory;
    QLabel *imageLabel;
    QTimer *timer;
};

#endif // CLIENTWIDGET_H
