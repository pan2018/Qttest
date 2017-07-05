#include "testevent.h"

const QEvent::Type TestEvent::EventType =
        (QEvent::Type)QEvent::registerEventType(QEvent::User+100);
TestEvent::TestEvent():QEvent(EventType)
{

}

