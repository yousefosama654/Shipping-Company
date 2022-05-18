#include "Time.h"
Time::Time(int d, int h)
{
	setday(d);
	sethour(h);
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
	this->setday(this->day + t1.day); 
	this->sethour(this->hour + t1.hour);
	return *this;
}
Time Time::operator+( int x)
{ 

	int xday = this->day + x / 24; 
	int xhour = this->hour + x%24;
	Time t;
	if(xhour==0)
	t.setday(xday+1);
	else
		t.setday(xday );
	t.sethour(xhour); 
	return t;
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
Time Time::toTime(int time)
{
	Time t;
	int days = time / 24;
	int hours = time % 24;
	if (hours == 0)
		t.setday(days + 1);
	else
		t.setday(days);
	t.sethour(hours);
	return t;
}
