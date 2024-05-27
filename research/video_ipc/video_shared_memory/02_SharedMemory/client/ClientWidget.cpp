#include "ClientWidget.hpp"
#include <QVBoxLayout>
#include <QDebug>
#include <QImage>
#include "../config.hpp"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent), sharedMemory("TriangleSharedMemory")
{
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClientWidget::updateImage);
    timer->start(16); // Około 60 FPS
}

ClientWidget::~ClientWidget()
{
    delete timer;
}

void ClientWidget::updateImage()
{
    if (!sharedMemory.attach()) {
        qDebug() << "Unable to attach to shared memory segment.";
        return;
    }

    if (!sharedMemory.lock()) {
        qDebug() << "Unable to lock shared memory.";
        sharedMemory.detach();
        return;
    }


    QImage image(reinterpret_cast<const uchar*>(sharedMemory.constData()), WIDTH, HEIGHT, QImage::Format_ARGB32_Premultiplied);
    qDebug() << "Client image.sizeInBytes() = " << image.sizeInBytes();
    qDebug() << "Client sharedMemory.size() = " << sharedMemory.size();
    QPixmap pixmap = QPixmap::fromImage(image);
    qDebug() << "Pixmap";

    imageLabel->setPixmap(pixmap);

    sharedMemory.unlock();
    sharedMemory.detach();
}
