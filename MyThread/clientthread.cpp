#include "clientthread.h"
#include <QDebug>
#include <QPushButton>
#include <QString>
ClientThread::ClientThread(QObject *parent):QThread(parent),m_bStopped(false)
{
    qDebug()<<"worker thread:"<<QThread::currentThreadId();
    nValue = 0;
    //connect(parent,SIGNAL(stopThread()),this,SLOT(stop()));
    //connect(parent,SIGNAL(restartThread()),this,SLOT(restartT()));
}

ClientThread::~ClientThread()
{
    qDebug()<<"~ClientTrhead";
    nValue = 101; //设置退出标志
    m_bStopped = true;
    //stop();
    quit();
    wait();
}

void ClientThread::stop()
{
   // QPushButton *btn = qobject_cast<QPushButton*>(sender());
    qDebug()<<"对象名:"<<QObject::sender();
    qDebug() << "Worker Stop Thread : " << QThread::currentThreadId();
    QMutexLocker locker(&m_mutex);
    if(QString::compare(QObject::sender()->objectName(),"pushButton_3")==0){
        m_bStopped = false;
        return ;
    }else if(QString::compare(QObject::sender()->objectName(),"pushButton_2")==0){
        m_bStopped = true;
        return ;
    }
}

void ClientThread::restartT()
{
    m_bStopped = false;
}

void ClientThread::run Q_DECL_OVERRIDE()
{
    qDebug() << "Worker Run Thread : " << QThread::currentThreadId();

    nValue = 0;
    while (nValue < 100)
    {
        // 休眠50毫秒
        msleep(50);
        ++nValue;

        // 准备更新
        emit resultReady(nValue);
        // 检测是否停止
        {
            //因为这里需要进行线程暂停，锁m_bStopped，导致无法修改他来退出，就形成死循环了。
            //QMutexLocker locker(&m_mutex);
            while(m_bStopped){
                qDebug()<<"heloo in";
                msleep(1000);
                if(nValue>100)
                    break;
            }
            if(nValue>100)//退出标志
                break;
        }
        // locker超出范围并释放互斥锁
    }
    qDebug()<<"已出run";
}
