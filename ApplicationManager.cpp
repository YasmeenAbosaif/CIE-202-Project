#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddBattery.h"
#include "Actions\ActionAddGround.h"
#include "Actions\ActionAddBulb.h"
#include "Actions\ActionAddSwitch.h"
#include "Actions\ActionAddBuzzer.h"
#include "Actions\ActionAddFuse.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLabel.h"
#include "Actions\ActionSIM_MODE.h"
#include "Actions\ActionEDIT.h"
#include "Actions\ActionDesignModeSwitch.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionConnect.h"
#include "Actions\ActionDelete.h"
#include"Actions/ActionOptions.h"
#include"Actions/ActionCopy.h"
#include"Actions/ActionCut.h"
#include"Actions/ActionPaste.h"
#include"Actions/ActionAmmeter.h"
#include <fstream>

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = nullptr;

	//Creates the UI Object & Initialize the UI
	pUI = new UI;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}

void ApplicationManager::AddConnection(Connection* pConn)
{
	ConnList[ConnCount++] = pConn;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = nullptr;
	switch (ActType)
	{
		case ADD_RESISTOR:
			pAct= new ActionAddRes(this);
			break;
		case ADD_BATTERY:
			pAct = new ActionAddBattery(this);
			break;
		case ADD_GROUND:
			pAct = new ActionAddGround(this);
			break;
		case ADD_SWITCH:
			pAct = new ActionAddSwitch(this);
			break;
		case ADD_LAMP:
			pAct = new ActionAddBulb(this);
			break;
		case ADD_BUZZER:
			pAct = new ActionAddBuzzer(this);
			break;
		case ADD_FUSE:
			pAct = new ActionAddFuse(this);
			break;
		case SAVE:
			pAct = new ActionSave(this);
			break;
		case ADD_CONNECTION:
			pAct = new ActionConnect(this);
			break;
		case SELECT:
			pAct = new ActionSelect(this);
			break;
		case ADD_Label:
			pAct = new ActionLabel(this);
			break;
		case EDIT_Label:
			pAct = new ActionEDIT(this);
			break;
		case SIM_MODE:
			pAct = new ActionSIM_MODE(this);
			break;

		case AMMETER_:
			pAct = new ActionAmmeter(this);
				break;
		case DSN_MODE:
			pAct = new ActionDesignModeSwitch(this);
			break;
		case DEL :
			pAct = new ActionDelete(this);
			break;
		case OPTIONS :
			pAct = new ActionOptions(this);
			break;
		case COPY:
			pAct = new ActionCopy(this);
			break;
		case PASTE:
			pAct = new ActionPaste(this);
			break;
		case CUT:
			pAct = new ActionCut(this);
			break;
		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = nullptr;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		update_comp_connlist();
		for (int i = 0; i < CompCount; i++)
		{
			CompList[i]->Draw(pUI);
		}
		for (int i = 0; i < ConnCount; i++)
		{
			ConnList[i]->Draw(pUI);
		}
}



////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////


//I will delete those getters later so do not use them

int ApplicationManager::GetCompCount()
{
	return CompCount;
}

int ApplicationManager::GetConnCount()
{
	return ConnCount;
}

Component** ApplicationManager::GetCompList()
{
	return CompList;
}

Connection** ApplicationManager::GetConnList()
{
	return ConnList;
}


///////////////////////////////////////////////////////////////


void ApplicationManager::Save()
{
	ofstream outfile;

	outfile.open("test.txt");
	//outfile << 1 << "\n" << 2;
	outfile << "#Components: " << CompCount << "\n";
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Save(outfile, i);
	}
	outfile << "#Connections: " << ConnCount << "\n";
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->Save(outfile, i);
	}
	outfile.close();

}

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];

	for (int i = 0; i < ConnCount; i++)
		delete ConnList[i];

	delete pUI;
	
}

// ===========Functions for the Editing , labeling , Deleting , Copy , paste =======================

//Function to take posistion of component
Component* ApplicationManager::take_component_position(int x, int y)  
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->ISComponent(x, y))
			return CompList[i];
	}
	return nullptr;
}

//Function to take posistion of connection
Connection* ApplicationManager::take_connection_position(int x, int y)  
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->isInRegion(x, y,pUI))
			return ConnList[i];
	}
	return nullptr;
}

//This function for deleting the component
void ApplicationManager::DeleteComponent(Component* pComp)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == pComp && pComp != nullptr)
		{
			Connection** conn1 = CompList[i]->get_terminal(RIGHT);
			Connection** conn2 = CompList[i]->get_terminal(LEFT);
			if (conn1 != nullptr)
				for (int k = 0; k < 20; k++)   // We make different for loop because the limit for num connections = 20
				{
					DeleteConnection(conn1[k]);
				}
			if (conn2 != nullptr)
				for (int k = 0; k < 20; k++)
				{
					DeleteConnection(conn2[k]);
				}
			delete CompList[i];
			CompList[i] = nullptr;
		}
	}
}

//This function for deleting the connection
void ApplicationManager::DeleteConnection(Connection* pConn)
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == pConn && pConn != nullptr)
		{
			Component* comp1 = ConnList[i]->getComp(1);
			Component* comp2 = ConnList[i]->getComp(2);
			if (comp1 != nullptr)
				comp1->DeleteConnectionComponents(ConnList[i]);
			if (comp2 != nullptr)
				comp2->DeleteConnectionComponents(ConnList[i]);
			delete ConnList[i];
			ConnList[i] = nullptr;
		}
	}
}

