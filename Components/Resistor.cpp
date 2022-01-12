#include "Resistor.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

Resistor::Resistor(const Resistor& CopiedResistor)   //The copy constructor
{
	this->m_pGfxInfo = new GraphicsInfo(2);
	this->setValue(CopiedResistor.getVal());
	this->set_label(CopiedResistor.get_Label());
}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo, selected); //update to draw resistor
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Resistor::Operate()
{

}



void Resistor::Save(ofstream& file, int id)
{
	file << "Ana Resistor. \t";
	Component::Save(file, id);
}

string Resistor::getType() const
{
	return type;
}