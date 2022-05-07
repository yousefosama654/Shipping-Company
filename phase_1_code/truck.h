#pragma once
#include "time.h"
#include "cargo.h"
class truck
{

	int TC;//
	int Maintance;//
	float Speed;//
	int JourneysLeft;//
	int JourneysBeforeCheckup;//
	char TruckType;//
	Time DeliveryInterval;//
	bool avaliable;//
	int ID;//
	Time MT;
	//PriQ<cargo*> cargos; // pri is delivary interval 
	
public:
	truck(); // default constructor
	truck(int id, int Mt, float s, int x,char tp); // non-default constructor

	//setters
	void setID(int);
	void setCapacity(int c);
	void setSpeed(float s);
	void setTruckType(char tt);
	void setAvailablity(bool a);
	void setJourneysBeforeCheckup(int);
	void setJourneysLeft(int);
	void setMaintance(int);
	void setDeliveryInterval(Time);
	void setMovingTime(Time);
	//getters
	int getID();
	int getCapcity() const;
	float getSpeed() const;
	char getTruckType() const;
	bool getAvailablity();
	int getJourneysBeforeCheckup();
	int getJourneysLeft();
	int getMaintance();
	Time setDeliveryInterval();
	Time getMovingTime();
	//decrement Journiesleft
	void decrementJourniesleft();
};

