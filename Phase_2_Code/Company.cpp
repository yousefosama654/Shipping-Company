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
			y = x;
	}
	while (!q.isEmpty())
	{
		q.dequeue(x);
		NormalWaitingCargos.enqueue(x);
	}
	vipCargo* v = new vipCargo(y);
	VipWaitingCargos.enqueue(v, (int)(v->getpriority() * 100));
	noPromotedCargos++;
	//int i = 1;
	//while (NormalCargos.getEntry(i))
	//{
	//	NormalCargo* N_Cargo = NormalCargos.getEntry(i);
	//	int N_CargoID = N_Cargo->getId();
	//	if (N_CargoID == ID)
	//	{
	//		if (!N_Cargo->AutoPromoted())
	//			promotedCount++;
	//		//cargo(int ID, Time Prep, int LD, int dd, int cost);
	//		int LD = N_Cargo->getLoadingTime();
	//		int cost = N_Cargo->getCost();
	//		int dd = N_Cargo->getdeliverydistance();
	//		Time prep = N_Cargo->getPreTime();
	//		Time MT = N_Cargo->getMovingTime();
	//		// still needs sime revision
	//		RemoveFromNormalCargos(i);

	//		vipCargo* c = new vipCargo(N_CargoID, prep, LD, dd, cost);
	//		c->setMovingTime(MT);
	//		AddToVIPCargos(c, c->getpriority());
	//		break;
	//	}
	//	i++;
	//}
}

//void Company::CancelCargo(int ID)
//{
//	/*int i = 1;
//	while (NormalCargos.getEntry(i))
//	{
//		int CargoID = (NormalCargos.getEntry(i))->getId();
//		if (CargoID == ID)
//		{
//			this->RemoveFromNormalCargos(i);
//			break;
//		}
//		i++;
//	}*/
//
//}

void Company::AddToVIPCargos(vipCargo* c, float pri)
{
	pri = c->getpriority();
	vipcargos.enqueue(c, (int)(pri * 100));
	this->VCargosCount++;
	CargosCount++;
}

