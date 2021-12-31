#include "Component.h"

Component::Component(GraphicsInfo *r_GfxInfo)
{
	m_pGfxInfo = r_GfxInfo;	
}

Component::Component()
{
	m_pGfxInfo = nullptr;
	term1_volt = term2_volt = 0;
	term1_conn_count = term2_conn_count = 0;

}

void Component::Save(int id)
{
}
// ================================================= label & edit ============================================
void Component::set_label(string name)
{
	m_Label = name;
}
string Component::get_Label()
{
	return m_Label;
}

bool Component::ISComponent(int x, int y) const
{
	int x1, y1, x2, y2;
	x1 = m_pGfxInfo->PointsList[0].x;
	y1 = m_pGfxInfo->PointsList[0].y;
	x2 = m_pGfxInfo->PointsList[1].x;
	y2 = m_pGfxInfo->PointsList[1].y;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2))
		return true;
	else
		return false;
}

//=============================================================================================================
Component::~Component()
{
}
