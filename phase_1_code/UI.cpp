#include "UI.h"
#include "global.h"
#include <iostream>
#include <fstream>
using namespace std;

void UI::printProgramInterface(const LinkedList<NormalCargo*>& NormalCargos, const PriQ<vipCargo*>& vipcargos, const Queue<SpecialCargo*>& SpecialCargos, const PriQ<cargo*>& LoadingCargos, const PriQ<cargo*>& MovingCargos, const PriQ<cargo*>& DeliveredCargos)
{
}

char UI::charcterSelectMode()
{
	Welecome();
	char x;
	bool looping = true;
	do
	{
		cin >> x;
		if (x == 'a' || x == 'b' || x == 'c')
			looping = false;
		else
			cout << "\t\t\t Please Enter A Valid Character : \t\t\t \n";
	} while (looping);
	cout << "\n\n\n";
	return x;
}

void UI::printCurrentTime(Time t)
{
	cout << "Current Time (Day:Hour): (" << t.getday() << ":" << t.gethour() << ")" << "\n";
}

void UI::printInteractiveMode(Time t, Queue<NormalCargo*>NWC, Queue<SpecialCargo*>SWC, PriQ<vipCargo*>VWC, int Wn, Queue<cargo*> Dq, int Dn)
{
	printCurrentTime(t);
	printWaitingCargos(NWC, SWC, VWC, Wn);
	printDeliveredCargos(Dq, Dn);
}

void UI::printSilentMode()
{
	cout << "\t\t\t\tSilent Mode\n\t\t\t\tSimulation Starts...\n\t\t\t\tSimulation ends, Output file created\n";
}

void UI::printEnd()
{
	cout << "\n~~~~~~~~~~~~~~~~~||THE END||~~~~~~~~~~~~~~~~~~~~\n";
}

void UI::printWaitingCargos(Queue<NormalCargo*> NWC, Queue<SpecialCargo*>SWC, PriQ<vipCargo*>VWC, int n)
{
	cout << n << " Waiting Cargos: ";
	if (!NWC.isEmpty())
	{
		NormalCargo* n;
		cout << "["; 
		while (!NWC.isEmpty())
		{
			NWC.dequeue(n); 
			cout << n->getId(); 
			if (NWC.peek(n))
				cout << ','; 

		}
		cout << "] "; 
	}
	if (!SWC.isEmpty())
	{
		SpecialCargo* s;
		cout << "("; 
		while (!SWC.isEmpty())
		{
			SWC.dequeue(s); 
			cout << s->getId(); 
			if (SWC.peek(s))
				cout << ','; 

		}
		cout << ") "; 
	}
	if (!VWC.isEmpty())
	{
		vipCargo* v;
		cout << "{";
		while (!VWC.isEmpty())
		{
			VWC.dequeue(v);
			cout << v->getId();
			if (VWC.peek(v))
				cout << ',';

		}
		cout << "} ";
	}
}

void UI::printDeliveredCargos(Queue<cargo*> q, int n)
{
	cout << endl << n << " Delivered Trucks : " ;
	cargo* x = nullptr;
	while (!q.isEmpty())
	{
		q.dequeue(x); 
		NormalCargo* nc = dynamic_cast<NormalCargo*> (x);
		SpecialCargo* sc = dynamic_cast<SpecialCargo*> (x);
		vipCargo* vc = dynamic_cast<vipCargo*> (x);
		if (nc)
			cout << "[" << nc->getId() << "] ";
		else if (sc)
			cout << "(" << sc->getId() << ") ";
		else if (vc)
			cout << "{" << vc->getId() << "} ";
	}
	cout << endl;
}

void UI::printEmptyTrucks(PriQ<truck*>, int)
{
}

void UI::printStepbyStep(Time t, Queue<NormalCargo*> NWC, Queue<SpecialCargo*> SWC, PriQ<vipCargo*> VWC,int Wn, Queue<cargo*> Dq, int Dn)
{
	printInteractiveMode(t, NWC,SWC,VWC, Wn, Dq, Dn);
	Sleep(1000);
}
void UI::Welecome()
{
	cout << "\t\t\t\t***************************************************" << endl;
	cout << "\t\t\t\t*                ~~SHIPPING COMPANY~~             *" << endl;
	cout << "\t\t\t\t***************************************************" << endl;
	cout << "\t\t\t\t--------------------------------------------------" << endl;
	cout << "\t\t\t\tEnter 'a' for simulation in the Interactive Mode |" << endl;
	cout << "\t\t\t\t--------------------------------------------------" << endl;
	cout << "\t\t\t\tEnter 'b' for the Step-By-Step Mode              |" << endl;
	cout << "\t\t\t\t--------------------------------------------------" << endl;
	cout << "\t\t\t\tEnter 'c' for the Silent Mode                    |" << endl;
	cout << "\t\t\t\t--------------------------------------------------" << endl;
	cout << "\t\t\t\t--> ";

}


UI::UI()
{
}

UI::~UI()
{
}
