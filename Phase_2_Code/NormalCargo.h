#pragma once
#include "cargo.h"
class NormalCargo : public cargo
{
	int AutoPromote; //read from the file
public:

	NormalCargo();
	NormalCargo(int ID, Time prep, int LD, int dd, int cost);
	int GetAutoPromotion();
	void SetAutoPromotion(int f);
	~NormalCargo();
};

