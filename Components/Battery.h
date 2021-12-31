#pragma once
#include "Component.h"

class Battery :public Component
{
	string value = "val.";
public:
	Battery(GraphicsInfo* r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the battery
	virtual void  Save(ofstream& file, int id);
	void setValue(string val);

};
