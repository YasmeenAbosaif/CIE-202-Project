#pragma once
#include "Component.h"

class Fuse :public Component
{
	string name;
public:
	string type = "Fuse";
	string getType() const;
	Fuse(GraphicsInfo* f_GfxInfo);
	Fuse(const Fuse* CopiedFuse);   //The copy constructor
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws the fuse
	virtual void Save(ofstream& file, int id);

};
