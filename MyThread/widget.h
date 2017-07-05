#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "clientthread.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void S_init();
protected:
    bool eventFilter(QObject *, QEvent *);
private slots:
    void handleResults(int value);
    void startThread();
signals:
    void stopThread();
    void restartThread();
private:
    Ui::Widget *ui;
    ClientThread *m_workerThread;
};

#endif // WIDGET_H
