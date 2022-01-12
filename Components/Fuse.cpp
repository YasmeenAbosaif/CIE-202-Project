#include "Fuse.h"
#include "../ApplicationManager.h"
#include"../Actions/Action.h"

Fuse::Fuse(GraphicsInfo* f_GfxInfo) :Component(f_GfxInfo)
{}

Fuse::Fuse(const Fuse& CopiedFuse)   //The copy constructor
{
	this->m_pGfxInfo = new GraphicsInfo(2);
	this->set_label(CopiedFuse.get_Label());
}

void Fuse::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawFuse(*m_pGfxInfo, selected); //update to draw battery
	int x = m_pGfxInfo->PointsList[0].x;
	int y = m_pGfxInfo->PointsList[0].y;
	pUI->Label_name(get_Label(), x, y);
}


void Fuse::Operate()
{

}
void Fuse:: Save(ofstream& file, int id)
{
	file << "Ana Fuse. \t";
	Component::Save(file, id);
}

string Fuse::getType() const
{
	return type;
}