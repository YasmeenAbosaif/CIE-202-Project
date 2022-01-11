#pragma once
#include "Component.h"

	class Bulb :public Component
{
		string name;
public:
	Bulb(GraphicsInfo* r_GfxInfo);
	Bulb(const Bulb* CopiedBulb);  //const to avoid changing , "&" to avoid memory leakage 
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the bulb
	virtual void Save(ofstream& file, int id);

};
