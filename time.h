#pragma once
class time
{
	int day;
	int hour;
public:
	time(int d = 0, int h = 0);
	void setday(int );
	void sethour(int);
	int gethour();
	int getday();
	time operator + (const time& t1); 
	time operator - (const time& t1);
};

