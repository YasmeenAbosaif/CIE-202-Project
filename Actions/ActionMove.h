#pragma once
#include "Action.h"

//Class responsible for adding a new label action
class ActionMove : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp label
	int iX, iY;	//Center point of the comp label

public:
	ActionMove(ApplicationManager* pApp);
	virtual ~ActionMove(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};