void Company::IncrementCurrentHour()
{
	currentTime.IncrementHour();
	ExecuteEvent();
	AssignVipCargo();
	AssignNormalCargo();
	AssignSpecialCargo();
	MoveTruckFromLoadingToMoving();                     // the priority here is prop to what
	MoveTruckFromMovingToCheckupOrWaiting();
	MoveRoverFromCheckupToEmpty();
	checkMovingCargos();
	AssignNormalCargo_MaxW();
	AssignSpecialCargo_MaxW();
	AutoPromotinFunc();
	if (mode != 'c')
		print();
	// phase 1 
	/*if (((currentTime.gethour()) % 5 == 0) && (!NormalWaitingCargos.isEmpty()
		|| !VipWaitingCargos.isEmpty() || !SpecialWaitingCargos.isEmpty()))
	{
		NormalCargo* n;
		SpecialCargo* s;
		vipCargo* v;
		NormalWaitingCargos.peek(n);
		SpecialWaitingCargos.peek(s);
		VipWaitingCargos.peek(v);
		int nt = n ? n->getPreTime().toInt() : INT_MAX;
		int st = s ? s->getPreTime().toInt() : INT_MAX;
		int vt = v ? v->getPreTime().toInt() : INT_MAX;
		int m = min(min(nt, st), vt);
		if (m == nt)
		{
			NormalWaitingCargos.dequeue(n);
			DeliveredCargos.enqueue(n);
			noDeliveredCargos++;
			noWaitingCargos--;
		}
		if (m == st)
		{
			SpecialWaitingCargos.dequeue(s);
			DeliveredCargos.enqueue(s);
			noDeliveredCargos++;
			noWaitingCargos--;

		}
		if (m == vt)
		{
			VipWaitingCargos.dequeue(v);
			DeliveredCargos.enqueue(v);
			noDeliveredCargos++;
			noWaitingCargos--;

		}
	}*/
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

void Company::AddToNormalCargos(NormalCargo* c)
{

	NormalCargos.insert(++NCargosCount, c);
	CargosCount++;

}

void Company::AddToSpeacialCargos(SpecialCargo* c)
{
	SpecialCargos.enqueue(c);
	this->SCargosCount++;
	CargosCount++;

}

//void Company::AddToNormalTrucks(truck* NT, float speed)
//{
//	if (TrucksCount < maxTrucksCount)// Checking condition to not increase the actual available trucks count more than their max
//	{
//		TrucksCount++;
//		noOfVT++;
//	}
//	NormalTrucks.enqueue(NT);
//}

//void Company::AddToSpecialTrucks(truck* ST, float speed)
////
////{
////	if (TrucksCount < maxTrucksCount)// Checking condition to not increase the actual available trucks count more than their max
////	{
////		TrucksCount++;
////		noOfST++;
////	}
////	SpecialTrucks.enqueue(ST);
////}

//void Company::AddToVipTrucks(truck* VT, float speed)
//{
//
//	if (TrucksCount < maxTrucksCount)// Checking condition to not increase the actual available trucks count more than their max
//	{
//		TrucksCount++;
//		noOfVT++;
//	}
//	VipTrucks.enqueue(VT);
//}



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
	SpecialCargos.peek(c);
	int max = c->getLoadingTime();
	for (int i = 0; i < cap; i++)
	{
		SpecialCargos.dequeue(c);
		q.enqueue(c);
		if (max < c->getLoadingTime())
			max = c->getLoadingTime();
	}
	while (!SpecialCargos.isEmpty())
	{
		SpecialCargos.dequeue(c);
		q.enqueue(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		SpecialCargos.enqueue(c);
	}

	return max;
}

int Company::getMaxVipLoadingTime(int cap)
{
	if (VipWaitingCargos.isEmpty())
		return 0;
	Queue<vipCargo*> q;
	vipCargo* c;
	vipcargos.peek(c);
	int max = c->getLoadingTime();
	for (int i = 0; i < cap; i++)
	{
		vipcargos.dequeue(c);
		q.enqueue(c);
		if (max < c->getLoadingTime())
			max = c->getLoadingTime();
	}
	while (!vipcargos.isEmpty())
	{
		vipcargos.dequeue(c);
		q.enqueue(c);
	}
	while (!q.isEmpty())
	{
		q.dequeue(c);
		vipcargos.enqueue(c, c->getpriority());
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
	currentTime.setday(0);
	currentTime.sethour(0);
	inputFileName = IFN;
	inputFile.open(inputFileName, ios::in);
	ReadInput();
	ui = new UI();
	InitialiseTrucks();
}

void Company::ReadInput()
{
	if (inputFile.is_open())
	{
		inputFile >> noOfNT >> noOfST >> noOfVT;
		inputFile >> speedOfNT >> speedOfST >> speedOfVT;
		inputFile >> capacityOfNT >> capacityOfST >> capacityOfVT;
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
			CargosCount++;
			switch (CargoType)
			{
				

				
			case 'N':
				NCargosCount++;
				break;
			case 'S':
				SCargosCount++;
				break;
			case 'V':
				VCargosCount++;
				break;
			};
			break;
		}
		case 'X':
		{
			inputFile >> EventTime >> id;
			event* cancel = new cancellationEvent(EventTime, id, this);
			Events.enqueue(cancel);
			CargosCount--;
			NCargosCount--;
			break;
		}
		case 'P':
		{
			inputFile >> EventTime >> id >> extraMoney;
			event* promotion = new promotionEvent(EventTime, id, this, extraMoney);
			Events.enqueue(promotion);
			NCargosCount--;
			VCargosCount++;
			break;
		}
		};
	}
	inputFile.close();
}

void Company::InitialiseTrucks()
{
	//NTrucksCount;
				//STrucksCount;
				//VTrucksCount;
				//TrucksCount;

	
	int last = 0;
	for (int i = 1; i <= noOfNT; i++)
	{
		truck* t = new truck(i, checkDurationNT, speedOfNT, 'n', capacityOfNT);
		NormalTrucks.enqueue(t);
		last = i;
	}
	last++;
	int n = last;
	for (int i = n; i < noOfST + n; i++)
	{
		truck* t = new truck(last + i, checkDurationSP, speedOfST, 's', capacityOfST);
		SpecialTrucks.enqueue(t);
		last = i;
	}
	last++;
	n = last;
	for (int i = n; i < noOfVT + n; i++)
	{
		truck* t = new truck(last + i, checkDurationVT, speedOfVT, 'v', capacityOfVT);
		VipTrucks.enqueue(t);
	}
}

