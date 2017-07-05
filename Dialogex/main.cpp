#include "widget.h"
#include "qreelwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 0
    Widget w;
    w.show();
#else
    QReelWidget * tw = new QReelWidget;
    tw->setOriPos(QPoint(100, 100));
    tw->setOriSize(QSize(400,300));
    tw->showExpan();
#endif

    return a.exec();
}
