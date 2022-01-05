#include "Bulb.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Bulb::Bulb(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Bulb::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawBulb(*m_pGfxInfo); //update to draw resistor
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Bulb::Operate()
{

}

void Bulb::setValue(string val)
{
	value = val;
}

void Bulb:: Save(int id) 
{
}
