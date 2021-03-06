#include "Buzzer.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Buzzer::Buzzer(GraphicsInfo* b_GfxInfo) :Component(b_GfxInfo)
{}

Buzzer::Buzzer(const Buzzer& CopiedBuzzer)   //The copy constructor
{
	this->m_pGfxInfo = new GraphicsInfo(2);
	this->setValue(CopiedBuzzer.getVal());
	this->set_label(CopiedBuzzer.get_Label());
}

void Buzzer::Draw(UI* pUI)
{
	//Call output class and pass buzzer drawing info to it.
	pUI->DrawBuzzer(*m_pGfxInfo, selected); //update to draw buzzer
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Buzzer::Operate()
{

}
void Buzzer::Save(ofstream& file, int id)
{
	file << "Ana Buzzer. \t";
	Component::Save(file, id);
}

string Buzzer::getType() const
{
	return type;
}