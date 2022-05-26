#include "Company.h"

istream& operator>> (istream& is, Time& t)
{
	int day, hour;
	is >> day;
	is.ignore();
	is >> hour;
	t.setday(day);
	t.sethour(hour);
	return is;
}
void Company::PromoteCargo(int ID)
{
	Queue<NormalCargo*> q;
	NormalCargo* x = nullptr;
	NormalCargo* y = nullptr;
	while (!NormalWaitingCargos.isEmpty())
	{
		NormalWaitingCargos.dequeue(x);
		if (x->getId() != ID)
		{
			q.enqueue(x);
		}
		else
		{
			NCargosCount--;
			VCargosCount++;
			y = x;

		}
	}
	while (!q.isEmpty())
	{
		q.dequeue(x);
		NormalWaitingCargos.enqueue(x);
	}
	if (y)
	{
		vipCargo* v = new vipCargo(y);
		VipWaitingCargos.enqueue(v, (int)(v->getpriority()));
	}
}
void Company::IncrementCurrentHour()
{
	ExecuteEvent();
	MoveTruckFromLoadingToMoving();                     // twice because lag 1 hour
	MoveTruckFromMovingTonReguarMaintance();
	MoveTruckFromUnReguarMaintanceToEmpty();
	MoveTruckFromMovingToCheckupOrWaiting();
	MoveTruckFromCheckupToEmpty();
	checkMovingCargos();
	AssignVipCargo();
	AssignNormalCargo();
	AssignSpecialCargo();
	AssignVipCargo_MaxW();
	AssignNormalCargo_MaxW();
	AssignSpecialCargo_MaxW();
	AutoPromotinFunc();
	if (mode != 'c')
		print();

	currentTime.IncrementHour();
}
void Company::IncrementCurrentDay()
{
	currentTime.IncrementDay();
}

int Company::getCurrentHour()
{
	return currentTime.gethour();
}
int Company::getCurrentday()
{
	return currentTime.getday();
}

bool Company::isWorkingTime()
{
	if (currentTime.gethour() >= 5)
		return 1;
	return 0;
}

