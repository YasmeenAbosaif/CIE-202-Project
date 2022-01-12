#include "Bulb.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Bulb::Bulb(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

Bulb::Bulb(const Bulb* CopiedBulb)   //The copy constructor
{
	this->setValue(CopiedBulb->getVal());
	this->name = CopiedBulb->name;
}
void Bulb::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawBulb(*m_pGfxInfo, selected, 1); //update to draw resistor
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Bulb::Operate()
{

}


void Bulb:: Save(ofstream& file, int id)
{
	file << "Ana Bulb. \t";
	Component::Save(file, id);
}

string Bulb::getType() const
{
	return type;
}
bool Bulb:: getOn() const
{
	return on;
}

void Bulb::setOn(bool isOn)
{
	on = isOn;
}