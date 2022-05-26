#pragma once
#include"truck.h"
truck::truck()// default constructor
{
	Capacity = 0;
	Maintance = 0;
	Speed = 0;
	JourneysLeft = 0;
	//JourneysBeforeCheckup=0;
	TruckType = 'U';
	DeliveryInterval = 0;
	ID = 0;
	noOfCargos = 0;
}

truck::truck(int id, int Mt, float s, char tp, int tc) // non-default constructor
{
	ID = id;
	Maintance = Mt;
	Speed = s;
	JourneysLeft = 0;
	Capacity = tc;
	//JourneysBeforeCheckup = x;
	TruckType = tp;
	maxDelivaryDistance = INT_MIN;
	sumOfLoadingTimes = 0; // time  
	sumOfMovingTimes = 0;
	sumOfLoading = 0;
	CargosDelivered = 0;
	distanceBeforeUnRegulerChechUp = 0;
}

//setters
void truck::setID(int id)
{
	this->ID = id;
}
void  truck::setCapacity(int c)
{
	this->Capacity = c;
}
void  truck::setSpeed(float s)
{
	Speed = s;
}
void truck::setTruckType(char tt)
{
	TruckType = tt;
}


void truck::setJourneysLeft(int JL)
{
	JourneysLeft = JL;
}
void truck::setMaintance(int M)
{
	Maintance = M;
}
void truck::setDeliveryInterval()
{
	DeliveryInterval = MT + ceil(maxDelivaryDistance / Speed) * 2 + sumOfLoadingTimes;
	sumOfMovingTimes += ceil(maxDelivaryDistance / Speed) + sumOfLoadingTimes;
	distanceBeforeUnRegulerChechUp += maxDelivaryDistance * 2;
}
void truck::setMovingTime(Time x)
{
	MT = x;
}
void truck::setFinishedChecking(Time fc)
{
	finishedChecking = fc;
}
void truck::incrementSumOfLoading(int i)
{
	sumOfLoading += i;
}

void truck::incrementNoOfCargos()
{
	noOfCargos++;
}
void truck::setSumOfLoadingTimes(int x)
{
	sumOfLoadingTimes = x;
}
void truck::setMovingWaitingTimeCargos(const Time& mt)
{
	Queue<cargo*> q;
	cargo* c = nullptr;
	while (!cargos.isEmpty())
	{
		cargos.dequeue(c);
		c->setMovingTime(mt);
		c->calWaitingTime();
		q.enqueue(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		cargos.enqueue(c, -c->getDeliverlyTime().toInt());
	}

}
void truck::setNight(bool n)
{
	Night = n;
}
//getters
int truck::getID()
{
	return ID;
}
int truck::getCapcity() const
{
	return Capacity;
}
float truck::getSpeed() const
{
	return Speed;
}
char truck::getTruckType() const
{
	return this->TruckType;
}


int truck::getJourneysLeft()
{
	return this->JourneysLeft;
}
int truck::getMaintance()
{
	return this->Maintance;
}

Time truck::getDeliveryInterval()
{
	return this->DeliveryInterval;
}

Time truck::getFinishedChecking()
{
	return finishedChecking;
}

int truck::getsumOfLoadingTimes()
{
	return sumOfLoadingTimes;
}

Time truck::getMovingTime()
{
	return MT;
}

int truck::getNoOfJourneys()
{
	return NoOfJourneys;
}

int truck::getNoOfCargos()
{
	return noOfCargos;
}

cargo* truck::DropCargo(Time t, int& movingCargos)
{
	cargo* c = nullptr;
	cargo* f = nullptr;
	Queue<cargo*> q;
	if (cargos.peek(c) && c->getDeliverlyTime() == t)
	{
		cargos.dequeue(c);
		f = c;

		noOfCargos--;
		movingCargos--;
		CargosDelivered++;
	}
	return f;
}

void truck::assignCargo(cargo* c) {
	if (!c)
		return;
	c->setassociated(this);
	c->calCDT();
	incrementNoOfCargos();
	if (c->getdeliverydistance() > maxDelivaryDistance)
		maxDelivaryDistance = c->getdeliverydistance();
	sumOfLoadingTimes += c->getLoadingTime();
	cargos.enqueue(c, -c->getDeliverlyTime().toInt());
}

void truck::incrementJournies()
{
	JourneysLeft++;
	NoOfJourneys++;
}

void truck::print()
{
	if (this->cargos.isEmpty())
		return;
	cargo* c = nullptr;
	cargo* x = nullptr;
	Queue<cargo*> q;
	cargos.peek(c);
	NormalCargo* nc = dynamic_cast<NormalCargo*> (c);
	SpecialCargo* sc = dynamic_cast<SpecialCargo*> (c);
	vipCargo* vc = dynamic_cast<vipCargo*> (c);
	if (nc)
		cout << '[';
	else if (sc)
		cout << '(';
	else
		cout << '{';
	while (cargos.dequeue(c))
	{
		string comma = cargos.peek(x) ? "," : "";
		string x = to_string(c->getId()) + comma;
		cout << x;
		q.enqueue(c);
	}
	if (nc)
		cout << ']';
	else if (sc)
		cout << ')';
	else
		cout << '}';
	while (q.dequeue(c))
	{
		cargos.enqueue(c, -c->getDeliverlyTime().toInt());
	}
}

void truck::decrementJourniesleft()
{
	JourneysLeft--;
}
void truck::resetdistanceBeforeUnRegulerChechUp()
{
	distanceBeforeUnRegulerChechUp = 0;
}
void truck::resetMaxDelivaryDistance()
{
	maxDelivaryDistance = 0;
}
int  truck::getToTCargosDelivered()
{
	return  CargosDelivered;
}

int truck::getSumofMovingTimes()
{
	return sumOfMovingTimes;
}

int truck::getSumOfLoading()
{
	return sumOfLoading;
}

int truck::getActiveTime()
{
	return getSumOfLoading() + getSumofMovingTimes();
}

int truck::getDistanceBeforeUnRegulerChechUp()
{
	return distanceBeforeUnRegulerChechUp;
}

int truck::getNight()
{
	return Night;
}

int truck::getPriority()
{
	return ceil(100 * Speed / Capacity);
}

cargo* truck::deliveryFailure()
{

	cargo* x = nullptr;
	cargos.dequeue(x);
	if (x)
	{
		noOfCargos--;
	}
	return x;
}
