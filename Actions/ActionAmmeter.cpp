#include "ActionAmmeter.h"
#include "../ApplicationManager.h"
#include "../Components/Battery.h"

ActionAmmeter::ActionAmmeter(ApplicationManager* pApp) : Action(pApp)
{
	pUI = pApp->GetUI();

	CompCount = pApp->GetCompCount();
	ConnCount = pApp->GetConnCount();

	CompList = pApp->GetCompList();
	ConnList = pApp->GetConnList();
}
 
void ActionAmmeter::calculateCurrent()
{
	//NOTE: The Batteries were to be entered in only one direction, thus this is considered to be valid.
	//		Batteries were considered to be ideal (NO internal resistance).

	double emf=0;
	double Rtotal=0;

	for (int i = 0; i < CompCount; i++)
	{
		Battery* checkcomp = dynamic_cast<Battery*> (CompList[i]);
		if (checkcomp) emf += stod(CompList[i]->getVal());
		else { Rtotal += stod(CompList[i]->getVal()); }
	}


	total_current = emf / Rtotal;

}


double ActionAmmeter::getCurrent() const
{
	return total_current;
}

void ActionAmmeter::selectComponent(int x, int y)
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

void ActionAmmeter::Execute()
{
	calculateCurrent();
	pUI->PrintMsg("Select a component to read the current across it: ");
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
			pUI->PrintMsg("No item selected!");


	} while (Cmpnt == nullptr);

	pUI->PrintMsg("The current across the item is: " + to_string(total_current));

}

ActionAmmeter::~ActionAmmeter(void)
{
}


void ActionAmmeter::Undo() {}

void ActionAmmeter::Redo() {}