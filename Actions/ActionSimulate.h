/*#pragma once
#include "action.h"

class ActionSimulate : public Action
{

private:

	int Cx, Cy; //coordinates of the clicked point
	Component* Cmpnt = nullptr;
	//Connection* Cnctn = nullptr;

	UI* pUI;  //Pointer to the user Interfaces

	int CompCount;
	int ConnCount;

	Component** CompList;
	Connection** ConnList;

public:
	ActionSimulate(ApplicationManager* pApp);
	virtual void Execute();
	void selectComponent(int x, int y);
	virtual void Undo();
	virtual void Redo();
	virtual ~ActionSimulate(void);
	void BulbCheck();
};
*/