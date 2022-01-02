#include "Bulb.h"

Bulb::Bulb(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Bulb::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawBulb(*m_pGfxInfo); //update to draw resistor

}

void Bulb::Operate()
{

}

void Bulb:: setValue(string val)
{
	value = val;
}

string Bulb::getValue()
{
	return value;
}

void Bulb::Save(ofstream& file, int id)
{
	string label = "MY LABEL";   //TO BE MODIFIED WITH THE ACTUAL LABEL.

	file << "Ana Buzzer. \t" << id + 1 << "\t" << label << "\t" << value << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";
}
