#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI\UI.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	int ConnCount;      //Actual number of Connections
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Connection* ConnList[MaxCompCount];	//List of all Connections (Array of pointers)

	UI* pUI; //pointer to the UI


public:	
	ApplicationManager(); //constructor


	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to UI Object
	UI* GetUI();
	/////////////////////////////// getters ////////////////////////////////////////////////

	//I will delete those getters later so do not use them

	//Gets current number of Components
	int GetCompCount();

	//Gets current number of Connections
	int GetConnCount();

	//Gets List of all Components (Array of pointers)
	Component** GetCompList();

	//Gets List of all Connections (Array of pointers)
	Connection** GetConnList();

	/////////////////////////////////////////////////////////////////////////////////////////

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

<<<<<<< HEAD
	//Adds a new connection to the list of connections
	void AddConnection(Connection* pConn);



=======
>>>>>>> refs/remotes/origin/main
public: void Save();
	//destructor
	~ApplicationManager();
};

#endif