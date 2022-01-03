#pragma once
#include "ActionConnect.h"
#include "ApplicationManager.h"
#include "Defs.h"

ActionConnect::ActionConnect(ApplicationManager* pApp) :Action(pApp)
{
	pUI = pApp->GetUI();

	CompCount = pApp->GetCompCount();
	ConnCount = pApp->GetConnCount();

	CompList = pApp->GetCompList();
	ConnList = pApp->GetConnList();
}

ActionConnect::~ActionConnect(void)
{
}

void ActionConnect::selectcomponent(int x, int y)
{
	ActionSelect* pSELECT = new ActionSelect(pManager, x, y);
	if (pSELECT)
	{
		pSELECT->Execute();
		delete pSELECT;
		pSELECT = nullptr;
	}
	pManager->UpdateInterface();
}

void ActionConnect::terminalXcoord(Component* cmpnt, int cx, GraphicsInfo* pGInfo,int pointindex)
{
	if (cmpnt-> whichTerminal(cx) == LEFT)
	{
		pGInfo->PointsList[pointindex].x = cmpnt->getcornerpoint_X1();
	}
	else
		pGInfo->PointsList[pointindex].x = cmpnt->getcornerpoint_X2();
}

void ActionConnect::AddTermConnection(Component* cmpnt, int cx,Connection* ptr)
{
	if (cmpnt->whichTerminal(cx) == LEFT)
	{
		cmpnt->AddTerm1Connection(ptr);
	}
	else
		cmpnt->AddTerm2Connection(ptr);
}

void ActionConnect::Execute()
{
	int Count = 0;
	pUI->PrintMsg("Please select two components");
	do 
	{ 
		pUI->GetPointClicked(C1x, C1y);
		selectcomponent(C1x, C1y);
	
		pUI->GetPointClicked(C2x, C2y);
		selectcomponent(C2x, C2y);

		pUI->ClearStatusBar();

		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->isInRegion(C1x, C1y, pUI))
				Cmpnt1 = CompList[i];
		}

		
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->isInRegion(C2x, C2y, pUI))
				Cmpnt2 = CompList[i];
		}

		if (Cmpnt1 == nullptr || Cmpnt2 == nullptr)
			pUI->PrintMsg("Try Again! please select two components to connect them");

	} while (Cmpnt1 == nullptr || Cmpnt2 == nullptr);
	

	GraphicsInfo* pGInfo = new GraphicsInfo(2); //Gfx endpoints info of the connection

	/////////////// Calculate the termenal points(endpoints of the connection)  ///////////////

	terminalXcoord(Cmpnt1, C1x, pGInfo,0);
	pGInfo->PointsList[0].y = Cmpnt1->getcenterpoint_y();

	terminalXcoord(Cmpnt2, C2x, pGInfo,1);
	pGInfo->PointsList[1].y = Cmpnt2->getcenterpoint_y();

	
	///////////////////////////////////////////////////////////////////////////////////////////
	

	Connection* ptr = new Connection(pGInfo, Cmpnt1, Cmpnt2);
	pManager->AddConnection(ptr);
	AddTermConnection(Cmpnt1, C1x, ptr);
	AddTermConnection(Cmpnt2, C2x, ptr);
}

void ActionConnect::Undo()
{}

void ActionConnect::Redo()
{}



