#include "UI.h"
UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode  // That is why the constructor takes this value 

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = RED;
	MsgColor = BLUE;
	BkGrndColor = WHITE;

	//Create the drawing window
	pWind = new window(width, height, wx, wy);

	ChangeTitle("Logic Simulator Project");
	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}

int UI::getCompWidth() const
{
	return COMP_WIDTH;
}

int UI::getCompHeight() const
{
	return COMP_HEIGHT;
}

//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click   It is a function defined in the CMU 
}

string UI::GetSrting()
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);    // WaitKeyPress a function defined in the CMU class

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)     // Size is a function in string
				userInput.resize(userInput.size() - 1);
			break;      // Break is written only in this case because we need all cases to be done

		default:
			userInput += Key;
		};

		PrintMsg(userInput);   // It is a defined function in UI class
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() const   // The type for this function is action type
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RES:	return ADD_RESISTOR;
			case ITM_BATTERY:return ADD_BATTERY;
			case ITM_SWITCH: return  ADD_SWITCH;
			case ITM_GROUND: return ADD_GROUND;
			case ITM_LAMP:   return   ADD_LAMP;
			case ITM_SIM_Switch: return SIM_MODE;
			case ITM_EXIT:	return EXIT;
			case ITM_Label:	return ADD_Label;
			case ITM_Edit: return EDIT_Label;
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)  // Area for drawing 
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_CIRC_SIM:return SIMULATE ;
			case ITM_DESIGN_MODE: return DSN_MODE;
			case AMMETER:return AMMETER_;
			case VOLTMETER :return VOLTMETER_;

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

	}
}


//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);   // Function defined in CMU class
}
////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, height - StatusBarHeight, width, height - StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, height - MsgY, msg);

}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar()
{
	AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_RES] = "images\\Menu\\Menu_Resistor.jpg";
	MenuItemImages[ITM_WIRE] = "images\\Menu\\Menu_Wire.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_Switch.jpg";
	MenuItemImages[ITM_LAMP] = "images\\Menu\\Menu_Lamp.jpg";
	MenuItemImages[ITM_GROUND] = "images\\Menu\\Menu_Ground.jpg";
	MenuItemImages[ITM_BATTERY] = "images\\Menu\\Menu_Battery.jpg";
	MenuItemImages[ITM_SIM_Switch] = "images\\Menu\\Menu_SIM_Switch.jpg";
	MenuItemImages[ITM_Label]= "images\\Menu\\Menu_Label.jpg";
	MenuItemImages[ITM_Edit] = "images\\Menu\\Menu_Edit.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";


	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////


//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void UI::DrawResistor(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	string ResImage;
	if (selected)
		ResImage = "Images\\Comp\\Resistor_HI.jpg";	//use image of highlighted resistor
	else
		ResImage = "Images\\Comp\\Resistor.jpg";	//use image of the normal resistor

	//Draw Resistor at Gfx_Info (1st corner)
	pWind->DrawImage(ResImage, r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}

//TODO: Add similar functions to draw all other components

void UI::DrawBattery(const GraphicsInfo& b_GfxInfo, bool selected) const
{
	string BatteryImage;
	if (selected)
		BatteryImage = "Images\\Comp\\Battery_HI.jpg";
	else
		BatteryImage = "Images\\Comp\\Battery.jpg";
	pWind->DrawImage(BatteryImage, b_GfxInfo.PointsList[0].x, b_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


void UI::DrawBulb(const GraphicsInfo& b_GfxInfo, bool selected) const
{
	string BulbImage;
	if (selected)
		BulbImage = "Images\\Comp\\Bulb_HI.jpg";
	else
		BulbImage = "Images\\Comp\\Bulb.jpg"; //ERROR INTENDED TO TEST
	pWind->DrawImage(BulbImage, b_GfxInfo.PointsList[0].x, b_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}

void UI::DrawSwitch(const GraphicsInfo& s_GfxInfo, bool selected) const
{
	string SwitchImage;
	if (selected)
		SwitchImage = "Images\\Comp\\Switch_HI.jpg";
	else
		SwitchImage = "Images\\Comp\\Switch.jpg";
	pWind->DrawImage(SwitchImage, s_GfxInfo.PointsList[0].x, s_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


void UI::DrawGround(const GraphicsInfo& g_GfxInfo, bool selected) const
{
	string GroundImage;
	if (selected)
		GroundImage = "Images\\Comp\\Ground_HI.jpg";
	else
		GroundImage = "Images\\Comp\\Ground.jpg";
	pWind->DrawImage(GroundImage, g_GfxInfo.PointsList[0].x, g_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);  // Draw image is a function defined in CMU
	
	
}


//===================================== For changing to simulation mode ==============================
//Draws the menu (toolbar) in the simulation mode

void UI::CreateSimulationToolBar()
{
	Clear_Tool_Bar();
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_CIRC_SIM] = "Images\\Menu\\Menu_Simulate.jpg";
	MenuItemImages[AMMETER]= "Images\\Menu\\Menu_Ammeter.jpg";
	MenuItemImages[VOLTMETER] = "Images\\Menu\\Menu_Voltmeter.jpg";
	MenuItemImages[ITM_DESIGN_MODE] = "Images\\Menu\\Menu_DesignMode.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);

} 
//////////////////////////////////////   SIMULATION KEY //////////////////////////////////////////////////
void UI::SIM_MODE_Button() 
{
		AppMode = SIMULATION;	//Simulation Mode 
		CreateSimulationToolBar();	//Create the desgin toolbar
}

// ===================================== End of simulation mode ========================================//

// Drawing connections ================================================================================= //

void UI::DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
}

void UI::Clear_Tool_Bar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, 0, width, ToolBarHeight);
}

//================================== For labeling & Editing the components names====================================

void UI::Label_name(string name, int x, int y)
{
	int MsgX = x ;
	int MsgY = y ;	
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX+50,  MsgY-20, name);
}

void UI::DeleteOldLabel( int x , int y)
{
	int MsgX = x;
	int MsgY = y;
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(MsgX - 50 , MsgY - 50 , MsgX + 100 , MsgY + 50 );
}

//================================================Return to design mode ================================//
void UI:: DesignModeSwitch()
{
	Clear_Tool_Bar(); 
	AppMode = DESIGN;	 
	CreateDesignToolBar();	//Create the desgin toolbar
}

UI::~UI()
{
	delete pWind;
}