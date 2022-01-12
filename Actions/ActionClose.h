#pragma once
#include"Action.h"

class ActionClose : public Action
{

public:
	ActionClose(ApplicationManager* pApp);
	virtual  ~ActionClose(void);

	virtual void Execute();
	virtual void Redo();
	virtual void Undo();
};