#include "Fuse.h"

Fuse::Fuse(GraphicsInfo* f_GfxInfo) :Component(f_GfxInfo)
{}

void Fuse::Draw(UI* pUI)
{
	//Call output class and pass battery drawing info to it.
	pUI->DrawFuse(*m_pGfxInfo); //update to draw battery

}

void Fuse::Operate()
{

}
void Fuse::Save(ofstream& file, int id)
{
	string label = "MY LABEL";			//TO BE MODIFIED WITH THE ACTUAL LABEL.
	file << "Ana Fuse. \t" << id + 1 << "\t" << label << "\t" << "No val." << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";
}
