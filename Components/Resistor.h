#pragma once
#include "Component.h"

class Resistor:public Component
{
	string value = "val.";
public:
	Resistor(GraphicsInfo *r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the resistor
	virtual void Save(int id);
	void setValue(string val);
};
