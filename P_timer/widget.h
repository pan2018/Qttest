#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>
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

private slots:
    void on_pushButton_clicked();
    void onpantime();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    //QDateTime time1;
    //QDateTime time2;
    int time1;
    int time2;
    int flag ;
    QTimer *time;

};

#endif // WIDGET_H
