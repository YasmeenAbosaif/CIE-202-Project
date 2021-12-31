#include "Resistor.h"
#include "Component.h"
Resistor::Resistor(GraphicsInfo *r_GfxInfo):Component(r_GfxInfo)
{}

void Resistor::Draw(UI* pUI)
{
	int x_coordinate_label = m_pGfxInfo->PointsList[0].x;
	int y_coordinate_label = m_pGfxInfo->PointsList[0].y;
	//Call output class and pass resistor drawing info to it.
	pUI->DrawResistor(*m_pGfxInfo); //update to draw resistor
	pUI->Label_name (get_Label(), x_coordinate_label, y_coordinate_label);
}

void Resistor::Operate()
{

}