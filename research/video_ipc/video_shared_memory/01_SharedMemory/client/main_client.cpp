#include <QApplication>
#include "ClientWidget.hpp"
#include "../config.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientWidget w;
    w.resize(WIDTH, HEIGHT);
    w.show();

    return a.exec();
}


