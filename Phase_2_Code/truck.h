#pragma once
#include "time.h"
#include "cargo.h"
#include "PriQ.h"
#include"queue.h"
#include "NormalCargo.h"
#include "SpecialCargo.h"
#include "vipCargo.h"
#include <iostream>
#include <string>
class truck
{

	int TC;//
	int Maintance;//
	float Speed;//
	int JourneysLeft;//
	int NoOfJourneys; // 
	char TruckType;//
	Time DeliveryInterval;//
	Time finishedChecking; 
	bool avaliable;//
	int ID;//
	Time MT;
	int CargosDelivered;
	PriQ<cargo*> cargos; 
	int sumOfMovingTimes;
	int sumOfLoading;// sumOfLoading is Diffrent from  (sumOfLoadingTimes) and calc sum of All Loading Times;
	int maxDelivaryDistance;
	int sumOfLoadingTimes;
	int noOfCargos; //TODO what is the meaning of   noOfCargos
	//pri is (distance) first come first served for (Normal, Speical) cargo 
	//pri is weighted equation for vip cargo 
	
public:
	truck(); // default constructor
	truck(int id, int Mt, float s,char tp, int); // non-default constructor
	//setters
	void setID(int);
	void setCapacity(int c);
	void setSpeed(float s);
	void setTruckType(char tt);
	void setAvailablity(bool a);
	void setJourneysLeft(int);
	void setMaintance(int);
	void setDeliveryInterval();
	void setMovingTime(Time);
	void setFinishedChecking(Time);
	void setSumOfLoading(int i);
	void incrementNoOfCargos(); 
	/******************************************************/
	//getters
	int getID();
	int getCapcity() const;
	int getJourneysLeft();
	int getMaintance();
	int getNoOfJourneys();
	int getNoOfCargos();

	float getSpeed() const;
	char getTruckType() const;
	bool getAvailablity();
	Time getMovingTime();
	Time getDeliveryInterval();
	Time getFinishedChecking();
	int getsumOfLoadingTimes();
	int getToTCargosDelivered();
	int getSumofMovingTimes();
	int getSumOfLoading();
	int getActiveTime();
	/******************************************************/
	void print(); 
	cargo* DropCargo(Time t,int&);
	void assignCargo(cargo*); 
	//decrement Journiesleft
	void incrementJournies(); 
	void decrementJourniesleft();
};