bool Company::isWorkingTime(Time t)
{
	return (t.gethour() >= 5 && t.gethour() <= 23);
}
int Company::getMaxNormalLoadingTime(int cap)
{
	if (NormalWaitingCargos.isEmpty())
		return 0;
	Queue<NormalCargo*> q;
	NormalCargo* c;
	NormalWaitingCargos.peek(c);
	int max = c->getLoadingTime();
	for (int i = 0; i < cap; i++)
	{
		NormalWaitingCargos.dequeue(c);
		q.enqueue(c);
		if (max < c->getLoadingTime())
			max = c->getLoadingTime();
	}
	while (!NormalWaitingCargos.isEmpty())
	{
		NormalWaitingCargos.dequeue(c);
		q.enqueue(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		NormalWaitingCargos.enqueue(c);
	}
	return max;
}

int Company::getMaxSpecialLoadingTime(int cap)
{
	if (SpecialWaitingCargos.isEmpty())
		return 0;
	Queue<SpecialCargo*> q;
	SpecialCargo* c;
	SpecialWaitingCargos.peek(c);
	int max = c->getLoadingTime();
	for (int i = 0; i < cap; i++)
	{
		SpecialWaitingCargos.dequeue(c);
		q.enqueue(c);
		if (max < c->getLoadingTime())
			max = c->getLoadingTime();
	}
	while (!SpecialWaitingCargos.isEmpty())
	{
		SpecialWaitingCargos.dequeue(c);
		q.enqueue(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		SpecialWaitingCargos.enqueue(c);
	}

	return max;
}

int Company::getMaxVipLoadingTime(int cap)
{
	if (VipWaitingCargos.isEmpty())
		return 0;
	Queue<vipCargo*> q;
	vipCargo* c;
	VipWaitingCargos.peek(c);
	int max = c->getLoadingTime();
	for (int i = 0; i < cap; i++)
	{
		VipWaitingCargos.dequeue(c);
		q.enqueue(c);
		if (max < c->getLoadingTime())
			max = c->getLoadingTime();
	}
	while (!VipWaitingCargos.isEmpty())
	{
		VipWaitingCargos.dequeue(c);
		q.enqueue(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		VipWaitingCargos.enqueue(c, c->getpriority());
	}

	return max;
}

Company::Company(string OFN, string IFN)
{
	noOfNT = 0;
	noOfST = 0;
	noOfVT = 0;
	speedOfNT = 0;
	speedOfST = 0;
	speedOfVT = 0;
	capacityOfNT = 0;
	capacityOfST = 0;
	capacityOfVT = 0;
	checkDurationNT = 0;
	checkDurationSP = 0;
	checkDurationVT = 0;
	journeyBeforeCheck = 0;
	autoPromotionLimit = 0;
	maxWaiting = 0;
	numberOfEvents = 0;
	noMovingCargos = 0;
	noPromotedCargos = 0;
	currentTime.setday(0);
	currentTime.sethour(0);
	isNormalTruckLoading = 0;
	isVipTruckLoading = 0;
	isSpecialTruckLoading = 0;

	inputFileName = IFN;
	outputFileName = OFN;
	inputFile.open(inputFileName, ios::in);
	outputFile.open(outputFileName, ios::out);
	ReadInput();
	ui = new UI();
	initTrucks();
}

void Company::ReadInput()
{
	if (inputFile.is_open())
	{
		inputFile >> noOfNT >> noOfST >> noOfVT;
		inputFile >> noNightNormalTrucks >> noNightSpecialTrucks >> noNightVipTrucks;
		for (int i = 0; i < noOfNT + noOfST + noOfVT; i++)
		{
			int x; 
			inputFile >> x; 
			speed.enqueue(x);
		}
		for (int i = 0; i < noOfNT + noOfST + noOfVT; i++)
		{
			int x;
			inputFile >> x;
			capacity.enqueue(x);
		}
		//inputFile >> speedOfNT >> speedOfST >> speedOfVT;
		//inputFile >> capacityOfNT >> capacityOfST >> capacityOfVT;
		inputFile >> journeyBeforeCheck >> checkDurationNT >> checkDurationSP >> checkDurationVT;
		inputFile >> autoPromotionLimit >> maxWaiting;
		inputFile >> numberOfEvents;
	}
	for (int i = 0; i < numberOfEvents; i++)
	{
		char eventType;
		Time EventTime;
		int id;
		char CargoType;
		int distancation;
		int loadingTime;
		int cost;
		int extraMoney;
		inputFile >> eventType;
		switch (eventType)
		{
		case 'R':
		{
			inputFile >> CargoType >> EventTime >> id >> distancation >> loadingTime >> cost;
			event* ready = new PreparationEvent(this, EventTime, id, CargoType, distancation, cost, loadingTime);
			// use addToEvent function
			Events.enqueue(ready);
			break;
		}
		case 'X':
		{
			inputFile >> EventTime >> id;
			event* cancel = new cancellationEvent(EventTime, id, this);
			Events.enqueue(cancel);
			break;
		}
		case 'P':
		{
			inputFile >> EventTime >> id >> extraMoney;
			event* promotion = new promotionEvent(EventTime, id, this, extraMoney);
			Events.enqueue(promotion);
			break;
		}
		};
	}
	inputFile.close();
}

void Company::initTrucks()
{
	int sp, cap; 
	int last = 0;
	for (int i = 1; i <= noOfNT - noNightNormalTrucks; i++)
	{
		truck* t = new truck(i, checkDurationNT, speedOfNT, 'n', capacityOfNT);
		speed.dequeue(sp);
		capacity.dequeue(cap);
		t->setCapacity(cap);
		t->setSpeed(sp);
		t->setNight(0);
		NormalTrucks.enqueue(t,t->getPriority());
		last = i;
	}
	last++;
	int n = last;
	for (int i = n; i < noNightNormalTrucks + n; i++)
	{
		truck* t = new truck(i, checkDurationNT, speedOfNT, 'n', capacityOfNT);
		speed.dequeue(sp);
		capacity.dequeue(cap);
		t->setCapacity(cap);
		t->setSpeed(sp);
		t->setNight(1);
		NightNormalTrucks.enqueue(t,t->getPriority());
		last = i;
	}
	last++;
	n = last;
	for (int i = n; i < noOfST + n - noNightSpecialTrucks; i++)
	{
		truck* t = new truck(last + i, checkDurationSP, speedOfST, 's', capacityOfST);
		speed.dequeue(sp);
		capacity.dequeue(cap);
		t->setCapacity(cap);
		t->setSpeed(sp);
		t->setNight(0);
		SpecialTrucks.enqueue(t,t->getCapcity());
		last = i;
	}
	last++;
	n = last;
	for (int i = n; i < noNightSpecialTrucks + n; i++)
	{
		truck* t = new truck(i, checkDurationNT, speedOfNT, 'n', capacityOfNT);
		speed.dequeue(sp);
		capacity.dequeue(cap);
		t->setCapacity(cap);
		t->setSpeed(sp);
		t->setNight(1);
		NightSpecialTrucks.enqueue(t,t->getPriority());
		last = i;
	}
	last++;
	n = last;
	for (int i = n; i < noOfVT + n - noNightVipTrucks; i++)
	{
		truck* t = new truck(last + i, checkDurationVT, speedOfVT, 'v', capacityOfVT);
		speed.dequeue(sp);
		capacity.dequeue(cap);
		t->setCapacity(cap);
		t->setSpeed(sp);
		t->setNight(0);
		VipTrucks.enqueue(t,t->getPriority());
		last = i;
	}
	last++;
	n = last;
	for (int i = n; i < noNightVipTrucks + n; i++)
	{
		truck* t = new truck(last + i, checkDurationVT, speedOfVT, 'v', capacityOfVT);
		speed.dequeue(sp);
		capacity.dequeue(cap);
		t->setCapacity(cap);
		t->setSpeed(sp);
		t->setNight(1);
		VipTrucks.enqueue(t,t->getPriority());
	}
}

NormalCargo* Company::RemoveFromWaitingCargos(int id)
{
	Queue<NormalCargo*> q;
	NormalCargo* x;
	NormalCargo* y = nullptr;

	while (!NormalWaitingCargos.isEmpty())
	{
		NormalWaitingCargos.dequeue(x);
		if (x->getId() != id)
			q.enqueue(x);
		else
			y = x;
	}
	while (!q.isEmpty())
	{
		q.dequeue(x);
		NormalWaitingCargos.enqueue(x);
	}
	if (y)
	{
		NCargosCount--;
		noWaitingCargos--;
		CargosCount--;
	}
	return y;
}
cargo* Company::RemoveFromLoadingCargos()
{
	cargo* c = NULL;
	LoadingCargos.dequeue(c);
	return c;
}

cargo* Company::RemoveFromMovingCargos()
{
	cargo* c = NULL;
	MovingCargos.dequeue(c);
	return c;
}

cargo* Company::RemoveFromDeliveredCargos()
{
	noDeliveredCargos--;
	cargo* c = NULL;
	DeliveredCargos.dequeue(c);
	return c;
}

truck* Company::RemoveFromLoadingTrucks()
{
	truck* t = NULL;
	LoadingTrucks.dequeue(t);
	return t;
}

truck* Company::RemoveFromMovingTrucks()
{
	truck* t = NULL;
	MovingTrucks.dequeue(t);
	return t;
}
// complete all (add/remove cargos functions) 
truck* Company::RemoveFromTrucksCheckup()
{
	truck* t = NULL;
	CheckupTrucks.dequeue(t);
	return t;
}
void Company::checkMovingCargos()
{
	truck* t = nullptr;
	cargo* c = nullptr;
	Queue<truck*> q;
	bool failure = false;
	while (!MovingTrucks.isEmpty())
	{
		MovingTrucks.dequeue(t);
		// bonus

		do {
			bool probability = rand() % 101 < 2;
			c = t->DropCargo(currentTime, noMovingCargos);
			if (probability && c)
			{
				noMovingCargos++;
				while (c)
				{
					NormalCargo* nc = dynamic_cast<NormalCargo*>(c);
					SpecialCargo* sc = dynamic_cast<SpecialCargo*>(c);
					vipCargo* vc = dynamic_cast<vipCargo*>(c);
					if (nc)
					{
						nc->setPreparationTime(currentTime);
						noMovingCargos--;
						NormalWaitingCargos.enqueue(nc);
						noWaitingCargos++;
					}
					else if (sc)
					{
						sc->setPreparationTime(currentTime);
						noMovingCargos--;
						SpecialWaitingCargos.enqueue(sc);
						noWaitingCargos++;
					}
					else if (vc)
					{
						vc->setPreparationTime(currentTime);
						noMovingCargos--;
						VipWaitingCargos.enqueue(vc, vc->getpriority());
						noWaitingCargos++;
					}
					c = t->deliveryFailure();
				}
				t->setFinishedChecking(currentTime + t->getMaintance());
				CheckupTrucks.enqueue(t, -(currentTime + t->getMaintance()).toInt());
				c = nullptr;
				failure = true;
			}
			if (c)
			{
				DeliveredCargos.enqueue(c);
				noDeliveredCargos++;
			}

		} while (c);
		if (!failure)
		{
			q.enqueue(t);
		}
		failure = false;
	}

	while (q.dequeue(t))
	{
		MovingTrucks.enqueue(t, -(t->getDeliveryInterval().toInt()));
	}

}

void Company::ExecuteEvent()
{
	if (!Events.isEmpty())
	{
		event* x;
		Events.peek(x);
		while (x && x->getEventTime() == currentTime)
		{
			x->Execute();
			Events.dequeue(x);
			delete x;
			Events.peek(x);
		}
	}

}

bool Company::CheckAvailabletruck(truck*& t, char Type)
{

	if (Type == 'V')
	{
		VipTrucks.peek(t);
		if (t)
			return true;
		return false;
	}
	else if (Type == 'N')
	{
		NormalTrucks.peek(t);
		if (t)
			return true;
		return false;
	}
	else
	{
		SpecialTrucks.peek(t);
		if (t)
			return true;
		return false;
	}
	return false;
}
int Company::GetAutoPromotionLimit()
{
	return AutoPromotion;
}

void Company::AddToWaitingCargos(cargo* c)
{
	if (!c)
		return;
	noWaitingCargos++;
	NormalCargo* nc = dynamic_cast<NormalCargo*>(c);
	SpecialCargo* sc = dynamic_cast<SpecialCargo*>(c);
	vipCargo* vc = dynamic_cast<vipCargo*>(c);
	if (nc)
	{
		NCargosCount++;
		CargosCount++;
		NormalWaitingCargos.enqueue(nc);
	}
	else if (sc)
	{
		SCargosCount++;
		CargosCount++;
		SpecialWaitingCargos.enqueue(sc);
	}
	else if (vc)
	{
		VCargosCount++;
		CargosCount++;
		VipWaitingCargos.enqueue(vc, (int)(vc->getpriority()));
	}
}

void Company::AddToLoadingTrucks(truck* t, int n)
{
	LoadingTrucks.enqueue(t, n);
}


void Company::AddToMovingTrucks(truck* t, int n)
{
	MovingTrucks.enqueue(t, n);
}
void Company::AddToTrucksCheckup(truck* t, int n)
{
	CheckupTrucks.enqueue(t, n);
}

bool Company::check()
{

	if (mode == 'c')
	{
		closeCompany();
		return false;
	}
	return isOpen();
}

bool Company::isOpen()
{
	return !Events.isEmpty() || CargosCount != noDeliveredCargos;
}
void Company::closeCompany()
{
	while (isOpen())
	{
		IncrementCurrentHour();
	}
	ui->printSilentMode();
}


void Company::setMode()
{
	mode = ui->charcterSelectMode();
}

void Company::AssignTruckToCargo(truck* t, cargo* c)
{
	// needs revision 
	t->setMovingTime(c->getMovingTime());
	t->decrementJourniesleft();
	c->setassociated(t);
}


void Company::MoveTruckFromLoadingToMoving()
{
	truck* t;
	LoadingTrucks.peek(t);
	if (!t)
		return;
	while (t && t->getMovingTime() == currentTime)
	{
		t->setMovingWaitingTimeCargos(currentTime);
		t->setDeliveryInterval();
		MovingTrucks.enqueue(t, -(t->getDeliveryInterval().toInt()));
		t->incrementJournies();
		noMovingCargos += t->getNoOfCargos();
		LoadingTrucks.dequeue(t);
		switch (t->getTruckType())
		{
		case 'n':
			isNormalTruckLoading = 0;
			break;
		case 's':
			isSpecialTruckLoading = 0;
			break;
		case 'v':
			isVipTruckLoading = 0;
			break;
		};
		LoadingTrucks.peek(t);
	}
}
void Company::MoveTruckFromMovingToCheckupOrWaiting()
{
	truck* t = nullptr;
	MovingTrucks.peek(t);
	while (t && currentTime == t->getDeliveryInterval())
	{
		if (t->getJourneysLeft() == journeyBeforeCheck)
		{
			int x = -((currentTime + t->getMaintance()).toInt());
			CheckupTrucks.enqueue(t, x);
			t->setFinishedChecking(currentTime + t->getMaintance());
		}
		else
		{
			if (!t->getNight())
			{
				if (t->getTruckType() == 'n')
					NormalTrucks.enqueue(t,t->getPriority());
				else if (t->getTruckType() == 's')
					SpecialTrucks.enqueue(t, t->getPriority());
				else
					VipTrucks.enqueue(t, t->getPriority());
			}
			else
			{
				if (t->getTruckType() == 'n')
					NightNormalTrucks.enqueue(t, t->getPriority());
				else if (t->getTruckType() == 's')
					NightSpecialTrucks.enqueue(t, t->getPriority());
				else
					NightVipTrucks.enqueue(t, t->getPriority());
			}
		}
		t->setSumOfLoadingTimes(0);
		t->resetMaxDelivaryDistance();
		MovingTrucks.dequeue(t);
		MovingTrucks.peek(t);
	}
}

void Company::MoveTruckFromMovingTonReguarMaintance()
{
	truck* t = nullptr;
	MovingTrucks.peek(t);
	while (t && t->getDistanceBeforeUnRegulerChechUp() >= 1000 && t->getDeliveryInterval() == currentTime)
	{

		if (t->getTruckType() == 'n')
			MaintanceForSomeReasons_Normal.enqueue(t);
		else if (t->getTruckType() == 's')
			MaintanceForSomeReasons_Special.enqueue(t);
		else
			MaintanceForSomeReasons_Vip.enqueue(t);

		t->setFinishedChecking(currentTime + t->getMaintance());
		t->resetMaxDelivaryDistance();
		t->resetdistanceBeforeUnRegulerChechUp();
		t->setSumOfLoadingTimes(0);
		MovingTrucks.dequeue(t);
		MovingTrucks.peek(t);
	}
}

void Company::MoveTruckFromCheckupToEmpty()
{
	truck* t = nullptr;
	CheckupTrucks.peek(t);
	while (t && currentTime == t->getFinishedChecking())
	{
		CheckupTrucks.dequeue(t);
		if (t->getTruckType() == 'n')
			NormalTrucks.enqueue(t, t->getPriority());
		else if (t->getTruckType() == 's')
			SpecialTrucks.enqueue(t, t->getPriority());
		else
			VipTrucks.enqueue(t, t->getPriority());
		t->setJourneysLeft(0);
		CheckupTrucks.peek(t);
	}

}
void Company::MoveTruckFromUnReguarMaintanceToEmpty()
{
	truck* t = nullptr;
	MaintanceForSomeReasons_Normal.peek(t);
	while (t && currentTime == t->getFinishedChecking())
	{
		MaintanceForSomeReasons_Normal.dequeue(t);
		if (t->getTruckType() == 'n')
			NormalTrucks.enqueue(t, t->getPriority());
		else if (t->getTruckType() == 's')
			SpecialTrucks.enqueue(t, t->getPriority());
		else
			VipTrucks.enqueue(t, t->getPriority());
		t->setJourneysLeft(0);
		MaintanceForSomeReasons_Normal.peek(t);
	}

	t = nullptr;
	MaintanceForSomeReasons_Special.peek(t);
	while (t && currentTime == t->getFinishedChecking())
	{
		MaintanceForSomeReasons_Special.dequeue(t);
		if (t->getTruckType() == 'n')
			NormalTrucks.enqueue(t, t->getPriority());
		else if (t->getTruckType() == 's')
			SpecialTrucks.enqueue(t, t->getPriority());
		else
			VipTrucks.enqueue(t, t->getPriority());
		t->setJourneysLeft(0);
		MaintanceForSomeReasons_Special.peek(t);
	}

	t = nullptr;
	MaintanceForSomeReasons_Vip.peek(t);
	while (t && currentTime == t->getFinishedChecking())
	{
		MaintanceForSomeReasons_Vip.dequeue(t);
		if (t->getTruckType() == 'n')
			NormalTrucks.enqueue(t, t->getPriority());
		else if (t->getTruckType() == 's')
			SpecialTrucks.enqueue(t, t->getPriority());
		else
			VipTrucks.enqueue(t, t->getPriority());
		t->setJourneysLeft(0);
		MaintanceForSomeReasons_Vip.peek(t);
	}

}

void Company::printTrucksData()
{

	//Printing trucks data
	int NOT = noOfNT + noOfST + noOfVT;
	outputFile << "Trucks: " << NOT << " [N: " << noOfNT << ", S: " << noOfST << ", V: " << noOfVT << "]\n";
}
void Company::printCargosData()
{
	//Printing Cargos data
	outputFile << "Cargos: " << CargosCount << " [N: " << NCargosCount << ", S: " << SCargosCount << ", V: " << VCargosCount << "]\n";
}

void Company::LoadCargosToTruck(PriQ<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	truck* t = nullptr;
	vipCargo* nc;
	cList.peek(nc);
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);

		if (t->getCapcity() <= cList.getCount() && !isLoading)
		{
			int max = getMaxVipLoadingTime(t->getCapcity());

			if (isWorkingTime(currentTime + max))
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < t->getCapcity(); i++)
				{
					cList.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
				isLoading = 1;
				t->incrementSumOfLoading(max);
				qTruck.dequeue(t);
				if (Mainta != 0)
					t->setSpeed(t->getSpeed() / 2);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
				systemNeed = false;
			}
		}
	}

}

