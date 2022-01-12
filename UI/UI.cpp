#include "UI.h"

UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

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
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
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
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}

//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction() const
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
			case ITM_RES:	 return ADD_RESISTOR;
			case ITM_BATTERY:return  ADD_BATTERY;
			case ITM_WIRE:   return ADD_CONNECTION;
			case ITM_SWITCH: return   ADD_SWITCH;
			case ITM_GROUND: return   ADD_GROUND;
			case ITM_LAMP:   return     ADD_LAMP;
			case ITM_BUZZER: return   ADD_BUZZER;
			case ITM_FUSE:   return     ADD_FUSE;
			case ITM_Options: return  OPTIONS;
			case ITM_SIM_Switch: return SIM_MODE;
			case ITM_EXIT:	return EXIT;
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
		//[2] If user clicks on the OptionsMenu
		else if (x >= 719 && x <= 799)
		{
			int ChoosenItemOrder = ( (y - ToolBarHeight) / ToolItemheight);
			switch (ChoosenItemOrder)
			{
			case ITM_Label:	return ADD_Label;
			case ITM_Edit: return EDIT_Label;
			case ITM_Copy: return COPY;
			case ITM_Paste: return PASTE;
			case ITM_Cut: return CUT;
			case ITM_Delete: return DEL;
			case ITM_SAVE: return SAVE;
			case ITM_Move: return MOVE;
			case ITM_Close: return ClOSE;
			default: return OPTIONS_TOOL;	//A click on empty place in Options toolbar
			}
		}
		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
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
			case ITM_CIRC_SIM:return SIMULATE;
			case ITM_DESIGN_MODE: return DSN_MODE;
			case AMMETER:return AMMETER_;
			case VOLTMETER:return VOLTMETER_;

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
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
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
	MenuItemImages[ITM_BUZZER] = "images\\Menu\\Menu_Buzzer.jpg";
	MenuItemImages[ITM_FUSE] = "images\\Menu\\Menu_Fuse.jpg";
	MenuItemImages[ITM_SIM_Switch] = "images\\Menu\\Menu_SIM_Switch.jpg";
	MenuItemImages[ITM_Options] = "images\\Menu\\Menu_Options.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}
// Creating Options Menu

void UI::create_options_menu()
{
	string MenuOptionsItems[OptionsCount];
	MenuOptionsItems[ITM_Label] = "images\\Menu\\Menu_Label.jpg";
	MenuOptionsItems[ITM_Edit] = "images\\Menu\\Menu_Edit.jpg";
	MenuOptionsItems[ITM_Copy] = "images\\Menu\\Menu_Copy.jpg";
	MenuOptionsItems[ITM_Paste] = "images\\Menu\\Menu_Paste.jpg";
	MenuOptionsItems[ITM_Cut] = "images\\Menu\\Menu_Cut.jpg";
	MenuOptionsItems[ITM_Delete] = "images\\Menu\\Menu_Delete.jpg";
	MenuOptionsItems[ITM_Move] = "images\\Menu\\Menu_Move.jpg";
	MenuOptionsItems[ITM_SAVE] = "images\\Menu\\Menu_Save.jpg";
	MenuOptionsItems[ITM_Close] = "images\\Menu\\Menu_Close.jpg";
	for (int i = 0; i < OptionsCount; i++)
	{
		pWind->DrawImage(MenuOptionsItems[i], 719, 80 + i * ToolItemheight, ToolItemWidth, ToolItemheight);
		pWind->SetPen(BLUE, 3);
		pWind->DrawLine(719, 80 + ToolItemheight * (i + 1), 719, 80 + ToolItemheight * (i + 1));
		pWind->DrawLine(719, 80 + ToolItemheight * (i + 1), 719 + 80, 80 + ToolItemheight * (i + 1));
		pWind->DrawLine(719, 80, 719, 80 + ToolItemheight * (i + 1));
		pWind->DrawLine(719 + 80, 80, 719 + 80, 80 + ToolItemheight * (i + 1));
	}
}

//==========================================================================================================

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


