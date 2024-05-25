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

