#pragma once
#include "event.h"
class cancellationEvent : public event
{
public:

    cancellationEvent(Time ET, int ID, Company* com);
    virtual void Execute();
    ~cancellationEvent();

};

