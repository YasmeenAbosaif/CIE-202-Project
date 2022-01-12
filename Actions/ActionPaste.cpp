#include"../ApplicationManager.h"
#include"ActionPaste.h"

ActionPaste:: ActionPaste(ApplicationManager* pApp) : Action(pApp)
{
}

ActionPaste ::~ActionPaste(void)
{
}

//Execute action (code depends on action type)
void ActionPaste::Execute()
{
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	pManager->UpdateInterface();

	pUI->PrintMsg("Choose where you want the copied component to be drawn ");
	pUI->GetPointClicked(Cx, Cy);

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp
	int compWidth = pUI->getCompWidth();
	int compHeight = pUI->getCompHeight();
	pGInfo->PointsList[0].x = Cx - compWidth / 2;
	pGInfo->PointsList[0].y = Cy - compHeight / 2;
	pGInfo->PointsList[1].x = Cx + compWidth / 2;
	pGInfo->PointsList[1].y = Cy + compHeight / 2;
	//Component* copiedcomp = pManager->getCopyCopmonent();
	Component* copiedcomponent_ = pManager->getCopyCopmonent();
	copiedcomponent_->set_GraphicsnewPosition(pGInfo);
	copiedcomponent_->get_GraphicsnewPosition();
	pManager->AddComponent(copiedcomponent_);
	pManager->UpdateInterface();
}

void ActionPaste::Undo()
{
}

void ActionPaste::Redo()
{
}