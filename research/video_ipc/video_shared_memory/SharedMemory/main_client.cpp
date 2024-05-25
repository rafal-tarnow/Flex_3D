// #include "widget.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     Widget w;
//     w.show();
//     return a.exec();
// }

// #include <QApplication>
// #include <QSharedMemory>
// #include <QLabel>
// #include <QImage>
// #include <QBuffer>
// #include <QDebug>

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     // Załaduj pamięć współdzieloną
//     QSharedMemory sharedMemory("TriangleSharedMemory");
//     if (!sharedMemory.attach()) {
//         qDebug() << "Unable to attach to shared memory segment.";
//         return -1;
//     }

//     // Odczytaj obraz z pamięci współdzielonej
//     sharedMemory.lock();
//     QByteArray byteArray((char*)sharedMemory.constData(), sharedMemory.size());
//     sharedMemory.unlock();

//     QBuffer buffer(&byteArray);
//     buffer.open(QIODevice::ReadOnly);
//     QImage image;
//     image.load(&buffer, "PNG");

//     if (image.isNull()) {
//         qDebug() << "Failed to load image from shared memory.";
//         return -1;
//     }

//     // Wyświetl obraz
//     QLabel label;
//     label.setPixmap(QPixmap::fromImage(image));
//     label.show();

//     qDebug() << "Image displayed from shared memory.";

//     return app.exec();
// }

#include <QApplication>
#include "client/ClientWidget.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientWidget w;
    w.resize(1700, 900);
    w.show();

    return a.exec();
}


