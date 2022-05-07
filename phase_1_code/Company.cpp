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
	if (((currentTime.gethour()) % 5 == 0) && (!NormalWaitingCargos.isEmpty()
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
	}
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

void Company::AddToNormalTrucks(truck* NT, float speed)
{
	if (TrucksCount < maxTrucksCount)// Checking condition to not increase the actual available trucks count more than their max
	{
		TrucksCount++;
		noOfVT++;
	}
	NormalTrucks.enqueue(NT, (int)speed);
}

void Company::AddToSpecialTrucks(truck* ST, float speed)

{
	if (TrucksCount < maxTrucksCount)// Checking condition to not increase the actual available trucks count more than their max
	{
		TrucksCount++;
		noOfST++;
	}
	SpecialTrucks.enqueue(ST, (int)speed);
}

void Company::AddToVipTrucks(truck* VT, float speed)
{

	if (TrucksCount < maxTrucksCount)// Checking condition to not increase the actual available trucks count more than their max
	{
		TrucksCount++;
		noOfVT++;
	}
	VipTrucks.enqueue(VT, (int)speed);
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
	currentTime.setday(0);
	currentTime.sethour(0);
	inputFileName = IFN;
	inputFile.open(inputFileName, ios::in);
	ReadInput();
	ui = new UI();
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
	TrucksCount--;
	noOfVT--;
	return t;
}

truck* Company::RemoveFromSpecialTrucks()
{
	truck* t = NULL;
	SpecialTrucks.dequeue(t);
	TrucksCount--;
	STrucksCount--;
	return t;
}

truck* Company::RemoveFromNormalTrucks()
{
	truck* t = NULL;
	NormalTrucks.dequeue(t);
	TrucksCount--;
	NTrucksCount--;
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
	TrucksCheckup.dequeue(t);
	return t;
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
		while (x->getEventTime() == currentTime)
		{
			x->Execute();
			event* z;
			Events.dequeue(z);
			if (z != x)
			{
				x = z;
			}
			else
			{
				break;
			}
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
	TrucksCheckup.enqueue(t, n);
}

bool Company::check() 
{
	if (mode == 'c')
	{
		ui->printSilentMode();
		return false; // phase 2 no output file is required
	}
	return !Events.isEmpty() || CargosCount != noDeliveredCargos;
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

void Company::MoveTruckFromLoadingToEmpty()
{

}
void Company::MoveTruckFromLoadingToCheckup(truck* t)
{

}
void Company::MoveRoverFromCheckupToEmpty()
{

}
void Company::printTrucksData()
{

	//Printing trucks data
	outputFile << "Trucks: " << TrucksCount << " [N: " << NTrucksCount << ", S: " << STrucksCount << ", V: " << noOfVT << "]\n";
}
void Company::printCargosData()
{
	//Printing Cargos data
	outputFile << "Cargos: " << CargosCount << " [N: " << NCargosCount << ", S: " << SCargosCount << ", V: " << VCargosCount << "]\n";
}
void Company::print()
{
	// calling all print functions of UI
	if (mode == 'a')
	{
		ui->printInteractiveMode(currentTime, NormalWaitingCargos, SpecialWaitingCargos, VipWaitingCargos, noWaitingCargos, DeliveredCargos, noDeliveredCargos);
		cout << endl << "Press Enter to Increment 1 hour \n";
		cin.ignore(INT_MAX, '\n');
	}
	else if (mode == 'b')
		ui->printStepbyStep(currentTime, NormalWaitingCargos, SpecialWaitingCargos, VipWaitingCargos, noWaitingCargos, DeliveredCargos, noDeliveredCargos);
	else if (mode == 'c')
		ui->printSilentMode();
}
void Company::PrintOutput()
{
	//Opening the output file
	outputFile.open("Output.txt", ios::out);
	//Setting the file
	outputFile << "CDT\tID\tPT\tWT\tTID\n";
	//Collecting statistics and printing the data
	getStatistics();

}
void Company::getStatistics()
{
	cargo* c;

	// while loop to get the rest of data
	// 	   any avg is divided by the number
		//Printing the statistics results
	printCargosData();
	printTrucksData();

}
Company::~Company()
{
	Events.~Queue();
	NormalCargos.~LinkedList();
	vipcargos.~PriQ();
	SpecialCargos.~Queue();
	LoadingCargos.~PriQ();
	MovingCargos.~PriQ();
	DeliveredCargos.~Queue();
	VipTrucks.~PriQ();
	NormalTrucks.~PriQ();
	SpecialTrucks.~PriQ();
	LoadingTrucks.~PriQ();
	MovingTrucks.~PriQ();
	TrucksCheckup.~PriQ();
	delete ui;
}

void Company::AssignVipCargo()
{
	vipCargo* c = nullptr;
	while (vipcargos.peek(c))
	{
		truck* t = nullptr;
		if (!CheckAvailabletruck(t, 'V')) //Check for Vip first
			if (!CheckAvailabletruck(t, 'N')) //If not, check for Normal
				if (!CheckAvailabletruck(t, 'S')) //Finally, check for Special if all of the above are false
					break; //No available truck-->Do not assign
		c->setMovingTime(t->getMovingTime());
		RemoveFromvipCargos();
		// AddToLoadingCargos(c); // what is the priority
		// how can i update the status
		AssignTruckToCargo(t, c);
		MoveTruckFromEmptyToLoading(t);
	}

}
void Company::AssignNormalCargo()
{
	NormalCargo* c = nullptr;
	while (!NormalCargos.isEmpty())
	{
		c = NormalCargos.getEntry(1);
		truck* t = nullptr;
		if (!CheckAvailabletruck(t, 'N')) //Check for Normal first
			if (!CheckAvailabletruck(t, 'V')) //If not, check for vip
				break; //No available truck-->Do not assign
		c->setMovingTime(t->getMovingTime());
		RemoveFromNormalCargos();
		// AddToLoadingCargos(c); // what is the priority
		// how can i update the status
		AssignTruckToCargo(t, c);
		MoveTruckFromEmptyToLoading(t);
	}
}
void Company::AssignSpecialCargo()
{
	SpecialCargo* c = nullptr;
	while (SpecialCargos.peek(c))
	{
		truck* t = nullptr;
		if (!CheckAvailabletruck(t, 'S')) //check for Special only
			break; //No available truck-->Do not assign
		c->setMovingTime(t->getMovingTime());
		RemoveFromSpecialCargos();
		// AddToLoadingCargos(c); // what's the priority?
		// how can i update the status
		AssignTruckToCargo(t, c);
		MoveTruckFromEmptyToLoading(t);
	}
}