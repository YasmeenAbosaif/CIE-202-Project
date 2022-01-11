#pragma once
#include "Action.h"
#include"..\Components\Component.h"
#include "../Components/Connection.h"
#include "ActionSelect.h"

class ActionAmmeter : public Action
{
private:
	double total_current=5;

	int Cx, Cy; //coordinates of the clicked point
	Component* Cmpnt = nullptr;
	//Connection* Cnctn = nullptr;

	UI* pUI;  //Pointer to the user Interfaces

	int CompCount;
	int ConnCount;

	Component** CompList;
	Connection** ConnList;

public:
	void calculateCurrent();
	double getCurrent() const;
	ActionAmmeter(ApplicationManager* pApp);
	virtual void Execute();
	void selectComponent(int x, int y);
	virtual void Undo();
	virtual void Redo();
	virtual ~ActionAmmeter(void);
};

