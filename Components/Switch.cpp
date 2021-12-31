#include "Switch.h"

Switch::Switch(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Switch::Draw(UI* pUI)
{
	//Call output class and pass resistor drawing info to it.
	pUI->DrawSwitch(*m_pGfxInfo); //update to draw resistor

}

void Switch::Operate()
{

}

void Switch:: Save(ofstream& file, int id)
{
	string label = "MY LABEL";			//TO BE MODIFIED WITH THE ACTUAL LABEL.
	file << "Ana Switch. \t" << id + 1 << "\t" << label << "\t" << "No Val" << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";
}