#pragma once
#include "Action.h"
#include "ActionSelect.h"

//forward class declaration
class Component;
class UI;
class Connection;
struct GraphicsInfo;
class ActionSelect;


//Class responsible for adding a new connection action
class ActionConnect :public Action
{
private:

	int x1, y1, x2, y2;	//Two endpoints of the connection
	int C1x, C1y, C2x, C2y;  //coordinates of the two clicked points
	Component* Cmpnt1 = nullptr, * Cmpnt2 = nullptr;

	UI* pUI;  //Pointer to the user Interfaces

	int CompCount;
	int ConnCount;

	Component** CompList;
	Connection** ConnList;

public:
	ActionConnect(ApplicationManager* pApp);
	virtual ~ActionConnect(void);

	//select the component clicked
	void selectcomponent(int x, int y);

	//based on whether its a left or right terminal this function assign the x-coordinate to the endpoint
	void terminalXcoord(Component* cmpnt, int cx, GraphicsInfo* pGInfo, int pointindex);

	// add a connection pointer to connections list of pointers located in the component
	void AddTermConnection(Component* cmpnt, int cx, Connection* ptr);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

