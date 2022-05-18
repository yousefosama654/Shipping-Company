#pragma once
#include"Time.h"
#include "info.h"
#include <math.h>
class truck;
class cargo
{
protected:

	Time PT;//
	int loadingTime;// 
	int deliveryDistance;//
	int id;//
	int cost; //
	status state;
	Time MT;
	Time WT;
	Time CDT;
	// add setters and getters for them
	

	truck* associated;
	bool requested; 	 // when the cargo is requested it is transformed fro waiting to moving 
	
	bool isAutoP{false};

	 
public:
	cargo(); // default constructor
	cargo(int ID, Time Prep, int LD, int dd, int cost); //non-default constructor
	// getters
	truck* getassociated();
	int getCost();
	int getdeliverydistance();
	Time getDeliverlyTime();
	int getLoadingTime();
	int getId();
	status getStatus();
	bool getrequest();
	Time getPreTime();
	Time getWaitingTime();
	Time getMovingTime();
	Time getCargoDeliveryTime();
	

	//function to check loading
	bool checkloading();
	//function to check autopromotion
	bool AutoPromoted();

	//setters
	void setPreparationTime(Time);
	void setrequest(bool);
	void setCost(int c); 
	void setDeliveryDistance(int dd); 
	void setLoadingTime(int loadingTime); 
	void setId(int ID); 
	void setStatus(status s);
	void setassociated(truck* p);
	void setAutoP(); //Set AtuoP to 1
	void setMovingTime(Time);
	void setCDT(Time);
	void calCDT();
	virtual ~cargo(); 
};
