#include<iostream>
#include"Company.h"

using namespace std;

int main()
{
	Company* cmp = new Company("Output.txt", "Input.txt");
	cmp->setMode();
	while (cmp->check())
	{
		cmp->IncrementCurrentHour();
		cmp->print();
	}
	Sleep(5000);
	delete cmp;
	return 0;
}