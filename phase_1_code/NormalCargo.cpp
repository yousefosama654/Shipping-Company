#include "NormalCargo.h"
NormalCargo::NormalCargo(int ID, Time prep, int LD, int dd, int cost) :cargo(ID, prep, LD, dd, cost)
{

}
int NormalCargo::GetAutoPromotion()
{
    return AutoPromote;
}
void NormalCargo::SetAutoPromotion(int f)
{
    AutoPromote = f;
}
NormalCargo::~NormalCargo()
{
}
NormalCargo::NormalCargo()
{
}
