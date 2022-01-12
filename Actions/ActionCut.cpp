#include"../ApplicationManager.h"
#include"ActionCut.h"

//Class responsible for deleting action
ActionCut::ActionCut(ApplicationManager* pApp) : Action(pApp)
{
}
ActionCut:: ~ActionCut(void)
{
}

void ActionCut::Execute()
{
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	pManager->UpdateInterface();
	pUI->PrintMsg("Choose the component you want to cut");
	pUI->GetPointClicked(Cx, Cy);
	Component* cutComp = pManager->take_component_position(Cx, Cy);
	pUI->ClearStatusBar();
	if (cutComp != nullptr)
	{
		pManager->Copy_Cut_Component(cutComp);
		pUI->PrintMsg("The component is cut");
		pManager->DeleteComponent(cutComp);
		pManager->update_comp_connlist();
		pUI->ClearDrawingArea();
		pManager->UpdateInterface();
	}

}

void ActionCut::Undo()
{
}
void ActionCut::Redo()
{
}

