#include "event.h"
event::event(Time ET, int ID, Company* com): CargoID(ID), EventTime(ET)
{
	Comp = com;
}

void event::setEventTime(Time ET)
{
	EventTime = ET;
}

Time event::getEventTime()
{
	return EventTime;
}

void event::setCargoID(int ID)
{
	this->CargoID = ID;
}

int event::getCargoID()
{
	return CargoID;
}

event::~event()
{

}