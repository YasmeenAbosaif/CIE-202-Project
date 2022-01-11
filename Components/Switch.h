#pragma once
#include "Component.h"

class Switch :public Component
{
	string name;
public:
	Switch(GraphicsInfo* r_GfxInfo);
	Switch(const Switch* CopiedSwitch);  //const to avoid changing 
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the switch
	virtual void Save(ofstream& file, int id);
	bool open = 0;
};