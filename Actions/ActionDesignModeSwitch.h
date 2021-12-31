#pragma once
#include "Action.h"
class ActionDesignModeSwitch : public Action
{
public:
	ActionDesignModeSwitch(ApplicationManager* pApp);
	virtual ~ActionDesignModeSwitch(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};