#pragma once
#include "cargo.h"
class SpecialCargo : public cargo
{

public:
	SpecialCargo();
	SpecialCargo(int ID, Time prep, int LD, int dd, int cost);
	~SpecialCargo();
// priority=special;

};

