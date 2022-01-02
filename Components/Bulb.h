#pragma once
#include "Component.h"

	class Bulb :public Component
{
		string value = "val.";
public:
	Bulb(GraphicsInfo* r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the bulb
	virtual void   Save(ofstream& file, int id);
	void setValue(string val);
	string getValue();
};
