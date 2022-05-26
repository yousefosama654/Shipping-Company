#pragma once
#include <iostream>
#include "NormalCargo.h"
#include "SpecialCargo.h"
#include "vipCargo.h"
#include <fstream>
#include "PriQ.h"
#include "queue.h"
#include "LinkedList.h"
#include "UI.h"
#include "event.h"
#include "Status.h"
#include "truck.h"
#include <math.h>
#include"queue.h"
using namespace std;
class UI;
class Company
{
	// UI parameters 
	string inputFileName;
	string outputFileName;
	ifstream inputFile;
	ofstream outputFile;
	// number of trucks
	int noOfNT;
	int noOfST;
	int noOfVT;
	// speeds
	int speedOfNT;
	int speedOfST;
	int speedOfVT;
	// capacities
	int capacityOfNT;
	int capacityOfST;
	int capacityOfVT;

	// checkup durations
	int checkDurationNT;
	int checkDurationSP;
	int checkDurationVT;

	// journeys
	int journeyBeforeCheck;

	// auto promotion limit
	int autoPromotionLimit;
	// maximum waiting period 
	int maxWaiting;
	// no of events
	int numberOfEvents;

	int TrucksCount;
	int maxTrucksCount;
	int promotedCount;
	int CargosCount;

	int NCargosCount;
	int SCargosCount;
	int VCargosCount;

	int NTrucksCount;
	int STrucksCount;
	int VTrucksCount;

	int noNightNormalTrucks;
	int noNightSpecialTrucks;
	int noNightVipTrucks;



	int noWaitingCargos;
	int noMovingCargos;
	int noDeliveredCargos;
	// used in cargo promotion 
	int AutoPromotion;
	int noPromotedCargos;

	bool isNormalTruckLoading;
	bool isSpecialTruckLoading;
	bool isVipTruckLoading;
	// program mode (interactive | silent | step by step)
	char mode;


	//Events
	Queue<event*>Events;

	// cargos type
	Queue<NormalCargo*> NormalWaitingCargos;
	Queue<SpecialCargo*> SpecialWaitingCargos;
	PriQ<vipCargo*> VipWaitingCargos;

	PriQ<cargo*> LoadingCargos;
	PriQ<cargo*> MovingCargos;
	Queue<cargo*> DeliveredCargos;

	PriQ<truck*> NormalTrucks;
	PriQ<truck*> VipTrucks;
	PriQ<truck*> SpecialTrucks;

	PriQ<truck*> NightNormalTrucks;
	PriQ<truck*> NightSpecialTrucks;
	PriQ<truck*> NightVipTrucks;

	Queue<int> speed; // speed for each truck (bonus)
	Queue<int> capacity; // capacity for each truck (bonus)


	PriQ<truck*> LoadingTrucks;
	PriQ<truck*> MovingTrucks;
	PriQ<truck*> CheckupTrucks;

	// Bonus
	Queue<truck*> MaintanceForSomeReasons_Normal;
	Queue<truck*> MaintanceForSomeReasons_Special;
	Queue<truck*> MaintanceForSomeReasons_Vip;

	//UI 
	UI* ui;

	//Current Day
	Time currentTime;


	int getMaxNormalLoadingTime(int);
	int getMaxSpecialLoadingTime(int);
	int getMaxVipLoadingTime(int);
	void ReadInput(); // reads input from file 
	void initTrucks();


	// Current hour
	int getCurrentHour();
	void IncrementCurrentDay();
	int getCurrentday();
	bool isWorkingTime();
	bool isWorkingTime(Time);

	// Add TO

	// Trucks 
	void AddToLoadingTrucks(truck* t, int n);
	void AddToMovingTrucks(truck* t, int n);
	void AddToTrucksCheckup(truck* t, int n);



	cargo* RemoveFromLoadingCargos();
	cargo* RemoveFromMovingCargos();
	cargo* RemoveFromDeliveredCargos();

	truck* RemoveFromLoadingTrucks();
	truck* RemoveFromMovingTrucks();
	truck* RemoveFromTrucksCheckup();
	//
	void checkMovingCargos();
	//Check if waiting cargos are all empty or not

	//Execute Events
	void ExecuteEvent(); //

	// Assignment for phase 2 
	void AssignNormalCargo();
	void AssignSpecialCargo();
	void AssignVipCargo();

	bool CheckAvailabletruck(truck*& t, char Type);
	void AssignTruckToCargo(truck* t, cargo* c); 


	//Move Trucks 
	void MoveTruckFromLoadingToMoving();
	void MoveTruckFromMovingToCheckupOrWaiting();
	void MoveTruckFromMovingTonReguarMaintance();
	void MoveTruckFromCheckupToEmpty();
	void MoveTruckFromUnReguarMaintanceToEmpty();
	// MaxW Assignment
	void AssignNormalCargo_MaxW();
	void AssignSpecialCargo_MaxW();
	void AssignVipCargo_MaxW();
	// AutP 
	void AutoPromotinFunc();
	// check the implementation
	//Output file associated functions

