#pragma once
#include"Action.h"

//Class responsible for deleting action
class ActionCopy : public Action
{
private:
	
	int Cx, Cy , x_ , y_ ; // (x_ , y_)  for the copied component , (Cx , Cy) for knowing old object
public:
	ActionCopy(ApplicationManager* pApp);
	virtual ~ActionCopy(void);
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();


};
