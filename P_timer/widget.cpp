#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    flag = 1;
    time1 = QTime::currentTime().second();
    time2 = QTime::currentTime().second();
    time = new QTimer();
    time->setInterval(5000);
    S_init();
    connect(time, SIGNAL(timeout()), this, SLOT(onpantime()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::S_init()
{
    ui->pushButton_2->setAutoFillBackground(true);
    QPalette p = ui->pushButton_2->palette();
    p.setColor(QPalette::ButtonText,Qt::red);
    p.setColor(QPalette::Active,QPalette::Button,Qt::green);
    ui->pushButton_2->setPalette(p);

    ui->label->setAutoFillBackground(true);
    QPalette p1 = ui->label->palette();
    p1.setColor(QPalette::Base,Qt::red);
    p1.setColor(QPalette::Active,QPalette::Text,Qt::red);
    ui->label->setPalette(p1);
}

void Widget::on_pushButton_clicked()
{

    if(flag == 1){
        time->start();
        qDebug()<<"ok";
        flag = 0;
        ui->label_3->setStyleSheet("background-color: rgb(255, 85, 0)");
    }else{
        qDebug()<<"no";
        return;
    }
    qDebug()<<"runing in";
}

void Widget::onpantime()
{
    flag = 1;
    ui->label_3->setStyleSheet("background-color: rgb(0, 255, 0)");
}

void Widget::on_pushButton_2_clicked()
{
    qApp->exit(0);
}
