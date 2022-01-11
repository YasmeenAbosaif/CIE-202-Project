#pragma once
#include"Action.h"
//Class responsible for deleting action
class ActionOptions : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp label
	int Cx, Cy;	//Center point of the comp label

public:
	ActionOptions(ApplicationManager* pApp);
	virtual ~ActionOptions(void);
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
