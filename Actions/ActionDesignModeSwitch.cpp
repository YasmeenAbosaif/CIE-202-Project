#include "ActionDesignModeSwitch.h"
#include "..\ApplicationManager.h"

ActionDesignModeSwitch::ActionDesignModeSwitch(ApplicationManager* pApp) : Action(pApp)
{
}

ActionDesignModeSwitch::~ActionDesignModeSwitch(void)
{
}

void ActionDesignModeSwitch::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	pUI->DesignModeSwitch();
	pUI->ClearStatusBar();
}
void ActionDesignModeSwitch::Undo()
{}

void ActionDesignModeSwitch::Redo()
{}