void ApplicationManager::update_comp_connlist()
{
	  //Don't forget should be initialized by zero
	Component* newcomplist[MaxCompCount];
	int newnum = 0;
	//====================================== for rearranging components after deleting components
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != nullptr)
		{
			newcomplist[newnum] = CompList[i];
			newnum++;
		}
	}
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i] = newcomplist[i];
		newcomplist[i] = nullptr;           //Should be zero again 
	}
	CompCount = newnum;
	newnum = 0;
	//===================================== = for rearranging connections after deleting connections
	Connection* newconnlist[MaxConnCount];
	for (int i = 0; i < ConnCount; i++)
	{
		if (CompList[i] != nullptr)
		{
			newconnlist[newnum] = ConnList[i];
			newnum++;
		}
	}
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i] = newconnlist[i];
		newconnlist[i] = nullptr;            //Should be zero again 
	}
	ConnCount = newnum;
	newnum = 0;
}

// Function for Copy the component 
void ApplicationManager::Copy_Component(Component* copiedcomp )
{
	if (copiedcomp != nullptr)
	{
		Battery* copiedBattery = dynamic_cast <Battery*> (copiedcomp);
		Resistor* copiedResistor = dynamic_cast <Resistor*> (copiedcomp);
		Bulb* copiedBulb = dynamic_cast <Bulb*> (copiedcomp);
		Buzzer* copiedBuzzer = dynamic_cast <Buzzer*> (copiedcomp);
		Fuse* copiedFuse = dynamic_cast <Fuse*> (copiedcomp);
		Ground* copiedGround = dynamic_cast <Ground*> (copiedcomp);
		Switch* copiedSwitch = dynamic_cast <Switch*> (copiedcomp);
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == copiedcomp)
			{
				if (copiedBattery != nullptr)
				{
					Battery* NewCopiedComponent = new Battery (copiedBattery ); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
				else if (copiedResistor != nullptr)
				{
					Resistor* NewCopiedComponent = new Resistor(copiedResistor ); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
				else if (copiedBulb != nullptr)
				{
					Bulb* NewCopiedComponent = new Bulb(copiedBulb ); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
				else if (copiedBuzzer != nullptr)
				{
					Buzzer* NewCopiedComponent = new Buzzer(copiedBuzzer ); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
				else if (copiedFuse != nullptr)
				{
					Fuse* NewCopiedComponent = new Fuse(copiedFuse ); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
				else if (copiedGround != nullptr)
				{
					Ground* NewCopiedComponent = new Ground(copiedGround ); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
				else if (copiedSwitch != nullptr)
				{
					Switch* NewCopiedComponent = new Switch(copiedSwitch); //Should be constructor
					copycomponent = NewCopiedComponent;
				}
			}
		}
	}
}

// Function for Copy the component 
void ApplicationManager::Cut_Component(Component* copiedcomp , GraphicsInfo* r_GfxInfo)
{
	if (copiedcomp != nullptr)
	{
		Battery* copiedBattery = dynamic_cast <Battery*> (copiedcomp);
		Resistor* copiedResistor = dynamic_cast <Resistor*> (copiedcomp);
		Bulb* copiedBulb = dynamic_cast <Bulb*> (copiedcomp);
		Buzzer* copiedBuzzer = dynamic_cast <Buzzer*> (copiedcomp);
		Fuse* copiedFuse = dynamic_cast <Fuse*> (copiedcomp);
		Ground* copiedGround = dynamic_cast <Ground*> (copiedcomp);
		Switch* copiedSwitch = dynamic_cast <Switch*> (copiedcomp);
		Switch* NewCopiedComponent = new Switch(copiedSwitch);
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == copiedcomp)
			{
				Battery* NewCopiedBattery = new Battery(copiedBattery);
				Resistor* NewCopiedResistor = new Resistor(copiedResistor);
				Bulb* NewCopiedBulb = new Bulb(copiedBulb);
				Fuse* NewCopiedFuse = new Fuse(copiedFuse);
				Buzzer* NewCopiedBuzzer = new Buzzer(copiedBuzzer);
				Ground* NewCopiedGround = new Ground(copiedGround);
				Switch* NewCopiedSwitch = new Switch(copiedSwitch);

				if (copiedBattery != nullptr)
				{
					copycomponent = NewCopiedBattery;
				}
				else if (copiedResistor != nullptr)
				{
					copycomponent = NewCopiedResistor;
				}
				else if (copiedBulb != nullptr)
				{
					copycomponent = NewCopiedBulb;
				}
				else if (copiedBuzzer != nullptr)
				{
					copycomponent = NewCopiedBuzzer;
				}
				else if (copiedFuse != nullptr)
				{
					copycomponent = NewCopiedFuse;
				}
				else if (copiedGround != nullptr)
				{
					copycomponent = NewCopiedGround;
				}
				else if (copiedSwitch != nullptr)
				{
					copycomponent = NewCopiedSwitch;
				}
				DeleteComponent(CompList[i]);
				update_comp_connlist();
			}
		}
	}
}

// Function for Paste copy

void ApplicationManager :: Paste_Component(GraphicsInfo* r_GfxInfo)
{
	AddComponent(copycomponent);
}

//==========================================================================================================

//void ApplicationManager::setCopyCopmonent(Component* selectedcopy)
//{
//	copycomponent = selectedcopy;
//}
//
//Component* ApplicationManager::getCopyCopmonent()
//{
//	return copycomponent;
//}


