#include"truck.h"
truck::truck()// default constructor
{
	TC = 0;
	Maintance = 0;
	Speed = 0;
	JourneysLeft = 0;
	//JourneysBeforeCheckup=0;
	TruckType = 'U';
	DeliveryInterval = 0;
	avaliable = 0;
	ID = 0;
	noOfCargos = 0;
}

truck::truck(int id, int Mt, float s, char tp, int tc) // non-default constructor
{
	ID = id;
	Maintance = Mt;
	Speed = s;
	JourneysLeft = 0;
	TC = tc;
	//JourneysBeforeCheckup = x;
	TruckType = tp;
	maxDelivaryDistance = INT_MIN;
	sumOfLoadingTimes = 0;
	sumOfMovingTimes = 0;
	sumOfLoading = 0;
	CargosDelivered = 0;
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
	DeliveryInterval = MT + (maxDelivaryDistance / Speed) * 2 + sumOfLoadingTimes;
	sumOfMovingTimes += (maxDelivaryDistance / Speed) + sumOfLoadingTimes;
}
void truck::setMovingTime(Time x)
{
	MT = x;
}
void truck::setFinishedChecking(Time fc)
{
	finishedChecking = fc;
}
void truck::setSumOfLoading(int i)
{
	sumOfLoading += i;
}
void truck::incrementNoOfCargos()
{
	noOfCargos++;
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
	cargo* c = nullptr;	cargo* f = nullptr;
	Queue<cargo*> q;
	cargos.peek(c);
	while (!cargos.isEmpty())
	{
		if (c->getDeliverlyTime() == t)
		{
			f = c;
			noOfCargos--;
			movingCargos--;
			CargosDelivered++;
		}
		else
		{
			q.enqueue(c);
		}

		cargos.dequeue(c);
		cargos.peek(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		cargos.enqueue(c, c->getdeliverydistance());
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
	c->setCDT(c->getCargoDeliveryTime());
	sumOfLoadingTimes += c->getLoadingTime();

	cargos.enqueue(c, c->getdeliverydistance());
}

void truck::incrementJournies()
{
	JourneysLeft++;
	NoOfJourneys++;
}

void truck::print()
{
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
		cout << c->getId() << ',';
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
		cargos.enqueue(c, c->getdeliverydistance());
	}
}

void truck::decrementJourniesleft()
{
	JourneysLeft--;
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
