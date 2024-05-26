#include <QApplication>
#include "TriangleWidget.h"
#include "../config.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TriangleWidget w(false);
    w.resize(WIDTH, HEIGHT);
    w.show();

    return a.exec();
}

