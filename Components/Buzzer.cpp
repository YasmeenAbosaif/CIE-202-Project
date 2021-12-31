#include "Buzzer.h"

Buzzer::Buzzer(GraphicsInfo* b_GfxInfo) :Component(b_GfxInfo)
{}

void Buzzer::Draw(UI* pUI)
{
	//Call output class and pass buzzer drawing info to it.
	pUI->DrawBuzzer(*m_pGfxInfo); //update to draw buzzer

}

void Buzzer::Operate()
{

}


void Buzzer::setValue(string val)
{
	value = val;
}

void Buzzer::Save(ofstream& file, int id)
{
	string label = "MY LABEL";    //TO BE MODIFIED WITH THE ACTUAL LABEL.

	file << "Ana Buzzer. \t" << id + 1 << "\t" << label << "\t" << value << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";
}