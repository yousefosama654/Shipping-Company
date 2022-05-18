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

void UI::printInteractiveMode(Time t, Queue<NormalCargo*>NWC, Queue<SpecialCargo*>SWC, PriQ<vipCargo*>VWC,
							  PriQ<truck*> LT, Queue<truck*> ENT, Queue<truck*> EST,Queue<truck*> EVT ,PriQ<truck*> CT,
							  PriQ<truck*> MT,int movingCargo, int Wn, Queue<cargo*> Dq, int Dn)
{
	printCurrentTime(t);
	cout << endl <<"-------------------------------------------------------------------"<<endl; 
	printWaitingCargos(NWC, SWC, VWC, Wn);
	cout << endl <<"-------------------------------------------------------------------"<<endl;
	printLoadingTrucks(LT);
	cout << endl <<"-------------------------------------------------------------------"<<endl;
	printEmptyTrucks(ENT,EST,EVT); 
	cout << endl <<"-------------------------------------------------------------------"<<endl;
	printInCheckUpTrucks(CT); 
	cout << endl <<"-------------------------------------------------------------------"<<endl;
	printMovingCargos(MT,movingCargo); 
	cout << endl <<"-------------------------------------------------------------------"<<endl;
	printDeliveredCargos(Dq, Dn);
	cout << endl <<"-------------------------------------------------------------------"<<endl;

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

void UI::printLoadingTrucks(PriQ<truck*> q)
{
	cout << q.getCount() << " Loading Trucks : "; 
	truck* t = nullptr; 
	while (q.dequeue(t))
	{
		cout << t->getID();
		t->print(); 
		cout << " "; 
	}
}

void UI::printEmptyTrucks(Queue<truck*> NT, Queue<truck*> ST, Queue<truck*> VT)
{
	cout << NT.getCount() + ST.getCount() + VT.getCount() << " Empty Trucks: ";
	truck* t = nullptr; 
	while (NT.dequeue(t))
	{
		cout << '[' << t->getID() << "]";
		if (NT.peek(t))
			cout << ','; 
	}
	if (ST.peek(t))
		cout << ','; 
	while (ST.dequeue(t))
	{
		cout << '(' << t->getID() << ")";
		if (ST.peek(t))
			cout << ',';
	}
	if (VT.peek(t))
		cout << ',';
	while (VT.dequeue(t))
	{
		cout << '{' << t->getID() << "}";
		if (VT.peek(t))
			cout << ',';
	}
}

void UI::printMovingCargos(PriQ<truck*> q,int movingCargos)
{
	cout << movingCargos << " Moving Cargos : ";
	truck* t; 
	while (q.dequeue(t))
	{
		cout << t->getID();
		t->print();
	}
}

void UI::printInCheckUpTrucks(PriQ<truck*> q)
{
	cout << q.getCount() << " In-Checkup Trucks: ";
	truck* t; 
	while (q.dequeue(t))
	{
		if (t->getTruckType() == 'n')
		{
			cout << '[' << t->getID() << ']'; 
		}
		else if (t->getTruckType() == 's')
		{
			cout << '(' << t->getID() << ')';
		}
		else
		{
			cout << '{' << t->getID() << '}';
		}
		cout << " "; 
	}
}

void UI::printDeliveredCargos(Queue<cargo*> q, int n)
{
	cout << endl << n << " Delivered Cargos : " ;
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

void UI::printStepbyStep(Time t, Queue<NormalCargo*> NWC, Queue<SpecialCargo*> SWC, PriQ<vipCargo*> VWC,int Wn, Queue<cargo*> Dq, int Dn)
{
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
