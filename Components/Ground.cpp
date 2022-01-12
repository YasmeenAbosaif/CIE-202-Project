#include "Ground.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Ground::Ground(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

Ground::Ground(const Ground* CopiedGround)
{
	this->name = CopiedGround->name;
}

void Ground::Draw(UI* pUI)
{
	//Call output class and pass ground drawing info to it.
	pUI->DrawGround(*m_pGfxInfo, selected); //update to draw ground
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}

void Ground::Operate()
{

}
void Ground:: Save(ofstream& file, int id)
{
	file << "Ana Ground. \t";
	Component::Save(file, id);
}
string Ground::getType() const
{
	return type;
}
