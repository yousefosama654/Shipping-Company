#pragma once
#include "Time.h"
class Company;
#include"Status.h"
class event
{
	int CargoID;
	Time EventTime; 
protected:
	Company* Comp;
public:
	//Constructor
	event (Time ET, int ID, Company*com);
	// getter and setters 
	void setEventTime(Time ET);
	Time getEventTime();
	void setCargoID(int ID);
	int getCargoID();
	virtual void Execute() = 0;
	virtual ~event();
		
};

