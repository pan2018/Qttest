#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
#include <QObject>
#include <QThread>
#include <QMutexLocker>
class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(QObject *parent = 0);
    ~ClientThread();

protected:
    virtual void run();
public slots:
        void stop();
        void restartT();

signals:
    void resultReady(int value);
    void stopThread();
    void restartThread();
private:
    bool m_bStopped;
        int nValue;
    QMutex m_mutex;
};

#endif // CLIENTTHREAD_H
