#include "ActionSIM_MODE.h"
#include "..\ApplicationManager.h"

ActionSIM_MODE::ActionSIM_MODE(ApplicationManager* pApp) : Action(pApp)
{
}

ActionSIM_MODE::~ActionSIM_MODE(void)
{
}

void ActionSIM_MODE::Execute()
{
	UI* pUI = pManager->GetUI();
	bool valid=1; 
	if (valid)
	{
		pUI->SIM_MODE_Button();

		pUI->ClearStatusBar();
	}
	else pUI->PrintMsg("CIRCUIT INVALID!");

}
void ActionSIM_MODE::Undo()
{}

void ActionSIM_MODE::Redo()
{}