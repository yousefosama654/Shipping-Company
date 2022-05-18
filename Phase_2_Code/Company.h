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
	/* Ui HAS a func receives event  and we call it from the ready event */
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
	
	int maxTrucksCount; 
	int promotedCount;
	int CargosCount;

	int NCargosCount; 
	int SCargosCount; 
	int VCargosCount; 



	int noWaitingCargos;
	int noMovingCargos; 
	int noDeliveredCargos;
	// used in cargo promotion 
	int AutoPromotion;
	int noPromotedCargos;
	// TODO take care with this counter in tour functions
	// program mode (interactive | silent | step by step)
	char mode; 
	
	
	//Events
	Queue<event*>Events;
	
	// cargos type
	LinkedList<NormalCargo*> NormalCargos;
	PriQ<vipCargo*> vipcargos;
	Queue<SpecialCargo*> SpecialCargos;
	
	Queue<NormalCargo*> NormalWaitingCargos; 
	Queue<SpecialCargo*> SpecialWaitingCargos; 
	PriQ<vipCargo*> VipWaitingCargos;
	
	PriQ<cargo*> LoadingCargos;
	PriQ<cargo*> MovingCargos;
	Queue<cargo*> DeliveredCargos;
	
	Queue<truck*> NormalTrucks;
	Queue<truck*> VipTrucks;
	Queue<truck*> SpecialTrucks;
	
	PriQ<truck*> LoadingTrucks;
	PriQ<truck*> MovingTrucks;
	PriQ<truck*> CheckupTrucks;
	
	//UI 
	UI* ui;
	
	//Current Day
	Time currentTime;


	int getMaxNormalLoadingTime(int);
	int getMaxSpecialLoadingTime(int);
	int getMaxVipLoadingTime(int);
public:
	Company(string OFN, string IFN);
	void ReadInput(); // reads input from file 
	void InitialiseTrucks();


	// Current hour
	void IncrementCurrentHour(); // includes the logic for phase 1 
	int getCurrentHour(); 
	void IncrementCurrentDay(); 
	int getCurrentday(); 
	bool isWorkingTime(); 
	bool isWorkingTime(Time);

	// Add TO
	// Cargos 
	void AddToNormalCargos(NormalCargo*); 
	void AddToVIPCargos(vipCargo*, float); 
	void AddToSpeacialCargos(SpecialCargo*); 
	
	// Types 
	void AddToWaitingCargos(cargo* c); 
	void AddToLoadingCargos(cargo* c); 
	void AddToMovingCargos(cargo* c);
	void AddToDeliveredCargos(cargo* c);
	
	// Trucks 
	void AddToLoadingTrucks(truck* t, int n);
	void AddToNormalTrucks(truck* NT, float speed); 
	void AddToSpecialTrucks(truck* ST, float speed); 
	void AddToVipTrucks(truck* VT, float speed); 
	
	void AddToMovingTrucks(truck* t, int n);
	void AddToTrucksCheckup(truck* t, int n);
	
	// for simulation 
	bool check(); 
	void setMode(); 

	// Remove from Lists
	NormalCargo* RemoveFromNormalCargos( int pos=1 );
	SpecialCargo* RemoveFromSpecialCargos(); 
	vipCargo* RemoveFromvipCargos();

	truck* RemoveFromVipTrucks(); 
	truck* RemoveFromSpecialTrucks(); 
	truck* RemoveFromNormalTrucks(); 
	
	NormalCargo* RemoveFromWaitingCargos(int);
	cargo* RemoveFromLoadingCargos(); 
	cargo* RemoveFromMovingCargos(); 
	cargo* RemoveFromDeliveredCargos(); 
	
	truck* RemoveFromLoadingTrucks(); 
	truck* RemoveFromMovingTrucks(); 
	truck* RemoveFromTrucksCheckup(); 
	//
	void checkMovingCargos();
	//Check if waiting cargos are all empty or not
	bool CheckWaitingCargos(); //

	//Execute Events
	void ExecuteEvent(); //

	// Assignment for phase 2 
	void AssignNormalCargo(); 
	void AssignSpecialCargo(); 
	void AssignVipCargo(); 

	bool CheckAvailabletruck(truck*& t, char Type); 
	void AssignTruckToCargo(truck*t, cargo* c); // see the result in above functions
												
	// Promote NormalCargo
	void PromoteCargo(int CargoID); 
	
	//Move Trucks 
	void MoveTruckFromEmptyToLoading(truck*);
	void MoveTruckFromLoadingToMoving();                     // the priority here is prop to what
	void MoveTruckFromMovingToCheckupOrWaiting();
	void MoveRoverFromCheckupToEmpty();
	
	// MaxW Assignment
	void AssignNormalCargo_MaxW();
	void AssignSpecialCargo_MaxW();
	
	// AutP 
	void AutoPromotinFunc();
	// check the implementation
	//Output file associated functions
	void PrintOutput(); 
	
	void getStatistics(); 
	void printTrucksData(); 
	void printCargosData(); 

	//Print from UI
	void print(); 

	//get auto promotion
	int GetAutoPromotionLimit(); 
	
	~Company(); 
	//edits for maxw
};
