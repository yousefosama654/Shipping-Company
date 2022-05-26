#include "Time.h"
Time::Time(int d, int h)
{
	hour = h;
	day = h;
}
void Time::setday(int x)
{
	day = x > 0 ? x : 1;
}
void Time::sethour(int x)
{
	if (x > 23)
	{
		day++;
		hour = x - 24;
		return;
	}
	hour = x >= 0 ? x : 0;
}
int Time::gethour()
{
	return hour;
}
int Time::getday()
{
	return day;
}

Time Time::operator+(const Time& t1)
{
	this->setday(this->day + t1.day);
	this->sethour(this->hour + t1.hour);
	return *this;
}
Time Time::operator+(int x)
{
	int Day = (day + x / 24);
	int Hour = (hour + x % 24);
	Time res;
	res.setday(Day);
	res.sethour(Hour);
	return res;
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
	Time t; 
	t.day = (this->day - t1.day);
	t.sethour(this->hour - t1.hour);
	return t;
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
Time Time::toTime(float time)
{
	Time t;
	int x = round(time);
	int days =  x / 24;
	int hours = x % 24;
	if (hours == 0)
		t.setday(days + 1);
	else
		t.day = days;
	t.sethour(hours);
	return t;
}
