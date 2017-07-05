#ifndef TESTEVENT_H
#define TESTEVENT_H
#include <QEvent>

class TestEvent : public QEvent
{
public:
    TestEvent();
public:
    static const Type EventType;
};

#endif // TESTEVENT_H
