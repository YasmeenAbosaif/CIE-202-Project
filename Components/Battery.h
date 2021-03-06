#pragma once
#include "Component.h"

class Battery :public Component
{
	//int Cx, Cy;	//Center point of the comp
	//int x1, y1, x2, y2;	//Two corners of the rectangluar area
	string name;
	string emf = "0";
public:
	string getType() const;
	const string type = "Battery";
	Battery(GraphicsInfo* r_GfxInfo);   //Contructor
	Battery(const Battery& CopiedBattery);  //const to avoid changing , "&" to avoid memory leakage 
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the battery
	virtual void Save(ofstream& file, int id);
	//void setEmf(string newEmf);
};
