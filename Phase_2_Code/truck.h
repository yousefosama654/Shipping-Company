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

	float Speed;//
	char TruckType;//
	int Capacity;//
	int Maintance;//
	int JourneysLeft;//
	int NoOfJourneys; // 
	int ID;//
	int sumOfMovingTimes;
	int sumOfLoading;// sumOfLoading is Diffrent from  (sumOfLoadingTimes) and calc sum of All Loading Times;
	int maxDelivaryDistance;
	int sumOfLoadingTimes;
	int noOfCargos; //TODO what is the meaning of   noOfCargos
	int distanceBeforeUnRegulerChechUp;
	int CargosDelivered;
	bool Night;

	//pri is (distance) first come first served for (Normal, Speical) cargo 
	Time DeliveryInterval;//
	Time finishedChecking;
	Time MT;
	PriQ<cargo*> cargos;
	//pri is weighted equation for vip cargo 

public:
	truck(); // default constructor
	truck(int id, int Mt, float s, char tp, int); // non-default constructor
	//setters
	void setID(int);
	void setCapacity(int c);
	void setSpeed(float s);
	void setTruckType(char tt);
	void setJourneysLeft(int);
	void setMaintance(int);
	void setDeliveryInterval();
	void setMovingTime(Time);
	void setFinishedChecking(Time);
	void setSumOfLoadingTimes(int); // is reseted in moving to checkup or waiting (sum of unloading (Times))
	void setMovingWaitingTimeCargos(const Time&);
	void setNight(bool); 
	void incrementNoOfCargos();
	void incrementSumOfLoading(int);// used in statstics 


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
	Time getMovingTime();
	Time getDeliveryInterval();
	Time getFinishedChecking();
	int getsumOfLoadingTimes();
	int getToTCargosDelivered();
	int getSumofMovingTimes();
	int getSumOfLoading();
	int getActiveTime();
	int getDistanceBeforeUnRegulerChechUp();
	int getNight();
	int getPriority();
	cargo* deliveryFailure();

	/******************************************************/
	void print();
	cargo* DropCargo(Time t, int&);
	void assignCargo(cargo*);
	//decrement Journiesleft
	void incrementJournies();
	void decrementJourniesleft();
	void resetdistanceBeforeUnRegulerChechUp();
	void resetMaxDelivaryDistance();
};

