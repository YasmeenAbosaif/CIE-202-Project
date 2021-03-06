#ifndef __UI_H_
#define __UI_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include <string>
using namespace std;

struct Point
{
	int x, y , x2 , y2;
};


//A structure to contain drawing parameters for each component/connection
//Each component stores its drawing points in this struct 
//For example, a resistor can store points of the rectangluar area it occupies
//The Connection can store the points of its line segments
//this structure can be extended if desired
struct GraphicsInfo
{
	int PointsCount;
	Point* PointsList;
	GraphicsInfo(int PtsCnt)
	{
		PointsCount = PtsCnt;
		PointsList = new Point[PointsCount];	//allocate required points
	}

};


class UI
{
	enum DsgnMenuItem //The items of the design menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_RES,		//Resistor item in menu
		ITM_SWITCH,      //Switch item in menu
		ITM_LAMP,        //Lamp item in menu
		ITM_GROUND,      //Ground item in menu
		ITM_BATTERY,    //Battery item in menu
		ITM_WIRE,       //Wire item in menu
		ITM_BUZZER,
		ITM_FUSE,
		ITM_SIM_Switch,
		ITM_Options,
		ITM_EXIT,		//Exit item
		//TODO: Add more items names here

		ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

	};

	enum Options
	{
		ITM_Label,    // Label item
		ITM_Edit,   // Edit item
		ITM_Copy,
		ITM_Paste,
		ITM_Cut,
		ITM_Delete,
		ITM_Move,
		ITM_SAVE,
		ITM_Close,
		OptionsCount   //no. of options menu items ==> This should be the last line in this enum
	};

	enum SimMenuItem //The items of the simulation menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in menu
		ITM_CIRC_SIM,	//Circuit Simulate menu item
		AMMETER,
		VOLTMETER,
		ITM_DESIGN_MODE,
		//TODO:Add more items names here
		ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	};

	MODE AppMode;		//Application Mode (design or simulation)

	static const int	width = 1200, height = 650,	//Window width and height
		wx = 15, wy = 15,			//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		ToolBarHeight = 80,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ToolItemWidth = 80,		//Width of each item in toolbar menu
		ToolItemheight= 50,
		//Arbitrary values, you can change as you wish
		COMP_WIDTH = 100,		//Component Image width
		COMP_HEIGHT = 30;		//Component Image height

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color



	window* pWind;

public:

	UI();
	int getCompWidth() const;	//returns Component width
	int getCompHeight() const;	//returns Component height


	// Input Functions  ---------------------------
	void GetPointClicked(int&, int&);	//Get coordinate where user clicks
	string GetSrting();		//Returns a string entered by the user

	ActionType GetUserAction() const; //Reads the user click and maps it to an action


	// Output Functions  ---------------------------
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area


	// Draws a resistor
	void DrawResistor(const GraphicsInfo& r_GfxInfo, bool selected = false) const;

	///TODO: Make similar functions for drawing all other components, connections, .. etc
	
	// Draws a battery
	void DrawBattery(const GraphicsInfo& b_GfxInfo, bool selected = false) const;
	void DrawBulb(const GraphicsInfo& bu_GfxInfo, bool selected = false,bool on=false) const;
	void DrawGround(const GraphicsInfo& g_GfxInfo, bool selected = false) const;
	void DrawSwitch(const GraphicsInfo& s_GfxInfo, bool selected = false, bool open= true) const;
	void DrawBuzzer(const GraphicsInfo& bz_GfxInfo, bool selected = false) const;
	void DrawFuse(const GraphicsInfo& f_GfxInfo, bool selected = false) const;

	// Draws Connection
	void DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected = false) const;

	void PrintMsg(string msg) const;	//Print a message on Status bar

// SIM MODE
	void SIM_MODE_Button();

	// Add label & edit 
	void Label_name(string name, int x, int y);
	
	// Clear_Tool_Bar
	void Clear_Tool_Bar()const;

	//================================================Return to design mode ===================================
	void DesignModeSwitch();

	//======================================Drop Menu for options==================================
	void create_options_menu();

	//===================================== Draging function ========================================
	void  MouseState_Move(int CX, int CY);

	~UI();
};
#endif