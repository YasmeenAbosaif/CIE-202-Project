#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\UI\UI.h"
#include "Connection.h"

//Base class for all components (resistor, capacitor,....etc) .
class Component
{
private:
	string value;
	string m_Label;
protected:
	//Each component has two ending terminals (term1, term2)
	double term1_volt, term2_volt;	//voltage at terminals 1&2
	bool selected = false;
	//Component* copycomponent;   //pointer for the copied component
	Connection* term1;
	Connection* term2;
	//Each terminal is connected to set of connections
	Connection *term1_connections[MAX_CONNS]; //list of pointers to connections  for component
	Connection *term2_connections[MAX_CONNS];

	int term1_conn_count;	//actual no. of connections to each terminal
	int term2_conn_count;


	GraphicsInfo *m_pGfxInfo;	//The parameters required to draw a component

	////////////////////////////////////// Coordinates ////////////////////////////////////////////////

	//coordinates of cornerpoint 1
	double cornerpoint_X1;
	double cornerpoint_y1;
	//coordinates of cornerpoint 2
	double cornerpoint_X2;
	double cornerpoint_y2;
	//coordinates of centerpoint
	double centerpoint_x;
	double centerpoint_y;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	Component(GraphicsInfo *r_GfxInfo);
	//void setTerm1Volt(double v);		//sets the voltage at terminal1
	//void setTerm2Volt(double v);		//sets the voltage at terminal2
	//double getTerm1Volt();				//returns the voltage at terminal1
	//double getTerm2Volt();				//returns the voltage at terminal2

	virtual void Operate() = 0;	//Calculates the output voltage according to the inputs
	virtual void Draw(UI* ) = 0;	//for each component to Draw itself
	
	virtual void Save(int id) = 0;    //**********TESTING***********//


	Terminal whichTerminal(int x); //determinw which terminale is selected


	void AddTerm1Connection(Connection* pConn);//{term1_connections[term1_conn_count] = pConn;}
	void AddTerm2Connection(Connection* pConn);

	bool isInRegion(int x, int y, UI* pUI);

	void setSelected(bool x);
	bool getSelected();

	double getcornerpoint_X1();
	double getcornerpoint_X2();
	double getcenterpoint_y();


	//virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	//virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

//===============================================================================================================	
	//For label & editing

	bool ISComponent(int x, int y) const;
	
	void set_label(string name);
	string get_Label();

	void DeleteConnectionComponents(Connection* pConn);
	
	int getComponentCenterX(UI* pUI)const;
	int getComponentCenterY(UI* pUI)const;

	void Component::addTerminal1Connection(Connection* c);
	void Component::addTerminal2Connection(Connection* c);

	virtual void setValue(string val);  // To let each component has its own value value

//======================for deletin terminals after deleting component ===============================================
	
	Connection** get_terminal(Terminal);

//=================== for copying the component ======================
	/*void setCopyCopmonent(Component* copiedcomp);
	Component* getCopyCopmonent();*/

	//virtual Component* copy(Component*copiedcomp) = 0;

	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
