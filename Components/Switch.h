#pragma once
#include "Component.h"

class Switch :public Component
{
	
public:
	Switch(GraphicsInfo* r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the switch
	virtual void  Save(ofstream& file, int id);
	bool open = 0;
};