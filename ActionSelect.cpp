#include "ActionSelect.h"
#include "ApplicationManager.h"

ActionSelect::ActionSelect(ApplicationManager* pApp, int Cx, int Cy) :Action(pApp)
{
	this->Cx = Cx;
	this->Cy = Cy;

	pUI = pApp->GetUI();  //Pointer to the user Interfaces

	CompCount = pApp->GetCompCount();
	ConnCount = pApp->GetConnCount();

	CompList = pApp->GetCompList();
	ConnList = pApp->GetConnList();
}


ActionSelect::~ActionSelect(void)
{
}

Component* ActionSelect::Select_Component(int x, int y)
{
	if (CompList != nullptr)
	{
		for (int i = 0; i < CompCount; i++)
		{

			if (CompList[i]->isInRegion(x, y, pUI))
			{
				CompList[i]->setSelected(true);
				CompList[i]->Draw(pUI);
				return CompList[i];
			}
		}

		return nullptr;	
	}
}

/**/
Connection* ActionSelect::Select_Connection(int x, int y)
{
	
	if (ConnList != nullptr)
	{
		for (int i = 0; i < ConnCount; i++)
		{
			if (ConnList[i]->isInRegion(x, y, pUI))
			{

				ConnList[i]->setSelected(true);
				ConnList[i]->Draw(pUI);
				return ConnList[i];
			}
		}

		return nullptr;
	}
}
/**/

/**/
void ActionSelect::unSelect()
{
	for (int i = 0; i < CompCount; i++)
		CompList[i]->setSelected(false);

	for (int i = 0; i < ConnCount; i++)
        ConnList[i]->setSelected(false);
}
/**/

void ActionSelect::Execute()
{
	if (Cx == 0 && Cy == 0)
	{
		//Get Center point of the area where the Comp should be drawn
		pUI->GetPointClicked(Cx, Cy);
	}

	//if a component is clicked this component will be selected else it will return nullptr
	Component* selected_Component = Select_Component(Cx, Cy);

	//if a connection is clicked this connection will be selected else it will return nullptr
	Connection* selected_Connection =Select_Connection(Cx, Cy);

	//else unselect all components & connections
	if (selected_Component == nullptr && selected_Connection == nullptr)
		unSelect();


	/*

	//Print Action Message
	pUI->PrintMsg("Adding a new resistor: Click anywhere to add");

	//Clear Status Bar
	pUI->ClearStatusBar();


	*/
}


void ActionSelect::Undo()
{}

void ActionSelect::Redo()
{}

