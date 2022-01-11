#pragma once
#include "../UI/UI.h"

class Component;	//forward class declaration

class Connection 
{

	// declared variable for name of connection
	string connectionLabel;
	//connection connects between two compoenets
	Component	*Cmpnt1, *Cmpnt2;
	GraphicsInfo * m_pGfxInfo;	//The parameters required to draw a connection
	bool selected = false;

	////////////////////////////////////// Coordinates ////////////////////////////////////////////////
	
	//coordinates of endpoint 1
	double endpoint_X1;
	double endpoint_y1;
	//coordinates of endpoint 2
	double endpoint_X2;
	double endpoint_y2;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	Connection(GraphicsInfo *r_GfxInfo, Component *cmp1=nullptr, Component *cmp2=nullptr);

	void setSelected(bool x);
	double evaluateLineEquation(int x);
	bool isInRegion(int x, int y, UI* pUI);

	virtual void Draw(UI* );	//for connection to Draw itself
	virtual void Save(ofstream& file, int id);
	 

//================================	setters and getters for connections================================
	void set_labelConn(string name);
	string get_LabelConn();
	Component* getComp(int n);
	GraphicsInfo* getconnection() const;
	int ChooseComponentToDelete(Component* comp);
	void Connection::setNewComponent(int n, Component* comp);
//========================================================================================================


//Destructor
	
	~Connection();
};