void Company::LoadCargosToTruck(Queue<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	truck* t = nullptr;
	vipCargo* nc;
	cList.peek(nc);
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);

		if (t->getCapcity() <= cList.getCount() && !isLoading)
		{
			int max = getMaxVipLoadingTime(t->getCapcity());

			if (isWorkingTime(currentTime + max))
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < t->getCapcity(); i++)
				{
					cList.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
				isLoading = 1;
				t->incrementSumOfLoading(max);
				qTruck.dequeue(t);
				if (Mainta != 0)
					t->setSpeed(t->getSpeed() / 2);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
				systemNeed = false;
			}
		}
	}

}

void Company::LoadCargosToTruck_MaxW(PriQ<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	vipCargo* nc;
	cList.peek(nc);
	truck* t;
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);
		if (currentTime.toInt() >= (nc->getPreTime() + maxWaiting).toInt())
		{

			int max = getMaxVipLoadingTime(cList.getCount());

			if (isWorkingTime(currentTime + max))
			{
				//  while (!cList.isEmpty() && t->getCapcity() < i)
				for (int i = 0; i < t->getCapcity() && !cList.isEmpty(); i++)
				{
					t->setMovingTime(currentTime + max);
					cList.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
				isLoading = 1;
				qTruck.dequeue(t);
				if (Mainta != 0)
					t->setSpeed(t->getSpeed() / 2);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
				systemNeed = false;

			}
		}
	}
}