vipCargo* Company::RemoveFromvipCargos()
{
	vipCargo* c = NULL;
	vipcargos.dequeue(c);
	VCargosCount--;
	CargosCount--;
	return c;
}

NormalCargo* Company::RemoveFromNormalCargos(int i)
{
	NormalCargo* c = NormalCargos.getEntry(i);
	if (c)
	{
		NormalCargos.remove(i);
		NCargosCount--;
		CargosCount--;
	}
	return c;

}

SpecialCargo* Company::RemoveFromSpecialCargos()
{
	SpecialCargo* c = NULL;
	SpecialCargos.dequeue(c);
	SCargosCount--;
	CargosCount--;
	return c;
}

truck* Company::RemoveFromVipTrucks()
{
	truck* t = NULL;
	VipTrucks.dequeue(t);
	noOfVT--;
	return t;
}

truck* Company::RemoveFromSpecialTrucks()
{
	truck* t = NULL;
	SpecialTrucks.dequeue(t);
	noOfST--;
	return t;
}

truck* Company::RemoveFromNormalTrucks()
{
	truck* t = NULL;
	NormalTrucks.dequeue(t);
	noOfNT--;
	return t;
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

	while (MovingTrucks.dequeue(t))
	{
		do {
			c = t->DropCargo(currentTime, noMovingCargos);
			if (c)
			{
				DeliveredCargos.enqueue(c);
				noDeliveredCargos++;
			}
		} while (c);
		q.enqueue(t);
	}

	while (q.dequeue(t))
	{
		MovingTrucks.enqueue(t, -(t->getDeliveryInterval().toInt()));
	}

}
bool Company::CheckWaitingCargos()
{
	if (NormalCargos.isEmpty() && vipcargos.isEmpty() && SpecialCargos.isEmpty())
		return true;
	return false;
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
		NormalWaitingCargos.enqueue(nc);
	else if (sc)
		SpecialWaitingCargos.enqueue(sc);
	else
		VipWaitingCargos.enqueue(vc, (int)(vc->getpriority() * 100));
}
void Company::AddToLoadingCargos(cargo* c)
{
	LoadingCargos.enqueue(c, -(c->getLoadingTime()));
}
void Company::AddToMovingCargos(cargo* c)
{
	MovingCargos.enqueue(c, -(c->getCargoDeliveryTime().toInt()));
}
void Company::AddToDeliveredCargos(cargo* c)
{
	noDeliveredCargos++;
	DeliveredCargos.enqueue(c);
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
	return !Events.isEmpty() || CargosCount != noDeliveredCargos;
}

void Company::setMode()
{
	mode = ui->charcterSelectMode();
	if (mode == 'c')
		print();
}

void Company::AssignTruckToCargo(truck* t, cargo* c)
{
	// needs revision 
	t->setMovingTime(c->getMovingTime());
	t->decrementJourniesleft();
	c->setassociated(t);
}

void Company::MoveTruckFromEmptyToLoading(truck* t)
{

	char type = t->getTruckType();
	switch (type) {
	case('N'):
		t = RemoveFromNormalTrucks();
		AddToLoadingTrucks(t, -1);

		break;
	case('V'):
		t = RemoveFromVipTrucks();
		AddToLoadingTrucks(t, -1);						///what's the proirity?
		break;
	case('S'):
		t = RemoveFromSpecialTrucks();
		AddToLoadingTrucks(t, -1);
		break;
	}
}

