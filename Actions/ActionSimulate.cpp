
#include "ActionSimulate.h"
#include "..\ApplicationManager.h"
#include "..\Components\Bulb.h"
#include "..\Components\Switch.h"
#include "..\Components\Fuse.h"

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
	bool op = 0;
	bool allclosed = 1;

	for (int i = 0; i < CompCount; i++)
	{
		if ((CompList[i]->getType()) == "Switch")
		{
			Switch* Sptr = dynamic_cast<Switch*>(CompList[i]);
			if (Sptr)	  op = Sptr->getOpen();
			if (Sptr->getOpen())     allclosed = 0;
		}
	}


	if (allclosed)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if ((CompList[i]->getType()) == "Bulb")
			{
				Bulb* Bptr = dynamic_cast<Bulb*>(CompList[i]);
				if (Bptr)
				{
					{ Bptr->setOn(1);
					pManager->UpdateInterface();
					}
				}
			}
		}
	}
}
/*
void ActionSimulate::FuseCheck()
{
	for (int i = 0; i < CompCount; i++)
	{
		if ((CompList[i]->getType()) == "Fuse")
		{
			Fuse* Fptr = dynamic_cast<Fuse*>(CompList[i]);
			if ()
		}
		
	}
}
*/
void ActionSimulate::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Simulating:");
	//FuseCheck();
	BulbCheck();


}

void ActionSimulate::Undo()
{}

void ActionSimulate::Redo()
{}
