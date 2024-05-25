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
// #include <QImage>
// #include <QBuffer>
// #include <QDebug>
// #include "TriangleWidget.h"

// int main(int argc, char *argv[])
// {
//     qDebug() << "START SOURCE_DIR = " << QString(SOURCE_DIR);

//     QApplication a(argc, argv);

//     // Załaduj obraz
//     QImage image(QString(SOURCE_DIR) + "/" + "baboon.png");
//     if (image.isNull()) {
//         qDebug() << "Failed to load image.";
//         return -1;
//     }

//     // Konwertuj obraz na QByteArray
//     QByteArray byteArray;
//     QBuffer buffer(&byteArray);
//     buffer.open(QIODevice::WriteOnly);
//     image.save(&buffer, "PNG");

//     // Utwórz i załaduj pamięć współdzieloną
//     QSharedMemory sharedMemory("SharedImage");
//     if (sharedMemory.isAttached()) {
//         sharedMemory.detach();
//     }

//     if (!sharedMemory.create(byteArray.size())) {
//         qDebug() << "Unable to create shared memory segment.";
//         return -1;
//     }

//     // Zapisz obraz do pamięci współdzielonej
//     sharedMemory.lock();
//     char *to = (char*)sharedMemory.data();
//     const char *from = byteArray.data();
//     memcpy(to, from, qMin(sharedMemory.size(), byteArray.size()));
//     sharedMemory.unlock();

//     qDebug() << "Image written to shared memory.";

//     TriangleWidget triangleWidget;
//     triangleWidget.show();

//     return a.exec();
// }

#include <QApplication>
#include "TriangleWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TriangleWidget w;
    w.resize(1700, 900);
    w.show();

    return a.exec();
}

