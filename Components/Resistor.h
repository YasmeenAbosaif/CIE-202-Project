#pragma once
#include "Component.h"

class Resistor:public Component
{
	string name;
public:
	const string type = "Resistor";
	string getType() const;
	Resistor(GraphicsInfo *r_GfxInfo);
	Resistor(const Resistor* CopiedResistor );  //const to avoid changing 
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the resistor
	virtual void Save(ofstream& file, int id);

};
