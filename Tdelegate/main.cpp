#include "widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    Widget w;
    w.show();
#elif 0


#endif
    return a.exec();
}
