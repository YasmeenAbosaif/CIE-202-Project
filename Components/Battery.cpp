#include "Battery.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Battery::Battery(GraphicsInfo* b_GfxInfo) :Component(b_GfxInfo)
{
}

Battery::Battery(const Battery& CopiedBattery)   //The copy constructor
{
	this->m_pGfxInfo = new GraphicsInfo(2);
	this->setValue(CopiedBattery.getVal());
	this->set_label(CopiedBattery.get_Label());
}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo, selected); //update to draw battery
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	name = get_Label();
	pUI->Label_name(name , x, y);
}

void Battery::Operate()
{
}

/*
void Battery::setEmf(string newEmf)
{
	emf = newEmf;
}
*/ 

void Battery::Save(ofstream& file, int id)
{
	file << "Ana Battery. \t";
	Component::Save(file, id);
}

string Battery::getType() const
{
	return type;
}