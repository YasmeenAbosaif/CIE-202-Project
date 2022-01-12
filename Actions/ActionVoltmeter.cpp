#include "ActionVoltmeter.h"
#include "../ApplicationManager.h"
#include "../Components/Battery.h"
#include "../Components/Switch.h"
ActionVoltmeter::ActionVoltmeter(ApplicationManager* pApp) : Action(pApp)
{
	pUI = pApp->GetUI();

	CompCount = pApp->GetCompCount();
	ConnCount = pApp->GetConnCount();

	CompList = pApp->GetCompList();
	ConnList = pApp->GetConnList();
}


void ActionVoltmeter:: calculateCurrent()
{
	double emf = 0;
	double Rtotal = 0;

	for (int i = 0; i < CompCount; i++)
	{
		Battery* checkcomp = dynamic_cast<Battery*> (CompList[i]);
		if (checkcomp) emf += stod(CompList[i]->getVal());
		else { Rtotal += stod(CompList[i]->getVal()); }
	}
	total_current = emf / Rtotal;
}
template <typename T>
void ActionVoltmeter::calculateVoltage(T* Cptr)
	{
	Connection* connptr = dynamic_cast<Connection*> (Cptr);
	if (connptr) voltage = 0;
	else
	{
		Component* comptr = dynamic_cast<Component*> (Cptr);
		if ((Cptr->getType()) == "Resistor")     voltage = (total_current * (stod(comptr->getVal())));
		else if ((Cptr->getType()) == "Bulb")    voltage = (total_current * (stod(comptr->getVal())));
		else if ((Cptr->getType()) == "Buzzer")  voltage = (total_current * (stod(comptr->getVal())));
		else if ((Cptr->getType()) == "Switch")
		{
			Switch* sptr = dynamic_cast<Switch*> (Cptr);
			if (!(sptr->getOpen()))
				voltage = 0;
			//		else
				//		voltage = emf;
		}
		else if ((Cptr->getType()) == "Battery") voltage = stod(comptr->getVal()); //That's not so accurate, in case of multiple Batteries.
		else if ((Cptr->getType()) == "Fuse")    voltage = 0;
		//else if ((CompList[i]->getType()) == "Ground")  voltage = emf;
	}


}


double ActionVoltmeter::getVoltage() const
{
	return voltage;
}

void ActionVoltmeter::selectComponent(int x, int y)
{
	ActionSelect* pSELECT = new ActionSelect(pManager, x, y);
	if (pSELECT)
	{
		pSELECT->Execute();
		delete pSELECT;
		pSELECT = nullptr;
	}
	pManager->UpdateInterface();
}

void ActionVoltmeter::Execute()
{
	calculateCurrent();
	pUI->PrintMsg("Select a component to read the voltage betweem its terminal: ");
	do
	{
		pUI->GetPointClicked(Cx, Cy);
		selectComponent(Cx, Cy);

		pUI->ClearStatusBar();

		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->isInRegion(Cx, Cy, pUI))
				Cmpnt = CompList[i];
		}

		for (int i = 0; i < ConnCount; i++)
		{
			if (ConnList[i]->isInRegion(Cx, Cy, pUI))
				Cnctn = ConnList[i];
		}

		if (Cmpnt == nullptr && Cnctn==nullptr)
			pUI->PrintMsg("No item selected!");            //Review


	} while (Cmpnt == nullptr&& Cnctn==nullptr);
	if(Cmpnt) calculateVoltage(Cmpnt);
	if (Cnctn) calculateVoltage(Cnctn);
	pUI->PrintMsg("The voltage across the item is: " + to_string(voltage));

}

ActionVoltmeter::~ActionVoltmeter(void)
{
}


void ActionVoltmeter::Undo() {}

void ActionVoltmeter::Redo() {}