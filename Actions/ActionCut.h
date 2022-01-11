#pragma once
#include"Action.h"
//Class responsible for adding a new resistor action
class ActionCut : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp
	int Cx, Cy , x_ , y_;	//Center point of the comp
	

public:
	ActionCut(ApplicationManager* pApp);
	virtual ~ActionCut(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
