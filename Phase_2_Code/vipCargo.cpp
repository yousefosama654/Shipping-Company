#include "vipCargo.h"
vipCargo::vipCargo()
{
}
float vipCargo::getpriority()
{
	return priority;
}
vipCargo::~vipCargo()
{
}
vipCargo::vipCargo(int ID, Time prep, int LD, int dd, int cost):cargo(ID, prep,LD,dd,cost)
{
	setpriority();
}
vipCargo::vipCargo(NormalCargo* N) : cargo(N->getId(), N->getPreTime(), N->getLoadingTime(),N->getdeliverydistance(), N->getCost())
{
	setpriority();
}
void vipCargo::setpriority()
{
	// what is the real equation ??
	//priority = float(cost) / (dd);

	priority = cost / (deliveryDistance * PT.toInt()); 
	// what if days can be concluded
	// (preparation day -current day)*24 + prapartion hour - current hour;
	/// another reason is the simulation

}



