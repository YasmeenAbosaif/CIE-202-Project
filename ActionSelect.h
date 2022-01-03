#pragma once
#include "Actions/Action.h"
#include "Components/Resistor.h"

//Class responsible for select/unselect Action 
class ActionSelect : public Action
{
private:
	
	int Cx, Cy;	//clicked point 

	UI* pUI; //Pointer to the user Interfaces

	int CompCount;
	int ConnCount;

	Component** CompList;
	Connection** ConnList;


public:

	ActionSelect(ApplicationManager* pApp, int Cx = 0, int Cy = 0); //  constructor

	virtual ~ActionSelect(void);   //destructor


	
	////////////////////////////////	Member functions used in Execute	/////////////////////////////
	Component* Select_Component(int x, int y);


	Connection* Select_Connection(int x, int y);


	void unSelect();
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	
	virtual void Execute();		//Execute action (code depends on action type)

	virtual void Undo();

	virtual void Redo();


};