	void getStatistics();
	void printTrucksData();
	void printCargosData();

	template <class T>
	void LoadCargosToTruck(PriQ<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& , int Mainta = 0);
	template <class T>
	void LoadCargosToTruck(Queue<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& , int Mainta = 0);

	void LoadCargosToTruck(PriQ<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& , int Mainta = 0);

	void LoadCargosToTruck(Queue<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& , int Mainta = 0);

	template<class T>
	void LoadCargosToTruck_MaxW(PriQ<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& isLoading, int Mainta = 0);
	template<class T>
	void LoadCargosToTruck_MaxW(Queue<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& isLoading, int Mainta = 0);

	void LoadCargosToTruck_MaxW(PriQ<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& isLoading, int Mainta = 0);

	void LoadCargosToTruck_MaxW(Queue<truck*>& qTruck, PriQ<vipCargo*>& cList, bool& systemNeed, bool& isLoading, int Mainta = 0);

	//Print from UI

	//get auto promotion
	int GetAutoPromotionLimit();

	bool isOpen();
	void closeCompany();

	void destroyTrucks();
public:
	Company(string OFN, string IFN);
	void print();
	NormalCargo* RemoveFromWaitingCargos(int);
	void IncrementCurrentHour(); // includes the logic for phase 1 
	void setMode();
	// for simulation 
	bool check();
	// Promote NormalCargo
	void AddToWaitingCargos(cargo* c);
	void PromoteCargo(int CargoID);
	void PrintOutput();
	~Company();
};

template<class T>
inline void Company::LoadCargosToTruck(PriQ<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{

	truck* t = nullptr;
	T* nc;
	cList.peek(nc);
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);

		if (t->getCapcity() <= cList.getCount() && !isLoading)
		{
			NormalCargo* Mnc = dynamic_cast<NormalCargo*> (nc);
			SpecialCargo* Msc = dynamic_cast<SpecialCargo*> (nc);

			int max;

			if (Mnc)
				max = getMaxNormalLoadingTime(t->getCapcity());
			else if (Msc)
				max = getMaxSpecialLoadingTime(t->getCapcity());

			if (isWorkingTime(currentTime + max) || t->getNight())
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

template<class T>
inline void Company::LoadCargosToTruck(Queue<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	truck* t = nullptr;
	T* nc;
	cList.peek(nc);
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);

		if (t->getCapcity() <= cList.getCount() && !isLoading)
		{
			NormalCargo* Mnc = dynamic_cast<NormalCargo*> (nc);
			SpecialCargo* Msc = dynamic_cast<SpecialCargo*> (nc);

			int max;

			if (Mnc)
				max = getMaxNormalLoadingTime(t->getCapcity());
			else if (Msc)
				max = getMaxSpecialLoadingTime(t->getCapcity());

			if (isWorkingTime(currentTime + max) || t->getNight())
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

template<class T>
inline void Company::LoadCargosToTruck_MaxW(PriQ<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	T* nc;
	cList.peek(nc);
	truck* t;
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);
		if (currentTime.toInt() >= (nc->getPreTime() + maxWaiting).toInt())
		{
			NormalCargo* Mnc = dynamic_cast<NormalCargo*> (nc);
			SpecialCargo* Msc = dynamic_cast<SpecialCargo*> (nc);

			int max;

			if (Mnc)
				max = getMaxNormalLoadingTime(cList.getCount());
			else if (Msc)
				max = getMaxSpecialLoadingTime(cList.getCount());

			if (isWorkingTime(currentTime + max))
			{
				//  while !cList.isEmpty() && t->getCapcity() < i
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

template<class T>
inline void Company::LoadCargosToTruck_MaxW(Queue<truck*>& qTruck, Queue<T*>& cList, bool& systemNeed, bool& isLoading, int Mainta)
{
	T* nc;
	cList.peek(nc);
	truck* t;
	if (cList.isEmpty())
		return;

	if (!qTruck.isEmpty())
	{
		qTruck.peek(t);
		if (currentTime.toInt() >= (nc->getPreTime() + maxWaiting).toInt())
		{
			NormalCargo* Mnc = dynamic_cast<NormalCargo*> (nc);
			SpecialCargo* Msc = dynamic_cast<SpecialCargo*> (nc);

			int max;

			if (Mnc)
				max = getMaxNormalLoadingTime(cList.getCount());
			else if (Msc)
				max = getMaxSpecialLoadingTime(cList.getCount());

			if (isWorkingTime(currentTime + max))
			{
				//  while !cList.isEmpty() && t->getCapcity() < i
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
