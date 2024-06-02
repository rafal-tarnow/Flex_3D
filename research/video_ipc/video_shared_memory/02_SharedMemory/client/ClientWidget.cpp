#include "ClientWidget.hpp"
#include <QVBoxLayout>
#include <QDebug>
#include <QImage>
#include <cstring> // for memcpy

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent), sharedMemory("TriangleSharedMemory")
{
    // Alokowanie pamięci współdzielonej
    if (!sharedMemory.create(100000000)) {
        qDebug() << "Unable to create shared memory segment.";
    }
    qDebug() << "sharedMemory.size()" << sharedMemory.size();

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

    if (!sharedMemory.lock()) {
        return;
    }

    // Read width and height from shared memory
    const char *from = static_cast<const char*>(sharedMemory.constData());
    uint32_t width;
    uint32_t height;
    memcpy(&width, from, sizeof(width));
    memcpy(&height, from + sizeof(width), sizeof(height));

    qDebug() << "Width = " << width;
    qDebug() << "Height = " << height;

    // Ensure we have enough data for the image
    int headerSize = sizeof(width) + sizeof(height);
    int imageSize = sharedMemory.size() - headerSize;
    if (imageSize < static_cast<int>(width * height * 4)) {
        qDebug() << "Shared memory segment does not contain enough data.";
        sharedMemory.unlock();
        return;
    }

    // Create image from shared memory data
    QImage image(reinterpret_cast<const uchar*>(from + headerSize), width, height, QImage::Format_ARGB32_Premultiplied);

    sharedMemory.unlock();

    qDebug() << "Client image.sizeInBytes() = " << image.sizeInBytes();
    qDebug() << "Client sharedMemory.size() = " << sharedMemory.size();

    QPixmap pixmap = QPixmap::fromImage(image);

    imageLabel->setPixmap(pixmap);



    // if(width != this->width() || height != this->height()){
    //     resize(width, height);
    // }
}
