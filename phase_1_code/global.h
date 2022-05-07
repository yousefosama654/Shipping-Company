#pragma once
#include "Time.h"
#include <iostream>
using namespace std;
ostream& operator<< (ostream& os, Time x)
{
	os << x.getday() << ':' << x.gethour();
	return os;
}
/*
* Linker 2005
istream& operator>> (istream& is, Time& t)
{
	int day, hour;
	is >> day;
	is.ignore();
	is >> hour;
	t.setday(day);
	t.sethour(hour);
	return is;
}*/