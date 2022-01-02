#include "Resistor.h"

Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Resistor::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor

}

void Resistor::Operate()
{

}

void Resistor::setValue(string val)
{
	value = val;
}

string Resistor::getValue()
{
	return value;
}

void Resistor::Save(ofstream& file, int id)
{
	string label = "MY LABEL";			//TO BE MODIFIED WITH THE ACTUAL LABEL.
	file << "Ana Resistor. \t" << id+1 << "\t" << label << "\t" << value << "\t" << m_pGfxInfo->PointsList[0].x
	<<"\t" << m_pGfxInfo->PointsList[0].y << "\n";
}