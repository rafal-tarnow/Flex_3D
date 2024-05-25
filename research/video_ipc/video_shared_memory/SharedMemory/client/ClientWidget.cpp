#include "ClientWidget.hpp"
#include <QVBoxLayout>
#include <QDebug>
#include <QImage>

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

    QImage image(reinterpret_cast<const uchar*>(sharedMemory.constData()), 1700, 900, QImage::Format_RGBA8888);
    QPixmap pixmap = QPixmap::fromImage(image.mirrored());

    imageLabel->setPixmap(pixmap);

    sharedMemory.unlock();
    sharedMemory.detach();
}
