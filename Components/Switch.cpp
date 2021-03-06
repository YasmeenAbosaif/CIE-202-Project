#include "Switch.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Switch::Switch(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

Switch::Switch(const Switch& CopiedSwitch)   //The copy constructor
{
	this->set_label(CopiedSwitch.get_Label());
}

void Switch::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawSwitch(*m_pGfxInfo, selected, open); //update to draw switch
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Switch::Operate()
{
}

void Switch:: Save(ofstream& file, int id)
{
	file << "Ana Switch. \t";
	Component::Save(file, id);
}
string Switch::getType() const
{
	return type;
}

bool Switch::getOpen() const
{
	return open;
}

void Switch::setOpen(bool isOpen)
{
	open = isOpen;
}

