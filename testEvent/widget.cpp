#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *obj, QEvent * k){
    if(k->type() == TestEvent::EventType){
        qDebug("hello jinlaile");
        return false;
    }

    return QWidget::eventFilter(obj, k);

}
#if pan
bool Widget::event(QEvent *event)
{
    if(event->type() == TestEvent::EventType){
        qDebug()<<"event() is dispathting TestEvent";
        TestEvent *testEvent = static_cast<TestEvent*>(event);
        processTestEvent(testEvent);

        if(testEvent->isAccepted()){
            qDebug()<<"the testEvent has been handled";
            return true;
        }
    }
    return QObject::event(event);
}
#endif
void Widget::processTestEvent(TestEvent *event)
{
    qDebug("processTestEvent");
    event->accept();//表明事件已经被接收，不用继续传递下去了。
}
