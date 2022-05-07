#include "Time.h"
Time::Time(int d, int h)
{
	hour = h;
	day = h;
}
void Time::setday(int x)
{
	day = x > 0 ? x: 1;
}
void Time::sethour(int x)
{
	if (x > 23)
	{
		day++;
		hour = x - 24;
		return;
	}
	hour = x > 0 ? x : 0;
}
int Time :: gethour()
{
	return hour;
}
int Time:: getday()
{
	return day;
}

Time Time::operator+(const Time& t1)
{
	this->setday(this->day +t1.day); 
	this->sethour(this->hour + t1.hour);
	return *this;
}
Time Time::operator+( int x)
{  
	int day = x / 24; 
	int hour = x - day * 24;
	this->setday(this->day + day);
	this->sethour(this->hour + hour);
	return *this;
}
bool Time::operator < (const Time& t1)
{
	int t = this->day * 24 + this->hour; 
	int t2 = t1.day * 24 + t1.hour; 
	return t < t2; 
}
bool Time::operator==(const Time& t1)
{
	return (hour == t1.hour) && (day == t1.day); 
}
bool Time::operator > (const Time& t1)
{
	int t = this->day * 24 + this->hour;
	int t2 = t1.day * 24 + t1.hour;
	return t > t2;
}

Time Time::operator-(const Time& t1)
{
	this->sethour(this->hour - t1.hour);
	return *this;
}

void Time::IncrementHour()
{
	sethour(++hour); 
}

void Time::IncrementDay()
{
	setday(++day); 
}

int Time::toInt()
{
	return hour + day * 24; 
}
