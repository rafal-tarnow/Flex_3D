#pragma

#include <QQuickImageProvider>
#include <QPainter>
#include <QSharedMemory>

class ScadGLView : public QQuickImageProvider
{

public:
    ScadGLView()
        : QQuickImageProvider(QQuickImageProvider::Pixmap),
        sharedMemory("TriangleSharedMemoryyy")
    {
        if (!sharedMemory.create(100000000)) {
            qDebug() << "Unable to create shared memory segment.";
        }

        if(!sharedMemory.isAttached()){
            qDebug() << "Try attach to existing shared memory segment.";
            sharedMemory.attach();
        }
    }

    ~ScadGLView(){
        if(sharedMemory.isAttached()){
            sharedMemory.detach();
        }
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        // int width = 200;
        // int height = 100;

        // if (size)
        //     *size = QSize(width, height);
        // qDebug() << "requestedSize.width() " << requestedSize.width();
        // qDebug() << "requestedSize.height() " << requestedSize.height();
        // QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
        //                requestedSize.height() > 0 ? requestedSize.height() : height);
        // pixmap.fill(QColor(id).rgba());

        // // write the color name
        // QPainter painter(&pixmap);
        // QFont f = painter.font();
        // f.setPixelSize(20);
        // painter.setFont(f);
        // painter.setPen(Qt::black);
        // if (requestedSize.isValid())
        //     painter.scale(requestedSize.width() / width, requestedSize.height() / height);
        // painter.drawText(QRectF(0, 0, width, height), Qt::AlignCenter, id);

        // return pixmap;

        //--------------
        if (!sharedMemory.lock()) {
            return QPixmap();;
        }

        // Read width and height from shared memory
        const char *from = static_cast<const char*>(sharedMemory.constData());
        uint32_t width;
        uint32_t height;
        memcpy(&width, from, sizeof(width));
        memcpy(&height, from + sizeof(width), sizeof(height));

        int headerSize = sizeof(width) + sizeof(height);
        int imageSize = sharedMemory.size() - headerSize;
        if (imageSize < static_cast<int>(width * height * 4)) {
            qWarning() << "Shared memory segment does not contain enough data.";
            sharedMemory.unlock();
            return QPixmap(); // Zwracamy pustą QImage w przypadku błędu
        }
        // Tworzenie obrazka z danych w pamięci współdzielonej
        QImage image(reinterpret_cast<const uchar*>(from + headerSize), width, height, QImage::Format_ARGB32_Premultiplied);

        sharedMemory.unlock();


        if (size)
            *size = image.size(); // Ustawienie rozmiaru obrazka

        return QPixmap::fromImage(image);

    }
private:
    QSharedMemory sharedMemory;
};
