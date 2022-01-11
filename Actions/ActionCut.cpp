#include"../ApplicationManager.h"
#include"ActionCut.h"

//Class responsible for deleting action
ActionCut::ActionCut (ApplicationManager* pApp) : Action(pApp)
{
}
ActionCut:: ~ActionCut (void)
{
}
//Execute action (code depends on action type)
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
		UI* pUI = pManager->GetUI();
		pUI->ClearDrawingArea();
		pManager->UpdateInterface();
		pUI->PrintMsg("Choose the component you want to copy");
		pUI->GetPointClicked(Cx, Cy);
		Component* cutComp = pManager->take_component_position(Cx, Cy);
		pUI->ClearStatusBar();
		if (cutComp != nullptr)
		{
			pUI->PrintMsg("Choose where you want the copied component to be drawn ");
			pUI->GetPointClicked(x_, y_);
			pUI->ClearStatusBar();
		
			GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp

		//Calculate the rectangle Corners

			int compWidth = pUI->getCompWidth();
			int compHeight = pUI->getCompHeight();
			pGInfo->PointsList[0].x = x_ - compWidth / 2;
			pGInfo->PointsList[0].y = y_ - compHeight / 2;
			pGInfo->PointsList[1].x = x_ + compWidth / 2;
			pGInfo->PointsList[1].y = y_ + compHeight / 2;
			pManager->Cut_Component(cutComp, pGInfo);
		}
	}
}

void ActionCut::Undo()
{
}
void ActionCut::Redo()
{
}
