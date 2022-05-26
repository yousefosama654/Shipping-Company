#include "PreparationEvent.h"
// Initializing constructor
PreparationEvent::PreparationEvent(Company* Com,Time PT,int ID ,char Type,int DS, int CT, int LD) :event(PT, ID, Com)
{
    cargoType=Type;
    loadTime=LD;
    distance=DS;
    cost=CT;
	this->PT = PT;
}
void PreparationEvent::Execute()
{
	if (cargoType == 'V')
	{
		vipCargo* VC = new vipCargo(this->getCargoID(), PT, loadTime, distance, cost); // Create new vip Cargo
		Comp->AddToWaitingCargos(VC); 
		return;
	}
	else if (cargoType == 'N')
	{
		NormalCargo* NC = new NormalCargo(this->getCargoID(), PT, loadTime, distance, cost); // Create new normal Cargo
		Comp->AddToWaitingCargos(NC);
		return;
	}
	else
	{
		SpecialCargo* SC = new SpecialCargo(this->getCargoID(), PT, loadTime, distance, cost); // Create new special Cargo
		Comp->AddToWaitingCargos(SC);
		return;
	}
}

PreparationEvent::~PreparationEvent()
{

}
