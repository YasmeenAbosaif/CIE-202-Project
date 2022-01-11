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
	/*
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();

	pUI->PrintMsg("Choose where you want the copied component to be drawn ");
	pUI->GetPointClicked(x_, y_);
	pUI->ClearStatusBar();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp


	int compWidth = pUI->getCompWidth();
	int compHeight = pUI->getCompHeight();
	pGInfo->PointsList[0].x = x_ - compWidth / 2;
	pGInfo->PointsList[0].y = y_ - compHeight / 2;
	pGInfo->PointsList[1].x = x_ + compWidth / 2;
	pGInfo->PointsList[1].y = y_ + compHeight / 2;

	pManager->Paste_Component();
	pManager->UpdateInterface();
	*/
}

void ActionPaste::Undo()
{
}

void ActionPaste::Redo()
{
}