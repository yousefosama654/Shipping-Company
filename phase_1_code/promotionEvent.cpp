#include "promotionEvent.h"
promotionEvent::promotionEvent(Time ET, int ID, Company* com, int ex):event(ET,ID,com)
{
	extra = ex;
}
void promotionEvent::Execute()
{
	Comp->PromoteCargo( this->getCargoID() ); //Promate a normal cargo by ID to vip
	
}
promotionEvent::~promotionEvent()
{

}
