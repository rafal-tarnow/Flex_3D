#include <QApplication>
#include "ClientWidget.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientWidget w;
    w.resize(1700, 900);
    w.show();

    return a.exec();
}


