#include "Battery.h"

Battery::Battery(GraphicsInfo* b_GfxInfo) :Component(b_GfxInfo)
{}

void Battery::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawBattery(*m_pGfxInfo); //update to draw battery

}

void Battery::Operate()
{

}

void Battery::setValue(string val)
{
	value = val;
}

void Battery::Save(ofstream& file, int id)
{
	string label = "MY LABEL";   //TO BE MODIFIED WITH THE ACTUAL LABEL.

	file << "Ana Battery. \t" << id + 1 << "\t" << label << "\t" << value << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";
}
