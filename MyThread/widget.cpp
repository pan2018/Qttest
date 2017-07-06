#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_workerThread = new ClientThread(this);
    ui->setupUi(this);
    S_init();
    qDebug()<<"GUI"<<QThread::currentThreadId();

}

Widget::~Widget()
{
    m_workerThread->quit();
    delete ui;
    delete m_workerThread;
}

void Widget::S_init()
{
    ui->pushButton->setText(QString::fromLocal8Bit("start"));
    ui->progressBar->setFixedHeight(25);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(startThread()));
    //connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SIGNAL(stopThread()));//如果两个类中没有包含及一个类中没有另个类的实例，则需要父窗口转发
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),m_workerThread,SLOT(stop()));//此问题中，父类中有m_workThread对象，既可以直接发送信号调用槽函数
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),m_workerThread,SLOT(stop()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(startThread()));
    connect(m_workerThread,SIGNAL(resultReady(int)),this,SLOT(handleResults(int)));

}

bool Widget::eventFilter(QObject *obj, QEvent *k)
{
    //if(event->type() == )

    return QWidget::eventFilter(obj, k);//返回给父窗口
}

void Widget::handleResults(int value)
{
   // qDebug() << "Handle Thread : " << QThread::currentThreadId();
    ui->progressBar->setValue(value);
}

void Widget::startThread()
{

    if(!m_workerThread->isRunning()){
       // connect(&m_workerThread, SIGNAL(finished()), &m_workerThread, SLOT(deleteLater()));
        m_workerThread->start();
    }else{
         qDebug()<<"isready start";
    }
   // ClientThread workerThread = new ClientThread(this);
   // connect(workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)));
    // 线程结束后，自动销毁
   // connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    // workerThread->start();
}

