#pragma once
#include "Component.h"

class Buzzer :public Component
{
	string name;
public:
	Buzzer(GraphicsInfo* r_GfxInfo);
	Buzzer(const Buzzer* CopiedBuzzer);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the buzzer
	virtual void Save(int id);

};
