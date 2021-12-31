#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddBattery.h"
#include "Actions\ActionAddGround.h"
#include "Actions\ActionAddBulb.h"
#include "Actions\ActionAddSwitch.h"
#include "Actions\ActionAddBuzzer.h"
#include "Actions\ActionAddFuse.h"
#include "Actions\ActionSave.h"
<<<<<<< HEAD
#include "Actions\ActionLabel.h"
#include "Actions\ActionSIM_MODE.h"
#include "Actions\ActionEDIT.h"
#include "Actions\ActionDesignModeSwitch.h"
=======
<<<<<<< HEAD
#include "ActionConnect.h"
#include "ActionSelect.h"
=======
>>>>>>> refs/remotes/origin/main
>>>>>>> 8536dfaf5ea30ebe8e6cfe076e156f6f3a4e8baf
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
<<<<<<< HEAD
=======
	
		case SELECT:
			pAct = new ActionSelect(this);
			break;
>>>>>>> 8536dfaf5ea30ebe8e6cfe076e156f6f3a4e8baf

		case ADD_Label:
			pAct = new ActionLabel(this);
			break;
		case EDIT_Label:
			pAct = new ActionEDIT(this);
			break;
		case SIM_MODE:
			pAct = new ActionSIM_MODE(this);
			break;
		case DSN_MODE:
			pAct = new ActionDesignModeSwitch(this);
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
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(pUI);

		for (int i = 0; i < ConnCount; i++)
			ConnList[i]->Draw(pUI);
}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
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
=======
>>>>>>> refs/remotes/origin/main

void ApplicationManager::Save()
{
	
	ofstream outfile;
	
	outfile.open("test.txt");
	//outfile << 1 << "\n" << 2;
	outfile <<"#Components: "<< CompCount << "\n";
	for(int i =0; i<CompCount; i++)
	{
		CompList[i]->Save(outfile, i);
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

// Function for knowing the component for the Editing and labeling

Component* ApplicationManager::take_component_position(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->ISComponent(x, y))
			return CompList[i];
	}
	return nullptr;
}
