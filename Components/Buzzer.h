#pragma once
#include "Component.h"

class Buzzer :public Component
{
private:
	string value="val.";
public:
	Buzzer(GraphicsInfo* r_GfxInfo);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the buzzer
	virtual void  Save(ofstream& file, int id);
	void setValue(string val);
};
