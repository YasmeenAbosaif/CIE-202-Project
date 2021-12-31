#include "Ground.h"

Ground::Ground(GraphicsInfo* r_GfxInfo) :Component(r_GfxInfo)
{}

void Ground::Draw(UI* pUI)
{
	//Call output class and pass ground drawing info to it.
	pUI->DrawGround(*m_pGfxInfo); //update to draw ground

}

void Ground::Operate()
{

}
void Ground::Save(ofstream& file, int id)
{
	string label = "MY LABEL";			//TO BE MODIFIED WITH THE ACTUAL LABEL.
	file << "Ana Ground. \t" << id + 1 << "\t" << label << "\t" << "NO Val." << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";
}