void Company::MoveTruckFromLoadingToMoving()
{
	truck* t;
	LoadingTrucks.peek(t);
	if (!t)
		return;
	while (t && t->getMovingTime() == currentTime)
	{
		t->setDeliveryInterval();
		MovingTrucks.enqueue(t, -(t->getDeliveryInterval().toInt()));
		t->incrementJournies();
		noMovingCargos += t->getNoOfCargos();
		LoadingTrucks.dequeue(t);
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
			CheckupTrucks.enqueue(t, -(currentTime + t->getMaintance()).toInt());
			t->setFinishedChecking(currentTime + t->getMaintance());
		}
		else
		{
			if (t->getTruckType() == 'n')
				NormalTrucks.enqueue(t);
			else if (t->getTruckType() == 's')
				SpecialTrucks.enqueue(t);
			else
				VipTrucks.enqueue(t);
		}
		MovingTrucks.dequeue(t);
		MovingTrucks.peek(t);
	}
}

void Company::MoveRoverFromCheckupToEmpty()
{
	truck* t = nullptr;
	CheckupTrucks.peek(t);
	while (t && currentTime == t->getFinishedChecking())
	{
		CheckupTrucks.dequeue(t);
		if (t->getTruckType() == 'n')
			NormalTrucks.enqueue(t);
		else if (t->getTruckType() == 's')
			SpecialTrucks.enqueue(t);
		else
			VipTrucks.enqueue(t);
		CheckupTrucks.peek(t);
	}

}
void Company::print()
{
	// calling all print functions of UI
	if (mode == 'a')
	{
		ui->printInteractiveMode(currentTime, NormalWaitingCargos, SpecialWaitingCargos, VipWaitingCargos, LoadingTrucks,
			NormalTrucks, SpecialTrucks, VipTrucks, CheckupTrucks, MovingTrucks, noMovingCargos, noWaitingCargos, DeliveredCargos, noDeliveredCargos);
		cout << endl << "Press Enter to Increment 1 hour \n";
		//cin.ignore(INT_MAX, '\n'); 
	}
	else if (mode == 'b')
		ui->printStepbyStep(currentTime, NormalWaitingCargos, SpecialWaitingCargos, VipWaitingCargos, noWaitingCargos, DeliveredCargos, noDeliveredCargos);
	else if (mode == 'c')
		ui->printSilentMode();
}
void Company::printTrucksData()
{
	//Printing trucks data
	outputFile << "Trucks: " << noOfNT+ noOfST+ noOfVT << " [N: " << noOfNT << ", S: " << noOfST << ", V: " << noOfVT << "]\n";
}
void Company::printCargosData()
{
	//Printing Cargos data
	outputFile << "Cargos: " << CargosCount << " [N: " << NCargosCount << ", S: " << SCargosCount << ", V: " << VCargosCount << "]\n";
}
void Company::PrintOutput()
{
	//Opening the output file
	outputFile.open("Output.txt", ios::out);
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
	int CargoToTWait=0;
	int TruckTotActive=0;
	int noMovingTrucks=0;
	int noLoadingTrucks=0;
	int TruckToTUtilization = 0;
	int TrucksCount = noOfNT + noOfST + noOfVT;
	//TODO We should add to the company in gthe need od ui class
	while (!DeliveredCargos.isEmpty())
	{
		outputFile << "first hello world";
		DeliveredCargos.dequeue(CargoDelivered);
		outputFile << CargoDelivered->getCargoDeliveryTime().getday()<<":"<< CargoDelivered->getCargoDeliveryTime().gethour() << "\t";
		outputFile << CargoDelivered->getId() << "\t";
		outputFile << CargoDelivered->getPreTime().getday()<< ":" << CargoDelivered->getPreTime().gethour() << "\t";
		outputFile << CargoDelivered->getWaitingTime().getday()<< ":" <<CargoDelivered->getWaitingTime().gethour() << "\t";
		outputFile << CargoDelivered->getassociated()->getID() << "\t";
		CargoToTWait += CargoDelivered->getWaitingTime().toInt();
		delete CargoDelivered;
		CargoDelivered = nullptr;
		//TODO check if the program crash
	}

	//outputFile << "second hello world";
	outputFile << "-----------------------------------------------------------\n";
	outputFile << "-----------------------------------------------------------\n";
	printCargosData();
	if (noDeliveredCargos==0)
	{
		CargoAvgWait = 0;
	}
	else
	{
		Time t;
		CargoAvgWait = t.toTime((int(CargoToTWait / noDeliveredCargos)));
	}
	outputFile << "Cargo Avg Wait = " << CargoAvgWait.getday()<<" : "  << CargoAvgWait.gethour() << "\n";
	if (AutoPromotion > 0)
	{
		
		outputFile << "Auto-promoted Cargos: " << (float)noPromotedCargos * 100 / (float)(NCargosCount) << '%' << "\n"; 
	}
	else
	{
		outputFile << "Auto-promoted Cargos: " << "0 %"<<"\n";
	}
	printTrucksData();
	//avg utilization
	while (!LoadingTrucks.isEmpty())
	{
		LoadingTrucks.dequeue(TruckLoadingORDelivering);
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		//TODO class truck
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();
		//TODO with waleed
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		int TruckUtilization = TDC /( TC*N )*(TAT/TSIM) ;
		TruckTotActive += TruckLoadingORDelivering->getSumOfLoading();
		TruckToTUtilization += TruckUtilization;
		//TODO the time of loading in each truck is sum of loading time of cargos 
		delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}
	while (!MovingTrucks.isEmpty())
	{
		MovingTrucks.dequeue(TruckLoadingORDelivering);
		int TruckUtilization;
		int TDC = TruckLoadingORDelivering->getToTCargosDelivered();
		//TODO class truck
		int TC = TruckLoadingORDelivering->getCapcity();
		int TAT = TruckLoadingORDelivering->getActiveTime();;
		//TODO with waleed
		int N = TruckLoadingORDelivering->getNoOfJourneys();
		int TSIM = this->currentTime.toInt();
		if (N = !0)
			TruckUtilization = TDC / (TC * N) * (TAT / TSIM);
		else
			TruckUtilization = 0;
		TruckToTUtilization += TruckUtilization;
		TruckTotActive += TruckLoadingORDelivering->getSumofMovingTimes();
		delete TruckLoadingORDelivering;
		TruckLoadingORDelivering = nullptr;
	}

	outputFile << "Avg Active Time : " <<(float(TruckTotActive)*100)/(TrucksCount) <<"\n";
	outputFile << "Avg Utilization : " << (float(TruckToTUtilization) * 100) / (TrucksCount) << "\n";
	//TODO waleed should use my counters in adding or remove trucks (initialize tucks)
	//TODO we will use Remove and add functions which
	//1-dequeue and --
	//2-enqueue and ++

}
Company::~Company()
{
	Events.~Queue();
	NormalCargos.~LinkedList();
	SpecialCargos.~Queue();
	vipcargos.~PriQ();
	LoadingCargos.~PriQ();
	MovingCargos.~PriQ();
	DeliveredCargos.~Queue();
	VipTrucks.~Queue();
	NormalTrucks.~Queue();
	SpecialTrucks.~Queue();
	LoadingTrucks.~PriQ();
	MovingTrucks.~PriQ();
	CheckupTrucks.~PriQ();
	delete ui;
}