void Company::LoadCargosToTruck_MaxW(Queue<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	vipCargo* nc;
	cList.peek(nc);
	truck* t;
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);
		if (currentTime.toInt() >= (nc->getPreTime() + maxWaiting).toInt())
		{

			int max = getMaxVipLoadingTime(cList.getCount());

			if (isWorkingTime(currentTime + max))
			{
				//  while (!cList.isEmpty() && t->getCapcity() < i)
				for (int i = 0; i < t->getCapcity() && !cList.isEmpty(); i++)
				{
					t->setMovingTime(currentTime + max);
					cList.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
				isLoading = 1;
				qTruck.dequeue(t);
				if (Mainta != 0)
					t->setSpeed(t->getSpeed() / 2);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
				systemNeed = false;

			}
		}
	}

}

void Company::print()
{
	// calling all print functions of UI
	if (mode == 'a')
	{
		ui->printInteractiveMode(currentTime, NormalWaitingCargos, SpecialWaitingCargos, VipWaitingCargos,
			LoadingTrucks, NormalTrucks, SpecialTrucks, VipTrucks, NightNormalTrucks, NightSpecialTrucks, NightVipTrucks,
			CheckupTrucks, MovingTrucks, noMovingCargos, noWaitingCargos, DeliveredCargos, MaintanceForSomeReasons_Normal,
			MaintanceForSomeReasons_Special, MaintanceForSomeReasons_Vip, noDeliveredCargos);
		ui->promptUser();
	}
	else if (mode == 'b')
		ui->printStepbyStep(currentTime, NormalWaitingCargos, SpecialWaitingCargos, VipWaitingCargos,
			LoadingTrucks, NormalTrucks, SpecialTrucks, VipTrucks, NightNormalTrucks, NightSpecialTrucks, NightVipTrucks,
			CheckupTrucks, MovingTrucks, noMovingCargos, noWaitingCargos, DeliveredCargos, MaintanceForSomeReasons_Normal,
			MaintanceForSomeReasons_Special, MaintanceForSomeReasons_Vip, noDeliveredCargos);
	else if (mode == 'c')
		ui->printSilentMode();
}
void Company::PrintOutput()
{
	//Setting the file
	outputFile << "CDT\tID\tPT\tWT\tTID\n";
	//Collecting statistics and printing the data
	getStatistics();
	outputFile.close();
}
void Company::getStatistics()
{
	cargo* CargoDelivered;
	truck* TruckLoadingORDelivering;
	Time CargoAvgWait;
	int CargoToTWait = 0;
	int TruckTotActive = 0;
	int noMovingTrucks = 0;
	int noLoadingTrucks = 0;
	float TruckToTUtilization = 0;
	int TrucksCount = noOfNT + noOfST + noOfVT;
	while (!DeliveredCargos.isEmpty())
	{
		DeliveredCargos.dequeue(CargoDelivered);
		outputFile << CargoDelivered->getCargoDeliveryTime().getday() << ":" << CargoDelivered->getCargoDeliveryTime().gethour() << "\t";
		outputFile << CargoDelivered->getId() << "\t";
		outputFile << CargoDelivered->getPreTime().getday() << ":" << CargoDelivered->getPreTime().gethour() << "\t";
		outputFile << CargoDelivered->getWaitingTime().getday() << ":" << CargoDelivered->getWaitingTime().gethour() << "\t";
		outputFile << CargoDelivered->getassociated()->getID() << "\t";
		CargoToTWait += CargoDelivered->getWaitingTime().toInt();
		delete CargoDelivered;
		CargoDelivered = nullptr;
		outputFile << '\n';
	}

	outputFile << "-----------------------------------------------------------\n";
	outputFile << "-----------------------------------------------------------\n";
	printCargosData();
	if (noDeliveredCargos == 0)
	{
		CargoAvgWait = 0;
	}
	else
	{
		Time t;
		CargoAvgWait = t.toTime((float)CargoToTWait / noDeliveredCargos);
	}
	outputFile << "Cargo Avg Wait = " << CargoAvgWait.getday() << " : " << CargoAvgWait.gethour() << "\n";
	if (autoPromotionLimit > 0 && NCargosCount!=0)
	{

		outputFile << "Auto-promoted Cargos: " << (float)noPromotedCargos * 100 / (float)(NCargosCount) << '%' << "\n";
	}
	else
	{
		outputFile << "Auto-promoted Cargos: " << "0 %" << "\n";
	}
	printTrucksData();
	//avg utilization
	while (!NormalTrucks.isEmpty())
	{
		NormalTrucks.dequeue(TruckLoadingORDelivering);
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		float TruckUtilization;
		if (N != 0)
			TruckUtilization = TDC / (TC * N) * (TAT / TSIM);
		else
			TruckUtilization = 0;
		TruckTotActive += TAT;
		TruckToTUtilization += TruckUtilization;
		delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}
	while (!SpecialTrucks.isEmpty())
	{
		SpecialTrucks.dequeue(TruckLoadingORDelivering);
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		float TruckUtilization;
		if (N != 0)
			TruckUtilization = TDC / (TC * N) * (TAT / TSIM);
		else
			TruckUtilization = 0;
		TruckTotActive += TAT;
		TruckToTUtilization += TruckUtilization;
		delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}
	while (!VipTrucks.isEmpty())
	{
		VipTrucks.dequeue(TruckLoadingORDelivering);
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		float TruckUtilization;
		if (N != 0)
			TruckUtilization = TDC / (TC * N) * (TAT / TSIM);
		else
			TruckUtilization = 0;
		TruckTotActive += TAT;
		TruckToTUtilization += TruckUtilization;
		delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}

	while (!CheckupTrucks.isEmpty())
	{
		CheckupTrucks.dequeue(TruckLoadingORDelivering);
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		float TruckUtilization;
		if (N != 0)
			TruckUtilization = TDC / (TC * N) * (TAT / TSIM);
		else
			TruckUtilization = 0;
		TruckTotActive += TAT;
		TruckToTUtilization += TruckUtilization;
		delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}
	while (!MovingTrucks.isEmpty())
	{
		MovingTrucks.dequeue(TruckLoadingORDelivering);
		float TruckUtilization;
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();;
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		if (N != 0)
			TruckUtilization = TDC / ((float)TC * N) * ((float)TAT / TSIM);
		else
			TruckUtilization = 0;
		TruckToTUtilization += TruckUtilization;
		TruckTotActive += TAT;
		//delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}

	outputFile << "Avg Active Time : " << round(((float(TruckTotActive)) / (TrucksCount * currentTime.toInt())) * 100) << " %" << "\n";
	outputFile << "Avg Utilization : " << round(((float)TruckToTUtilization) / (TrucksCount) * 100) << " %"  "\n";

}

Company::~Company()
{
	Events.~Queue();
	LoadingCargos.~PriQ();
	MovingCargos.~PriQ();
	DeliveredCargos.~Queue();
	destroyTrucks();
	delete ui;
}
void Company::destroyTrucks()
{
	truck* x;
	while (NormalTrucks.dequeue(x))
		delete x;
	while (SpecialTrucks.dequeue(x))
		delete x;
	while (VipTrucks.dequeue(x))
		delete x;
	while (NightNormalTrucks.dequeue(x))
		delete x;
	while (NightSpecialTrucks.dequeue(x))
		delete x;
	while (NightVipTrucks.dequeue(x))
		delete x;
	while (MovingTrucks.dequeue(x))
		delete x;
	while (CheckupTrucks.dequeue(x))
		delete x;
	while (MaintanceForSomeReasons_Normal.dequeue(x))
		delete x;
	while (MaintanceForSomeReasons_Special.dequeue(x))
		delete x;
	while (MaintanceForSomeReasons_Vip.dequeue(x))
		delete x;
}
void Company::AutoPromotinFunc()
{
	NormalCargo* nc;

	NormalWaitingCargos.peek(nc);

	while (nc && currentTime.toInt() - nc->getPreTime().toInt() == autoPromotionLimit * 24)
	{
		NormalWaitingCargos.dequeue(nc);
		vipCargo* vc = new vipCargo(nc);
		VipWaitingCargos.enqueue(vc, ((int)(vc->getpriority())));
		noPromotedCargos++;
		delete nc;
		NormalWaitingCargos.peek(nc);
	}
}



void Company::AssignNormalCargo_MaxW()
{
	bool systemNeed = true;
	if (NormalWaitingCargos.isEmpty())
		return;
	if (!isWorkingTime())
	{
		LoadCargosToTruck_MaxW(NightNormalTrucks, NormalWaitingCargos, systemNeed, isNormalTruckLoading);
		LoadCargosToTruck_MaxW(NightVipTrucks, NormalWaitingCargos, systemNeed, isVipTruckLoading);
		return;
	}
	LoadCargosToTruck_MaxW(NormalTrucks, NormalWaitingCargos, systemNeed, isNormalTruckLoading);
	LoadCargosToTruck_MaxW(NightNormalTrucks, NormalWaitingCargos, systemNeed, isNormalTruckLoading);
	LoadCargosToTruck_MaxW(VipTrucks, NormalWaitingCargos, systemNeed, isVipTruckLoading);
	LoadCargosToTruck_MaxW(NightVipTrucks, NormalWaitingCargos, systemNeed, isVipTruckLoading);

	if (systemNeed)
	{

		LoadCargosToTruck_MaxW(MaintanceForSomeReasons_Normal, NormalWaitingCargos, systemNeed, isNormalTruckLoading, 5);

		LoadCargosToTruck_MaxW(MaintanceForSomeReasons_Vip, NormalWaitingCargos, systemNeed, isVipTruckLoading, 5);
	}
}

void Company::AssignSpecialCargo_MaxW()
{
	bool systemNeed = true;

	if (SpecialWaitingCargos.isEmpty())
		return;
	if (!isWorkingTime())
	{
		LoadCargosToTruck_MaxW(NightSpecialTrucks, SpecialWaitingCargos, systemNeed, isSpecialTruckLoading);
		return;
	}
	LoadCargosToTruck_MaxW(SpecialTrucks, SpecialWaitingCargos, systemNeed, isSpecialTruckLoading);
	LoadCargosToTruck_MaxW(NightSpecialTrucks, SpecialWaitingCargos, systemNeed, isSpecialTruckLoading);

	if (systemNeed)
	{
		LoadCargosToTruck_MaxW(MaintanceForSomeReasons_Special, SpecialWaitingCargos, systemNeed, isSpecialTruckLoading, 5);
	}
}
void Company::AssignVipCargo_MaxW()
{
	bool SystemNeed = true;

	if (!isWorkingTime())
	{
		LoadCargosToTruck_MaxW(NightVipTrucks, VipWaitingCargos, SystemNeed, isVipTruckLoading);
		LoadCargosToTruck_MaxW(NightNormalTrucks, VipWaitingCargos, SystemNeed, isNormalTruckLoading);
		LoadCargosToTruck_MaxW(NightSpecialTrucks, VipWaitingCargos, SystemNeed, isSpecialTruckLoading);
		return;
	}
	LoadCargosToTruck_MaxW(VipTrucks, VipWaitingCargos, SystemNeed, isVipTruckLoading);
	LoadCargosToTruck_MaxW(NightVipTrucks, VipWaitingCargos, SystemNeed, isVipTruckLoading);
	LoadCargosToTruck_MaxW(NormalTrucks, VipWaitingCargos, SystemNeed, isNormalTruckLoading);
	LoadCargosToTruck_MaxW(NightNormalTrucks, VipWaitingCargos, SystemNeed, isNormalTruckLoading);
	LoadCargosToTruck_MaxW(SpecialTrucks, VipWaitingCargos, SystemNeed, isSpecialTruckLoading);
	LoadCargosToTruck_MaxW(NightSpecialTrucks, VipWaitingCargos, SystemNeed, isSpecialTruckLoading);

	if (SystemNeed)
	{
		LoadCargosToTruck_MaxW(MaintanceForSomeReasons_Vip, VipWaitingCargos, SystemNeed, isVipTruckLoading, 5);

		LoadCargosToTruck_MaxW(MaintanceForSomeReasons_Normal, VipWaitingCargos, SystemNeed, isNormalTruckLoading, 5);

		LoadCargosToTruck_MaxW(MaintanceForSomeReasons_Special, VipWaitingCargos, SystemNeed, isSpecialTruckLoading, 5);

	}

}
void Company::AssignNormalCargo()
{

	bool SystemNeed = true;
	if (NormalWaitingCargos.isEmpty())
		return;
	if (!isWorkingTime())
	{
		LoadCargosToTruck(NightNormalTrucks, NormalWaitingCargos, SystemNeed, isNormalTruckLoading);
		LoadCargosToTruck(NightVipTrucks, NormalWaitingCargos, SystemNeed, isNormalTruckLoading);
		return;
	}



	LoadCargosToTruck(NormalTrucks, NormalWaitingCargos, SystemNeed, isNormalTruckLoading);
	LoadCargosToTruck(NightNormalTrucks, NormalWaitingCargos, SystemNeed, isNormalTruckLoading);
	LoadCargosToTruck(VipTrucks, NormalWaitingCargos, SystemNeed, isVipTruckLoading);
	LoadCargosToTruck(NightVipTrucks, NormalWaitingCargos, SystemNeed, isNormalTruckLoading);

	if (SystemNeed)
	{

		LoadCargosToTruck(MaintanceForSomeReasons_Normal, NormalWaitingCargos, SystemNeed, isNormalTruckLoading, 5);

		LoadCargosToTruck(MaintanceForSomeReasons_Vip, NormalWaitingCargos, SystemNeed, isVipTruckLoading, 5);
	}
}

void Company::AssignSpecialCargo()
{
	bool SystemNeed = true;
	if (SpecialWaitingCargos.isEmpty())
		return;
	if (!isWorkingTime())
	{
		LoadCargosToTruck(NightSpecialTrucks, SpecialWaitingCargos, SystemNeed, isSpecialTruckLoading);
		return;
	}
	LoadCargosToTruck(SpecialTrucks, SpecialWaitingCargos, SystemNeed, isSpecialTruckLoading);
	LoadCargosToTruck(NightSpecialTrucks, SpecialWaitingCargos, SystemNeed, isSpecialTruckLoading);

	if (SystemNeed)
	{
		LoadCargosToTruck(MaintanceForSomeReasons_Special, SpecialWaitingCargos, SystemNeed, isSpecialTruckLoading, 5);
	}
}
void Company::AssignVipCargo()
{
	bool SystemNeed = true;
	if (VipWaitingCargos.isEmpty())
		return;
	if (!isWorkingTime())
	{
		LoadCargosToTruck(NightVipTrucks, VipWaitingCargos, SystemNeed, isVipTruckLoading);
		LoadCargosToTruck(NightNormalTrucks, VipWaitingCargos, SystemNeed, isNormalTruckLoading);
		LoadCargosToTruck(NightSpecialTrucks, VipWaitingCargos, SystemNeed, isSpecialTruckLoading);
		return;
	}
	LoadCargosToTruck(VipTrucks, VipWaitingCargos, SystemNeed, isVipTruckLoading);
	LoadCargosToTruck(NightVipTrucks, VipWaitingCargos, SystemNeed, isVipTruckLoading);
	LoadCargosToTruck(NormalTrucks, VipWaitingCargos, SystemNeed, isNormalTruckLoading);
	LoadCargosToTruck(NightNormalTrucks, VipWaitingCargos, SystemNeed, isNormalTruckLoading);
	LoadCargosToTruck(SpecialTrucks, VipWaitingCargos, SystemNeed, isSpecialTruckLoading);
	LoadCargosToTruck(NightSpecialTrucks, VipWaitingCargos, SystemNeed, isSpecialTruckLoading);

	if (SystemNeed)
	{
		LoadCargosToTruck(MaintanceForSomeReasons_Vip, VipWaitingCargos, SystemNeed, isVipTruckLoading, 5);

		LoadCargosToTruck(MaintanceForSomeReasons_Normal, VipWaitingCargos, SystemNeed, isNormalTruckLoading, 5);

		LoadCargosToTruck(MaintanceForSomeReasons_Special, VipWaitingCargos, SystemNeed, isSpecialTruckLoading, 5);

	}
}
