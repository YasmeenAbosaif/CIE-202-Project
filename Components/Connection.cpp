#include "Connection.h"
#include "Component.h"

Connection::Connection(GraphicsInfo *r_GfxInfo, Component *cmp1, Component *cmp2)
{
	m_pGfxInfo = r_GfxInfo;
	Cmpnt1 = cmp1;
	Cmpnt2 = cmp2;

	////////////////////////////////////// Coordinates ////////////////////////////////////////////////

		//coordinates of cornerpoint 1
	endpoint_X1 = m_pGfxInfo->PointsList[0].x;
	endpoint_y1 = m_pGfxInfo->PointsList[0].y;
	//coordinates of cornerpoint 2
	endpoint_X2 = m_pGfxInfo->PointsList[1].x;
	endpoint_y2 = m_pGfxInfo->PointsList[1].y;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void Connection::setSelected(bool x)
{
	selected = x;
}


double Connection::evaluateLineEquation(int x)
{
	double m;   //slope

	if (endpoint_X1 <= endpoint_X2)
		m = (endpoint_y2 - endpoint_y1) / (endpoint_X2 - endpoint_X1);

	else
		m = (endpoint_y1 - endpoint_y2) / (endpoint_X1 - endpoint_X2);

	//intercept
	double c = endpoint_y1 - (m * endpoint_X1);

	//substitute in the line equation
	double y = m * x + c;

	return y;

}


bool Connection::isInRegion(int x, int y, UI* pUI)
{

	bool condition1 = bool(endpoint_X1 < endpoint_X2&& x >= endpoint_X1 && x <= endpoint_X2);
	bool condition2 = bool(endpoint_X2 < endpoint_X1&& x >= endpoint_X2 && x <= endpoint_X1);
	bool condition3 = bool(endpoint_X1 == endpoint_X2);

	bool constrain1 = bool((y - evaluateLineEquation(x)) >= -4 && (y - evaluateLineEquation(x)) <= 4); //above or below the conection with 2 units "degree of freedom in y-axis"
	bool constrain2 = bool((x - endpoint_X1) >= -4 && (x - endpoint_X1) <= 4); //on the right/left of connection with two units "degree of freedom in x-axis"


	if ((condition1 || condition2) && constrain1)
	{
		return true;
	}
	else if (condition3 && constrain1 && constrain2)
	{
		return true;
	}
	else
		return false;
}

void Connection::Draw(UI* pUI)
{
	pUI->DrawConnection(*m_pGfxInfo, selected);
}
void Connection:: Save(int id)
{

}
void Connection::Save(ofstream& file, int id)
{
	string label = "MY LABEL";         //TO BE MODIFIED WITH THE ACTUAL LABEL.
	file << "Ana Resistor. \t" << id + 1 << "\t" << label << "\t" << "No val." << "\t" << pGfxInfo->PointsList[0].x
		<< "\t" << pGfxInfo->PointsList[0].y << "\n";
}


