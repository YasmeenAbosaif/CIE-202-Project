#include "ActionEDIT.h"
#include "..\ApplicationManager.h"

ActionEDIT::ActionEDIT(ApplicationManager* pApp) : Action(pApp)
{
}

ActionEDIT::~ActionEDIT(void)
{
}

void ActionEDIT::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	//Print Action Message
	pUI->PrintMsg("Choose the needed component to edit its name or value");

	//Get Center point of the area where the Comp label should be written
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();

	// Edit label for both component & connection

	Component* component_ = pManager->take_component_position(Cx, Cy);  // Take the label position for the drawn component

	Connection* connection_ = pManager->take_connection_position(Cx, Cy);  // Take the label position for the drawn connection

	pUI->PrintMsg("Enter 1 for editing component or connection name  & 2 for editing component value  & 3 for editing connection & 4 for cancel");

	string option;   // string works but char doesn't work
	option = pUI->GetSrting();

	if (option == "1")            // ''  for char but "" for string
	{
		if (component_ != nullptr)              // we can check it by nullptr
		{
			pUI->PrintMsg(" Write new label for the component ");
			string new_name = pUI->GetSrting();   // Get string is a function for getting label
			pUI->DeleteOldLabel(Cx, Cy);
			component_->get_Label();
			component_->set_label(new_name);
			pUI->Label_name(new_name, Cx, Cy);
			pUI->ClearStatusBar();
		}
		else if (connection_ != nullptr)
		{
			pUI->PrintMsg(" Write new label for the connection ");
			string newNameConn = pUI->GetSrting();   // Get string is a function for getting label
			pUI->DeleteOldLabel(Cx, Cy);
			connection_->get_LabelConn();
			connection_->set_labelConn(newNameConn);
			pUI->Label_name(newNameConn, Cx, Cy);
			pUI->ClearStatusBar();
		}
		else
		{
			pUI->PrintMsg(" Neither Component nor connection is selected ");
		}
	}
	else if (option == "2")
	{
		switch(Elements)
		{
		case RESISTOR : //for resistance 
			pUI->PrintMsg("Write the new value for resistor");
			pUI->ClearStatusBar();
			string new_resistanceValue = pUI->GetSrting();
			
		}
	}
	else if (option == "3")
	{
		
	}
	else if (option == "4")
	{
		pUI->ClearStatusBar();
	}
	pManager->UpdateInterface();
}

void ActionEDIT::Undo()
{}

void ActionEDIT::Redo()
{}