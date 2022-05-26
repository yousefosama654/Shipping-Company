#pragma once
#include <fstream>
#include <math.h>
class Time
{
	int day;
	int hour;
public:
	Time(int d = 0, int h = 0);
	void setday(int );
	void sethour(int);
	int gethour();
	int getday();
	Time operator + (const Time& t1); 
	Time operator - (const Time& t1);
	Time operator + (int x); 
	bool operator > (const Time& t1); 
	bool operator < (const Time& t1);
	bool operator == (const Time& t1); 
	void IncrementHour();
	void IncrementDay();
	int toInt(); 
	Time toTime(float);
	// ADD overlaoding to an integer
};
