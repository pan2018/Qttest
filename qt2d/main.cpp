#include "qt2d.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt2d w;
    w.show();

    return a.exec();
}
