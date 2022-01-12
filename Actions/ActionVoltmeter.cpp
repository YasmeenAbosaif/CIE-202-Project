#include "ActionVoltmeter.h"
#include "../ApplicationManager.h"
#include "../Components/Battery.h"

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


	for (int i = 0; i < CompCount; i++)
	{
		Battery* checkcomp = dynamic_cast<Battery*> (CompList[i]);
		if (checkcomp) emf += stod(CompList[i]->getVal());
		else { Rtotal += stod(CompList[i]->getVal()); }
	}
	total_current = emf / Rtotal;
}

void ActionVoltmeter::calculateVoltage()
	{
	for (int i = 0; i < CompCount; i++)
	{
		if ((CompList[i]->getType()) == "Resistor")     voltage = (total_current * stod(CompList[i]->getVal()));
		else if ((CompList[i]->getType()) == "Bulb")    voltage = total_current * stod(CompList[i]->getVal());
		else if ((CompList[i]->getType()) == "Buzzer")  voltage = total_current * stod(CompList[i]->getVal());
		else if ((CompList[i]->getType()) == "Switch") 
		{
			if (!(CompList[i]->open))
				voltage = 0;
			else
				voltage = emf;
		} 
		else if ((CompList[i]->getType()) == "Battery") voltage = stod(CompList[i]->getVal()); //That's not so accurate, in case of multiple Batteries.
		else if ((CompList[i]->getType()) == "Fuse")    voltage = 0;
		else if ((CompList[i]->getType()) == "Ground")  voltage = emf;

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
	calculateVoltage();
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
		if (Cmpnt == nullptr)
			pUI->PrintMsg("No item selected!");            //Review


	} while (Cmpnt == nullptr);

	pUI->PrintMsg("The voltage across the item is: " + to_string(voltage));

}

ActionVoltmeter::~ActionVoltmeter(void)
{
}


void ActionVoltmeter::Undo() {}

void ActionVoltmeter::Redo() {}