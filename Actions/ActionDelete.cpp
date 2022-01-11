#include"ActionDelete.h"
#include "..\ApplicationManager.h"
#include <string>

ActionDelete::ActionDelete (ApplicationManager* pApp) : Action(pApp)
{
}

ActionDelete::~ActionDelete(void)
{
}

void ActionDelete::Execute()
{
	Connection* conn = nullptr;
	Component* comp = nullptr;
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	pManager->UpdateInterface();
	pUI->PrintMsg("(1) >>> For deleting component (2) >>> For deleting connection");
	string chosen = pUI->GetSrting();
	if (chosen == "1")
	{
		pUI->PrintMsg("Enter the number of components you want to delete ");
		string num = pUI->GetSrting();  //num is the number of comp or connections want to delete 
		int num_comp = stoi(num);   // stoi is a function for changing from string to num
		pUI->ClearStatusBar();
		for (int i = 0; i < num_comp; i++)
		{
			pUI->PrintMsg("Choose Component you want to delete ");
			pUI->GetPointClicked(Cx, Cy);
			pUI->ClearStatusBar();
			comp = pManager->take_component_position(Cx, Cy);
			if (comp != nullptr)
			{
				pManager->DeleteComponent(comp);
				pManager->update_comp_connlist();
			}
		}
		pUI->ClearDrawingArea();
		pManager->UpdateInterface();
	}
	else if (chosen == "2")
	{
		pUI->PrintMsg("Enter the number of connections you want to delete ");
		string num_ = pUI->GetSrting();  //num is the number of comp or connections want to delete 
		int num_conn = stoi(num_);   // stoi is a function for changing from string to num
		pUI->ClearStatusBar();
		for (int i = 0; i < num_conn; i++)
		{
			pUI->PrintMsg("Choose Connection you want to delete ");
			pUI->GetPointClicked(Cx, Cy);
			pUI->ClearStatusBar();
			conn = pManager->take_connection_position(Cx, Cy);
			if (conn != nullptr)
			{
				pManager->DeleteConnection(conn);
				pManager->update_comp_connlist();
			}
		}
		pUI->ClearDrawingArea();
		pManager->UpdateInterface();
	}
	comp = nullptr;
	pManager = nullptr;
	conn = nullptr;
}

void ActionDelete::Undo()
{}

void ActionDelete::Redo()
{}