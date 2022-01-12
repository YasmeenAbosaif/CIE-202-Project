#include "Component.h"

Component::Component(GraphicsInfo *r_GfxInfo)
{
	m_pGfxInfo = r_GfxInfo;	
	////////////////////////////////////// Coordinates ////////////////////////////////////////////////

		//coordinates of cornerpoint 1
	cornerpoint_X1 = m_pGfxInfo->PointsList[0].x;
	cornerpoint_y1 = m_pGfxInfo->PointsList[0].y;
	//coordinates of cornerpoint 2
	cornerpoint_X2 = m_pGfxInfo->PointsList[1].x;
	cornerpoint_y2 = m_pGfxInfo->PointsList[1].y;
	//coordinates of centerpoint
	centerpoint_x = (cornerpoint_X1 + cornerpoint_X2) / 2;
	centerpoint_y = (cornerpoint_y1 + cornerpoint_y2) / 2;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
}

Terminal Component::whichTerminal(int Cx)
{
	if (Cx <= centerpoint_x)
	{
		return LEFT;
	}
	else
		return RIGHT;
}

void Component::AddTerm1Connection(Connection* pConn)
{
	term1_connections[term1_conn_count++] = pConn;
}
void Component::AddTerm2Connection(Connection* pConn)
{
	term2_connections[term2_conn_count++] = pConn;
}

bool Component::isInRegion(int Cx, int Cy, UI* pUI)
{

	if (Cx >= cornerpoint_X1 && Cx <= cornerpoint_X2)
	{
		if (Cy >= cornerpoint_y1 && Cy <= cornerpoint_y2)
			return true;
		else
			return false;
	}
	else
		return false;
}
void Component::setSelected(bool x)
{
	selected = x;
}
bool Component::getSelected()
{
	return selected;
}

double Component::getcornerpoint_X1()
{
	return cornerpoint_X1;
}
double Component::getcornerpoint_X2()
{
	return cornerpoint_X2;
}
double Component::getcenterpoint_y()
{
	return centerpoint_y;
}

Component::Component()
{
	m_pGfxInfo = nullptr;
	term1_volt = term2_volt = 0;
	term1_conn_count = term2_conn_count = 0;

}

void Component::Save(ofstream& file, int id)
{
	file << "\t" << id + 1 << "\t" << m_Label << "\t" << getVal() << "\t" << m_pGfxInfo->PointsList[0].x
		<< "\t" << m_pGfxInfo->PointsList[0].y << "\n";

}

// ==============================Any related functions to label & edit =================================
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
//Just deleting the link between component itself & connection 
void Component::DeleteConnectionComponents(Connection* pCon) 
{
	for (int i = 0; i < term1_conn_count; i++) 
	{
		if (term1_connections[i] == pCon)     //for left 
			term1_connections[i] = nullptr;
	}
	for (int i = 0; i < term2_conn_count; i++)   
	{
		if (term2_connections[i] == pCon)    //for right
			term2_connections[i] = nullptr;
	}
}

int Component::getComponentCenterX(UI* pUI)const 
{
	return m_pGfxInfo->PointsList[0].x + pUI->getCompWidth() / 2;
}
int Component::getComponentCenterY(UI* pUI)const 
{
	return m_pGfxInfo->PointsList[0].y + pUI->getCompHeight() / 2;
}

void Component::addTerminal1Connection(Connection* c) 
{
	term1_connections[term1_conn_count++] = c;
}
void Component::addTerminal2Connection(Connection* c) 
{
	term2_connections[term2_conn_count++] = c;
}


void Component::setValue(string newvalue)
{
	value = newvalue;
}
//=============================================================================================================
// for getting the terminals of the component to be deleted

Connection** Component :: get_terminal(Terminal Term )  //We should declare new term
{
	switch (Term)
	{
	case RIGHT:
		return term1_connections;
		break;
	case LEFT:
		return term2_connections;
		break;
	default:
		return nullptr;
	}
	
}

//===================================== for copying the component ==========================================
//void Component::setCopyCopmonent(Component* selectedcopy)
//{
//	copycomponent = selectedcopy;
//}
//
//Component* Component::getCopyCopmonent()
//{
//	return copycomponent;
//}

//==========================================================================================================


bool Component::SeriesConnCheck()  //validation check
{
	if (term1_conn_count < 2 && term2_conn_count < 2)
		return true;
	else
		return false;
}


string Component::getVal() const
{
	return value;       //Note that its resistance for all except battery
}


Component::~Component()
{
}
