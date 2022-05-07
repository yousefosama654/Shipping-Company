#pragma once
#include "event.h"
#include "info.h"
#include "time.h"
#include "queue.h"
#include "cargo.h"
#include "truck.h"
#include"Company.h"
#include"SpecialCargo.h"
#include"vipCargo.h"
#include"truck.h"
#include"NormalCargo.h"

class PreparationEvent : public event
{
	char cargoType;
    int loadTime; 
	Time PT;
    int distance; 
    int cost; 
public:
	// Initializing constructor
	PreparationEvent(Company* Com,Time PT, int ID,  char Type, int DS, int CT, int lD);
	// Execute
	virtual void Execute();
	// Destructor
	~PreparationEvent(); 
};

