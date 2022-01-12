#include"../ApplicationManager.h"
#include"ActionMove.h"

ActionMove::ActionMove(ApplicationManager* pApp) : Action(pApp)
{
}

ActionMove ::~ActionMove(void)
{
}

//Execute action (code depends on action type)
void ActionMove::Execute()
{
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	pManager->UpdateInterface();
	pUI->PrintMsg("Select the component you want to drag");
	pUI->GetPointClicked(iX, iY);
	Component* component = pManager->take_component_position(iX, iY);
	if (component != 0)
	{
		pUI->MouseState_Move(iX, iY);
	}
}

void ActionMove::Undo()
{
}

void ActionMove::Redo()
{
}