void Company::AssignNormalCargo()
{
	truck* t = nullptr;
	NormalCargo* nc;
	if (!isWorkingTime() || NormalWaitingCargos.isEmpty())
		return;
	
	if (!NormalTrucks.isEmpty())
	{
		NormalTrucks.peek(t);
		
		if (t->getCapcity() <= NormalWaitingCargos.getCount())
		{
			int max = getMaxNormalLoadingTime(capacityOfNT);
			if (isWorkingTime(currentTime + max))
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < capacityOfNT; i++)
				{
					NormalWaitingCargos.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
				t->setSumOfLoading(max);
				NormalTrucks.dequeue(t);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
			}
		}
	}
	else if (!VipTrucks.isEmpty())
	{
		VipTrucks.peek(t);
		if (t->getCapcity() <= NormalWaitingCargos.getCount())
		{
			int max = getMaxVipLoadingTime(capacityOfVT);
			if (isWorkingTime(currentTime + max))
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < capacityOfVT; i++)
				{
					NormalWaitingCargos.dequeue(nc);
					noWaitingCargos--;

					t->assignCargo(nc);
				}
				t->setSumOfLoading(max);
				VipTrucks.dequeue(t);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
			}
		}
	}

	//while (!NormalCargos.isEmpty())
	//{	
	//	c = NormalCargos.getEntry(1);
	//	truck* t = nullptr;
	//	if (!CheckAvailabletruck(t, 'N')) //Check for Normal first
	//		if (!CheckAvailabletruck(t, 'V')) //If not, check for vip
	//			break; //No available truck-->Do not assign
	//	c->setMovingTime(t->getMovingTime());
	//	RemoveFromNormalCargos();
	//	// AddToLoadingCargos(c); // what is the priority
	//	// how can i update the status
	//	AssignTruckToCargo(t, c);
	//	MoveTruckFromEmptyToLoading(t);
	//}
}

