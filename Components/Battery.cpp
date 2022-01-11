#include "Battery.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Battery::Battery(GraphicsInfo* b_GfxInfo) :Component(b_GfxInfo)
{
}

Battery::Battery( const Battery* CopiedBattery)   //The copy constructor
{
	this->value = CopiedBattery->value;
	this->name = CopiedBattery->name;
}

//Component* Battery :: copy (Component* copiedcomp)
//{
//	for (int i = 0; i < CompCount; i++)
//			{
//				if (CompList[i] == copiedcomp)
//				{
//					Battery* newcomp = new Battery (GraphicsInfo*b_GfxInfo);
//					newcomp(CompList[i]);
//				}
//			}
//}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo); //update to draw battery
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	name = get_Label();
	pUI->Label_name(name , x, y);
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