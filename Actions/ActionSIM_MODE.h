#pragma once
#include "Action.h"
class ActionSIM_MODE : public Action
{
public :
	ActionSIM_MODE(ApplicationManager* pApp);
	virtual ~ActionSIM_MODE(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};