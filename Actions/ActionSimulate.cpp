/*
#include "ActionSimulate.h"
#include "..\ApplicationManager.h"
#include "..\Components\Bulb.h"
#include "..\Components\Switch.h"
ActionSimulate::ActionSimulate(ApplicationManager* pApp) :Action(pApp)
{
	pUI = pApp->GetUI();

	CompCount = pApp->GetCompCount();
	ConnCount = pApp->GetConnCount();

	CompList = pApp->GetCompList();
	ConnList = pApp->GetConnList();
}

ActionSimulate::~ActionSimulate(void)
{
}

void ActionSimulate::BulbCheck()
{
	for (int i = 0; i < CompCount; i++)
	{
		if ((CompList[i]->getType()) == "Switch")
		{
			Switch* Sptr = dynamic_cast<Switch*>(CompList[i]);
			bool op= Sptr->getOpen();
		}
	}

}

void ActionSimulate::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Simulating:");

	BulbCheck();


}

void ActionSimulate::Undo()
{}

void ActionSimulate::Redo()
{}

*/