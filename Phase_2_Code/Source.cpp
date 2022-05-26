#include<iostream>
#include"Company.h"
using namespace std;
int main()
{ 

	
	//Company* cmp = new Company("Output_1.txt", "Input_1.txt");
	Company* cmp = new Company("Output_2.txt", "Input_2.txt"); // <----  Delivary Failure is input_2
	//Company* cmp = new Company("Output_3.txt", "Input_3.txt");
	//Company* cmp = new Company("Output_4.txt", "Input_4.txt");
	//Company* cmp = new Compaany("Output_5.txt", "Input_5.txt");
	//Company* cmp = new Company("Output_6.txt", "Input_6.txt");
	//Company* cmp = new Company("Output_7.txt", "Input_7.txt");   // <----- Auto Promotion 
	//Company* cmp = new Company("Output_8.txt", "Test_UnRegMaintance.txt");

	
	cmp->setMode();
	

	while (cmp->check())
	{
		cmp->IncrementCurrentHour();

	}

	cmp->PrintOutput(); 
	Sleep(2000);
	delete cmp;
	return 0;
}