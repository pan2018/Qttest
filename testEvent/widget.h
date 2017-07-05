#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "testevent.h"
#include "globel_t.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
#if pan
    bool event(QEvent *event);
#endif
    void processTestEvent(TestEvent *event);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
