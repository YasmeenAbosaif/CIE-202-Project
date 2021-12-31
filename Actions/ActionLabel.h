#pragma once
#include "Action.h"

//Class responsible for adding a new label action
class ActionLabel : public Action
{
private:
	//Parameters for rectangular area to be occupied by the comp label
	int Cx, Cy;	//Center point of the comp label
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	ActionLabel(ApplicationManager* pApp);
	virtual ~ActionLabel(void);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};