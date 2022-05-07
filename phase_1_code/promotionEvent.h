#pragma once
//#include "event.h"
//#include"Company.h"
//#include"time.h"
#include"files.h"
class promotionEvent : public event
{
    int extra; 
public:
    promotionEvent(Time ET, int ID, Company* com,int ex);
    virtual void Execute();
    ~promotionEvent();

};

