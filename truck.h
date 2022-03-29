#pragma once
#include "time.h"
#include "cargo.h"
class truck
{
	cargo** cargos;
	int capacity;
	time maintance; 
	int speed;
	time deliveryInterval;

};

