#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\UI\UI.h"
#include "Connection.h"


//Base class for all components (resistor, capacitor,....etc) .
class Component
{
private:
	string m_Label;
protected:
	//Each component has two ending terminals (term1, term2)
	double term1_volt, term2_volt;	//voltage at terminals 1&2
	bool selected = false;

	//Each terminal is connected to set of connections
	Connection *term1_connections[MAX_CONNS]; //list of pointers to connections
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

<<<<<<< HEAD
	Terminal whichTerminal(int x); //determinw which terminale is selected


	void AddTerm1Connection(Connection* pConn);//{term1_connections[term1_conn_count] = pConn;}
	void AddTerm2Connection(Connection* pConn);

	bool isInRegion(int x, int y, UI* pUI);

	void setSelected(bool x);
	bool getSelected();

	double getcornerpoint_X1();
	double getcornerpoint_X2();
	double getcenterpoint_y();
=======
>>>>>>> refs/remotes/origin/main

	//virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	//virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
