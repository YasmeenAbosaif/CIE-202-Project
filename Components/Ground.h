#pragma once
#include "Component.h"

class Ground :public Component
{
	string name;
public:
	string type = "Ground";
	string getType() const;
	Ground(GraphicsInfo* r_GfxInfo);
	Ground(const Ground& CopiedGround);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*);	//Draws ground
	virtual void Save(ofstream& file, int id);

};
