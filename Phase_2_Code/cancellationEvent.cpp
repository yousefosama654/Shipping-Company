#include "cancellationEvent.h"
#include"event.h"
#include"Company.h"
cancellationEvent::cancellationEvent(Time ET, int ID, Company* com):event(ET, ID, com)
{

}
void cancellationEvent::Execute()
{
	//Comp->CancelCargo(this->getCargoID());  //Cancel a normal cargo by ID
	Comp->RemoveFromWaitingCargos(this->getCargoID()); 
}
cancellationEvent::~cancellationEvent()
{

}
