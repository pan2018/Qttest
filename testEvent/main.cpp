#include "widget.h"
#include <QApplication>
#include "testevent.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    TestEvent tEvent;
    a.sendEvent(&w,&tEvent);
    return a.exec();
}
