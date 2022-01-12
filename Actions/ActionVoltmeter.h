#pragma once
#include "Action.h"
#include"..\Components\Component.h"
#include "../Components/Connection.h"
#include "ActionSelect.h"

class ActionVoltmeter : public Action
{
private:
	//double emf = 0;
	//double Rtotal = 0;
	double voltage = 10;
	double total_current = 0;

	int Cx, Cy; //coordinates of the clicked point
	Component* Cmpnt = nullptr;
	//Connection* Cnctn = nullptr;

	UI* pUI;  //Pointer to the user Interfaces

	int CompCount;
	int ConnCount;

	Component** CompList;
	Connection** ConnList;

public:
	void calculateVoltage();
	void calculateCurrent();
	double getVoltage() const;
	ActionVoltmeter(ApplicationManager* pApp);
	virtual void Execute();
	void selectComponent(int x, int y);
	virtual void Undo();
	virtual void Redo();
	virtual ~ActionVoltmeter(void);
};

