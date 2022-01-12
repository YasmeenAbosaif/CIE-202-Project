#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddBattery.h"
#include "Actions\ActionAddGround.h"
#include "Actions\ActionAddBulb.h"
#include "Actions\ActionAddSwitch.h"
#include "Actions\ActionAddBuzzer.h"
#include"Actions\ActionAddFuse.h"
#include"Actions\ActionSave.h"
#include"Actions\ActionLabel.h"
#include"Actions\ActionSIM_MODE.h"
#include"Actions\ActionEDIT.h"
#include"Actions\ActionDesignModeSwitch.h"
#include"Actions\ActionSelect.h"
#include"Actions\ActionConnect.h"
#include"Actions\ActionDelete.h"
#include"Actions/ActionOptions.h"
#include"Actions/ActionCopy.h"
#include"Actions/ActionCut.h"
#include"Actions/ActionPaste.h"
#include"Actions/ActionMove.h"
#include"Actions/ActionVoltmeter.h"
#include"Actions/ActionAmmeter.h"
#include"Actions/ActionClose.h"
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
		case VOLTMETER_:
			pAct = new ActionVoltmeter(this);
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
		case MOVE:
			pAct = new ActionMove(this);
			break;
		case ClOSE:
			pAct = new ActionClose(this);
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


// Function for Copy & Cut the component 
void ApplicationManager::Copy_Cut_Component(Component* copiedcomp)
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
					Battery* NewCopiedComponent = new Battery(*copiedBattery);
					copycomponent = NewCopiedComponent;
				}
				else if (copiedResistor != nullptr)
				{
					Resistor* NewCopiedComponent = new Resistor(*copiedResistor);
					copycomponent = NewCopiedComponent;
				}
				else if (copiedBulb != nullptr)
				{
					Bulb* NewCopiedComponent = new Bulb(*copiedBulb);
					copycomponent = NewCopiedComponent;
				}
				else if (copiedBuzzer != nullptr)
				{
					Buzzer* NewCopiedComponent = new Buzzer(*copiedBuzzer);
					copycomponent = NewCopiedComponent;
				}
				else if (copiedFuse != nullptr)
				{
					Fuse* NewCopiedComponent = new Fuse(*copiedFuse);
					copycomponent = NewCopiedComponent;
				}
				else if (copiedGround != nullptr)
				{
					Ground* NewCopiedComponent = new Ground(*copiedGround);
					copycomponent = NewCopiedComponent;
				}
				else if (copiedSwitch != nullptr)
				{
					Switch* NewCopiedComponent = new Switch(*copiedSwitch);
					copycomponent = NewCopiedComponent;
				}
			}
		}
	}
}

//=============================== For saving the copy to be pasted =========================================

void ApplicationManager::setCopyCopmonent(Component* selectedcopy)
{
	copycomponent = selectedcopy;
}

Component* ApplicationManager::getCopyCopmonent()
{
	return copycomponent;
}

//=========================================================================================================//
bool ApplicationManager::circuitValidation()
{
	pUI = GetUI();
	int Groundcount = 0;
	string message;

	int error1count = 0;
	int error2count = 0;
	int error3count = 0;

	bool check1 = false;  //check series connection
	bool check2 = false;  //check that there is at least one ground
	bool check3 = false;  //check closed loop

	string error1 = " ERROR:All connections must be series   ";
	string error2 = " ERROR:The circuit must contain only one Ground   ";
	string error3 = " ERROR:The circuit must be closed   ";

	if (CompCount)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (error1count == 0) //------------check1
			{
				try
				{
					if (!(CompList[i]->SeriesConnCheck()))
					{
						check1 = false;
						error1count++;
						throw error1;
					}
					else
						check1 = true;
				}
				catch (string error1)
				{
					message = message + error1;
				}
			}

			if (error2count == 0) //------------check2
			{
				Ground* Groundptr = dynamic_cast<Ground*>(CompList[i]);

				if (Groundptr != nullptr)
					Groundcount = Groundcount + 1;
				try
				{
					if (Groundcount != 1)
					{
						check2 = false;
						error2count++;
						throw error2;
					}
					else
						check2 = true;
				}
				catch (string error2)
				{
					message = message + error2;
				}
			}

			if (error3count == 0)    //------------check3
			{
				Switch* Switchptr = dynamic_cast<Switch*>(CompList[i]);
				if (Switchptr != nullptr)
				{
					try
					{
						if (!(Switchptr->getOpen()) && check1 == false)  ///getstatus() function is not yet implemented in UI class or selet switch
						{
							check3 = false;
							error3count++;
							throw error3;
						}

						else
							check3 = true;
					}
					catch (string error3)
					{
						message = message + error3;
					}
				}
			}
		}

		if (message.empty())
			return true;
		else
		{
			pUI->PrintMsg(message);
			return false;
		}
	}
	else
	{
		pUI->PrintMsg("ERROR:can't simulate without a given circuit");
		return false;
	}
}