void UI::DrawBulb(const GraphicsInfo& b_GfxInfo, bool selected, bool on) const
{
	string BulbImage;
	if (selected)
	{
		if (on)                                                      ////Modify
			BulbImage = "Images\\Comp\\BulbOn_HI.jpg";
		else
			BulbImage = "Images\\Comp\\BulbOFF_HI.jpg";
	}
	else
	{
		if (on)
			BulbImage = "Images\\Comp\\BulbON.jpg";
		else
			BulbImage = "Images\\Comp\\BulbOFF.jpg";
	}
	pWind->DrawImage(BulbImage, b_GfxInfo.PointsList[0].x, b_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}

void UI::DrawSwitch(const GraphicsInfo& s_GfxInfo, bool selected, bool open) const
{
	string SwitchImage;
	if (selected)
	{
		if (open)
			SwitchImage = "Images\\Comp\\SwitchOpen_HI.jpg";
		else
			SwitchImage = "Images\\Comp\\SwitchClosed_HI.jpg";
	}
	else
	{
		if (open)
			SwitchImage = "Images\\Comp\\SwitchOpen.jpg";
		else
			SwitchImage = "Images\\Comp\\SwitchClosed.jpg";
	}
	pWind->DrawImage(SwitchImage, s_GfxInfo.PointsList[0].x, s_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


void UI::DrawGround(const GraphicsInfo& g_GfxInfo, bool selected) const
{
	string GroundImage;
	if (selected)
		GroundImage = "Images\\Comp\\Ground_HI.jpg";
	else
		GroundImage = "Images\\Comp\\Ground.jpg";
	pWind->DrawImage(GroundImage, g_GfxInfo.PointsList[0].x, g_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


void UI::DrawBuzzer(const GraphicsInfo& bz_GfxInfo, bool selected) const
{
	string BuzImage;
	if (selected)
		BuzImage = "Images\\Comp\\Buzzer_HI.jpg";
	else
		BuzImage = "Images\\Comp\\Buzzer.jpg";

	pWind->DrawImage(BuzImage, bz_GfxInfo.PointsList[0].x, bz_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
}


void UI::DrawFuse(const GraphicsInfo& f_GfxInfo, bool selected) const
{
	string FuseImage;
	if (selected)
		FuseImage = "Images\\Comp\\Fuse_HI.jpg";
	else
		FuseImage = "Images\\Comp\\Fuse.jpg";


	pWind->DrawImage(FuseImage, f_GfxInfo.PointsList[0].x, f_GfxInfo.PointsList[0].y, COMP_WIDTH, COMP_HEIGHT);
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

//===================================== For changing to simulation mode ==============================
//Draws the menu (toolbar) in the simulation mode

void UI::CreateSimulationToolBar()
{
	this->Clear_Tool_Bar();
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_CIRC_SIM] = "Images\\Menu\\Menu_Simulate.jpg";
	MenuItemImages[AMMETER] = "Images\\Menu\\Menu_Ammeter.jpg";
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
	if (selected)
		pWind->SetPen(RED, 5);	//use red pen to draw highlited connection
	else
		pWind->SetPen(BLACK, 5); //use black pen to draw normal connection

	//Draw connection with Gfx_Info (two endpoints)
	pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y, FRAME);
}


//==================== For labeling & Editing the components names & connections =========================

void UI::Label_name(string name, int x, int y)
{
	int MsgX = x;
	int MsgY = y;
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX , MsgY - 30, name);
}

//================================================Return to design mode ================================//
void UI::DesignModeSwitch()
{
	this->Clear_Tool_Bar();
	AppMode = DESIGN;
	CreateDesignToolBar();	//Create the desgin toolbar
}

//============================================Draging=====================================================
void UI::MouseState_Move(int	CX, int CY)
{
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	pWind->SetBuffering(true);

	int RectULX = CX;
	int RectULY = CY;
	bool bDragging = false;

	int iX = 0;  int iY = 0;

	int iXOld = 0;
	int iYOld = 0;

	char cKeyData;
	// Loop until there escape is pressed
	while (pWind->GetKeyPress(cKeyData) != ESCAPE)
	{
		//testWindow.DrawRectangle(0, 0, testWindow.GetWidth() - 1, testWindow.GetHeight() - 1);

		if (bDragging == false) {
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
				if (((iX > RectULX) && (iX < (RectULX + 80))) && ((iY > RectULY) && (iY < (RectULY + 80)))) {
					bDragging = true;
					iXOld = iX; iYOld = iY;
				}
			}
		}
		else {
			if (pWind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP) {
				bDragging = false;
			}
			else {
				if (iX != iXOld) {
					RectULX = RectULX + (iX - iXOld);
					iXOld = iX;
				}
				if (iY != iYOld) {
					RectULY = RectULY + (iY - iYOld);
					iYOld = iY;
				}
			}
		}
		pWind->UpdateBuffer();
	}
	pWind->SetBuffering(false);
}

UI::~UI()
{
	if(this)
	delete this;
	if(pWind)
	delete pWind;
}