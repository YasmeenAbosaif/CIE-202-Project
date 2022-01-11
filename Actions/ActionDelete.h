#pragma once
#include"Action.h"

//Class responsible for deleting action
class ActionDelete : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp label
	int Cx, Cy;	//Center point of the comp label
public:
	ActionDelete(ApplicationManager* pApp);
	virtual ~ActionDelete(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};
