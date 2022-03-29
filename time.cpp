#include "time.h"
time::time(int d, int h)
{
	hour = h;
	day = h;
}
void time::setday(int x)
{
	day = x > 0 ? x: 1;
}
void  time ::sethour(int x)
{
	if (x > 23)
	{
		day++;
		hour = 0;
		return;
	}
	hour = x > 0 ? x : 0;
}
int time:: gethour()
{
	return hour;
}
int time:: getday()
{
	return day;
}

time time::operator+(const time& t1)
{
	this->setday(this->day +t1.day); 
	this->sethour(this->hour + t1.hour);
	return *this;
}

time time::operator-(const time& t1)
{
	this->sethour(this->hour - t1.hour);
	return *this;
}
