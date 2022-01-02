#include "Connection.h"
#include "Component.h"

Connection::Connection(GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
	pGfxInfo = r_GfxInfo;
	Cmpnt1 = cmp1;
	Cmpnt2 = cmp2;
}
void Connection::Draw(UI* pUI)
{
	pUI->DrawConnection(*pGfxInfo);
}
void Connection::Save(ofstream& file, int id)
{
	string label = "MY LABEL";         //TO BE MODIFIED WITH THE ACTUAL LABEL.
	file << "Ana Resistor. \t" << id + 1 << "\t" << label << "\t" << "No val." << "\t" << pGfxInfo->PointsList[0].x
		<< "\t" << pGfxInfo->PointsList[0].y << "\n";
}


