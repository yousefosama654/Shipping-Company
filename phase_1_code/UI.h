#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "event.h"
#include "PreparationEvent.h"
#include "cancellationEvent.h"
#include "promotionEvent.h"
#include "time.h"
#include "truck.h"
#include "PriQ.h"
class UI
{
	
public:
	UI(); 
	void Welecome();

	void printProgramInterface(const LinkedList<NormalCargo*>& NormalCargos, const PriQ<vipCargo*>& vipcargos, const Queue<SpecialCargo*>& SpecialCargos, const PriQ<cargo*>& LoadingCargos, const PriQ<cargo*>& MovingCargos, const PriQ<cargo*>& DeliveredCargos);
	char charcterSelectMode(); 
	void printCurrentTime(Time t); 
	void printInteractiveMode(Time t, Queue<NormalCargo*>,Queue<SpecialCargo*>,PriQ<vipCargo*> , int Wn, Queue<cargo*> Dq, int Dn);
	void printSilentMode(); 
	void printEmptyTrucks(PriQ<truck*>, int);
	void printStepbyStep(Time t, Queue<NormalCargo*>, Queue<SpecialCargo*>, PriQ<vipCargo*>, int Wn, Queue<cargo*> Dq, int Dn);
	
	void printWaitingCargos(Queue<NormalCargo*>, Queue<SpecialCargo*>, PriQ<vipCargo*>,int); 
	void printLoadingTrucks(PriQ<truck*>, int); // for phase 2
	void printMovingCargos(PriQ<cargo*>,int); // for phase 2
	void printInCheckUpTrucks(PriQ<truck*>, int); // for phase 2
	void printDeliveredCargos(Queue<cargo*>,int); // 
	

	
	void printEnd(); 
	~UI();
};

