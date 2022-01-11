#include "Resistor.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

Resistor::Resistor(const Resistor* CopiedResistor ) //The copy constructor
{
	this->m_pGfxInfo = new GraphicsInfo (2);
	this->value = CopiedResistor->value;
	this->name = CopiedResistor->name;
}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Resistor::Operate()
{

}

void Resistor::setValue(string val)
{
	value = val;
}


void Resistor::Save(int id)
{
	
}
