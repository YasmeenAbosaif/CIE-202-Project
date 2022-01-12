#include"../ApplicationManager.h"
#include"ActionCopy.h"

//Class responsible for deleting action
ActionCopy::ActionCopy(ApplicationManager* pApp) : Action(pApp)
{
}
ActionCopy:: ~ActionCopy(void)
{
}
//Execute action (code depends on action type)
void ActionCopy::Execute()
{
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	pManager->UpdateInterface();
	pUI->PrintMsg("Choose the component you want to copy");
	pUI->GetPointClicked(Cx, Cy);
	Component* copycomponent = pManager->take_component_position(Cx, Cy);
	pUI->ClearStatusBar();
	if (copycomponent != nullptr)
	{
		pManager->Copy_Cut_Component(copycomponent);
		pUI->PrintMsg("The component is copied");
	}
}

void ActionCopy::Undo()
{
}
void ActionCopy::Redo()
{
}







