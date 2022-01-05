#include "ActionLabel.h"
#include "..\ApplicationManager.h"

ActionLabel::ActionLabel(ApplicationManager* pApp) :Action(pApp)
{
}

ActionLabel::~ActionLabel(void)
{
}

void ActionLabel::Execute()
{
	//Get a Pointer to the user Interfaces
	UI* pUI = pManager->GetUI();
	//Print Action Message
	pUI->PrintMsg("Choose the needed component or connection");

	//Get Center point of the area where the Comp label should be written
	pUI->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pUI->ClearStatusBar();

	// Label  for component & connection 

	Component* component_ = pManager->take_component_position(Cx, Cy);  // Take the label position for the drawn component
	Connection* connection_ = pManager->take_connection_position(Cx, Cy);  // Take the label position for the drawn connection
	if (component_ != nullptr)              // we can check it by nullptr
	{
		pUI->PrintMsg(" Write label for the component ");
		string name = pUI->GetSrting();   // Get string is a function for getting label
		component_->set_label(name);
		component_->get_Label();
		pUI->ClearStatusBar();
		pUI->Label_name(name,Cx,Cy);
	}
	else if (connection_ != nullptr)
	{
		pUI->PrintMsg(" Write label for the connection ");
		string name = pUI->GetSrting();   // Get string is a function for getting label
		connection_->set_labelConn(name);
		connection_->get_LabelConn();
		pUI->ClearStatusBar();
		pUI->Label_name(name, Cx, Cy);
	}
	else
	{
		pUI->PrintMsg(" Neither Component nor connection is selected ");
	}
}

void ActionLabel::Undo()
{}

void ActionLabel::Redo()
{}