void Company::AssignNormalCargo_MaxW()
{
	truck* t = nullptr;
	NormalCargo* nc;
	NormalWaitingCargos.peek(nc);
	
	if (!isWorkingTime() || NormalWaitingCargos.isEmpty())
		return;

	if (!NormalTrucks.isEmpty())
	{
		NormalTrucks.peek(t);
		if (currentTime.toInt() == (nc->getPreTime() + maxWaiting).toInt())
		{
			int max = getMaxNormalLoadingTime(NormalWaitingCargos.getCount());

			while (!NormalWaitingCargos.isEmpty())
			{
				if (isWorkingTime(currentTime + max))
				{
					t->setMovingTime(currentTime + max);
					NormalWaitingCargos.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
			}
			t->setSumOfLoading(max);
			NormalTrucks.dequeue(t);
			LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
		}
	}
	else if (!VipTrucks.isEmpty())
	{
		VipTrucks.peek(t);

		if (currentTime.toInt() == (nc->getPreTime() + maxWaiting).toInt())
		{
			int max = getMaxNormalLoadingTime(NormalWaitingCargos.getCount());

			while (!NormalWaitingCargos.isEmpty())
			{
				if (isWorkingTime(currentTime + max))
				{
					t->setMovingTime(currentTime + max);
					NormalWaitingCargos.dequeue(nc);
					noWaitingCargos--;
					t->assignCargo(nc);
				}
			}
			NormalTrucks.dequeue(t);
			LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
		}
	}
}

void Company::AssignSpecialCargo_MaxW()
{
	truck* t = nullptr;
	SpecialCargo* sc;
	SpecialWaitingCargos.peek(sc);

	if (!isWorkingTime() || SpecialWaitingCargos.isEmpty())
		return;

	if (!SpecialTrucks.isEmpty())
	{
		SpecialTrucks.peek(t);
		if (currentTime.toInt() == (sc->getPreTime() + maxWaiting).toInt())
		{
			int max = getMaxSpecialLoadingTime(SpecialWaitingCargos.getCount());

			while (!SpecialWaitingCargos.isEmpty())
			{
				if (isWorkingTime(currentTime + max))
				{
					t->setMovingTime(currentTime + max);
					SpecialWaitingCargos.dequeue(sc);
					noWaitingCargos--;
					t->assignCargo(sc);
				}
			}
			t->setSumOfLoading(max);
			SpecialTrucks.dequeue(t);
			LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
		}
	}
}

void Company::AutoPromotinFunc()
{
	NormalCargo* nc;

	NormalWaitingCargos.peek(nc);

	while (nc && currentTime.toInt() - nc->getPreTime().toInt() == autoPromotionLimit * 24)
	{
		NormalWaitingCargos.dequeue(nc);
		vipCargo* vc = new vipCargo(nc);
		VipWaitingCargos.enqueue(vc,((int) (vc->getpriority() * 100)));
		delete nc;
		NormalWaitingCargos.peek(nc);
		noPromotedCargos++;
		// TODO what is the difference between AutoPromotinFunc and promote cargo
		// TODO we must mke deletion after the deqeue like malik in line 1017
		// TODO why didn't malek use promote cargo function
	
	}
}
void Company::AssignSpecialCargo()
{
	truck* t = nullptr;
	SpecialCargo* nc;
	if (!isWorkingTime() || SpecialWaitingCargos.isEmpty());
	return;
	if (!SpecialTrucks.isEmpty())
	{
		SpecialTrucks.peek(t);
		if (t->getCapcity() <= SpecialWaitingCargos.getCount())
		{
			int max = getMaxSpecialLoadingTime(capacityOfST);
			if (isWorkingTime(currentTime + max))
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < capacityOfST; i++)
				{
					SpecialWaitingCargos.dequeue(nc);
					noWaitingCargos--;

					t->assignCargo(nc);
				}
				t->setSumOfLoading(max);
				SpecialTrucks.dequeue(t);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
			}
		}
	}

	//SpecialCargo* c = nullptr;
	//while (SpecialCargos.peek(c))
	//{
	//	truck* t = nullptr;
	//	if (!CheckAvailabletruck(t, 'S')) //check for Special only
	//		break; //No available truck-->Do not assign
	//	c->setMovingTime(t->getMovingTime());
	//	RemoveFromSpecialCargos();
	//	// AddToLoadingCargos(c); // what's the priority?
	//	// how can i update the status
	//	AssignTruckToCargo(t, c);
	//	MoveTruckFromEmptyToLoading(t);
	//}
}
void Company::AssignVipCargo()
{
	truck* t = nullptr;
	vipCargo* nc;
	if (!isWorkingTime() || VipWaitingCargos.isEmpty())
		return;
	if (!VipTrucks.isEmpty())
	{
		VipTrucks.peek(t);
		if (t->getCapcity() <= VipWaitingCargos.getCount())
		{
			int max = getMaxVipLoadingTime(capacityOfVT);
			if (max + currentTime.gethour() >= 5)
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < capacityOfVT; i++)
				{
					VipWaitingCargos.dequeue(nc);
					noWaitingCargos--;

					t->assignCargo(nc);
				}
				t->setSumOfLoading(max);
				VipTrucks.dequeue(t);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
			}
		}
	}
	else if (!NormalTrucks.isEmpty())
	{
		NormalTrucks.peek(t);
		if (t->getCapcity() <= VipWaitingCargos.getCount())
		{
			int max = getMaxVipLoadingTime(capacityOfNT);
			if (max + currentTime.gethour() >= 5)
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < capacityOfNT; i++)
				{
					VipWaitingCargos.dequeue(nc);
					noWaitingCargos--;

					t->assignCargo(nc);
				}
				t->setSumOfLoading(max);
				NormalTrucks.dequeue(t);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
			}
		}
	}
	else if (!SpecialTrucks.isEmpty())
	{
		SpecialTrucks.peek(t);
		if (t->getCapcity() <= SpecialWaitingCargos.getCount())
		{
			int max = getMaxVipLoadingTime(capacityOfST);
			if (max + currentTime.gethour() >= 5)
			{
				t->setMovingTime(currentTime + max);
				for (int i = 0; i < capacityOfST; i++)
				{
					VipWaitingCargos.dequeue(nc);
					noWaitingCargos--;

					t->assignCargo(nc);
				}
				t->setSumOfLoading(max);
				SpecialTrucks.dequeue(t);
				LoadingTrucks.enqueue(t, -(currentTime + max).toInt());
			}
		}
	}
	//vipCargo* c = nullptr;
	//while (vipcargos.peek(c))
	//{
	//	truck* t = nullptr;
	//	if (!CheckAvailabletruck(t, 'V')) //Check for Vip first
	//		if (!CheckAvailabletruck(t, 'N')) //If not, check for Normal
	//			if (!CheckAvailabletruck(t, 'S')) //Finally, check for Special if all of the above are false
	//				break; //No available truck-->Do not assign
	//	c->setMovingTime(t->getMovingTime());
	//	RemoveFromvipCargos();
	//	// AddToLoadingCargos(c); // what is the priority
	//	// how can i update the status
	//	AssignTruckToCargo(t, c);
	//	MoveTruckFromEmptyToLoading(t);
	//}

}