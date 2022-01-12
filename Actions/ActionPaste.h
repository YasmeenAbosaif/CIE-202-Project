#pragma once
#include"Action.h"

class ActionPaste : public Action
{
private:
	//Coordinates to get the copied component position
	int Cx, Cy;	//Center point of the comp 
public:
	ActionPaste(ApplicationManager*pApp);
	virtual  ~ActionPaste(void);
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Redo() ;
	virtual void Undo() ;
};