#include "ActionSimulate.h"
#include "..\ApplicationManager.h"

ActionSimulate::ActionSimulate(ApplicationManager* pApp) :Action(pApp)
{
}

ActionSimulate::~ActionSimulate(void)
{
}

void ActionSimulate::Execute()
{

	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();

	//Print Action Message
	pUI->PrintMsg("Simulating: Please choose a tool: ");

	//Get Center point of the area where the Comp should be drawn
	pUI->GetPointClicked(x_click, y_click);

	//Clear Status Bar
	pUI->ClearStatusBar();

	//Read the resistance value
	/*pUI->PrintMsg("Enter the resistance value in Ohms: ");
	string value = pUI->GetSrting();*/

	pUI->ClearStatusBar();

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx info to be used to construct the Comp


	/*
	pGInfo->PointsList[0].x = Cx - compWidth / 2;
	pGInfo->PointsList[0].y = Cy - compHeight / 2;
	pGInfo->PointsList[1].x = Cx + compWidth / 2;
	pGInfo->PointsList[1].y = Cy + compHeight / 2;
	*/

}

void ActionSimulate::Undo()
{}

void ActionSimulate::Redo()
{}

