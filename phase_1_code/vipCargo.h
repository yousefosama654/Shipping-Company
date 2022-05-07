#pragma once
#include "cargo.h"
#include "NormalCargo.h"

class vipCargo: public cargo
{
	 float priority;
	 // add it to type paramter of node
public:
	vipCargo();
	vipCargo( int ID,Time prep,int LD, int dd, int cost);
	vipCargo(NormalCargo*); 
	void setpriority();
	float getpriority();
	~vipCargo();

	// queue< vip > a;
	// waiting to tommorow //fuck walid ??
};

