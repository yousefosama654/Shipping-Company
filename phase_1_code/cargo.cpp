#include"cargo.h"
#include"truck.h"
void cargo::setrequest(bool x)
{
	requested = x;
}
Time cargo::getCargoDeliveryTime()
{
	return CDT;
}
bool cargo::checkloading()
{
	if (this->getStatus() == WAITING)
		return 0;
	return 1;

}
bool cargo::getrequest()
{
	return requested;
}
cargo::cargo() :WT(0), state(WAITING), MT(0), CDT(0),associated(nullptr)
{

}
cargo::cargo(int ID, Time Prep, int LD, int dd, int cost) //:maxWaitingTime(MW)
{
	setCost(cost);
	setId(ID);
	setDeliveryDistance(dd);
	setLoadingTime(LD);
	setPreparationTime(Prep);
	WT = 0;
	state = WAITING;
	MT = 0;
	associated = nullptr;
	WT = MT - PT;
	// what if speed ==0
	// what if asscoiated is null
	
	// ADD overlaoding to an integer
}
Time cargo::getWaitingTime()
{
	return WT;
}
void cargo:: setPreparationTime(Time prep)
{
	PT = prep;
}
Time cargo::getMovingTime()
{
	return MT;
}
void cargo::setCost(int c)
{
	cost = c;
}
void cargo:: setDeliveryDistance(int dd)
{
	deliveryDistance = dd;
}
void cargo::setLoadingTime(int x)
{
	loadingTime = x;
}
void cargo::setId(int ID)
{
	id = ID;
}
void cargo::setStatus(status s)
{
	state = s;
}



void cargo::setAutoP()
{
	isAutoP = true;
}
void cargo::setMovingTime(Time m )
{
	MT = m;
}
void cargo::calCDT()
{
	if (associated) {
		int x = ceil(deliveryDistance / associated->getSpeed());
		CDT = MT + x + loadingTime;
	}
}
bool cargo::AutoPromoted()
{
	return isAutoP;
}
void cargo:: setassociated(truck* ass)
{
	this->associated=ass;
}
int cargo::getCost()
{
	return cost;
}
truck* cargo::getassociated()
{
	return this->associated;
}
Time cargo::getDeliverlyTime()
{
	return CDT;
}
int cargo::getdeliverydistance()
{
	return this->deliveryDistance;
}
int cargo:: getLoadingTime()
{
	return loadingTime;
}
int cargo:: getId()
{
	return id;
}
status cargo :: getStatus()
{
	return state;
}

Time cargo:: getPreTime()
{
	return this->PT;
}
cargo::~cargo()
{

}