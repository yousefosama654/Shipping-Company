#include"truck.h"
truck::truck()// default constructor
{
	TC=0;
	Maintance=0;
	Speed=0;
	JourneysLeft=0;
	JourneysBeforeCheckup=0;
	TruckType='U';
	DeliveryInterval=0;
	avaliable=0;
	ID=0;
}

truck::truck(int id, int Mt, float s, int x, char tp) // non-default constructor
{
ID = id;
Maintance = Mt;
Speed = s;
JourneysLeft = x;
JourneysBeforeCheckup = x;
TruckType = tp;
}

//setters
void truck::setID(int id)
{
	this->ID = id;
}
void  truck::setCapacity(int c)
{
	this->TC = c;
}
void  truck::setSpeed(float s)
{
	Speed = s;
}
void truck::setTruckType(char tt)
{
	TruckType = tt;
}
void truck::setAvailablity(bool a)
{
	avaliable = a;
}
void truck::setJourneysBeforeCheckup(int JBC)
{
	JourneysBeforeCheckup = JBC;
}
void truck::setJourneysLeft(int JL)
{
	JourneysLeft = JL;
}
void truck::setMaintance(int M)
{
	Maintance = M;
}
void truck::setDeliveryInterval(Time DI)
{
	DeliveryInterval = DI;
}
void truck::setMovingTime(Time x)
{
	MT = x;
}
//getters
int truck::getID()
{
	return ID;
}
int truck::getCapcity() const
{
	return TC;
}
float truck::getSpeed() const
{
	return Speed;
}
char truck::getTruckType() const
{
	return this->TruckType;
}
bool truck::getAvailablity()
{
	return this->avaliable;
}
int truck::getJourneysBeforeCheckup()
{
	return this->JourneysBeforeCheckup;
}
int truck::getJourneysLeft()
{
	return this->JourneysLeft;

}
int truck::getMaintance()
{
	return this->Maintance;
}
Time truck::setDeliveryInterval()
{
	return this->DeliveryInterval;
}

Time truck::getMovingTime()
{
	return MT;
}

void truck::decrementJourniesleft()
{
	JourneysLeft--;
}
