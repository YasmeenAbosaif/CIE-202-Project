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
			component_->get_Label();
			component_->set_label(new_name);
			pUI->DeleteOldLabel(Cx, Cy);
			pUI->Label_name(new_name, Cx, Cy);
			pUI->ClearStatusBar();
		}
		else if (connection_ != nullptr)
		{
			pUI->PrintMsg(" Write new label for the connection ");
			string newNameConn = pUI->GetSrting();   // Get string is a function for getting label
			connection_->get_LabelConn();
			connection_->set_labelConn(newNameConn);
			pUI->DeleteOldLabel(Cx, Cy);
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
		if (component_ != nullptr)
		{
			pUI->PrintMsg(" Write new value for the choosen component ");
			string newvalue = pUI->GetSrting();
			pUI->ClearStatusBar();
			component_->setValue(newvalue);
		}
	}
	else if (option == "3")
	{
		x2 = Cx; y2 = Cy;
		GraphicsInfo* newcoordinates = new GraphicsInfo(2);
		newcoordinates = connection_->getconnection();
		pUI->PrintMsg("Select the Terminal which you want to change");
		pUI->GetPointClicked(Cx, Cy);
		x1 = Cx; y1 = Cy;
		pUI->ClearStatusBar();
		Component* Comp1 = pManager->take_component_position(Cx, Cy);
		Component* Comp2;
		if (Comp1 != nullptr)
		{
			int componentnumber = connection_->ChooseComponentToDelete(Comp1); // 0 for comp1 or 1 for comp2
			if (componentnumber != 0)
			{
				pUI->PrintMsg("Select the new Component you want to connect to: ");
				pUI->GetPointClicked(Cx, Cy);
				pUI->ClearStatusBar();
				Comp2 = pManager->take_component_position(Cx, Cy);
				if (Comp2 != nullptr) {
					Comp1->DeleteConnectionComponents(connection_);
					if (Cx > Comp2->getComponentCenterX(pUI)) 
					{
						Comp2->addTerminal2Connection(connection_);
						newcoordinates->PointsList[componentnumber - 1].x = Comp2->getComponentCenterX(pUI) + (pUI->getCompWidth() / 2);
						newcoordinates->PointsList[componentnumber - 1].y = Comp2->getComponentCenterY(pUI);
					}
					else 
					{
						Comp2->addTerminal1Connection(connection_);
						newcoordinates->PointsList[componentnumber - 1].x = Comp2->getComponentCenterX(pUI) - (pUI->getCompWidth() / 2);
						newcoordinates->PointsList[componentnumber - 1].y = Comp2->getComponentCenterY(pUI);
					}
					connection_->setNewComponent(componentnumber, Comp2);
					//pUI->DeleteOldConnection(x1, y1, x2 + 5, y2 + 5);
				}
			}
			else if (option == "4")
			{
				pUI->ClearStatusBar();
			}

		}
	}
	component_ = nullptr;
	connection_ = nullptr;
}

void ActionEDIT::Undo()
{}
void ActionEDIT::Redo()
{}