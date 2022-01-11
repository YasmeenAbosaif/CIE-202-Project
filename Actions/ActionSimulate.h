#pragma once
#include "action.h"

class ActionSimulate : public Action
{
private:
	int x_click, y_click;

public:
	ActionSimulate(ApplicationManager* pApp);
	virtual ~ActionSimulate(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};