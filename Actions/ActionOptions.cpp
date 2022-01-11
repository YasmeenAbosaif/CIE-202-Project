#include"../ApplicationManager.h"
#include"ActionOptions.h"

ActionOptions::ActionOptions(ApplicationManager* pApp) : Action(pApp)
{
}
ActionOptions :: ~ActionOptions(void)
{
}
//Execute action (code depends on action type)
void ActionOptions::Execute()
{
	UI* pUI = pManager->GetUI();
	pUI->create_options_menu();   //Can't be deleted 
}
void ActionOptions::Undo()
{
}
void ActionOptions::Redo()
{
}

