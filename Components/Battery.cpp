#include "Battery.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Battery::Battery(GraphicsInfo* b_GfxInfo) :Component(b_GfxInfo)
{

}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo); //update to draw battery
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Battery::Operate()
{

}

void Battery::setValue(string val)
{
	value = val;
}

void Battery::Save(int id )
{
}
