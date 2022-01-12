#include"../ApplicationManager.h"
#include "ActionClose.h"

ActionClose::ActionClose(ApplicationManager* pApp) :Action(pApp)
{

}
ActionClose :: ~ActionClose(void)
{

}

void ActionClose::Execute()
{
	UI* pUI = pManager->GetUI();
	pUI->ClearDrawingArea();
	pManager->UpdateInterface();
}
void ActionClose::Redo()
{

}
void ActionClose::Undo()
{

}